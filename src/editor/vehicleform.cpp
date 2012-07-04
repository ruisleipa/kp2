#include "vehicleform.hpp"
#include "typespecificformfactory.hpp"
#include "objectfactory.hpp"

void VehicleForm::updateOriginal()
{
	std::string name = nameField->text().toStdString();
	int price = 0;
	int year = yearField->value();
	std::string info = infoField->toPlainText().toStdString();
	std::string imageName;

	vehicle->applyPropertiesOf(Game::Vehicle(name, price, year, info, imageName));
}

void VehicleForm::setItemIcon(QTreeWidgetItem* item)
{
	Game::PartContainer::Slot* slot = itemSlots[item];

	Game::Part* part = slot->getPart();

	if(part)
		item->setIcon(0, QIcon(QPixmap("data/editor/icons/item.png")));
	else
		item->setIcon(0, QIcon(QPixmap("data/editor/icons/empty.png")));
}

void VehicleForm::addSlotItem(Game::PartContainer::Slot* slot, std::string slotName, QTreeWidgetItem* parent)
{
	QStringList texts(QString(slotName.c_str()));

	QTreeWidgetItem* item = new QTreeWidgetItem(parent, texts);

	itemSlots[item] = slot;

	setItemIcon(item);

	if(!parent)
		partTree->addTopLevelItem(item);

	if(slot->getPart())
		addSlotsFor(slot->getPart(), item);
}

void VehicleForm::addSlotsFor(Game::PartContainer* container, QTreeWidgetItem* item)
{
	for(auto pair : container->getSlots())
	{
		std::string slotName = pair.first;
		Game::PartContainer::Slot* slot = pair.second;

		addSlotItem(slot, slotName, item);
	}
}

VehicleForm::VehicleForm(Game::Vehicle* vehicle, QWidget *parent) :
	TypeSpecificForm(parent),
	vehicle(vehicle)
{
	setupUi(this);

	nameField->setText(vehicle->getName().c_str());
	yearField->setValue(vehicle->getYear());
	infoField->setPlainText(vehicle->getInfo().c_str());

	addSlotsFor(vehicle);

	connect(nameField, SIGNAL(textChanged(QString)), this, SIGNAL(changed()));
	connect(yearField, SIGNAL(valueChanged(int)), this, SIGNAL(changed()));
	connect(infoField, SIGNAL(textChanged()), this, SIGNAL(changed()));
}

void VehicleForm::openEditor(Game::Object* object)
{
	editorContainer->removeWidget(editor.get());

	editor.reset(TypeSpecificFormFactory().createFormFor(object));

	editorContainer->addWidget(editor.get());
	editor->show();

	connect(editor.get(), SIGNAL(changed()), this, SLOT(objectEdited()));
}

void VehicleForm::on_partTree_itemClicked(QTreeWidgetItem* selectedItem, int column)
{
	(void)column;

	Game::PartContainer::Slot* slot = itemSlots[selectedItem];

	if(slot->getPart())
	{
		openEditor(slot->getPart());
	}
}

void VehicleForm::on_partTree_itemDoubleClicked(QTreeWidgetItem* selectedItem, int column)
{
	(void)column;

	Game::PartContainer::Slot* slot = itemSlots[selectedItem];

	if(!slot->getPart())
	{
		for(std::string className : readDirectory("data/editor/templates/"))
		{
			Game::Object* object = Editor::ObjectFactory().createObject(className);

			if(Game::Part* part = dynamic_cast<Game::Part*>(object))
			{
				try
				{
					slot->attachPart(part);

					setItemIcon(selectedItem);

					addSlotsFor(slot->getPart(), selectedItem);

					openEditor(slot->getPart());

					break;
				}
				catch(Game::PartContainer::Slot::IncompatibleTypeException)
				{

				}
			}

			delete object;
		}
	}
}

void VehicleForm::objectEdited()
{
	editor->updateOriginal();
}
