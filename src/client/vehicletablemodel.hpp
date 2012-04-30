#ifndef CLIENT_VEHICLETABLEMODEL_HPP
#define CLIENT_VEHICLETABLEMODEL_HPP

#include "game/vehicle.hpp"
#include "objecttablemodel.hpp"

class VehicleTableModel : public ObjectTableModel<Game::Vehicle>
{
	public:
		class NameField : public ObjectTableModel<Game::Vehicle>::Field
		{
			public:
				virtual std::string getHeader() const;
				virtual QVariant getData(Game::Vehicle* v) const;
				virtual QVariant getDecoration(Game::Vehicle*) const;
				NameField(ObjectTableModel* parent);

		} name;

		class PriceField : public ObjectTableModel<Game::Vehicle>::Field
		{
			public:
				virtual std::string getHeader() const;
				virtual QVariant getData(Game::Vehicle* v) const;
				virtual QVariant getDecoration(Game::Vehicle*) const;
				PriceField(ObjectTableModel* parent);

		} price;

		VehicleTableModel(const Game::Container<Game::Vehicle>& dataSource);
};

#endif
