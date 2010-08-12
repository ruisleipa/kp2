#include "texturecollection.hpp"

Texture::Texture()
{

}

void Texture::addTexture(Texture& texture)
{
	textures.insert(&texture);
}

void Texture::removeTexture(Texture& texture)
{
	textures.erase(&texture);
}

void Texture::reuploadTextures()
{
#ifdef WIN32
	std::set<Texture*>::iterator i;
		
	for(i=textures.begin();i!=textures.end();++i)
	{
		(*i)->reuploadTexture();
	}
#endif
}
