#ifndef __SOUND_HPP
#define __SOUND_HPP

#include <AL/al.h>
#include <AL/alc.h>
#include <AL/alut.h>
#include <string>

class Sound
{
	public:
		Sound();
		~Sound();
		int load(std::string);
		void unload();

		int play();			// loop until stopped
		int pause();
		int stop();

		void setPos(float,float);
		void setVel(float,float);
		void setVolume(float);
		void setPitch(float);
		void setLooping(bool);

	private:

		bool m_was_core_init;

		ALuint m_buffer;		// Buffers hold sound data.
		ALuint m_source;		// Sources are points emitting sound.
		bool m_playing;
};

#endif
