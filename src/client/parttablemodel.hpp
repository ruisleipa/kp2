#ifndef CLIENT_PARTTABLEMODEL_HPP
#define CLIENT_PARTTABLEMODEL_HPP

#include "game/part.hpp"
#include "objecttablemodel.hpp"

class PartTableModel : public ObjectTableModel<Game::Part>
{
	public:
		ObjectTableModel<Game::Part>::Field name;
		ObjectTableModel<Game::Part>::Field price;

		PartTableModel(const Game::Container<Game::Part>& dataSource):
			ObjectTableModel(dataSource),
			name(this, QObject::trUtf8("Nimi"), [](Game::Part* v){return QVariant(v->getName().c_str());}),
			price(this, QObject::trUtf8("Hinta"), [](Game::Part* v){return QVariant(QString::number(v->getPrice()));})
		{

		}
};

#endif
