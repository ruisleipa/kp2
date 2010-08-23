#include "menucontainer.hpp"

void MenuContainer::showMenu(std::string tag)
{
	for(int i=0; i<getChildCount(); i++)
	{
		getChild(i)->setVisible(false);
	}
	
	getChild(tag)->setVisible(true);
	background.setVisible(true);
}

void MenuContainer::showOverlayMenu(std::string tag)
{
	getChild(tag)->setVisible(true);
}

void MenuContainer::onDraw(Graphics& graphics)
{
	float alpha=m_bg_chage_timer.getSeconds()*10.0;
	if(alpha > 1.0)
		alpha = 1.0;
	
	m_background_back.setColor(Color(1,1,1,1.0-alpha));
}

void MenuContainer::changeBackground()
{
	int i=rand()%m_background_files.size();
	
	while(m_background.getTexture()==&m_background_files.at(i))
		i=rand()%m_background_files.size();
	
	m_background_back.setTexture(m_background.getTexture());
	m_background.setTexture(&m_background_files.at(i));
	
	m_bg_chage_timer.reset();
}

MenuContainer::MenuContainer()
{
	setSize(Vector2D(1,1));
}
