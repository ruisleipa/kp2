#include "tableview.hpp"

#include <QHeaderView>

void TableView::setVisibleColumns(std::vector<int> ids)
{
	for(int i = 0; i < horizontalHeader()->count(); i++)
		horizontalHeader()->hideSection(i);

	int to = 0;

	for(int id : ids)
	{
		horizontalHeader()->showSection(id);
		
		int from = horizontalHeader()->visualIndex(id);

		horizontalHeader()->moveSection(from, to);

		to++;
	}
}

TableView::TableView(QWidget* parent):
	QTableView(parent)
{
	QHeaderView* h = horizontalHeader();

	for(int i = 0; i < h->count(); ++i)
		h->setResizeMode(i, QHeaderView::ResizeToContents);
	
        verticalHeader()->setResizeMode(QHeaderView::ResizeToContents);
}

