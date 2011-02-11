#ifndef MACHINING_HPP
#define MACHINING_HPP

#include <string>

class Part;

class Machining
{
	public:
		const std::string& getName() const;	
		int getPrice() const;
		bool fitsForPart(Part& part) const;
	
		Machining();
		Machining(const std::string& filename);
		
	private:
		void load(const std::string& filename);
	
		std::string name;
		int price;
		std::string type;
};

#endif // MACHINING_HPP

