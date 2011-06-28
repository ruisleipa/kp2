#include "widgetloader.hpp"

#include <fstream>
#include <iostream>

#include "widgetfactory.hpp"

#include "layoutcontainer.hpp"
#include "freecontainer.hpp"
#include "scrollbox.hpp"

static bool is_in_string(char c, std::string str)
{
	return str.find(c) != std::string::npos;
}

void printNodes(WidgetNode& node, int indent = 0)
{
	for(int i = 0; i < indent; i++)
	{
		std::cout << '\t';
	}
	
	std::cout << node.type << std::endl;
	
	std::vector<WidgetNode>::iterator i;
		
	for(i = node.children.begin(); i != node.children.end(); ++i)
	{
		printNodes(*i, indent + 1);
	}
}

void WidgetLoader::load(const std::string& filename)
{
	std::ifstream file(filename.c_str(),std::ios_base::in);
	
	if(!file.good())	
	{
		throw std::runtime_error("Cannot open file \"" + filename + "\" for reading.");
	}
	
	std::string line;
	
	std::stack<WidgetNode*> parent;
	
	std::vector<WidgetLine> lines;
	
	while(getline(file,line))
	{
		if(!line.length())
			continue;
			
		if(line.at(0) == '#')
			continue;	
	
		WidgetLine widgetLine = parseLine(line);	

		lines.push_back(widgetLine);
	}
	
	file.close();	
	
	WidgetNode rootNode;
	
	if(!lines.size())
		return;
		
	std::vector<WidgetLine>::iterator i;
		
	
	rootNode.type = lines[0].type;
	rootNode.attributes = lines[0].attributes;	
	
	lines.erase(lines.begin());
	
	convertWidgetLines(rootNode, lines);
	
	createWidgets(rootNode);
}

Widget& WidgetLoader::getRootWidget()
{
	return *(widgets.at(0));
}

void WidgetLoader::convertWidgetLines(WidgetNode& parentNode, std::vector<WidgetLine> lines)
{
	std::vector<WidgetLine>::iterator i;

	int level = 0;
	
	i = lines.begin();
		
	while(i != lines.end())
	{
		WidgetLine& line = *i;
	
		if(level == 0)
			level = line.level;
		
		if(line.level == level)
		{
			WidgetNode node;
			
			node.type = line.type;
			node.attributes = line.attributes;
			
			parentNode.children.push_back(node);
			
			++i;
		}
		else
		{			
			std::vector<WidgetLine> childLines;
			
			while(i != lines.end() && i->level > level)
			{
				childLines.push_back(*i);
				
				++i;
			}				
			
			convertWidgetLines(parentNode.children.back(), childLines);
		}		
	}
}

WidgetLine WidgetLoader::parseLine(std::string line)
{
	WidgetLine widgetLine;
	
	while(line.at(0) == '\t')
	{
		widgetLine.level++;
		
		line.erase(0, 1);
	}
	
	widgetLine.type = line.substr(0, line.find(' '));
	
	std::string attributes = line.substr(line.find(' ') + 1);
	
	widgetLine.attributes = parseAttributes(attributes);
	
	return widgetLine;
}

enum AttributeParseState
{
	NAME,
	SKIP_UNTIL_VALUE,
	VALUE,
	ESCAPED,
	SKIP_UNTIL_NAME
};

IniFile WidgetLoader::parseAttributes(std::string line)
{
	IniFile attributes;
	
	std::string key = "";
	std::string value = "";
	
	std::string::iterator i;		
	
	AttributeParseState state = NAME;
	
	for(i = line.begin(); i != line.end(); ++i)
	{
		char c = *i;
	
		if(state == NAME)
		{
			if(is_in_string(c, " ="))
				state = SKIP_UNTIL_VALUE;
			else
				key.push_back(c);
		}
		else if(state == SKIP_UNTIL_VALUE)
		{
			if(is_in_string(c, "\""))
				state = VALUE;
		}
		else if(state == VALUE)
		{
			if(is_in_string(c, "\\"))
			{
				state = ESCAPED;
			}
			else if(is_in_string(c, "\""))
			{
				attributes.setValue(key, value);
				
				key = "";
				value = "";
			
				state = SKIP_UNTIL_NAME;
			}
			else
			{
				value.push_back(c);
			}
		}
		else if(state == ESCAPED)
		{
			char character;
		
			switch(c)
			{
				case 'n':
					character = '\n';
					break;
				default:
					character = c;
					break;							
			}
			
			value.push_back(character);
			
			state = VALUE;
		}
		else if(state == SKIP_UNTIL_NAME)
		{				
			if(c != ' ')
			{
				key.push_back(c);
			
				state = NAME;
			}
		}
	}

	return attributes;
}

Widget* WidgetLoader::createWidgets(WidgetNode& rootNode)
{
	WidgetFactory widgetFactory;
	
	std::tr1::shared_ptr<Widget> widget(widgetFactory.build(rootNode));
	
	widgets.push_back(widget);
	
	Widget* container = widget.get();
	
	std::vector<WidgetNode>::iterator i;

	for(i = rootNode.children.begin(); i != rootNode.children.end(); ++i)
	{
		Widget* widget = createWidgets(*i);
		
		if(!widget)
			continue;
		
		if(dynamic_cast<LayoutContainer*>(container))
			addWidgetToContainer(dynamic_cast<LayoutContainer*>(container), widget, i->attributes);
		if(dynamic_cast<FreeContainer*>(container))
			addWidgetToContainer(dynamic_cast<FreeContainer*>(container), widget, i->attributes);
		if(dynamic_cast<ScrollBox*>(container))
			addWidgetToContainer(dynamic_cast<ScrollBox*>(container), widget, i->attributes);
	}
	
	return widget.get();
}

void WidgetLoader::addWidgetToContainer(LayoutContainer* container, Widget* widget, const IniFile& attributes)
{
	std::string width = attributes.getValueWithDefault("width", "auto");
	std::string height = attributes.getValueWithDefault("height", "auto");
	
	container->addWidget(*widget, width, height);
}

void WidgetLoader::addWidgetToContainer(FreeContainer* container, Widget* widget, const IniFile& attributes)
{
	std::string left = attributes.getValueWithDefault("left", "0px");
	std::string top = attributes.getValueWithDefault("top", "0px");
	std::string width = attributes.getValueWithDefault("width", "auto");
	std::string height = attributes.getValueWithDefault("height", "auto");
	
	container->addWidget(*widget, left, top, width, height);
}

void WidgetLoader::addWidgetToContainer(ScrollBox* container, Widget* widget, const IniFile& attributes)
{
	std::string width = attributes.getValueWithDefault("width", "auto");
	std::string height = attributes.getValueWithDefault("height", "auto");
	
	container->addWidget(*widget, width, height);
}

WidgetLoader::WidgetLoader(const std::string& filename)
{
	load(filename);
}
