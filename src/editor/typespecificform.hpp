#ifndef EDITOR_TYPESPECIFICFORM_HPP
#define EDITOR_TYPESPECIFICFORM_HPP

#include <QWidget>

#include "game/chassis.hpp"

class TypeSpecificForm : public QWidget
{
	Q_OBJECT

	public:
		virtual void updateOriginal() = 0;
	
		explicit TypeSpecificForm(QWidget *parent = 0);

	signals:
		void changed();
};

#endif
