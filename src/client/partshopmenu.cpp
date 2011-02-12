#include "partshopmenu.hpp"

#include <iostream>
#include <sstream>

#include "utils/string.hpp"

const std::string PART_TYPES[] = {"camshaft", "charger", "clutch", "cooler", "cylinderhead", "differential", "engine", "exhaustmanifold", "exhaustpipe", "fuelintake", "fuelpump", "injector", "intakemanifold", "tire"};

PartShopMenu::PartShopMenu(Connection& connection):
	connection(connection)
{
	partImage.setTexture(Texture("data/images/parts/engine.jpg"));
	
	partInfo.setFont(Font("small"));
	
	categoryInfo.setText("Tähän tulee kategoriainfo.");	
	
	categoryBox.setChangeHandler(std::tr1::bind(&PartShopMenu::categoryChangeHandler,this));
	categoryBox.setFluid(true);
	
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
	
	buyButton.setText("Osta");
	buyButton.setClickHandler(std::tr1::bind(&PartShopMenu::buyHandler,this));
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
	partBox.setChangeHandler(std::tr1::bind(&PartShopMenu::partChange, this));
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
	const Protocol::ShopParts& shopParts = connection.getShopParts();
	
	partBox.clearItems();
	
	for(size_t i = 0; i < shopParts.getItemCount(); ++i)
	{
		Protocol::ShopPart part = shopParts.getItem(i);
		
		if(PART_TYPES[categoryBox.getCurrentItemTag()].compare(part.type) == 0)
		{
			partBox.addItem(part.name, i);
		}
	}
}

void PartShopMenu::partChange()
{
	const Protocol::ShopParts& shopParts = connection.getShopParts();

	Protocol::ShopPart part = shopParts.getItem(partBox.getCurrentItemTag());
	
	std::stringstream ss;
	
	ss << part.name << "\n" << "\n";
	ss << "Paino: " << part.weight << " kg" << std::endl;
	ss << "Hinta: " << part.price << " €" << std::endl;
	
	partInfo.setText(ss.str());
}

void PartShopMenu::buyHandler()
{
	const Protocol::ShopParts& shopParts = connection.getShopParts();

	Protocol::ShopPart part = shopParts.getItem(partBox.getCurrentItemTag());
	
	shopParts.getItem(partBox.getCurrentItemTag());
	
	connection.buyPart(part.id);
}
