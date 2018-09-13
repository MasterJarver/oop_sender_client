#include <iostream>
#include <string>
#include <fstream>
#include "getfilesize.h"
using namespace std;
//typedef unsigned long long ul;
long long get_file_size(string filename)
{
    ifstream is(filename.c_str(), ifstream::binary); // открываем файл на чтение
    if(!is)
    {
        cout << "Error Open File" << endl;
        return -2;
    }
    else
    {
        is.seekg (0, is.end); // размещаем указатель в конец
        const long long size = (long long)is.tellg(); // узнаем размер файла
        is.close(); // закрываем файл на чтение
        return size; // возврааем размер
    }
}
