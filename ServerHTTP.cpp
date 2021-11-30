#define _WINSOCK_DEPRECATED_NO_WARNINGS
#include <iostream>
#include <WinSock2.h>
#include <WS2tcpip.h>
#include <string>
#include <cmath>
#include <fstream>

using namespace std;

#pragma comment(lib, "ws2_32.lib")

SOCKET sock;

void AttesaConnessione();
char LetturaFileHTML(string path);
void Engine();
string TipoMetodoRequest(string request);
string* SalvaRigaInArray(string request, int& arr_size);
string* SalvaRequestInArray(string request, int& arr_size);


int main() {

    AttesaConnessione();
    Engine();



    //tipo di response
    //char mess[] = "HTTP/1.1 200\r\nContent-Type:text/html\r\n\r\n<!DOCTYPE html><head><title>Document</title></head><body><p>ciao</p></body></html>";







}

void AttesaConnessione() {

    WSADATA wsa;
    WSAStartup(MAKEWORD(2, 2), &wsa);
    SOCKET s = socket(AF_INET, SOCK_STREAM, 0);
    sockaddr_in server, client;
    server.sin_family = AF_INET;
    server.sin_addr.s_addr = INADDR_ANY;
    server.sin_port = htons(80);
    bind(s, (sockaddr*)&server, sizeof(server));
    listen(s, 1);
    sockaddr_in from;
    int fromlen = sizeof(from);

    cout << ">> Attesa nuove connessioni..." << endl;
    sock = accept(s, (sockaddr*)&from, &fromlen);
    cout << ">> Nuova connessione!" << endl;

    Sleep(1000);
}

void Engine() {

    char buff[4096] = { 0 }; int arr_size = 0;

    while (true) {

        int risp = recv(sock, buff, 4096, 0);
        string request = string(buff);

        if (risp > 0) {

            if (TipoMetodoRequest(request) == "GET") {
                string* arr = SalvaRequestInArray(request, arr_size);

                int n = 0; 
                string *ahoi = SalvaRigaInArray(arr[5], n);

               

            }
            else if (TipoMetodoRequest(request) == "POST") {

            }

        }

       


    }

}

string TipoMetodoRequest(string request) {

    if (request.substr(0, 3) == "GET") return "GET";
    if (request.substr(0, 4) == "POST") return "POST";

    return "null";

}

string* SalvaRigaInArray(string request, int& arr_size) {

    static string riga[20]; int start = 0, end = 0;

    for (int cont = 0; cont <= request.length(); cont++) {
        if (request[cont] == ' ' || cont == request.length()) {
            riga[arr_size] = request.substr(start, end);
            start = cont + 1;
            end = 0;
            arr_size++;
        }
        else {
            end++;
        }
    }


    return riga;


}

string* SalvaRequestInArray(string request, int& arr_size) {

    static string arr[4096]; int start = 0, end = 0;

    for (int cont = 0; cont <= request.length(); cont++) {

        if (request[cont] == '\r' && request[cont + 1] == '\n') {
            arr[arr_size] = request.substr(start, end);
            start = cont + 2;
            end = 0;
            arr_size++;
            cont++;
        }
        else {
            end++;
        }

    }

    return arr;
}

char LetturaFileHTML(string path) {

    return 'c';

}