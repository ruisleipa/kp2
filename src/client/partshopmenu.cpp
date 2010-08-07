#include "partshopmenu.hpp"

#include <iostream>
#include <sstream>

#include "ui.hpp"
#include "graphics.hpp"
#include "shared/string.hpp"
#include "connection.hpp"

PartshopMenu::PartshopMenu(Connection& connection):
	m_connection(connection)
{
	m_background_texture.load("data/images/submenu.png");
	m_background.setTexture(&m_background_texture);
	m_background.setStretched(true);

	m_part_texture.load("data/images/parts/engine.jpg");
	m_part_image.setTexture(&m_part_texture);
	
	m_part_info.setFont(Font("small"));
	
	m_category_info.setText("Tähän tulee kategoriainfo.");	
		
	m_category_list.addItem("Lisävarusteet",PART_TYPE_ID_ACCESSORY);
	m_category_list.addItem("Nokka-akselit");
	m_category_list.addItem("Ahtimet");	
	m_category_list.addItem("Kytkimet");
	m_category_list.addItem("Jäähdyttimet");
	m_category_list.addItem("Kannet",PART_TYPE_ID_CYLINDERHEAD);
	m_category_list.addItem("Tasauspyörästöt");	
	m_category_list.addItem("Moottorit",PART_TYPE_ID_ENGINE);
	m_category_list.addItem("Pakosarjat");
	m_category_list.addItem("Pakoputkistot");
	m_category_list.addItem("Bensansyöttö");	
	m_category_list.addItem("Bensapumput");
	m_category_list.addItem("Ruiskut");
	m_category_list.addItem("Imusarjat");
	m_category_list.addItem("Renkaat");	
	m_category_list.addItem("Vaihteistot");
	
	m_category_list.setChangeHandler(Callback0(this,&PartshopMenu::categoryChangeHandler));
	
	m_buy_button.setText("Osta");
	
	addWidget(&m_background);
	
	m_top_row.addWidget(&m_category_info);
	m_top_row.addWidget(&m_part_image);
	
	addWidget(&m_top_row);
	
	m_bottom_row.addWidget(&m_category_list);
	m_bottom_row.addWidget(&m_part_list);
	m_bottom_row.addWidget(&m_part_info);
	
	addWidget(&m_bottom_row);	
	
	addWidget(&m_buy_button);	
}

void PartshopMenu::onResize(Graphics& graphics)
{
	setPosition(CAREER_SUBMENU_POSITION);
	setSize(CAREER_SUBMENU_SIZE);
	
	m_background.setSize(CAREER_SUBMENU_SIZE);
	
	m_top_row.setSize(CAREER_SUBMENU_SIZE*Vector2D(1,0.3));	
	m_bottom_row.setSize(CAREER_SUBMENU_SIZE*Vector2D(1,0.7));	
	m_bottom_row.setPosition(CAREER_SUBMENU_SIZE*Vector2D(0,0.3));	
	
	m_buy_button.autoSize();
	m_buy_button.setPosition(CAREER_SUBMENU_SIZE*Vector2D(0.5,1)-m_buy_button.getSize()*Vector2D(0,1)-Vector2D(0,PADDING));	
}

void PartshopMenu::onShow()
{
	
}

void PartshopMenu::categoryChangeHandler()
{	
	int part_type=m_category_list.getCurrentItemTag();
	
	m_part_list.clearItems();
	
	for(int i=0;i<=m_connection.getPartshopPartMaxId();++i)
	{
		Part part;
	
		bool success=false;
	
		if(part_type==PART_TYPE_ID_ENGINE)
			success=menu->m_connection.getPartshopPartOfType<Engine>(i,part);
		else if(part_type==PART_TYPE_ID_CYLINDERHEAD)
			success=menu->m_connection.getPartshopPartOfType<CylinderHead>(i,part);
		else if(part_type==PART_TYPE_ID_ACCESSORY)
			success=menu->m_connection.getPartshopPartOfType<Accessory>(i,part);

		
		if(!success)
			continue;
	
		m_part_list.addItem(part.getName(),i);
	}
}

void PartshopMenu::partChange()
{
	if(!getParent())
		return;
	
	PartshopMenu* menu=dynamic_cast<PartshopMenu*>(getParent()->getParent());
	
	if(!menu)
		return;
	
	int part_id=menu->m_part_list.getCurrentItemTag();
	
	Part part;
	
	menu->m_connection.getPartshopPart(part_id,part);
	
	menu->m_part_info.setText(part.getInfo());

}
