#include "partshopmenu.hpp"

#include <iostream>
#include <sstream>

#include "utils/string.hpp"

PartShopMenu::PartShopMenu(Connection& connection):
	connection(connection)
{
	partImage.setTexture(Texture("data/images/parts/engine.jpg"));
	
	partInfo.setFont(Font("small"));
	
	categoryInfo.setText("Tähän tulee kategoriainfo.");	
	
	categoryBox.setChangeHandler(std::tr1::bind(&PartShopMenu::categoryChangeHandler,this));
	categoryBox.setFluid(true);
	categoryBox.addItem("Lisävarusteet",PART_TYPE_ID_ACCESSORY);
	categoryBox.addItem("Nokka-akselit",PART_TYPE_ID_CAMSHAFT);
	categoryBox.addItem("Ahtimet",PART_TYPE_ID_CHARGER);	
	categoryBox.addItem("Kytkimet",PART_TYPE_ID_CLUTCH);
	categoryBox.addItem("Jäähdyttimet",PART_TYPE_ID_COOLER);
	categoryBox.addItem("Kannet",PART_TYPE_ID_CYLINDERHEAD);
	categoryBox.addItem("Tasauspyörästöt",PART_TYPE_ID_DIFFERENTIAL);	
	categoryBox.addItem("Moottorit",PART_TYPE_ID_ENGINE);
	categoryBox.addItem("Pakosarjat",PART_TYPE_ID_EXHAUSTMANIFOLD);
	categoryBox.addItem("Pakoputkistot",PART_TYPE_ID_EXHAUSTPIPE);
	categoryBox.addItem("Bensansyöttö",PART_TYPE_ID_FUELINTAKE);	
	categoryBox.addItem("Bensapumput",PART_TYPE_ID_FUELPUMP);
	categoryBox.addItem("Ruiskut",PART_TYPE_ID_INJECTOR);
	categoryBox.addItem("Imusarjat",PART_TYPE_ID_INTAKEMANIFOLD);
	categoryBox.addItem("Renkaat",PART_TYPE_ID_TIRE);	
	categoryBox.addItem("Vaihteistot",PART_TYPE_ID_TRANSMISSION);
	
	buyButton.setText("Osta");
	buyButton.autoSize();
	
	container.setFactorSize(Vector2D(1,1));
	
	addWidget(container);
	
	container.addWidget(categoryContainer);
	container.addWidget(partContainer);
	container.addWidget(partInfoContainer);
	
	categoryContainer.setFluid(true);
	categoryContainer.showOuterPadding(false);
	
	categoryContainer.addWidget(categoryInfo);
	categoryInfo.setFactorSize(Vector2D(0,0.25));
	
	categoryContainer.addWidget(categoryBox);	
	categoryBox.setFluid(true);
				
	partContainer.setFluid(true);
	partContainer.showOuterPadding(false);

	partContainer.addWidget(partImage);
	partImage.setFactorSize(Vector2D(0,0.25));
	partImage.setFill(true);
	
	partContainer.addWidget(partBox);	
	partBox.setFluid(true);
	
	partInfoContainer.setFluid(true);
	partInfoContainer.showOuterPadding(false);
	
	partInfoContainer.addWidget(partInfo);
	partInfo.setFluid(true);
	
	partInfoContainer.addWidget(buyButton);

}

void PartShopMenu::onResize(Window& window)
{

}

void PartShopMenu::categoryChangeHandler()
{	
	int partType=categoryBox.getCurrentItemTag();
	
	partBox.clearItems();
	
	for(int i=0;i<=connection.getPartshopPartMaxId();++i)
	{
		Part part;
	
		bool success=false;
	
		if(partType==PART_TYPE_ID_ACCESSORY)
			success=connection.getPartshopPartOfType<Accessory>(i,part);
		else if(partType==PART_TYPE_ID_CAMSHAFT)
			success=connection.getPartshopPartOfType<Camshaft>(i,part);
		else if(partType==PART_TYPE_ID_CHARGER)
			success=connection.getPartshopPartOfType<Charger>(i,part);
		else if(partType==PART_TYPE_ID_CLUTCH)
			success=connection.getPartshopPartOfType<Clutch>(i,part);
		else if(partType==PART_TYPE_ID_COOLER)
			success=connection.getPartshopPartOfType<Cooler>(i,part);
		else if(partType==PART_TYPE_ID_CYLINDERHEAD)
			success=connection.getPartshopPartOfType<CylinderHead>(i,part);
		else if(partType==PART_TYPE_ID_DIFFERENTIAL)
			success=connection.getPartshopPartOfType<Differential>(i,part);
		else if(partType==PART_TYPE_ID_ENGINE)
			success=connection.getPartshopPartOfType<Engine>(i,part);
		else if(partType==PART_TYPE_ID_EXHAUSTMANIFOLD)
			success=connection.getPartshopPartOfType<ExhaustManifold>(i,part);
		else if(partType==PART_TYPE_ID_EXHAUSTPIPE)
			success=connection.getPartshopPartOfType<ExhaustPipe>(i,part);
		else if(partType==PART_TYPE_ID_FUELINTAKE)
			success=connection.getPartshopPartOfType<FuelIntake>(i,part);
		else if(partType==PART_TYPE_ID_FUELPUMP)
			success=connection.getPartshopPartOfType<FuelPump>(i,part);
		else if(partType==PART_TYPE_ID_INJECTOR)
			success=connection.getPartshopPartOfType<Injector>(i,part);
		else if(partType==PART_TYPE_ID_INTAKEMANIFOLD)
			success=connection.getPartshopPartOfType<IntakeManifold>(i,part);
		else if(partType==PART_TYPE_ID_TIRE)
			success=connection.getPartshopPartOfType<Tire>(i,part);
		else if(partType==PART_TYPE_ID_TRANSMISSION)
			success=connection.getPartshopPartOfType<Transmission>(i,part);
	
		if(!success)
			continue;
	
		partBox.addItem(part.getName(),i);
	}
}

void PartShopMenu::partChange()
{
	int partId=partBox.getCurrentItemTag();
	
	Part part;
	
	connection.getPartshopPart(partId,part);
	
	partInfo.setText(part.getInfo());
}
