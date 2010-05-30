#ifndef __COLOR_HPP
#define __COLOR_HPP

/** Color is a class that stores information of a certain color.
 * The class stores values of red, green and blue. It also stores a value of transparency, called alpha. Every color element is a float value between 0.0 and 1.0.
 */
class Color
{
	public:
		Color();
		Color(float red,float green,float blue,float alpha=1);

		float getRed()			{return m_red;}
		void setRed(float red)		{m_red=red;}
		float getGreen()		{return m_green;}
		void setGreen(float green)	{m_green=green;}
		float getBlue()			{return m_blue;}
		void setBlue(float blue)	{m_blue=blue;}
		float getAlpha()		{return m_alpha;}
		void setAlpha(float alpha)	{m_alpha=alpha;}

		void apply();

	private:
		float m_red;
		float m_green;
		float m_blue;
		float m_alpha;
};

#endif
