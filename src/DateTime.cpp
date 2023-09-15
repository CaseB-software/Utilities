#include "UTL_DateTime.h"


namespace utl::time {


	// Timestamp
	Timestamp::Timestamp() {

	}
	Timestamp::Timestamp(std::chrono::system_clock::time_point time) {

	}
	Timestamp::~Timestamp() {

	}

	bool Timestamp::stamp(const std::chrono::system_clock::time_point& time) {
		using namespace std::literals;

		if (!m_isStamped) {
			m_time = time - 7h; // 7 hour time offset for real time
			m_isStamped = true;
			return true;
		}
		else
			return false;
	}
	std::string Timestamp::printDay() const {
		return std::format("{:%d}", m_time);
	}
	std::string Timestamp::printMonth() const {
		return std::format("{:%B}", m_time);
	}
	std::string Timestamp::printDate() const {
		return std::format("{:%Od %b %Y}", m_time);
	}
	std::string Timestamp::printHMS() const {
		return std::format("{:%H:%M:%OS}", m_time);
	}
	std::string Timestamp::print() const {
		std::ostringstream os;
		os << m_time;
		return os.str();
	}
	std::string Timestamp::printNumericDateAndTimeNoSpaces() const {
		return std::format("{:%Od-%m-%Y_%H-%M-%OS}", m_time);
	}
	bool Timestamp::isStamped()	const{
		return m_isStamped; 
	}
	std::chrono::system_clock::time_point	Timestamp::getRawTime() const {
		return m_time; 
	}
	std::chrono::year_month_day	Timestamp::getRawYMD() const {
		std::chrono::year_month_day ymd{ std::chrono::floor<std::chrono::days>(m_time) };
		return ymd;
	}
	std::ostream& operator<<(std::ostream& os, const Timestamp& time) {
		os << time.m_time;
		return os;
	}

	// End Timestamp





	// Timer
	Timer::Timer() {

	}
	Timer::Timer(const std::chrono::system_clock::time_point& start) {
		this->start(start);
	}
	Timer::~Timer() {

	}

	bool Timer::start(const std::chrono::system_clock::time_point& time) {
		if (!m_finished && !m_running) {
			m_start.stamp(time);
			m_running = true;
			return true;
		}
		else {
			return false;
		}
		return false;
	}
	bool Timer::end(const std::chrono::system_clock::time_point& end) {
		if (m_running && !m_finished) {
			m_end.stamp(end);
			m_rawDuration = m_end.getRawTime() - m_start.getRawTime();
			m_finished = true;
			m_running = false;
			return true;
		}
		else
			return false;

		return false;
	}
	bool Timer::isRunning() const {
		return m_running;
	}
	bool Timer::isFinished() const {
		return m_finished;
	}
	const Timestamp& Timer::getStartTimestamp()	const { return m_start; }
	const Timestamp& Timer::getEndTimestamp()	const { return m_end;   }
	std::chrono::system_clock::duration		Timer::getRawDuration()		const { return m_rawDuration; }
	std::chrono::system_clock::time_point	Timer::getRawStartTime()	const { return m_start.getRawTime(); }
	std::chrono::system_clock::time_point	Timer::getRawEndTime()		const { return m_end.getRawTime(); }
	std::string Timer::printDate() const {
		return m_start.printDate(); 
	}
	std::string Timer::printDuration() const {
		return std::format("{:%H:%M:%OS}", m_rawDuration);
	}
	std::string Timer::printStartTime() const {
		using namespace std::literals;

		return std::format("{:%OH:%OM:%OS}", this->getRawStartTime());
	}
	std::string Timer::printEndTime() const {
		using namespace std::literals;

		return std::format("{:%OH:%OM:%OS}", this->getRawEndTime());
	}
	// End Timer



	// Labaled Timer

	LabeledTimer::LabeledTimer(const std::string& name = "New Timer"){
	
	}
	LabeledTimer::~LabeledTimer() {

	}
	std::string LabeledTimer::getName() const			{ return m_name; }
	void		LabeledTimer::setName(std::string name) { m_name = name; }

	// End Labeled Timer




	std::chrono::system_clock::time_point stringToTimepoint(const std::string& time) {
		std::stringstream ss{ time };
		std::tm _tm{};
		ss >> std::get_time(&_tm, "%Y-%m-%d %H:%M:%OS");
		return std::chrono::system_clock::from_time_t(std::mktime(&_tm));
	}



	void to_json(utl::json::json& j, const Timestamp& t) {
		j = utl::json::json{
			{"timestamp",	t.print()},
		};
	}
	void from_json(const utl::json::json& j, Timestamp& t) {
		std::string timeBuf;
		j.at("timestamp").get_to(timeBuf);
		t.stamp(stringToTimepoint(timeBuf));
	}

	void to_json(utl::json::json& j, const Timer& t) {
		j = utl::json::json{
			{"start",	t.getStartTimestamp().print()},
			{"end",		t.getEndTimestamp().print()}
		};
	}
	void from_json(const utl::json::json& j, Timer& t) {
		std::string startBuf, endBuf;

		j.at("start").get_to(startBuf);
		j.at("end").get_to(endBuf);

		t.start(stringToTimepoint(startBuf));
		t.end(stringToTimepoint(endBuf));
	}
	void to_json(utl::json::json& j, const LabeledTimer& t) {
		j = utl::json::json{

			{"name",	t.getName()},
			{"start",	t.getStartTimestamp().print()},
			{"end",		t.getEndTimestamp().print()}
		};

	}
	void from_json(const utl::json::json& j, LabeledTimer& t) {
		std::string name, startBuf, endBuf;

		j.at("name").get_to(name);
		j.at("start").get_to(startBuf);
		j.at("end").get_to(endBuf);

		t.setName(name);
		t.start(stringToTimepoint(startBuf));
		t.end(stringToTimepoint(endBuf));
	}
}