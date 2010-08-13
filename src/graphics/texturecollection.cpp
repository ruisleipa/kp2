#include "texturecollection.hpp"

#include "texture.hpp"

void TextureCollection::add(Texture& texture)
{
	textures.insert(&texture);
}

void TextureCollection::remove(Texture& texture)
{
	textures.erase(&texture);
}

void TextureCollection::reuploadTextures()
{
#ifdef WIN32
	std::set<Texture*>::iterator i;
		
	for(i=textures.begin();i!=textures.end();++i)
	{
		(*i)->reuploadTexture();
	}
#endif
}
