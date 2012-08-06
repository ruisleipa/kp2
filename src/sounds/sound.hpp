#ifndef SOUND_HPP
#define SOUND_HPP

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

		bool isPlaying();

	private:
		void initSounds();

		static int m_sound_sys_ref_count;
		static bool m_sound_sys_init_tried;
		static bool m_sound_sys_init_success;

		ALuint m_buffer;		// Buffers hold sound data.
		ALuint m_source;		// Sources are points emitting sound.
		bool m_playing;
};

#endif
