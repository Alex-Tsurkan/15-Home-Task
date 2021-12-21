#pragma once

#include "sha1.h"
#include "string.h"

#define SIZE 10
#define LOGINLENGTH 10

class Chat {
public:
    Chat();
    ~Chat();
    void reg(char _login[LOGINLENGTH], char _pass[], int pass_length);
    bool login(char _login[LOGINLENGTH], char _pass[], int pass_length);

   


private:
      
    enum AuthDataStatus {
        free,
        engaged,
        deleted
    };


    struct AuthData {
        AuthData() :
            login(""),
            pass_sha1_hash(0),
            status(AuthDataStatus::free) {
        }
        ~AuthData() {
            if (pass_sha1_hash != 0)
                delete[] pass_sha1_hash;
        }
        AuthData(char _login[LOGINLENGTH], uint* sh1) {
            strcpy_s(login, _login);
            pass_sha1_hash = sh1;
            status = AuthDataStatus::engaged;
        }
        AuthData& operator = (const AuthData& other) {
            strcpy_s(login, other.login);

            if (pass_sha1_hash != 0)
                delete[] pass_sha1_hash;
            pass_sha1_hash = new uint[SHA1HASHLENGTHUINTS];

            memcpy(pass_sha1_hash, other.pass_sha1_hash, SHA1HASHLENGTHBYTES);

            status = other.status;

            return *this;
        }
        char login[LOGINLENGTH];
        uint* pass_sha1_hash;
        AuthDataStatus status;
    };

    void reg_resize(char _login[LOGINLENGTH], uint* hash);
    void resize();
    int hash_func(char login[LOGINLENGTH], int offset);

    AuthData* array;
    int mem_size;
    int Auth_count;
};