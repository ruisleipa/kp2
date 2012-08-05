#ifndef CLIENT_APPLICATION_HPP
#define CLIENT_APPLICATION_HPP

#include <QApplication>

namespace Client
{

class Application : public QApplication
{
	Q_OBJECT

	public:
		Application(int argc, char** argv);

	private:
		void applyCustomStyle();
		QString readStyleSheet();

};

}

#endif
