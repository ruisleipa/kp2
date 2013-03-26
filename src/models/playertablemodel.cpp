#include "playertablemodel.hpp"

std::string PlayerTableModel::NameField::getHeader() const
{
	return "Nimi";
}

QVariant PlayerTableModel::NameField::getData(Game::Player* part) const
{
	return QVariant(part->getName().c_str());
}

QVariant PlayerTableModel::NameField::getDecoration(Game::Player* part) const
{
	return QVariant();
}

PlayerTableModel::NameField::NameField(ObjectTableModel* parent):
	Field(parent)
{

}

std::string PlayerTableModel::MoneyField::getHeader() const
{
	return "Rahaa";
}

QVariant PlayerTableModel::MoneyField::getData(Game::Player* part) const
{
	return QVariant(QString::number(part->getMoney()));
}

QVariant PlayerTableModel::MoneyField::getDecoration(Game::Player* part) const
{
	return QVariant();
}

PlayerTableModel::MoneyField::MoneyField(ObjectTableModel* parent):
	Field(parent)
{

}

PlayerTableModel::PlayerTableModel(const Game::Container<Game::Player>& dataSource):
	ObjectTableModel(dataSource),
	name(this),
	money(this)
{

}
