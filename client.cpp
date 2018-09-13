#include <iostream>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <unistd.h>
#include <string>
#include <arpa/inet.h>
#include <fstream>
#include "client.h"
typedef long long ul;
Client::Client(char* ip, char* port, char* fileName)
{
    this->ip = ip;
    this->port = atoi(port);
    this->fileName = fileName;
}
ul Client::GetFileSize(char* fileName)
{
    this->fileSize = get_file_size(fileName);
    if(fileSize <= 0)
    {
        cout << "Error" << endl;
        return -1;
    }
    cout << "file open" << endl;
    return (ul)this->fileSize;
}
void Client::StartClient()
{
    GetFileSize(fileName);
    ClientSocket = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
    SockAddr.sin_family = AF_INET;
    SockAddr.sin_port = htons(port);
    SockAddr.sin_addr.s_addr = inet_addr(ip);
    connect(ClientSocket, (struct sockaddr*)(&SockAddr), sizeof(SockAddr));
}
ul Client::SendFileSize()
{
    if(fileSize <= 0)
    {
        cout << "Can't send file, size <= 0";
        return -1;
    }
    else
    {
        ul sendBytes = (ul)send(ClientSocket, &fileSize, 4, MSG_NOSIGNAL); // отправляем размер файла
        return sendBytes;
    }
}
void Client::InfoForHuman(int time)
{
    cout << "sending size file: " << fileSize << endl;
    //cout << "begin senging file..." << endl;
    sleep(time);
}
ul Client::SendFile()
{
    if(fileSize <= 0)
    {
        return -1;
    }
    else
    {
        ifstream is(fileName, ifstream::binary); // открываем файл на чтение
        while(i != fileSize) // пока i меньше размера файла
        {
            is.seekg(i, is.beg); // размещаем указатель на i элементов от начала (читаемый файл)
            is.read(Buffer, SIZE); // вычитываем size байт
            streamsize num = is.gcount(); // узнаем вычитанные байты
            //cout << "read bytes: " << num << endl;
            num = (ul)send(ClientSocket, Buffer, num,  MSG_NOSIGNAL); // пишем в сокет из Buffer число записанных байт num
            //cout << "send bytes: " << num << endl;
            i += num; // записываем в счетчик количество отправленных байт
            cout << "send bytes: " << i << endl;
        }
        is.close();
    }
    return i;
}
void Client::StopClient()
{
    shutdown(ClientSocket, SHUT_RDWR);//закрываем соединение и клиента и сервера
    close(ClientSocket);
}
void Client::ShowSendBytes()
{
    if(i <= 0 )
    {
        cout << "nothing to send" << endl;
    }
    else
    {
        cout << "all file send bytes: " << i << endl;
    }
}
