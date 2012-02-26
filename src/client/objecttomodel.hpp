#ifndef CLIENT_OBJECTMODEL_HPP
#define CLIENT_OBJECTMODEL_HPP

#include "game/vehicle.hpp"

#include <QVariant>
#include <QObject>

template <class Object>
class ObjectModel
{
	public:
		QVariant getData(Object* object, int col) const;
		int getColumnCount() const;
		std::string getHeader(int col) const;
};

template <>
class ObjectModel<Game::Vehicle>
{
	public:
		static const int NAME = 0;
		static const int PRICE = 1;
		

                QVariant getData(Game::Vehicle* object, int col) const
		{
			switch(col)
			{
				case NAME: return QVariant(object->getName().c_str());
				case PRICE: return QVariant(QObject::trUtf8("%1 €").arg(object->getPrice()));
				default: return "";
			}
		}

                int getColumnCount() const
		{
			return 2;
		}

                std::string getHeader(int col) const
		{
			switch(col)
			{
				case NAME: return "Nimi";
				case PRICE: return "Hinta";
				default: return "";
			}
		}
};

typedef ObjectModel<Game::Vehicle> VehicleModel;

#endif
