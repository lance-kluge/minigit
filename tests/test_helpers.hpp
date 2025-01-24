#ifndef TEST_H__
#define TEST_H__
#include <string>
#include <iostream>
#include <fstream>
#include <array>
#include "../code_1/hash.hpp"
#include "../code_1/miniGit.hpp"

using namespace std;

// TODO add detailed explanation on what the function should do
std::string exec(const char* cmd);
std::string readFileIntoString(std::string fileName);
string test_insert(string arr[], int len, int tabSize);
string test_MiniGit_Add(string files[], int len);
string test_MiniGit_RM(string files[], int len, string rmFiles[], int rmLen);
string test_MiniGit_GetSourcePath(string files[], int versions[], int len);
string test_MiniGit_isFileChanged(string file1, string file2);
void setValue(MiniGit *g, string path, string val, string msg);
void readValue(string path);
string test_MiniGit_Commit(string file1, string commitName);
string test_MiniGit_SEARCH();
string test_MiniGit_CHECKOUT();
string test_MiniGit_CommitExtended(string file1, string commitName, string file2);

#endif // TEST_H__