#ifndef VEHICLEMODEL_HPP
#define VEHICLEMODEL_HPP

#include <vector>
#include <string>

#include "part.hpp"

class GameState;

class VehicleModel
{
	public:		
		const std::string& getName() const;
		const std::string& getInfo() const;
		const std::string& getImageName() const;
		int getChassisWeight() const;
		int getYear() const;
		int getPrice() const;		
		
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
		int year;
		int price;
		
		std::vector<Part> parts;
		
};

#endif // VEHICLEMODEL_HPP

