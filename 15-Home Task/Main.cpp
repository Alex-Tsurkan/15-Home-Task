#include <iostream>
#include "Chat.h"




using namespace std;


int main()
{
    setlocale(LC_ALL, "");


    Chat c;

    c.reg((char*)"Client1", (char*)"qwerty12345", sizeof("qwerty12345"));
    c.reg((char*)"Client2", (char*)"asdfg", sizeof("asdfg"));


    c.login((char*)"Client1", (char*)"qwerty12345", sizeof("qwerty12345"));
    c.login((char*)"Client2", (char*)"asdfg", sizeof("asdfg"));

    return 0;
}