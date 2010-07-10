#include "ui.hpp"

void Ui::draw()
{
	m_root_window.doDraw(m_graphics);
}

Ui::Ui(Events& events,Graphics& graphics,Connection& connection):
	m_events(events),
	m_graphics(graphics),
	m_connection(connection),
	m_font_loader(m_graphics),
	m_root_window(),
	m_mainmenu(),
	m_settingsmenu(m_graphics),
	m_connectmenu(),
	m_localgamemenu(),
	m_newlocalgamemenu(m_connection),
	m_careermenu(),
	m_garagemenu(m_connection),
	m_tuningmenu()
{
	m_events.setEventListener(&m_root_window);
	m_connection.setEventListener(&m_root_window);

	m_root_window.addWidget("mainmenu",&m_mainmenu);
	m_root_window.addWidget("settingsmenu",&m_settingsmenu);
	m_root_window.addWidget("connectmenu",&m_connectmenu);
	m_root_window.addWidget("localgamemenu",&m_localgamemenu);
	m_root_window.addWidget("newlocalgamemenu",&m_newlocalgamemenu);
	
	m_root_window.addWidget("careermenu",&m_careermenu);
	
	m_root_window.addWidget("garagemenu",&m_garagemenu);	
	m_root_window.addWidget("tuningmenu",&m_tuningmenu);
	
	m_settingsmenu.setVisible(false);
	m_connectmenu.setVisible(false);
	m_localgamemenu.setVisible(false);
	m_newlocalgamemenu.setVisible(false);
	
	m_careermenu.setVisible(false);
	
	m_garagemenu.setVisible(false);	
		
	m_tuningmenu.setVisible(false);

	m_root_window.doResize(m_graphics);
}

