#ifndef PART_HPP
#define PART_HPP

#include <string>
#include <set>

#include "partmodel.hpp"

class GameState;
class Vehicle;
class Machining;

class Part
{
	public:
		const std::string& getName() const;
		int getPrice() const;
		const std::string& getType() const;
		float getWeight() const;
		
		template<typename T>
		const T& getModelImplementation() const
		{
			return dynamic_cast<const T&>(partModel->getImplementation());
		}
		
		bool fitsInVehicle(const Vehicle& vehicle) const;
		
		void addMachining(const Machining& machining);
		
		Part(const PartModel& partModel);
		
	private:
		const PartModel* partModel;
		
		std::set<const Machining*> machinings;
};

#endif // PART_HPP

