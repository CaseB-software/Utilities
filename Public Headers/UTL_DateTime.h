#pragma once
#include <chrono>
#include <format>

#include "UTL_Settings.h"
#include "UTL_json.h"

namespace utl {

	namespace time {

		class Timestamp {
		public:
			Timestamp() {};
			Timestamp(std::chrono::system_clock::time_point time) : m_time{ time } { m_isStamped = true; }
			virtual ~Timestamp() {};

			virtual bool stamp(const std::chrono::system_clock::time_point& time = std::chrono::system_clock::now());						// Stamps the time as now if m_isStamped is false
			virtual std::string printDay()		const;						// Prints DD (09)
			virtual std::string printMonth()	const;						// Prints MM (01 for January)

			virtual std::string printDate()		const;						// Prints in DD MMM YYYY format (12 Dec 2022)
			virtual std::string printHMS()		const;						// Prints the HH:MM::SS			(14:23:01)
			virtual std::string print()			const;						// Is the same as outputting getRawTimme to ostream
			virtual std::string printNumericDateAndTimeNoSpaces() const;	// Prints format DD-MM-YYYY_HH-MM-SS
	
			bool isStamped()				const { return m_isStamped; }

			std::chrono::system_clock::time_point	getRawTime()	const { return m_time; };
			std::chrono::year_month_day				getRawYMD()		const;

			friend std::ostream& operator<<(std::ostream& os, const Timestamp& time);

		private:
			std::chrono::system_clock::time_point m_time{};
			bool m_isStamped{ false };
		};

	
		class Timer
		{
		public:
			Timer() {};
			Timer(const std::chrono::system_clock::time_point& start);
			virtual ~Timer() {};

			virtual bool start(const std::chrono::system_clock::time_point& time = std::chrono::system_clock::now());
			virtual bool end(const std::chrono::system_clock::time_point& time = std::chrono::system_clock::now());

			bool isRunning()	const;
			bool isFinished()	const;

			const Timestamp& getStartTimestamp() const { return m_start; }
			const Timestamp& getEndTimestamp()	const { return m_end; }

			std::chrono::system_clock::duration		getRawDuration()	const { return m_rawDuration; }
			std::chrono::system_clock::time_point	getRawStartTime()	const { return m_start.getRawTime(); }
			std::chrono::system_clock::time_point	getRawEndTime()		const { return m_end.getRawTime(); }

			std::string printDate()			const { return m_start.printDate(); }
			std::string printDuration()		const;
			std::string printStartTime()	const;
			std::string printEndTime()		const;

		private:
			Timestamp	m_start{}, m_end{};
			std::chrono::system_clock::duration		m_rawDuration{};

			bool m_running{ false };
			bool m_finished{ false };
		};


		class LabeledTimer : public Timer {
		public:
			LabeledTimer(const std::string& name = "New Timer") : m_name{ name } { }
			~LabeledTimer() {};

			std::string getName() const { return m_name; }

			void setName(std::string name) { m_name = name; }

		private:
			std::string m_name{};
		};

		std::chrono::system_clock::time_point stringToTimepoint(const std::string& time);




		void to_json	(utl::json::json& j, const Timestamp& t);
		void from_json	(const utl::json::json& j, Timestamp& t);

		void to_json	(utl::json::json& j, const Timer& t);
		void from_json	(const utl::json::json& j, Timer& t);

		void to_json	(utl::json::json& j, const LabeledTimer& t);
		void from_json	(const utl::json::json& j, LabeledTimer& t);
	}
}