#include "player.hpp"

#include "packet.hpp"

const std::string& Player::getName() const
{
	return m_name;
}

void Player::setName(const std::string& name)
{
	m_name=name;
}

int Player::getMoney() const
{
	return m_money;
}

void Player::setMoney(int money)
{
	m_money=money;
}

bool Player::changeMoney(int money)
{
	/* We dont want to overflow the money amount. */
	if(m_money + money < 0)
		return false;
		
	m_money += money;
	return true;
}

Player::Player():
	m_name(""),
	m_money(20000)
{

}


