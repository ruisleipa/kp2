#ifndef EDITOR_MAINWINDOW_H
#define EDITOR_MAINWINDOW_H

#include <QWidget>

#include "game/object.hpp"

class EditFormFactory
{
	public:
		QWidget* createEditForm(Game::Object* object);
};

#endif
