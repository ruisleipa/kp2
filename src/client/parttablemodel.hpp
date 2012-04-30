#ifndef CLIENT_PARTTABLEMODEL_HPP
#define CLIENT_PARTTABLEMODEL_HPP

#include "game/part.hpp"
#include "objecttablemodel.hpp"

class PartTableModel : public ObjectTableModel<Game::Part>
{
	public:
		class NameField : public ObjectTableModel<Game::Part>::Field
		{
			public:
				virtual std::string getHeader() const;
				virtual QVariant getData(Game::Part* v) const;
				NameField(ObjectTableModel* parent);

		} name;

		class PriceField : public ObjectTableModel<Game::Part>::Field
		{
			public:
				virtual std::string getHeader() const;
				virtual QVariant getData(Game::Part* v) const;
				PriceField(ObjectTableModel* parent);

		} price;

		PartTableModel(const Game::Container<Game::Part>& dataSource);

	protected:
		virtual QVariant getToolTip(int row) const;
};

#endif
