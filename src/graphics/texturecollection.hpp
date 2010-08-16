#ifndef TEXTURECOLLECTION_HPP
#define TEXTURECOLLECTION_HPP

#include <map>
#include <string>

class Texture;

class TextureCollection
{
	public:		
		void addTexture(const std::string& name,const Texture& texture);
		Texture& getTexture(const std::string& name);
	
		void reuploadTextures();

	private:
		std::map<std::string,Texture> textures;

};

#endif // TEXTURECOLLECTION_HPP
