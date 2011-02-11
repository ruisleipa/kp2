#ifndef PART_HPP
#define PART_HPP

#include <string>
#include <vector>

class GameState;

class Part
{
	public:
		const std::string& getName() const;
		int getPrice() const;
		const std::string& getType() const;
		float getWeight() const;
		
		void addMachining(const std::string& name);
		
		Part(GameState& gameState,const std::string& partModelName);
		
	private:
		GameState* gameState;
		std::string partModelName;
		
		std::vector<std::string> machinings;
};

#endif // PART_HPP

