#ifndef CLIENT_PLAYERPROXY_HPP
#define CLIENT_PLAYERPROXY_HPP

#include "game/player.hpp"
#include "connection.hpp"

class InvalidPlayerException
{

};

class PlayerProxy : public Game::Player
{
	public:		
		virtual void setName(const std::string& name);
		virtual void setActiveVehicle(Game::Vehicle* vehicle);
		
		virtual void buyPart(const Game::Part* part);
		virtual void buyVehicle(const Game::Vehicle* vehicle);
		
		virtual void attachPart(Game::Part* part);
		virtual void detachPart(Game::Part* part);
		virtual void upgradePart(Game::Part* part, const Game::Upgrade* upgrade);

		PlayerProxy(const Json::Value& value, Game::ObjectFactory& factory, Connection& connection);
	
	private:
		int getIndex();
		void makeCall(const std::string& method, const Json::Value& arguments);
	
		Connection& connection;
	
};

#endif
