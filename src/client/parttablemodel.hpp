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
	
	protected:
		virtual QVariant getToolTip(int row) const
		{
			Game::Part* part = getObject(row);
			
			QString tooltip;

			tooltip += QString("<img src=\"data/images/parts/%1\" style=\"float:left;\">").arg("charger.jpg");
			tooltip += QString("<b>%1</b>").arg(part->getName().c_str());
			tooltip += QString("<div style=\"clear:both;\">");
			tooltip += QString("<b>Massa:</b> %1 kg").arg(part->getMass());
			
			return QVariant(tooltip);
		};
};

#endif
