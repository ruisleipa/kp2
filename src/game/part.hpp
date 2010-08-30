#ifndef PART_HPP
#define PART_HPP

#include <string>
#include <stdint.h>

#include "net/packet.hpp"

/*
These are the part type IDs for serialization. These should make sure that a 
serialized part object isn't mistaken for another type.
*/

const uint16_t PART_TYPE_ID_ACCESSORY=0;
const uint16_t PART_TYPE_ID_CAMSHAFT=1;
const uint16_t PART_TYPE_ID_CHARGER=2;
const uint16_t PART_TYPE_ID_CLUTCH=3;
const uint16_t PART_TYPE_ID_COOLER=4;
const uint16_t PART_TYPE_ID_CYLINDERHEAD=5;
const uint16_t PART_TYPE_ID_DIFFERENTIAL=6;
const uint16_t PART_TYPE_ID_ENGINE=7;
const uint16_t PART_TYPE_ID_EXHAUSTMANIFOLD=8;
const uint16_t PART_TYPE_ID_EXHAUSTPIPE=9;
const uint16_t PART_TYPE_ID_FUELINTAKE=10;
const uint16_t PART_TYPE_ID_FUELPUMP=11;
const uint16_t PART_TYPE_ID_INJECTOR=12;
const uint16_t PART_TYPE_ID_INTAKEMANIFOLD=13;
const uint16_t PART_TYPE_ID_TIRE=14;
const uint16_t PART_TYPE_ID_TRANSMISSION=15;


const int CYLINDER_ALIGNMENT_S=0;
const int CYLINDER_ALIGNMENT_V=1;

const int CAMSHAFT_POSITION_CIH=0;
const int CAMSHAFT_POSITION_OHV=1;
const int CAMSHAFT_POSITION_OHC=2;

class Part
{
	public:
		bool load(const std::string& filename);
	
		const std::string& getName() const;		
		const std::string& getInfo() const;		
		float getWeight() const;
		int getPrice() const;
		
		Part(const std::string& filename);
		Part();
		
		virtual ~Part();

		friend Packet& operator<<(Packet& packet,const Part& part);
		friend Packet& operator>>(Packet& packet,Part& part);
		
	protected:		
		std::string m_name;
		std::string m_info;
		float m_weight;
		int32_t m_price;
};

#endif // PART_HPP

