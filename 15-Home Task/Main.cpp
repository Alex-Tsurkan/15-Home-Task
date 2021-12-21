#include <iostream>
#include "Chat.h"




using namespace std;


int main()
{
    setlocale(LC_ALL, "");


    Chat c;

    c.reg((char*)"Client1", (char*)"987654", sizeof("987654"));
    c.reg((char*)"Client2", (char*)"alex-123456", sizeof("alex-123456"));


    c.login((char*)"Client1", (char*)"987654", sizeof("987654"));
    c.login((char*)"Client2", (char*)"alex-123456", sizeof("alex-123456"));

    return 0;
}