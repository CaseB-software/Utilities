#include <iostream>


#include "UTL_Settings.h"

#define _TEST "SUP"

int main(int argc, char* argv[]) {

	std::cout << utl::getVersion()  << std::endl;
	std::cout << utl::getWhenCompiled() << std::endl;

	std::cout << "hi\n";
	/*
	utl::time::Timestamp now;
	now.stamp();

	std::cout << "Time: " << now << std::endl;

	utl::json::json j;
	j = now;

	std::cout << std::setw(1) << std::setfill('\t') << j.dump() << std::endl;
	
	utl::time::Timestamp now2{ j };
	std::cout << "New timestamp: " << now2 << std::endl;

	std::cout << "\n\n" << std::endl;


	utl::time::Timer timer{};
	timer.start();

	std::cout << "Waiting for input to end timer..." << std::endl;
	std::string input;
	std::cin >> input;
	timer.end();

	utl::json::json timerJson;
	timerJson = timer;
	std::cout << std::setw(1) << std::setfill('\t') << timerJson.dump() << std::endl;

	try {
		utl::time::Timer timer2;
		timer2 = timerJson;
		std::cout << "New Timer: " << timer2.printDuration() << std::endl;
	}
	catch (std::exception& e) {
		std::cout << "\n\nERROR\n" << e.what() << std::endl;
	}

	std::cout << "\n\nLabeled Timer" << std::endl;
	utl::time::LabeledTimer lblTimer{ "LABELED TIMER" };
	lblTimer.start();
	lblTimer.end();

	utl::json::json lblTimerJson;
	lblTimerJson = lblTimer;

	std::cout << lblTimerJson.dump() << std::endl;

	*/
	return 0;

}