#include <iostream>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <unistd.h>
#include <string>
#include <arpa/inet.h>
#include <fstream>
#include "client.h"
using namespace std;
int main(int argc, char* argv[])
{
    if(argc != 4)
    {
        cout << "Invalid arguments, need 3" << endl;
        return 1;
    }
    Client client(argv[1], argv[2], argv[3]);
    client.StartClient();
    client.SendFileSize();
    client.InfoForHuman(3);
    client.SendFile();
    client.StopClient();
    client.ShowSendBytes();
    return 0;
}
