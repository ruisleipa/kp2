#include "vehicletablemodel.hpp"

virtual std::string VehicleTableModel::NameField::getHeader() const
{
	return "Nimi";
}

virtual QVariant VehicleTableModel::NameField::getData(Game::Vehicle* v) const
{
	return QVariant(v->getName().c_str());
}

VehicleTableModel::NameField::NameField(ObjectTableModel* parent):
	Field(parent)
{

}

virtual std::string VehicleTableModel::PriceField::getHeader() const
{
	return "Hinta";
}

virtual QVariant VehicleTableModel::PriceField::getData(Game::Vehicle* v) const
{
	return QVariant(QString::number(v->getPrice()));
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
