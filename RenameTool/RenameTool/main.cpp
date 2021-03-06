#include <iostream>
#include <windows.h>
#include <vector>
#include <string>
#include <map>

void findFiles(const char * pathName, std::vector<std::string>& files, std::vector<std::string> patterns)
{
	WIN32_FIND_DATAA FindFileData;
	HANDLE hFind = INVALID_HANDLE_VALUE;
	CHAR PathBuffer[_MAX_PATH];

	strcpy_s(PathBuffer, _MAX_PATH, pathName);
	if (pathName[strlen(pathName) - 1] != '/')
	{
		strcat_s(PathBuffer, _MAX_PATH, "/*");
	}
	else
	{
		strcat_s(PathBuffer, _MAX_PATH, "*");
	}

	hFind = FindFirstFileA(PathBuffer, &FindFileData);
	// 如果找不到文件夹就直接返回
	if (INVALID_HANDLE_VALUE == hFind)
	{
		return;
	}
	while (::FindNextFileA(hFind, &FindFileData))
	{
		// 过滤.和..
		if (strcmp(FindFileData.cFileName, ".") == 0
			|| strcmp(FindFileData.cFileName, "..") == 0)
		{
			continue;
		}

		// 构造完整路径
		std::string fullname = std::string(pathName) + "/" + std::string(FindFileData.cFileName);
		if (FindFileData.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY)
		{
			findFiles(fullname.c_str(), files, patterns);
		}
		else
		{
			int patternCount = patterns.size();
			for (int i = 0; i < patternCount; ++i)
			{
				if (fullname.length() >= patterns[i].length() && fullname.substr(fullname.length() - patterns[i].length(), patterns[i].length()) == patterns[i])
				{
					files.push_back(fullname);
				}
			}
		}
	}
	::FindClose(hFind);
}

std::string intToString(int i, int limitLen = 0)
{
	char str[256];
	sprintf_s(str, 256, "%d", i);
	std::string retString(str);
	int addLen = limitLen - strlen(str);
	if (addLen > 0)
	{
		char addStr[256];
		memset(addStr, 0, 256);
		for (int j = 0; j < addLen; ++j)
		{
			addStr[j] = '0';
		}
		retString = std::string(addStr) + retString;
	}

	return retString;
}

static void rightToLeft(std::string& str)
{
	int pathLength = str.length();
	for (int i = 0; i < pathLength; ++i)
	{
		if ('\\' == str[i])
		{
			str[i] = '/';
		}
	}
}

static std::string getParentDir(std::string dir)
{
	rightToLeft(dir);
	int pos = dir.find_last_of('/');
	std::string tempDir = dir;
	if (-1 != pos)
	{
		tempDir = dir.substr(0, pos);
	}
	return tempDir;
}

static std::string getFileName(std::string str)
{
	rightToLeft(str);
	int dotPos = str.find_last_of('/');
	if (dotPos != -1)
	{
		return str.substr(dotPos + 1, str.length() - 1);
	}
	return str;
}

static std::string getFileSuffix(std::string fileName)
{
	int dotPos = fileName.find_last_of('.');
	if (dotPos != -1)
	{
		return fileName.substr(dotPos, fileName.length() - dotPos);
	}
	return fileName;
}

static int stringToInt(const std::string& str)
{
	return atoi(str.c_str());
}

static void reorderList(std::vector<std::string>& fileList)
{
	std::map<int, std::string> reorderFiles;
	int fileCount = fileList.size();
	for (int i = 0; i < fileCount; ++i)
	{
		int lastUnderLine = fileList[i].find_last_of('_');
		int lastDot = fileList[i].find_last_of('.');
		std::string numberSuffix = fileList[i].substr(lastUnderLine + 1, lastDot - lastUnderLine - 1);
		int index = stringToInt(numberSuffix);
		reorderFiles.insert(std::make_pair(index, fileList[i]));
	}
	fileList.clear();
	std::map<int, std::string>::iterator iter = reorderFiles.begin();
	std::map<int, std::string>::iterator iterEnd = reorderFiles.end();
	for (; iter != iterEnd; ++iter)
	{
		fileList.push_back(iter->second);
	}
}

void main()
{
	std::cout << "是否再次重命名?(y/n)";
	char re = 'n';
	std::cin >> re;
	std::vector<std::string> fileList;
	std::vector<std::string> patterns;
	patterns.push_back(".png");
	findFiles("./", fileList, patterns);

	char autoRename = 'n';
	std::string preName;
	if (re == 'y')
	{
		std::cout << "是否自动重命名?(y/n)";
		std::cin >> autoRename;
	}
	if (re != 'y' || autoRename != 'y')
	{
		std::cout << "文件前缀:";
		std::cin >> preName;
	}
	int fileCount = fileList.size();
	if (fileCount > 0 && autoRename == 'y')
	{
		std::string fileName = getFileName(fileList[0]);
		preName = fileName.substr(0, fileName.find_last_of('_') + 1);
	}

	// 根据后缀数字重新排列文件
	if (re == 'y')
	{
		reorderList(fileList);
	}

	// 重命名文件
	fileCount = fileList.size();
	for (int i = 0; i < fileCount; ++i)
	{
		std::string fileDir = getParentDir(fileList[i]);
		std::string newName = preName + intToString(i + 1) + getFileSuffix(fileList[i]);
		rename(fileList[i].c_str(), (fileDir + "/" + newName).c_str());
	}
}