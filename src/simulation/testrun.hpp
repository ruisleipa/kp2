#ifndef SERVER_TESTRUN_HPP
#define SERVER_TESTRUN_HPP

#include "utils/timer.hpp"
#include "driver.hpp"

#include <tr1/memory>

using std::tr1::shared_ptr;
using std::tr1::weak_ptr;

class TestRun
{
	public:
		void sendState();
		
		void update();
		
		bool canDelete();
		
		TestRun(weak_ptr<Driver> driver);
		
	private:
		void sendStart();
		void sendVehicleData();
		
		weak_ptr<Driver> driver;
		
		Timer realTime;
};

#endif

