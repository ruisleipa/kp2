#include "ui.hpp"

void Ui::draw()
{
	m_root_window.draw(m_graphics);
}

Ui::Ui(Events& events,Graphics& graphics):
	m_events(events),
	m_graphics(graphics),
	m_font_loader(m_graphics),
	m_root_window(),
	m_mainmenu(),
	m_settingsmenu(m_graphics),
	m_connectmenu(),
	m_localgamemenu(),
	m_newlocalgamemenu()
{
	m_events.setEventListener(&m_root_window);

	m_root_window.addWidget("mainmenu",&m_mainmenu);
	m_root_window.addWidget("settingsmenu",&m_settingsmenu);
	m_root_window.addWidget("connectmenu",&m_connectmenu);
	m_root_window.addWidget("localgamemenu",&m_localgamemenu);
	m_root_window.addWidget("newlocalgamemenu",&m_newlocalgamemenu);
	
	m_settingsmenu.setVisible(false);
	m_connectmenu.setVisible(false);
	m_localgamemenu.setVisible(false);
	m_newlocalgamemenu.setVisible(false);

	m_root_window.resize(m_graphics);
}

