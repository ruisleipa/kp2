#ifndef SOUNDS_HPP
#define SOUNDS_HPP

class Sounds
{
	public:
		static Sounds& getInstance();

		void printSoundInfo();

		bool wasInit()	{return Sounds::m_was_init;}

		~Sounds();

	protected:
		Sounds();
		Sounds(const Sounds&);
		Sounds& operator=(const Sounds&);

	private:
		bool m_was_init;
};

#endif // SOUNDS_HPP
