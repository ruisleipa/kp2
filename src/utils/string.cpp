#include "string.hpp"

#include <stdint.h>

std::string convertToString(std::wstring str)
{
	std::string a;
	uint16_t val;

	for(int i=0;i<str.size();i++)
	{
		val=str[i];

		if(val<0x80)
		{
			a.push_back(str[i]);
		}
		else if(val<0x800)
		{
			uint8_t c2=(val&0x3f)|0x80;
			val>>=6;
			uint8_t c1=(val&0x1f)|0xc0;

			a.push_back(c1);
			a.push_back(c2);
		}
		else if(val<0x10000)
		{
			uint8_t c3=(val&0x3f)|0x80;
			val>>=6;
			uint8_t c2=(val&0x3f)|0x80;
			val>>=6;
			uint8_t c1=(val&0x0f)|0xe0;

			a.push_back(c1);
			a.push_back(c2);
			a.push_back(c3);
		}
	}

	return a;
}

std::wstring convertToWideString(std::string str)
{
	std::string::iterator i=str.begin();
	std::wstring result;

	int mb_lenght=0; //bytes left in a multibyte sequence
	unsigned int seq=0;
	unsigned char c;

	for(;i!=str.end();i++)
	{
		c=*i;

		if(mb_lenght)
		{
			if((c&0xc0)==0x80)
			{
				seq=seq<<6;
				seq|=c&(char)(~0xc0);
			}

			if(!(--mb_lenght))
				result.push_back(seq);

			continue;
		}

		if(c<=0x7f)
		{
			seq=c&(char)(~0x80);
			mb_lenght=0;
			result.push_back(seq);
		}
		else if(c>=0xc2 && c<=0xdf)
		{
			seq=c&(char)(~0xe0);
			mb_lenght=1;
		}
		else if(c>=0xe0 && c<=0xef)
		{
			seq=c&(char)(~0xf0);
			mb_lenght=2;
		}
		else if(c>=0xf0 && c<=0xf4)
		{
			seq=c&(char)(~0xf8);
			mb_lenght=3;
		}
	}

	return result;
}
