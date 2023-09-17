#include "UTL_Settings.h"


namespace utl {

	class Application {
	public:
		static Application& getInstance() noexcept { static Application app; return app; };
		~Application() {};

		std::string version()		const { return m_VERSION; }
		std::string compiledDate()	const { return m_COMPILED_DATE; }

		std::chrono::hours	getHourOffest()				const { return m_hourOffset; }
		void				setHourOffest(int offset) { m_hourOffset = std::chrono::hours(offset); }

	private:
		Application() {};
		const Application& operator=(const Application& rst) = delete;

		const std::string m_VERSION{ "v1.0.2" };
		const std::string m_COMPILED_DATE{ __DATE__ + std::string{" at "} + __TIME__ };

		std::chrono::hours m_hourOffset{ -7 };
	};

	Application& app = Application::getInstance();

	std::string version() {
		return app.version();
	}

	std::string compiledDate() {
		return app.compiledDate();
	}

	void setHourOffset(int offset) {
		app.setHourOffest(offset);
	}
	std::chrono::hours	getHourOffset() {
		return app.getHourOffest();
	}

}
