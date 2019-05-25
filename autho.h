#include <iostream>
#include <string>
#include <fstream>
#include <cstring>
#pragma warning(disable:4996)

using namespace std;

//struct logpass
//{
//string log;
//string pass;
//string whoami;
//};

fstream open_file_check();
void parsing_check(char *buff, const char *a, string *plog, string *ppass, string *pwhoami);

