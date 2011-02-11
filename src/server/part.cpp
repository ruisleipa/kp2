#include "part.hpp"

#include "gamestate.hpp"

#include <stdexcept>

const std::string& Part::getName() const
{
	return gameState->getPartModel(partModelName).getName();
}

int Part::getPrice() const
{
	return gameState->getPartModel(partModelName).getPrice();
}

const std::string& Part::getType() const
{
	return gameState->getPartModel(partModelName).getType();
}

float Part::getWeight() const
{
	return gameState->getPartModel(partModelName).getWeight();
}

void Part::addMachining(const std::string& name)
{
	if(gameState->getMachining(name).fitsForPart(*this))
		machinings.push_back(name);
	else
		throw std::runtime_error("Machining \"" + name + "\" does not fit for part model \"" + partModelName + "\"");
}

Part::Part(GameState& gameState,const std::string& partModelName):
	gameState(&gameState),
	partModelName(partModelName)	
{
	this->gameState->getPartModel(partModelName);
}
