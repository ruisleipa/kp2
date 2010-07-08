#ifndef __VEHICLE_HPP
#define __VEHICLE_HPP

#include <string>

class Packet;

const int ENGINE_FRONT=0;
const int ENGINE_REAR=1;

const int FRONT_DRIVE=0;
const int REAR_DRIVE=1;

class Vehicle
{
	public:
		bool load(const std::string& filename);
	
		const std::string& getName() const;		
		const std::string& getImageName() const;
		
		std::string getGeneralInfoString() const;
				
		Vehicle(const std::string& filename);
		Vehicle();
		
		friend Packet& operator<<(Packet& packet,const Vehicle& vehicle);
		friend Packet& operator>>(Packet& packet,Vehicle& vehicle);

	private:		
		std::string m_name;
		std::string m_image_name;
		std::string m_info;
		int32_t m_year;
		int32_t m_weight;
		int32_t m_engine_placement;
		int32_t m_drive;
		float m_drag;
};

#endif // __VEHICLE_HPP

