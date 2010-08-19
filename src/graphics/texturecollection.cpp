#include "texturecollection.hpp"

#include "texture.hpp"

#include <stdexcept>

void TextureCollection::addTexture(const std::string& name,const Texture& texture)
{
	textures[name] = texture;
}

Texture& TextureCollection::getTexture(const std::string& name)
{
	if(textures.find(name) == textures.end())
	{
		std::string msg;
		
		msg += "getTexture: invalid texture name '";
		msg += name;
		msg += "'";
	
		throw std::runtime_error(msg);
	}
	
	return textures[name];
}

void TextureCollection::reuploadTextures()
{
#ifdef WIN32
	std::map<std::string,Texture>::iterator i;
		
	for(i=textures.begin();i!=textures.end();++i)
	{
		(*i).second.reuploadTexture();
	}
#endif
}