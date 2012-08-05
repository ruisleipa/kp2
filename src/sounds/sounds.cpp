#include "sounds.hpp"

#include <AL/al.h>
#include <AL/alc.h>
#include <AL/alut.h>
#include <iostream>
#include <vector>

Sounds& Sounds::getInstance()
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

	const ALCchar* device_str=alcGetString(NULL,ALC_DEVICE_SPECIFIER);

	int i=0;

	std::vector<std::string> devices;
	std::string curr_dev;

	while(true)
	{
		if(device_str[i]==0)
		{
			devices.push_back(curr_dev);
			curr_dev.clear();

			if(device_str[i+1]==0)
				break;
		}
		else
		{
			curr_dev.push_back(device_str[i]);
		}

		i++;
	}

	//std::cout<<"Available sound devices:"<<std::endl;

	std::vector<std::string>::iterator j;

	for(j=devices.begin();j!=devices.end();++j)
	{
		//std::cout<<*j<<std::endl;
	}

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
