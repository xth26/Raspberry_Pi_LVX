#include"filename_lvx.h"

//读取路径中的文件
void filenameLvx::getFileNames(std::string path,std::vector<std::string>& filenames)
{
    DIR *pDir;
    struct dirent* ptr;
    if(!(pDir = opendir(path.c_str())))
        return;
    while((ptr = readdir(pDir))!=0) {
        if (strcmp(ptr->d_name, ".") != 0 && strcmp(ptr->d_name, "..") != 0)
            filenames.push_back(ptr->d_name);
    }
    closedir(pDir);
}

//比较文件名的大小
bool filenameLvx::greaterEqSort(std::string filePath1, std::string filePath2)
{
	int len1 = filePath1.length();
	int len2 = filePath2.length();
	if (len1 < len2)
	{
		return false;
	}
	else if (len1 > len2)
	{
		return true;
	}
	else
	{
		int iter = 0;
		while (iter < len1)
		{
			if (filePath1.at(iter) < filePath2.at(iter))
			{
				return false;
			}
			else if (filePath1.at(iter) > filePath2.at(iter))
			{
				return true;
			}
			++iter;
		}
	}
	return true;
}

//取出字符串中的数字
float filenameLvx::to_float(std::string s)
{
	int i = 0, n = 0;
	int point_index = s.find('.');
	float result = 0, under_0 = 0;
	if (std::count(s.begin(), s.end(), '.') > 1)
	{
		return 0; 
	}
	if (s.find('.') != -1)
	{
		if ((point_index == 0) || (point_index == s.size() - 1)) 
		{
			return 0;
		}
		for (i = 0; i <= point_index - 1; i++)
		{
			if (s[i] >= '0'&&s[i] <= '9')
			{
				result = result * 10 + s[i] - 48;
			}
		}
		for (i = s.size() - 1; i >= point_index - 1; i--)
		{
			if (s[i] >= '0'&&s[i] <= '9')
			{
				if (i == point_index - 1)
				{
					under_0 = under_0 * float(0.1) + 0;
				}
				else
				{
					under_0 = under_0 * float(0.1) + s[i] - 48;
				}
			}
		}
		result = result + under_0;
	}
	else
	{
		for (i = 0; i <= s.size() - 1; i++)
		{
			if (s[i] >= '0'&&s[i] <= '9')
			{
				result = result * 10 + s[i] - 48;
			}
		}
	}

	return result;
}

//读取文件中已有的文件，生成新的文件名
void filenameLvx::precondition(const std::string path_read, std::string &filename_lvx)
{	
	std::vector<std::string> filenames;

	DIR *pDir;
    struct dirent* ptr;
    if(!(pDir = opendir(path_read.c_str())))
        return;
    while((ptr = readdir(pDir))!=0) {
        if (strcmp(ptr->d_name, ".") != 0 && strcmp(ptr->d_name, "..") != 0)
            filenames.push_back(ptr->d_name);
    }
    closedir(pDir);

	for (size_t i = 0; i < filenames.size(); ++i)
	{
		for (size_t j = 0; j < filenames.size() - 1; ++j)
		{
			std::string filename_last = filenames[j];
			std::string filename_next = filenames[j + 1];
			if (greaterEqSort(filename_last, filename_next))
			{
				filenames[j] = filename_next;
				filenames[j + 1] = filename_last;
			}
		}
	}

	float num_filename = 0;
	if(filenames[filenames.size() - 1] == "System Volume Information")
	{
		num_filename = to_float(filenames[filenames.size() - 2]);
	}
	else
	{
		num_filename = to_float(filenames[filenames.size() - 1]);
	}
 
	int num_new = int(num_filename) + 1;
	std::string num_new_str = std::to_string(num_new);
	for (int i = 0; i < 3; ++i)
	{
		if (num_new_str.size() < 3)
		{
			num_new_str = "0" + num_new_str;
		}
	}

	filename_lvx = "SLAM" + num_new_str+".lvx";

	// std::cout << filename_lvx << std::endl;

	// std::cout << "get new lvx filename!" << std::endl;

}

//检查文件中是否有初始文件
bool filenameLvx::checkFile(const std::string path_read, const std::string filename_lvx)
{	
	std::vector<std::string> filenames;
	getFileNames(path_read,filenames);

	if(filenames.size() == 0)
	{
		return false;
	}

	//排序	
	for (size_t i = 0; i < filenames.size(); ++i)
	{
		for (size_t j = 0; j < filenames.size() - 1; ++j)
		{
			std::string filename_last = filenames[j];
			std::string filename_next = filenames[j + 1];
			if (greaterEqSort(filename_last, filename_next))
			{
				filenames[j] = filename_next;
				filenames[j + 1] = filename_last;
			}
		}
	}

	if(filenames[0] == filename_lvx)
	{
		return true;
	}
	else
	{
		return false;
	}

}