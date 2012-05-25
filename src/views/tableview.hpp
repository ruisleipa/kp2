#ifndef CLIENT_TABLEVIEW_HPP
#define CLIENT_TABLEVIEW_HPP

#include <QTableView>

class TableView: public QTableView
{
	Q_OBJECT

	public:
		void hideAllColumns();
		void showColumn(int id);

		TableView();
		explicit TableView(QWidget* parent);

	private:
		int nextVisualIndex;
};

#endif

