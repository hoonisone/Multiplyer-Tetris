#include <stdio.h>
#include <stdlib.h>
#include <WinSock2.h>
#include "client.h"
#include "bean.h"
#include "Uuid.h"
#include <algorithm>

string ip = "127.0.0.1";
int port = 5000;

using namespace std;
int main(int argc, char* argv[])
{

    Consol::changeScreenSize(WIDTH, HEIGHT);
    Consol::setCursorFlag(false);

    Director* director = Bean::getDirector();
    director->run("main menu scene");

}
/*

*/