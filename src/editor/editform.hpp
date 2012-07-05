#ifndef EDITOR_EDITFORM_HPP
#define EDITOR_EDITFORM_HPP

#include <memory>

#include <QWidget>

#include "typespecificform.hpp"

#include "ui_editform.h"
#include "game/object.hpp"

namespace Editor
{

class EditForm : public QWidget, private Ui::EditForm
{
	Q_OBJECT

	public:
		explicit EditForm(Game::Object* object, QWidget *parent = 0);

	signals:
		void edited(Game::Object*);
		
	private:
		Game::Object* object;
		
		TypeSpecificForm* form;
	
	private slots:
		void on_closeButton_clicked();
		void on_saveButton_clicked();
		void on_okButton_clicked();
	
};

};

#endif
