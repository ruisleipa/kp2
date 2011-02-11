#ifndef PARTMODEL_HPP
#define PARTMODEL_HPP

#include <string>

class PartModelImplementation;

class PartModel
{
	public:
		const std::string& getName() const;	
		int getPrice() const;		
		const std::string& getType() const;	
		float getWeight() const;
						
		PartModel();
		PartModel(const std::string& filename);
		~PartModel();
		
	private:
		void load(const std::string& filename);

		int price;
		std::string type;
		float weight;
		
		PartModelImplementation* partModelImplementation;
	
};

#endif // PARTMODEL_HPP

