#include "abstractobjecttablemodel.hpp"

int AbstractObjectTableModel::columnCount(const QModelIndex& parent) const
{
	if(parent.isValid())
		return 0;

	return getColumnCount();
}

int AbstractObjectTableModel::rowCount(const QModelIndex& parent) const
{
	return getRowCount();
}

QVariant AbstractObjectTableModel::data(const QModelIndex& index, int role) const
{
	switch(role)
	{
		case Qt::DisplayRole:
			return getData(index.row(), index.column());

		case Qt::DecorationRole:
			return getDecoration(index.row(), index.column());

		case Qt::ToolTipRole:
			return getToolTip(index.row());

		default:
			return QVariant();

	}
}

QVariant AbstractObjectTableModel::headerData(int section, Qt::Orientation orientation, int role) const
{
	if(role != Qt::DisplayRole)
		return QVariant();

	if(orientation != Qt::Horizontal)
		return QVariant();

	return QVariant(getHeader(section).c_str());
}

AbstractObjectTableModel::AbstractObjectTableModel(QObject *parent):
	QAbstractTableModel(parent)
{

}

QVariant AbstractObjectTableModel::getToolTip(int row) const
{
	return QVariant();
}
