#ifndef EDITOR_MAINWINDOW_H
#define EDITOR_MAINWINDOW_H

#include <memory>
#include <map>

#include <QMainWindow>

#include "ui_mainwindow.h"

#include "game/state.hpp"
#include "game/objectfactory.hpp"

namespace Editor
{

class MainWindow : public QMainWindow, private Ui::MainWindow
{
	Q_OBJECT

	public:
		explicit MainWindow(QWidget *parent = 0);

	private:
		void newFile();
		void openFile(const std::string& fileName);
		void saveFile();
		void closeFile();
		void setFileActionsEnabled(bool enabled);
		void openEditor(Game::Object* object);

		void initView();
		QTreeWidgetItem* findItemForObject(Game::Object* object);
		Game::Object* findObjectForItem(QTreeWidgetItem* item);

		void addVehicleItem(Game::Vehicle* vehicle);

		Game::ObjectFactory factory;

		std::unique_ptr<Game::State> state;

		std::string fileName;

		QTreeWidgetItem* vehicleItem;
		QTreeWidgetItem* newVehicleItem;

		std::map<QTreeWidgetItem*, Game::Object*> itemObjects;

	private slots:
		void on_newAction_triggered();
		void on_openAction_triggered();
		void on_saveAction_triggered();
		void on_saveAsAction_triggered();
		void on_closeAction_triggered();
		void on_quitAction_triggered();

		void on_objectTreeWidget_itemDoubleClicked(QTreeWidgetItem* item, int column);

		void objectEdited(Game::Object* object);

};

};

#endif
