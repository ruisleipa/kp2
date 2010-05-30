#include "sounds.hpp"

#include <AL/al.h>
#include <AL/alc.h>
#include <AL/alut.h>
#include <iostream>

Sounds* Sounds::getInstance()
{
	static Sounds instance;
	return instance;
}

void Sounds::printSoundInfo()
{
}

Sounds::Sounds()
{
	m_was_init=false;

	if(alutInit(NULL, NULL) == AL_FALSE)
	{
		std::cerr<<"alutInit(NULL,NULL) failed"<<std::endl;
		std::cerr<<alutGetErrorString(alutGetError())<<"\n";
		return;	
	}

	alGetError();
	
	printSoundInfo();

	m_was_init=true;
}

Sounds::~Sounds()
{
	if(m_was_init)
		alutExit();
}
