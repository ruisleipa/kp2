#ifndef GAME_CONTAINERSIGNALSANDSLOTS_HPP
#define GAME_CONTAINERSIGNALSANDSLOTS_HPP

#ifdef GAME_OBJECTS_QT
#include <QObject>
#endif

namespace Game
{

#ifdef GAME_OBJECTS_QT

class ContainerSignalsAndSlots : public QObject
{
	Q_OBJECT

	signals:
		void added(int index);
		void removed(int index);
		void changed(int index);

	protected slots:
		virtual void onChange() = 0;
};

#else

class ContainerSignalsAndSlots
{
	protected:
		void added(int index)
		{
			(void)index;
		};

		void removed(int index)
		{
			(void)index;
		};

		void changed(int index)
		{
			(void)index;
		};

		virtual void onChange()
		{

		};
};

#endif

};

#endif
