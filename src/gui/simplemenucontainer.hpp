#ifndef SIMPLEMENUCONTAINER_HPP
#define SIMPLEMENUCONTAINER_HPP

#include "menucontainer.hpp"

class SimpleMenuContainer: public MenuContainer
{
	public:
		void addMenu(std::string name,Menu& menu);
		
		SimpleMenuContainer(TextureCollection& backgroundtextures);
	
};

#endif // CONTAINER_HPP

