#include "gamestate.hpp"

#include "utils/directory.hpp"

#include "partmodelfactory.hpp"

#include <stdexcept>
#include <iostream>
#include <sstream>

const char* PARTMODEL_DIRECTORY = "gamedata/partmodels/";
const char* VEHICLEMODEL_DIRECTORY = "gamedata/vehiclemodels/";
const char* MACHINING_DIRECTORY = "gamedata/machinings/";

template <class Key,class T>
std::vector<Key> getKeysFromMap(std::map<Key,T> m)
{
	std::vector<Key> keys;

	typename std::map<Key,T>::iterator i;
	
	for(i=m.begin();i!=m.end();++i)
	{
		keys.push_back(i->first);
	}
	
	return keys;
}

std::vector<std::string> GameState::getVehicleModelIds()
{
	return getKeysFromMap(vehicleModels);
}

const VehicleModel& GameState::getVehicleModel(const std::string& id)
{
	if(vehicleModels.find(id) != vehicleModels.end())
		return vehicleModels.find(id)->second;
	else
		throw std::invalid_argument("Vehicle model \"" + id + "\" not found.");
}

std::vector<std::string> GameState::getPartModelIds()
{
	return getKeysFromMap(partModels);
}

const PartModel& GameState::getPartModel(const std::string& id)
{
	if(partModels.find(id) != partModels.end())
		return *partModels[id];
	else
		throw std::runtime_error("Part model \"" + id + "\" not found.");
}

std::vector<int> GameState::getPlayerIds()
{
	return getKeysFromMap(players);
}

Player& GameState::getPlayer(int id)
{
	if(players.find(id) != players.end())
	{
		return players.find(id)->second;
	}
	else
	{
		std::stringstream ss;
		
		ss << "Player #";
		ss << id;
		ss << " not found.";
	
		throw std::invalid_argument(ss.str());
	}
}

int GameState::addPlayer(const Player& player)
{
	int playerId;
	
	if(players.rbegin() == players.rend())
		playerId = 0;
	else	
		playerId = players.rbegin()->first + 1;
	
	players.insert(std::make_pair(playerId, player));
	
	return playerId;
}

std::vector<std::string> GameState::getMachiningIds()
{
	return getKeysFromMap(machinings);
}

const Machining& GameState::getMachining(const std::string& id)
{
	if(machinings.find(id) != machinings.end())
		return machinings[id];
	else
		throw std::runtime_error("Machining \"" + id + "\" not found.");
}

GameState::GameState()
{
	loadMachinings();
	loadPartModels();
	loadVehicleModels();
}

void GameState::loadPartModels()
{
	std::vector<std::string> files = readDirectory(PARTMODEL_DIRECTORY);	
	std::vector<std::string>::iterator i;
	
	PartModelFactory factory;
	
	for(i = files.begin(); i != files.end(); ++i)
	{
		try
		{
			partModels[(*i)] = std::tr1::shared_ptr<PartModel>(factory.loadPartModel(PARTMODEL_DIRECTORY + (*i)));
		}
		catch(std::runtime_error e)
		{
			std::cerr << "An error occured while loading part model \"";
			std::cerr << (*i);
			std::cerr << "\": ";
			std::cerr << e.what() << std::endl;
		}
	}
}

void GameState::loadVehicleModels()
{
	std::vector<std::string> files = readDirectory(VEHICLEMODEL_DIRECTORY);	
	std::vector<std::string>::iterator i;
	
	for(i=files.begin();i!=files.end();++i)
	{
		try
		{
			VehicleModel model(*this, VEHICLEMODEL_DIRECTORY + (*i));
				
			vehicleModels.insert(std::make_pair(*i,model));
		}
		catch(std::runtime_error e)
		{
			std::cerr << "An error occured while loading vehicle model \"";
			std::cerr << (*i);
			std::cerr << "\": ";
			std::cerr << e.what() << std::endl;
		}
	}
}

void GameState::loadMachinings()
{
	std::vector<std::string> files=readDirectory(MACHINING_DIRECTORY);	
	std::vector<std::string>::iterator i;
	
	for(i=files.begin();i!=files.end();++i)
	{
		try
		{
			machinings[(*i)] = Machining(MACHINING_DIRECTORY + (*i));
		}
		catch(std::runtime_error e)
		{
			std::cerr << "An error occured while loading machining \"";
			std::cerr << (*i);
			std::cerr << "\": ";
			std::cerr << e.what() << std::endl;
		}
	}
}

/*
void GameState::load(const std::string& name)
{
	
}

void GameState::save(const std::string& name)
{

}
*/
