#ifndef SERVER_EXCEPTIONS_HPP
#define SERVER_EXCEPTIONS_HPP

#include <string>

class InsufficientMoneyException
{

};

class PartDoesNotFitException
{
	public:
		PartDoesNotFitException(const std::string& reason):
			reason(reason)
		{
		
		}
		
		std::string reason;		
};

class NoSuchPartException
{

};

class NoSuchVehicleException
{

};

#endif
