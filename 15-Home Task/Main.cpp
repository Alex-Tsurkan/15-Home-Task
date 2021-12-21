#include <iostream>
#include "Chat.h"




using namespace std;


int main()
{
    setlocale(LC_ALL, "");


    Chat chat;

    chat.reg((char*)"Client1", (char*)"987654", sizeof("987654"));
    chat.reg((char*)"Client2", (char*)"alex-123456", sizeof("alex-123456"));


    chat.login((char*)"Client1", (char*)"987654", sizeof("987654"));
    chat.login((char*)"Client2", (char*)"alex-123456", sizeof("alex-123456"));

    return 0;
}