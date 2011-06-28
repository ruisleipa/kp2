#ifndef SERVER_TESTRUN_HPP
#define SERVER_TESTRUN_HPP

#include "utils/timer.hpp"
#include "driver.hpp"

#include <tr1/memory>

class TestRun
{
	public:
		void sendState();
		
		void update();
		
		//This class claims ownership on the driver objects.
		TestRun(std::tr1::shared_ptr<Driver> driver);
		
	private:
		void sendStart();
		void sendVehicleData();
		
		std::tr1::shared_ptr<Driver> driver;
		
		Timer realTime;
};

#endif

