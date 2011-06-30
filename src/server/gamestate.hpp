#ifndef GAMESTATE_HPP
#define GAMESTATE_HPP

#include <map>
#include <string>
#include <vector>
#include <list>
#include <tr1/memory>

using std::tr1::shared_ptr;

#include "vehiclemodel.hpp"
#include "part.hpp"
#include "player.hpp"
#include "machining.hpp"

class GameState
{
	public:		
		std::vector<std::string> getVehicleModelIds();
		const VehicleModel& getVehicleModel(const std::string& id);

		std::vector<std::string> getShopPartIds();
		const Part& getShopPart(const std::string& id);

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
		void loadShopParts();
		void loadMachinings();
		
		std::map<int, Player> players;
		
		std::map<std::string, VehicleModel> vehicleModels;
		std::map<std::string, shared_ptr<Part> > shopParts;
		std::map<std::string, Machining> machinings;
};

#endif // GAMESTATE_HPP

