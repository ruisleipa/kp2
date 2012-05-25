#ifndef EDITOR_MAINWINDOW_H
#define EDITOR_MAINWINDOW_H

#include <memory>

#include <QMainWindow>

#include "ui_mainwindow.h"

#include "models/vehicletablemodel.hpp"
#include "models/parttablemodel.hpp"
#include "game/state.hpp"
#include "game/objectfactory.hpp"

class MainWindow : public QMainWindow
{
	Q_OBJECT

	public:
		explicit MainWindow(QWidget *parent = 0);

	private:
		std::unique_ptr<Ui::MainWindow> ui;
		std::unique_ptr<Game::State> state;
		std::unique_ptr<VehicleTableModel> vehicleModel;
		std::unique_ptr<PartTableModel> partModel;

		std::string fileName;

	private slots:
		void on_newAction_triggered();
		void on_openAction_triggered();
		void on_saveAction_triggered();
		void on_saveAsAction_triggered();
		void on_closeAction_triggered();
		void on_quitAction_triggered();

};

#endif
