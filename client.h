#ifndef CLIENT_H
#define CLIENT_H
#include "getfilesize.h"
#include <string>
using namespace std;
typedef long long ul;
class Client
{
private:
    const static int SIZE = 1024;
    const static int WHENCE = 1024;
    char* ip; // ip сервера
    int port; // порт сервера
    char* fileName; // имя файла для передачи
    ul num = 0; // размервычитанных и записанных байт
    ul fileSize = 0; // размер файла
    ul i = 0; // счетчик байтов
    struct sockaddr_in SockAddr; // структура для задания пары IP port
    char Buffer[SIZE]; // буфер
    int ClientSocket = 0; // сокет клиента
    ul GetFileSize(char* fileName); // возвращает размер файла
public:
    Client(char* ip, char* port, char* fileName); // конструктор ip port fileName
    void StartClient(); // биндим сокет клиента и коннектимся с серверным
    ul SendFileSize(); // отправляем размер файла
    void InfoForHuman(int time); // вывод размера в байтах для хумана
    ul SendFile(); // отправка файла на сервер
    void StopClient(); // разрыв соединения и закрытие дескриптора
    void ShowSendBytes(); // выводит количество отправленных байт
};
#endif // CLIENT_H
