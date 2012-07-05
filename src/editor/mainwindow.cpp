#include "mainwindow.hpp"

#include "objectfactory.hpp"

#include <QtGui/QApplication>
#include <QFileDialog>
#include <QMdiSubWindow>
#include <fstream>
#include <iostream>

#include "editform.hpp"

namespace Editor
{

MainWindow::MainWindow(QWidget *parent) :
	QMainWindow(parent)
{
	setupUi(this);

	setFileActionsEnabled(false);
}

void MainWindow::initView()
{
	objectTreeWidget->setColumnCount(1);

	vehicleItem = new QTreeWidgetItem((QTreeWidgetItem*)0, QStringList(QString("Autot")));

	objectTreeWidget->insertTopLevelItem(0, vehicleItem);

	newVehicleItem = new QTreeWidgetItem(vehicleItem, QStringList(QString("[Uusi auto]")));

	newVehicleItem->setIcon(0, QIcon(QPixmap("data/editor/icons/newvehicle.png")));

	for(Game::Vehicle* vehicle : state->getShopVehicles())
	{
		addVehicleItem(vehicle);
	}

	setFileActionsEnabled(true);
}

void MainWindow::newFile()
{
	closeFile();

	state.reset(new Game::State(factory));

	initView();
}

void MainWindow::openFile(const std::string& fileName)
{
	closeFile();

	Json::Value stateJson;

	std::ifstream(fileName) >> stateJson;

	state.reset(new Game::State(stateJson, factory));

	initView();
}

void MainWindow::saveFile()
{
	Json::Value stateJson;

	state->save(stateJson);

	std::ofstream(fileName) << stateJson;
}

void MainWindow::closeFile()
{
	state.reset();

	objectTreeWidget->clear();

	setFileActionsEnabled(false);
}

void MainWindow::setFileActionsEnabled(bool enabled)
{
	saveAction->setEnabled(enabled);
	saveAsAction->setEnabled(enabled);
	closeAction->setEnabled(enabled);
	listContainer->setEnabled(enabled);
}

void MainWindow::openEditor(Game::Object* object)
{
	EditForm* child = new EditForm(object, this);

	Qt::WindowFlags flags = Qt::CustomizeWindowHint;
	flags |= Qt::WindowSystemMenuHint;
	flags |= Qt::WindowTitleHint;
	flags |= Qt::WindowCloseButtonHint;

	QMdiSubWindow* subWindow = mdiArea->addSubWindow(child, flags);

	subWindow->setAttribute(Qt::WA_DeleteOnClose);
	child->setAttribute(Qt::WA_DeleteOnClose);

	connect(child, SIGNAL(destroyed()), subWindow, SLOT(close()));
	connect(child, SIGNAL(edited(Game::Object*)), this, SLOT(objectEdited(Game::Object*)));

	child->show();
}

QTreeWidgetItem* MainWindow::findItemForObject(Game::Object* object)
{
	for(auto pair : itemObjects)
	{
		if(pair.second == object)
			return pair.first;
	}

	return nullptr;
}

Game::Object* MainWindow::findObjectForItem(QTreeWidgetItem* item)
{
	if(itemObjects.find(item) != itemObjects.end())
		return itemObjects[item];

	return nullptr;
}

void MainWindow::addVehicleItem(Game::Vehicle* vehicle)
{
	QStringList texts(QString(vehicle->getName().c_str()));

	QTreeWidgetItem* newItem = new QTreeWidgetItem((QTreeWidgetItem*)0, texts);

	newItem->setIcon(0, QIcon(QPixmap("data/editor/icons/vehicle.png")));

	int index = vehicleItem->indexOfChild(newVehicleItem);

	vehicleItem->insertChild(index, newItem);

	itemObjects[newItem] = vehicle;
}

void MainWindow::on_newAction_triggered()
{
	newFile();
}

void MainWindow::on_openAction_triggered()
{
	fileName = QFileDialog::getOpenFileName(this, tr("Avaa..."), "", tr("KP2 SE-tallennukset (*.kp2)")).toStdString();

	if(fileName == "")
		return;

	openFile(fileName);
}

void MainWindow::on_saveAction_triggered()
{
	if(fileName == "")
	{
		on_saveAsAction_triggered();
		return;
	}

	saveFile();
}

void MainWindow::on_saveAsAction_triggered()
{
	std::string fileName = QFileDialog::getSaveFileName(this, tr("Tallenna nimellä..."), "", tr("KP2 SE-tallennukset (*.kp2)")).toStdString();

	if(fileName == "")
		return;

	this->fileName = fileName;

	saveFile();
}

void MainWindow::on_closeAction_triggered()
{
	closeFile();
}

void MainWindow::on_quitAction_triggered()
{
	QApplication::exit(0);
}

void MainWindow::on_objectTreeWidget_itemDoubleClicked(QTreeWidgetItem* selectedItem, int column)
{
	(void)column;

	if(selectedItem == newVehicleItem)
	{
		Game::Object* object = Editor::ObjectFactory().createObject("Vehicle");
		Game::Vehicle* vehicle = dynamic_cast<Game::Vehicle*>(object);

		if(vehicle)
		{
			state->addShopVehicle(vehicle);

			addVehicleItem(vehicle);

			openEditor(vehicle);
		}
	}
	else if(Game::Object* object = findObjectForItem(selectedItem))
	{
		openEditor(object);
	}
}

void MainWindow::objectEdited(Game::Object* object)
{
	if(Game::Vehicle* vehicle = dynamic_cast<Game::Vehicle*>(object))
	{
		for(int i = 0; i < vehicleItem->childCount(); ++i)
		{
			if(QTreeWidgetItem* item = findItemForObject(object))
				item->setText(0, QString(vehicle->getName().c_str()));
		}
	}
}

}
