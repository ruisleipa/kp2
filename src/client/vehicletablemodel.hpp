#ifndef CLIENT_VEHICLETABLEMODEL_HPP
#define CLIENT_VEHICLETABLEMODEL_HPP

#include "game/vehicle.hpp"
#include "objecttablemodel.hpp"

class VehicleTableModel : public ObjectTableModel<Game::Vehicle>
{
	public:
		ObjectTableModel<Game::Vehicle>::Field name;
		ObjectTableModel<Game::Vehicle>::Field price;

		VehicleTableModel(const Game::Container<Game::Vehicle>& dataSource):
			ObjectTableModel(dataSource),
			name(this, QObject::trUtf8("Nimi"), [](Game::Vehicle* v){return QVariant(v->getName().c_str());}),
			price(this, QObject::trUtf8("Hinta"), [](Game::Vehicle* v){return QVariant(QString::number(v->getPrice()));})
		{

		}
};

#endif
