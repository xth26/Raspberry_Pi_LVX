#ifndef FILENAME_LVX_H_
#define FILENAME_LVX_H_

//头文件
#include <iostream>
#include <sys/types.h>
#include <dirent.h>
#include <vector>
#include <string.h>

#include <bits/stdc++.h>   //std::count()


class filenameLvx
{
private:
	bool greaterEqSort(std::string filePath1, std::string filePath2);
	float to_float(std::string s);
	void getFileNames(std::string path,std::vector<std::string>& filenames);
public:
	void precondition(const std::string path_read, std::string &filename_lvx);
	bool checkFile(const std::string path_read, const std::string filename_lvx);
};

#endif //FILENAME_LVX_H_