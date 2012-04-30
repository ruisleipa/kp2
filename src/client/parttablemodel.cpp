#include "parttablemodel.hpp"

#include <QPixmap>

std::string PartTableModel::NameField::getHeader() const
{
	return "Nimi";
}

QVariant PartTableModel::NameField::getData(Game::Part* v) const
{
	return QVariant(v->getName().c_str());
}

PartTableModel::NameField::NameField(ObjectTableModel* parent):
	Field(parent)
{

}

std::string PartTableModel::PriceField::getHeader() const
{
	return "Hinta";
}

QVariant PartTableModel::PriceField::getData(Game::Part* v) const
{
	return QVariant(QString::number(v->getPrice()));
}

PartTableModel::PriceField::PriceField(ObjectTableModel* parent):
	Field(parent)
{

}

PartTableModel::PartTableModel(const Game::Container<Game::Part>& dataSource):
	ObjectTableModel(dataSource),
	name(this),
	price(this)
{

}

QVariant PartTableModel::getToolTip(int row) const
{
	Game::Part* part = getObject(row);

	QString tooltip;

	tooltip += QString("<img src=\"%1\" style=\"float:left;\">").arg(getImagePath(part));
	tooltip += QString("<b>%1</b>").arg(part->getName().c_str());
	tooltip += QString("<div style=\"clear:both;\">");
	tooltip += QString("<b>Massa:</b> %1 kg").arg(part->getMass());

	return QVariant(tooltip);
}

QString PartTableModel::getImagePath(Game::Part* part) const
{
	Json::Value value;

	part->save(value);

	std::string imageName = "data/images/parts/";
	imageName += value["type"].asString();
	imageName += ".jpg";

	return imageName.c_str();
}
