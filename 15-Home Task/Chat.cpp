#include "Chat.h"
#include "iostream"
#include "string.h"

Chat::Chat() {
    Auth_count = 0;
    mem_size = 8;
    array = new AuthData[mem_size];
}




Chat::~Chat() {
    delete[] array;
}



// ф-ция регистрации нового пользователя
void Chat::reg(char _login[LOGINLENGTH], char _pass[], int pass_length) 
{
    uint* hash = sha1(_pass, pass_length);

    int index, i = 0;

    for (; i < mem_size; i++) 
    {
        index = hash_func(_login, i * i);
        if (array[index].status == AuthDataStatus::free)
        {
            break;
        }
    }
    if (i >= mem_size)
    {
        resize();
        reg(_login, _pass, pass_length);
    }
    else {
        array[index] = AuthData(_login, hash);
        Auth_count++;
    }
}



// булевская ф-ция авторизации
bool Chat::login(char _login[LOGINLENGTH], char _pass[], int pass_length) 
{
    int index, i = 0;

    for (; i < mem_size; i++) 
    {
        index = hash_func(_login, i * i);
        if (array[index].status == AuthDataStatus::free)
        {
            return false;
        }
        else if (array[index].status == AuthDataStatus::engaged && !memcmp(_login, array[index].login, LOGINLENGTH))
        {
            break;
        }
    }
    if (i >= mem_size)
    {
        return false;
    }

    uint* hash = sha1(_pass, pass_length);

    bool cmpHashes = !memcmp(array[index].pass_sha1_hash, hash, SHA1HASHLENGTHBYTES);
    delete[] hash;

    return cmpHashes;
}



// вспомагательная функция для изменения размера внутреннего массива: 
// регистрация по новой пользователей после увеличения размера массива
void Chat::reg_resize(char _login[LOGINLENGTH], uint* hash)
{
    
    int index, i = 0;

    for (; i < mem_size; i++)
    {
        index = hash_func(_login, i * i);
        if (array[index].status == AuthDataStatus::free)
        {
            break;
        }
    }
    if (i >= mem_size)
    {
        resize();
        reg_resize(_login, hash);
    }
    else {
        array[index] = AuthData(_login, hash);
        Auth_count++;
    }
}



// изменение размера внутреннего массива
void Chat::resize() 
{
    std::cout << "resize()" << endl;
    AuthData* save = array;
    int save_ms = mem_size;

    mem_size *= 2;
    Auth_count = 0;

    for (int i = 0; i < save_ms; i++) 
    {
        AuthData& old_data = save[i];
        if (old_data.status == AuthDataStatus::engaged) 
        {
            uint* hash2 = new uint[SHA1HASHLENGTHUINTS];
            memcpy(hash2, old_data.pass_sha1_hash, SHA1HASHLENGTHBYTES);

            reg_resize(old_data.login, hash2);
        }
    }
    delete[] save;
}



//хеш-функция
int Chat::hash_func(char login[LOGINLENGTH], int step) {
    long sum = 0;
    for (int i = 0; i < LOGINLENGTH; i++) {
        sum += login[i];
    }
    int f2 = mem_size * (0.7 * sum - int(0.7 * sum));

    return (f2 + step) % mem_size;
}