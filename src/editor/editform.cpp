#include "editform.hpp"

#include "typespecificformfactory.hpp"

namespace Editor
{

EditForm::EditForm(Game::Object* object, QWidget *parent) :
	QWidget(parent),
	object(object),
	form(TypeSpecificFormFactory().createFormFor(object))
{
	setupUi(this);

	formContainer->addWidget(form);
}

void EditForm::on_closeButton_clicked()
{
	close();
}

void EditForm::on_saveButton_clicked()
{
	form->updateOriginal();

	edited(object);
}

void EditForm::on_okButton_clicked()
{
	form->updateOriginal();

	edited(object);

	close();
}

}
