#ifndef CLIENT_ABSTRACTOBJECTTABLEMODEL_HPP
#define CLIENT_ABSTRACTOBJECTTABLEMODEL_HPP

#include <QAbstractTableModel>
#include <string>

class AbstractObjectTableModel: public QAbstractTableModel
{
	Q_OBJECT

	public:
		virtual int getRowCount() const = 0;
				
		int columnCount(const QModelIndex& parent) const;
		int rowCount(const QModelIndex& parent) const;
		QVariant data(const QModelIndex& index, int role = Qt::DisplayRole) const;
		QVariant headerData(int section, Qt::Orientation orientation, int role = Qt::DisplayRole) const;

		AbstractObjectTableModel(QObject *parent = 0);

	protected:
		virtual std::string getHeader(int col) const = 0;
		virtual int getColumnCount() const = 0;
		virtual QVariant getData(int row, int col) const = 0;
	
	protected slots:
		virtual void onAdd(int index) = 0;
		virtual void onRemove(int index) = 0;
		virtual void onChange(int index) = 0;
		
	private:

		
};

#endif
