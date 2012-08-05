#include "editformfactory.hpp"

#include "engineform.hpp"
#include "chassisform.hpp"
#include "vehicleform.hpp"
#include "editform.hpp"

void EditFormFactory::createEditForm(Game::Object* object)
{
	if(dynamic_cast<Game::Engine*>(object))
		child = new EngineForm(dynamic_cast<Game::Engine*>(object));
	if(dynamic_cast<Game::Chassis*>(object))
		child = new ChassisForm(dynamic_cast<Game::Chassis*>(object));
	if(dynamic_cast<Game::Vehicle*>(object))
		child = new VehicleForm(dynamic_cast<Game::Vehicle*>(object), factory);

	QWidget* form = new EditForm();


	if(child)
	{
		Qt::WindowFlags flags = Qt::CustomizeWindowHint;
		flags |= Qt::WindowSystemMenuHint;
		flags |= Qt::WindowTitleHint;
		flags |= Qt::WindowCloseButtonHint;

		QMdiSubWindow* subWindow = mdiArea->addSubWindow(child, flags);

		subWindow->setAttribute(Qt::WA_DeleteOnClose);
		child->setAttribute(Qt::WA_DeleteOnClose);

		connect(child, SIGNAL(destroyed()), subWindow, SLOT(close()));

		child->show();
	}
}

void MainWindow::on_newAction_triggered()
{

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

void MainWindow::on_vehicleView_doubleClicked(QModelIndex current)
{
	Game::Vehicle* vehicle = vehicleModel->getObject(current.row());

	if(vehicle)
		openEditor(vehicle);
}

void MainWindow::on_partView_doubleClicked(QModelIndex current)
{
	Game::Part* part = partModel->getObject(current.row());

	if(part)
		openEditor(part);
}

void MainWindow::on_addPartButton_clicked()
{
	std::vector<std::string> classNames;

	QStringList items;

	items << tr("Nokka-akseli");
	classNames.push_back("camshaft");
	items << tr("Ahdin");
	classNames.push_back("charger");
	items << tr("Kori");
	classNames.push_back("chassis");
	items << tr("Kytkin");
	classNames.push_back("clutch");
	items << tr("Jäähdytin");
	classNames.push_back("cooler");
	items << tr("Sylinterikansi");
	classNames.push_back("cylinderhead");
	items << tr("Tasauspyörästö");
	classNames.push_back("differential");
	items << tr("Moottori");
	classNames.push_back("engine");
	items << tr("Pakosarja");
	classNames.push_back("exhaustmanifold");
	items << tr("Pakoputki");
	classNames.push_back("exhaustpipe");
	items << tr("FuelIntake");
	classNames.push_back("fuelintake");
	items << tr("FuelPump");
	classNames.push_back("fuelpump");
	items << tr("Ruisku");
	classNames.push_back("injector");
	items << tr("Imusarja");
	classNames.push_back("intakemanifold");
	items << tr("Rengas");
	classNames.push_back("tire");
	items << tr("Vaihteisto");
	classNames.push_back("transmission");

	bool ok;
	QString item = QInputDialog::getItem(this, tr("Uusi osa..."), tr("Valitse osatyyppi"), items, 0, false, &ok);

	if(!ok)
		return;

	std::string className = classNames[items.indexOf(item)];

	Json::Value partTemplate;

	std::string fileName = "data/editor/templates/";
	fileName += className;

	std::ifstream(fileName) >> partTemplate;

	Game::ObjectFactory factory;

	Game::Object* object = factory.create(partTemplate);

	state->getShopParts().add(dynamic_cast<Game::Part*>(object));

	openEditor(object);
}
