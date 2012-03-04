#include "tableview.hpp"

#include <QHeaderView>

void TableView::hideAllColumns()
{	
	for(int i = 0; i < horizontalHeader()->count(); i++)
		horizontalHeader()->hideSection(i);
		
	nextVisualIndex = 0;
}

void TableView::showColumn(int id)
{
	horizontalHeader()->showSection(id);
		
	int from = horizontalHeader()->visualIndex(id);

	horizontalHeader()->moveSection(from, nextVisualIndex);

	nextVisualIndex++;
}

TableView::TableView():
	nextVisualIndex(0)
{

}

TableView::TableView(QWidget* parent):
	QTableView(parent),
	nextVisualIndex(0)
{
	QHeaderView* h = horizontalHeader();

	for(int i = 0; i < h->count(); ++i)
		h->setResizeMode(i, QHeaderView::ResizeToContents);
	
        verticalHeader()->setResizeMode(QHeaderView::ResizeToContents);
}

