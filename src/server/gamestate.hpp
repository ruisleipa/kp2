#ifndef GAMESTATE_HPP
#define GAMESTATE_HPP

#include <map>
#include <string>
#include <vector>
#include <tr1/memory>

#include "vehiclemodel.hpp"
#include "partmodel.hpp"
#include "player.hpp"
#include "machining.hpp"

class GameState
{
	public:		
		std::vector<std::string> getVehicleModelIds();
		const VehicleModel& getVehicleModel(const std::string& id);

		std::vector<std::string> getPartModelIds();
		const PartModel& getPartModel(const std::string& id);

		std::vector<int> getPlayerIds();
		Player& getPlayer(int id);
		int addPlayer(const Player& player);

		std::vector<std::string> getMachiningIds();
		const Machining& getMachining(const std::string& id);
		
		GameState();
		
		//void load(const std::string& name);
		//void save(const std::string& name);
		
	private:
		void loadVehicleModels();
		void loadPartModels();
		void loadMachinings();
			
		std::map<std::string, std::tr1::shared_ptr<PartModel> > partModels;		
		std::map<int,Player> players;
		std::map<std::string,VehicleModel> vehicleModels;
		std::map<std::string,Machining> machinings;		
};

#endif // GAMESTATE_HPP

