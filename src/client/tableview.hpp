#ifndef CLIENT_TABLEVIEW_HPP
#define CLIENT_TABLEVIEW_HPP

#include <QTableView>

class TableView: public QTableView
{
	Q_OBJECT

	public:
		void setVisibleColumns(std::vector<int> ids);

		explicit TableView(QWidget* parent);
};

#endif

