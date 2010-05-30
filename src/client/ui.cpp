#include "ui.hpp"

#include <GL/glew.h>

#include "graphics.hpp"
#include "assert.hpp"

void Ui::keyDown(KeyEvent event)
{
	if(getActiveView() == 0)
		return;
		
	getActiveView()->keyDown(event);
}

void Ui::keyUp(KeyEvent event)
{
	if(getActiveView() == 0)
		return;	
		
	getActiveView()->keyUp(event);
}

void Ui::mouseDown(MouseEvent event)
{
	if(getActiveView() == 0)
		return;
		
	getActiveView()->mouseDown(event);
}

void Ui::mouseUp(MouseEvent event)
{
	if(getActiveView() == 0)
		return;
	
	getActiveView()->mouseUp(event);
}

void Ui::mouseMove(MouseEvent event)
{
	if(getActiveView() == 0)
		return;	
		
	getActiveView()->mouseMove(event);
}

Ui& Ui::getInstance()
{
	static Ui instance;

	return instance;
}

void Ui::draw()
{
	glClear(GL_COLOR_BUFFER_BIT);
	glDisable(GL_DEPTH_TEST);
	
	std::vector<View*>::iterator i;
	
	for(i=m_visible_views.begin();i!=m_visible_views.end();++i)
	{
		(*i)->draw();
	}
}

void Ui::goToView(std::string name)
{
	std::map<std::string,View*>::iterator i;
	
	i=m_views.find(name);
	
	if(i==m_views.end())
		return;
		
	m_visible_views.push_back((*i).second);

	getActiveView()->onActivate();
	
	std::vector<View*>::iterator j;
	
	std::cout<<"views: ";
	
	for(j=m_visible_views.begin();j!=m_visible_views.end();++j)
	{
		std::cout<<(*j)<<" ";
	}
	
	std::cout<<std::endl;
}

void Ui::goToPreviousView()
{
	m_visible_views.pop_back();
	
	std::vector<View*>::iterator j;
	
	std::cout<<"views: ";
	
	for(j=m_visible_views.begin();j!=m_visible_views.end();++j)
	{
		std::cout<<(*j)<<" ";
	}
	
	std::cout<<std::endl;
}

void Ui::calculateLayouts()
{
	std::map<std::string,View*>::iterator i;
	
	for(i=m_views.begin();i!=m_views.end();++i)
	{
		(*i).second->calculateLayout();
	}
}

void Ui::addView(std::string name,View* view)
{
	assert(view != 0);

	if(view)
		m_views[name]=view;
}

void Ui::removeView(std::string name)
{
	std::map<std::string,View*>::iterator i;
	
	i=m_views.find(name);
	
	if(i==m_views.end())
		return;
		
	getActiveView()->onActivate();

	m_views.erase(name);
}

void Ui::setFont(std::string name,Font* font)
{
	m_fonts[name]=font;
}

Font* Ui::getFont(std::string name)
{
	if(m_fonts.find(name)!=m_fonts.end())
		return m_fonts[name];
	else
		return 0;
}

View* Ui::getActiveView()
{
	return (m_visible_views.back());
}

Ui::Ui()
{
		
}

Ui::~Ui()
{
	
}

