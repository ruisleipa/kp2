#ifndef TEXTURECOLLECTION_HPP
#define TEXTURECOLLECTION_HPP

#include <map>
#include <string>

#include "texture.hpp"

class TextureCollection
{
	public:		
		void addTexture(const std::string& name,const Texture& texture);
		Texture& getTexture(const std::string& name);
		Texture& getTexture(int index);

		int getTextureCount();
		
		void freeTextures();
		void uploadTextures();

	private:
		std::map<std::string,Texture> textures;
		
		Texture invalidTexture;

};

#endif // TEXTURECOLLECTION_HPP
