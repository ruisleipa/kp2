//Original Sound made by nitrotrigger

#include "sound.hpp"

#include <iostream>
#include <cstdlib>

int Sound::m_sound_sys_ref_count=0;
bool Sound::m_sound_sys_init_tried=false;
bool Sound::m_sound_sys_init_success=false;

Sound::Sound()
{
	m_buffer = 0;
	m_source = NULL;
	m_playing = false;
	
	m_sound_sys_ref_count++;
}

Sound::~Sound()
{
	unload();
	
	if(m_sound_sys_init_success && --m_sound_sys_ref_count==0)
		alutExit();
}

int Sound::load(std::string fname)
{
	if(!m_sound_sys_init_tried)
		initSounds();
		
	if(!m_sound_sys_init_success)
		return -1;

	unload();
	
	ALenum errflag = AL_NO_ERROR;

	ALfloat SourcePos[] = { 0.0, 0.0, 0.0 };
	ALfloat SourceVel[] = { 0.0, 0.0, 0.0 };

	m_buffer = alutCreateBufferFromFile(fname.c_str());
   
	errflag = alutGetError();
	if (errflag != ALUT_ERROR_NO_ERROR)
	{
		std::cerr << "ALUT error: " << alutGetErrorString (errflag) << "\n";
		return -1;
	}

	// Bind buffer with a source.
	alGenSources(1,&m_source);
	
	errflag = alGetError();
	if (errflag != AL_NO_ERROR)
	{
		std::cerr << "OpenAL error: " << alGetString(errflag) << "\n";
		return -1;
	}

	alSourcei(m_source, AL_BUFFER, m_buffer);
	alSourcef(m_source, AL_PITCH, 1.0f);
	alSourcef(m_source, AL_GAIN, 1.0f);
	alSourcei(m_source, AL_LOOPING, AL_FALSE);
	alSourcefv(m_source, AL_POSITION, SourcePos);
	alSourcefv(m_source, AL_VELOCITY, SourceVel);

	// Check here for AL-errors, return -1 if any.
	errflag = alGetError();
	if (errflag != AL_NO_ERROR)
	{
		std::cerr << "OpenAL error: " << alGetString(errflag) << "\n";
		return -1;
	}

	return 0;
}

void Sound::unload()
{
	stop();

	if (m_source)
	{
    	alDeleteSources(1,&m_source);
		m_source = 0;
		//std::cerr << "delete Source\n";
	}

	if (m_buffer)
	{
    	alDeleteBuffers(1, &m_buffer);
		m_buffer = 0;
		//std::cerr << "delete m_buffer\n";
	}
}

void Sound::setVolume(float volume)
{
	if(!m_source)
		return;
	
	alSourcef(m_source, AL_GAIN, volume);
}

void Sound::setPitch(float pitch)
{
	if(!m_source)
		return;
	
	alSourcef(m_source, AL_PITCH, pitch);
}

void Sound::setLooping(bool inf)
{
	if(!m_source)
		return;
	
	if (inf)
		alSourcei(m_source, AL_LOOPING, AL_TRUE);
	else
		alSourcei(m_source, AL_LOOPING, AL_FALSE);
}

void Sound::setPos(float x, float y)
{
	if(!m_source)
		return;
	
	ALfloat SourcePos[] = {x, y, 0.0f};
	alSourcefv(m_source, AL_POSITION, SourcePos);
}

void Sound::setVel(float vel_x, float vel_y)
{
	if(!m_source)
		return;
	
	ALfloat SourceVel[] = {vel_x, vel_y, 0.0f};
	alSourcefv(m_source, AL_VELOCITY, SourceVel);
}

int Sound::play()
{
	if(!m_source)
		return -1;
	
	if (m_source && m_buffer)
	{
		alSourcePlay(m_source);
		m_playing = true;
	}

}

int Sound::pause()
{
	if(!m_source)
		return -1;
	
	m_playing = false;
	if (m_source && m_buffer)
		alSourcePause(m_source);
	else
		return -1;
	return 0;
}

int Sound::stop()
{
	if(!m_source)
		return -1;
	
	m_playing = false;
	if (m_source && m_buffer)
		alSourceStop(m_source);
	else
		return -1;
	return 0;
}

bool Sound::isPlaying()
{
	return m_playing;
}

void Sound::initSounds()
{
	m_sound_sys_init_tried=true;	
	
	if(alutInit(NULL, NULL) == AL_FALSE)
	{
		std::cerr<<"alutInit(NULL,NULL) failed"<<std::endl;
		std::cerr<<alutGetErrorString(alutGetError())<<"\n";
		return;
	}	

	m_sound_sys_init_success=true;	
}
