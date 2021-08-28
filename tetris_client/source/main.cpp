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

    //Client c(ip, port);
    //while (1) {
    //    string request;
    //    cin >> request;
    //    string response = c.request("default", request);
    //    printf("Response: %s\n", response.c_str());
    //}
    //c.close(); 
    Consol::changeScreenSize(WIDTH, HEIGHT);
    Director* director = Bean::getDirector();
    director->run("main menu scene");

    //SingleScoreManager* ssm = Bean::getSingleScoreManager();
    //ssm->printAllObject();
    //vector<Test> v = { {3}, {3}, {3}, {2}, {2}, {2}, {1} ,{1} ,{1} };
    //cout << lower_bound(v.begin(), v.end(), 2-1)-v.begin() << endl;
}
