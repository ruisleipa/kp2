#ifndef PLAYER_HPP
#define PLAYER_HPP

#include <string>
#include <stdint.h>

class Packet;

class Player
{
	public:
		const std::string& getName() const;
		void setName(const std::string& name);
	
		int getMoney() const;
		void setMoney(int money);
		bool changeMoney(int money);
		
		Player();

	private:
		std::string m_name;
		int32_t m_money;
};

#endif // PLAYER_HPP

