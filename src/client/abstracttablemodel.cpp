#include "abstracttablemodel.hpp"

void AbstractTableModel::onDataChanged(Game::Object* object)
{
	updateData(object);
}
