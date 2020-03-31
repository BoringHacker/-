#include <iostream>
#include <stdlib.h>
#include <windows.h>
#include <fstream>
#include <stdio.h>
#include <vector>
#include <string>
#include <string>
#include <string.h>
#pragma comment (lib, "winmm.lib")
using namespace std;

vector < string > ShowFileList(string filename) {
	WIN32_FIND_DATAA p;
	vector<string> filelist;
	HANDLE h = FindFirstFileA(filename.c_str(), &p);
	filelist.push_back(p.cFileName);
	while (FindNextFileA(h, &p)) {
		filelist.push_back(p.cFileName);
		if (filelist.back() == "." || filelist.back() == "..") {
			filelist.pop_back();
		}
	}
	vector < string > result;
	for (int i = 0; i < filelist.size(); i++) {
		result.push_back(filelist[i]);
	}
	return result;
}

void ShowLastFileList(string & filepath) {
	string filepath2 = filepath;
	string tmp = "../";
	tmp += filepath2;
	filepath = tmp;
	ShowFileList(tmp);
}
void ShowSelectFileList(string filepath) {
	string yourchoose;
	cin >> yourchoose;
	yourchoose += '/';
	string filepath2 = filepath;
	yourchoose += filepath2;
	ShowFileList(yourchoose);
}
vector < string > case4(string filepath, string filename) {
	filename += '/';
	filename += filepath;
	return ShowFileList(filename);
}
void MainMenu() {
	printf("说明：\n");
	printf("批量重命名，格式为前缀名+数字标号+后缀名+文件格式\n");
	printf("如果不需要前缀名/后缀名/文件格式那么输入*即可\n");
	printf("作者：BoringHacker(部分代码来自网络)\n");
	printf("网站：https://boringhacker.github.io\n");
}
string check(string str) {
	return str == "*" ? "\0" : str;
}
int main() {
	vector < string > files;
	string filepath;
	string filename;
	string prefixName;
	string suffixName;
	string mssuffix;
	string msfeature;
	int count = 0;
	string filePath = filepath;
	
	MainMenu();
	system("pause");
	system("CLS");
	printf("输入文件夹位置\n");
	cin >> filename;
	printf("输入文件名前缀\n");
	cin >> prefixName;
	printf("输入数字标号从哪里开始\n");
	cin >> count;
	printf("输入数字后的文件名后缀\n");
	cin >> suffixName;
	printf("输入重命名限定的文件格式，如果没有，输入*\n");
	cin >> mssuffix;
	filepath = "*."+ mssuffix;
	system("CLS");
	
	for (int i = 0; i < (int)filename.size(); ++i)
		if (filename[i] == '\\' && filename[i + 1] == '\\') {
			msfeature = "\\";
			break;
		}
		else if (filename[i] == '\\') {
			msfeature = "\\";
			break;
		}
		else if (filename[i] == '/') {
			msfeature = '/';
			break;
		}
	
	files = case4(filepath, filename);
	system("pause");
	system("CLS");
	count--;
	
	for (string printer : files) {
		string oldName = filename + msfeature + printer;
		string newName = filename + msfeature + check(prefixName) + to_string(count) + check(suffixName) + "." + (mssuffix != "*" ? mssuffix : printer.substr(printer.find_last_of('.') + 1));
		rename(oldName.c_str(), newName.c_str());
		++count;
	}
	
	printf("重命名完成\n"); 
	system("pause");
	return 0;
}
