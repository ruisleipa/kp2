#ifndef TEXTURECOLLECTION_HPP
#define TEXTURECOLLECTION_HPP

#include "texture.hpp"
#include <set>

class TextureCollection
{
	public:		
		void add(Texture& texture);
		void remove(Texture& texture);
	
		void reuploadTextures();	
				
		Texture();

	private:
		std::set<Texture*> textures;

};

#endif // TEXTURECOLLECTION_HPP
