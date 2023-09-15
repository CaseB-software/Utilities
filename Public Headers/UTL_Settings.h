#pragma once
#include <sstream>
#include <chrono>

namespace utl {

	std::string version();
	std::string compiledDate();
	
	void setHourOffset(int offset);
	std::chrono::hours	getHourOffset();

}