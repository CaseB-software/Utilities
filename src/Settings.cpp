#include "UTL_Settings.h"

#define _VERSION "0.1.0-dev"

class Application {
public:
	static Application& getInstance() noexcept { static Application app; return app; };
	~Application() {};

	std::chrono::hours	getHourOffest()				const	{ return m_hourOffset; }
	void				setHourOffest(int offset)			{ m_hourOffset = std::chrono::hours(offset);	}

private:
	Application() {};
	const Application& operator=(const Application& rst) = delete;

	std::chrono::hours m_hourOffset{ -7 };
};

namespace utl {

	Application& app = Application::getInstance();

	std::string version() {

#ifdef  _VERSION
		return _VERSION;
#endif //  _VERSION

#ifndef _VERSION
		return "Version Not Specified";
#endif

	}

	std::string compiledDate() {
		std::ostringstream retBuf;
		retBuf << "Compiled on " << __DATE__ << " at " << __TIME__;
		return retBuf.str();
	}

	void setHourOffset(int offset) {
		app.setHourOffest(offset);
	}
	std::chrono::hours	getHourOffset() {
		return app.getHourOffest();
	}

}
