#include "settingsmenu.hpp"

#include <iostream>

#include "ui.hpp"
#include "graphics.hpp"
#include "shared/string.hpp"

SettingsMenu::SettingsMenu(Graphics& graphics):
	m_graphics(graphics)
{
	m_background_texture.load("data/images/settingsmenu.png");
	m_background.setTexture(&m_background_texture);
	
	m_title.setFont(Font("title"));
	m_title.setText("Asetukset");			
	
	m_resolution_label.setText("Näyttötila:");
	m_fullscreen_label.setText("Koko ruutu:");
	m_vsync_label.setText("Vsync:");	
	m_filter_label.setText("Tekstuurisuodatin:");	
	
	m_modes=m_graphics.getVideoModes();
	std::vector<Vector2D>::iterator i;
	
	for(i=m_modes.begin();i!=m_modes.end();++i)
	{
		std::string str=convertToString((*i).getX());
		str+="x";
		str+=convertToString((*i).getY());
		
		m_resolution_select.addItem(str);
	}	
	
	m_fullscreen_select.addItem("ei");
	m_fullscreen_select.addItem("kyllä");
	
	m_vsync_select.addItem("ei");
	m_vsync_select.addItem("kyllä");
	
	m_filter_select.addItem("nopein");
	m_filter_select.addItem("hyvä");
	m_filter_select.addItem("paras");
	
	m_back_button.setText("Takaisin");
	m_apply_button.setText("Ota käyttöön");

	addWidget(&m_background);
	
	addWidget(&m_title);
	
	addWidget(&m_resolution_label);
	addWidget(&m_fullscreen_label);
	addWidget(&m_vsync_label);	
	addWidget(&m_filter_label);	
			
	addWidget(&m_resolution_select);
	addWidget(&m_fullscreen_select);	
	addWidget(&m_vsync_select);
	addWidget(&m_filter_select);
		
	addWidget(&m_back_button);	
	addWidget(&m_apply_button);
}

void SettingsMenu::onResize(Graphics& graphics)
{
	m_background.setSize(Vector2D(1,1));
		
	m_title.setPosition(TITLE_POSITION);
	m_title.setSize(TITLE_SIZE);
		
	Vector2D buttonpos=CONTENT_POSITION;

	m_resolution_label.setPosition(buttonpos);
	m_resolution_label.autoSize();
	buttonpos+=BUTTON_HEIGHT;
	
	m_fullscreen_label.setPosition(buttonpos);
	m_fullscreen_label.autoSize();
	buttonpos+=BUTTON_HEIGHT;
	
	m_vsync_label.setPosition(buttonpos);
	m_vsync_label.autoSize();
	buttonpos+=BUTTON_HEIGHT;
	
	m_filter_label.setPosition(buttonpos);
	m_filter_label.autoSize();
	buttonpos+=BUTTON_HEIGHT;
	
	buttonpos=CONTENT_POSITION;
	buttonpos.setX(0.5);
	
	m_resolution_select.setPosition(buttonpos);
	m_resolution_select.autoSize();	
	buttonpos+=BUTTON_HEIGHT;
	
	m_fullscreen_select.setPosition(buttonpos);
	m_fullscreen_select.autoSize();
	buttonpos+=BUTTON_HEIGHT;	

	m_vsync_select.setPosition(buttonpos);
	m_vsync_select.autoSize();
	buttonpos+=BUTTON_HEIGHT;

	m_filter_select.setPosition(buttonpos);
	m_filter_select.autoSize();
	buttonpos+=BUTTON_HEIGHT;
	
	m_back_button.setPosition(BACK_BUTTON_POSITION);
	m_back_button.autoSize();

	m_apply_button.setPosition(NEXT_BUTTON_POSITION);
	m_apply_button.autoSize();

}

void SettingsMenu::onShow()
{
	updateDisplayOptions();
}

void SettingsMenu::updateDisplayOptions()
{
	Vector2D displaysize=m_graphics.getDisplaySize();
	
	for(int i=0;i<m_modes.size();++i)
	{
		if(displaysize==m_modes[i])
		{
			m_resolution_select.setIndex(i);
			break;
		}			
	}		

	m_fullscreen_select.setIndex(m_graphics.isFullScreen());
	
	m_vsync_select.setIndex(m_graphics.isVsynced());
	
	m_filter_select.setIndex(Texture::getFilterLimit());

	m_resolution_select.autoSize();	
	m_fullscreen_select.autoSize();
	m_vsync_select.autoSize();
}

void SettingsMenu::BackButton::onClick()
{
	getParent()->setVisible(false);
	((Container*)getParent()->getParent())->getWidget("mainmenu")->setVisible(true);
}

void SettingsMenu::ApplyButton::onClick()
{
	SettingsMenu* menu=dynamic_cast<SettingsMenu*>(getParent());
	
	Texture::setFilterLimit((TextureFilter)menu->m_filter_select.getIndex());
	
	Vector2D mode=menu->m_modes[menu->m_resolution_select.getIndex()];
	bool fullscreen=menu->m_fullscreen_select.getIndex();
	bool vsync=menu->m_vsync_select.getIndex();
	
	menu->m_graphics.setVideoMode(mode.getX(),mode.getY(),32,fullscreen,vsync,true);
	
	menu->updateDisplayOptions();
}

