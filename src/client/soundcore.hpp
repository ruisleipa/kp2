#ifndef __SOUNDCORE_HPP
#define __SOUNDCORE_HPP

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

#endif // __SOUNDCORE_HPP
