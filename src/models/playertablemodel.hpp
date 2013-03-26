#ifndef CLIENT_PLAYERTABLEMODEL_HPP
#define CLIENT_PLAYERTABLEMODEL_HPP

#include "game/player.hpp"
#include "objecttablemodel.hpp"

class PlayerTableModel : public ObjectTableModel<Game::Player>
{
	public:
		class NameField : public ObjectTableModel<Game::Player>::Field
		{
			public:
				virtual std::string getHeader() const;
				virtual QVariant getData(Game::Player* player) const;
				virtual QVariant getDecoration(Game::Player* player) const;
				NameField(ObjectTableModel* parent);

		} name;

		class MoneyField : public ObjectTableModel<Game::Player>::Field
		{
			public:
				virtual std::string getHeader() const;
				virtual QVariant getData(Game::Player* player) const;
				virtual QVariant getDecoration(Game::Player* player) const;
				MoneyField(ObjectTableModel* parent);

		} money;

		PlayerTableModel(const Game::Container<Game::Player>& dataSource);
};

#endif
