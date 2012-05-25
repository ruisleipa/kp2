#include "vehicletablemodel.hpp"

std::string VehicleTableModel::NameField::getHeader() const
{
	return "Nimi";
}

QVariant VehicleTableModel::NameField::getData(Game::Vehicle* v) const
{
	return QVariant(v->getName().c_str());
}

QVariant VehicleTableModel::NameField::getDecoration(Game::Vehicle*) const
{
	return QVariant();
}

VehicleTableModel::NameField::NameField(ObjectTableModel* parent):
	Field(parent)
{

}

std::string VehicleTableModel::PriceField::getHeader() const
{
	return "Hinta";
}

QVariant VehicleTableModel::PriceField::getData(Game::Vehicle* v) const
{
	return QVariant(QString::number(v->getPrice()));
}

QVariant VehicleTableModel::PriceField::getDecoration(Game::Vehicle*) const
{
	return QVariant();
}

VehicleTableModel::PriceField::PriceField(ObjectTableModel* parent):
	Field(parent)
{

}

VehicleTableModel::VehicleTableModel(const Game::Container<Game::Vehicle>& dataSource):
	ObjectTableModel(dataSource),
	name(this),
	price(this)
{

}
