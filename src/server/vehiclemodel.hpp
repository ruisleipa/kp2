#ifndef VEHICLEMODEL_HPP
#define VEHICLEMODEL_HPP

#include <vector>
#include <string>
#include <tr1/memory>

using std::tr1::shared_ptr;

#include "part.hpp"

class GameState;

class VehicleModel
{
	public:		
		const std::string& getName() const;
		const std::string& getInfo() const;
		const std::string& getImageName() const;
		int getChassisWeight() const;
		float getDragCoefficient() const;
		float getLength() const;
		float getWidth() const;
		float getHeight() const;
		float getWheelbase() const;
		int getYear() const;
		int getPrice() const;		
		int getMaxEngineVolume() const;		
		int getMaxEngineCylinderCount() const;		
		
		size_t getPartCount() const;
		const Part& getPart(size_t id) const;
				
		VehicleModel(GameState& gameState,const std::string& filename);
		
	private:
		void load(const std::string& filename);
		void createPart(const std::string& modelName,const std::string& machinings);
	
		GameState& gameState;
	
		std::string name;
		std::string info;
		std::string imageName;
		int chassisWeight;
		float dragCoefficient;
		float length;
		float width;
		float height;
		float wheelbase;
		int year;
		int price;
		int maxEngineVolume;
		int maxEngineCylinderCount;
		
		std::vector<shared_ptr<Part> > parts;
		
};

#endif // VEHICLEMODEL_HPP

