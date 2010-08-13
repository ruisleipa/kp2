#ifndef TEXTURECOLLECTION_HPP
#define TEXTURECOLLECTION_HPP

#include <set>

class Texture;

class TextureCollection
{
	public:		
		void add(Texture& texture);
		void remove(Texture& texture);
	
		void reuploadTextures();	

	private:
		std::set<Texture*> textures;

};

#endif // TEXTURECOLLECTION_HPP
