#include "UTL_Settings.h"

#define _VERSION "0.1.0-dev"


namespace utl {

	std::string getVersion() {

#ifdef  _VERSION
		return _VERSION;
#endif //  _VERSION

#ifndef _VERSION
		return "Version Not Specified";
#endif

	}

	std::string getWhenCompiled() {
		std::ostringstream retBuf;
		retBuf << "Compiled on " << __DATE__ << " at " << __TIME__;
		return retBuf.str();
	}
}
