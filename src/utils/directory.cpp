#include "directory.hpp"

#include <cstdio>
#include <sys/types.h>
#include <dirent.h>

#include <iostream>

std::vector<std::string> readDirectory(std::string path,std::string ext)
{
	std::vector<std::string> list;

	DIR* dir;
	struct dirent* ent;

	dir = opendir(path.c_str());

	if(dir)
	{
		while((ent = readdir(dir)))
		{
			std::string str = ent->d_name;

			if(!str.compare(".") || !str.compare(".."))
			{
				continue;
			}

			if(ext != "" && ext.size() > str.size())
			{
				continue;
			}

			if(ext != "" && ext.compare(str.substr(str.size() - ext.size())))
			{
				continue;
			}

			list.push_back(str);
		}

		closedir(dir);

		return list;
	}

	std::cout << "Cannot open the directory \"" << path << "\"" << std::endl;

	return list;

}
