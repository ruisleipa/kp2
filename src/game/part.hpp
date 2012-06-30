#ifndef SERVER_PART_HPP
#define SERVER_PART_HPP

#include <string>
#include <memory>

#include "partcontainer.hpp"

namespace Game
{

class Part : public PartContainer
{
	public:
		virtual int getPrice() const;
		float getMass() const;

		virtual bool canAttachPart(const Part* part) const;
		virtual int getAttachmentLimitOfType(const Part* part) const;

		Part(int price = 0, float mass = 0.0);
		Part(const Json::Value& value);
		virtual void save(Json::Value& value) const;

	private:
		int price;
		float mass;
};

};

#endif
