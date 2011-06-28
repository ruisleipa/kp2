#include "partshopmenu.hpp"

#include <iostream>
#include <sstream>

#include "utils/string.hpp"

#include "gui/columnlayoutcontainer.hpp"
#include "gui/rowlayoutcontainer.hpp"
#include "gui/label.hpp"
#include "gui/button.hpp"
#include "gui/image.hpp"
#include "gui/field.hpp"
#include "gui/listbox.hpp"

const std::string PART_TYPES[] = {"camshaft", "charger", "clutch", "cooler", "cylinderhead", "differential", "engine", "exhaustmanifold", "exhaustpipe", "fuelintake", "fuelpump", "injector", "intakemanifold", "tire", "transmission"};

PartShopMenu::PartShopMenu(Connection& connection, Container& parent):
	connection(connection),
	loader("data/ui/partshopmenu.ui")
{
	addWidget(loader.getRootWidget(), "0px", "0px", "100%", "100%");
	
	Listbox& categoryBox = dynamic_cast<Listbox&>(getChildByName("categoryBox"));
	
	categoryBox.setChangeHandler(std::tr1::bind(&PartShopMenu::categoryChangeHandler,this));

	categoryBox.addItem("Nokka-akselit", 0);
	categoryBox.addItem("Ahtimet", 1);
	categoryBox.addItem("Kytkimet", 2);
	categoryBox.addItem("Jäähdyttimet", 3);
	categoryBox.addItem("Sylinterikannet", 4);
	categoryBox.addItem("Tasauspyörästöt", 5);
	categoryBox.addItem("Moottorit", 6);
	categoryBox.addItem("Pakosarjat", 7);
	categoryBox.addItem("Pakoputket", 8);
	categoryBox.addItem("Polttoaineensyöttö", 9);
	categoryBox.addItem("Polttoainepumput", 10);
	categoryBox.addItem("Suuttimet", 11);
	categoryBox.addItem("Imusarjat", 12);
	categoryBox.addItem("Renkaat", 13);
	categoryBox.addItem("Vaihteistot", 14);
	
	dynamic_cast<Button&>(getChildByName("buyButton")).setClickHandler(std::tr1::bind(&PartShopMenu::buyHandler,this));
	dynamic_cast<Listbox&>(getChildByName("partBox")).setChangeHandler(std::tr1::bind(&PartShopMenu::partChange, this));
	getChildByName<Button>("backButton").setClickHandler(std::tr1::bind(&Container::showOnlyWidget, &parent, "installpartsmenu"));
}

void PartShopMenu::categoryChangeHandler()
{
	Listbox& partBox = dynamic_cast<Listbox&>(getChildByName("partBox"));
	Listbox& categoryBox = dynamic_cast<Listbox&>(getChildByName("categoryBox"));
	
	partBox.clearItems();
	
	std::vector<std::string> ids = connection.getShopParts().getKeys();	
	
	for(size_t i = 0; i < ids.size(); ++i)
	{
		Protocol::ShopPart part = connection.getShopParts().getItem(ids[i]);
		
		if(PART_TYPES[categoryBox.getCurrentItemTag()] == part.type)
		{
			partBox.addItem(part.name, i);
		}
	}
}

void PartShopMenu::partChange()
{
	Listbox& partBox = dynamic_cast<Listbox&>(getChildByName("partBox"));
	Label& partInfo = dynamic_cast<Label&>(getChildByName("partInfo"));
	
	std::vector<std::string> ids = connection.getShopParts().getKeys();	
	
	Protocol::ShopPart part = connection.getShopParts().getItem(ids[partBox.getCurrentItemTag()]);
	
	std::stringstream ss;
	
	ss << part.name << "\n" << "\n";
	ss << "Paino: " << part.weight << " kg" << std::endl;
	ss << "Hinta: " << part.price << " €" << std::endl;
	
	partInfo.setText(ss.str());
}

void PartShopMenu::buyHandler()
{
	Listbox& partBox = dynamic_cast<Listbox&>(getChildByName("partBox"));
	
	std::vector<std::string> ids = connection.getShopParts().getKeys();	
	
	if(partBox.getCurrentItemTag() != -1)
		connection.buyPart(ids[partBox.getCurrentItemTag()]);
}
