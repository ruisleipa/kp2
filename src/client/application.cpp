#include "application.hpp"
#include <QFile>
#include <QTextStream>
#include <QString>
#include <QWindowsStyle>

namespace Client
{

Application::Application(int argc, char** argv) :
	QApplication(argc, argv)
{
	applyCustomStyle();
}

void Application::applyCustomStyle()
{
	QApplication::setStyle(new QWindowsStyle);

	setStyleSheet(readStyleSheet());
}

QString Application::readStyleSheet()
{
	QFile file("data/style/stylesheet.qss");
	file.open(QIODevice::ReadOnly);
	QString styleSheet = QTextStream(&file).readAll();
	file.close();

	return styleSheet;
}

}
