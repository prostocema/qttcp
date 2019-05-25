#include "autho.h"

#include <iostream>
#include <string>
#include <fstream>
#include <cstring>
#pragma warning(disable:4996)

using namespace std;

struct logpass
{
string log;
string pass;
string whoami;
};

fstream open_file_check()
{
fstream a;
a.open("D:\\Uchiha\\qt\\works\\parcing\\db.json", ios::binary | ios::in);
return a;
}

void parsing_check(char *buff, const char *a, string *plog, string *ppass, string *pwhoami)
{
char * transfer;
int i = 0;
string log;
string pass;
string whoami;

transfer = strtok(buff, a);

while (transfer != NULL)
{
i++;
transfer = strtok(NULL, "\"");

if (i == 3)
(*plog) = transfer;
else if (i == 7)
(*ppass) = transfer;
else if (i == 11)
(*pwhoami) = transfer;
}
}

int main()
{
setlocale(LC_ALL, "Russian");
fstream file;

char buff[256];
string log, pass;

logpass user;

file = open_file_check();
if (!file.is_open()) {

return 0;
}

cin>>log;
cin>>pass;
cout<<"\n";

//парсинг файла с логинами

 while (file.getline(buff, 256))
{

if (buff[0] == '{' || buff[0] == '}')
continue;

parsing_check(buff, "\"", &user.log, &user.pass, &user.whoami);

if (log == user.log && pass==user.pass)
{
cout << user.whoami<<"\n";

break;
}
}

file.close();

system("pause");
return 0;
}
