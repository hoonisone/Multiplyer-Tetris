#include <stdio.h>
#include <stdlib.h>
#include <WinSock2.h>
#include "client.h"
#include "bean.h"
#include "Uuid.h"

string ip = "127.0.0.1";
int port = 5000;

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
    //Consol::setCursorFlag(false);
    //Bean::getDirector()->run("main menu");
    //UIElement* element1 = Bean::getUIElement(0, 0, 20, 5, "", 3, 3);
    //UIElement* element2 = new UIElement(5, 5, 20, 5, "", 3, 3);
    //UIElement* element3 = new UIElement(0, 0, 20, 5, "hello");
    //UIElement* element4 = new UIElement(0, 4, 20, 5, "hello");
    //UIElement* element5 = new UIElement(0, 8, 20, 5, "hello");
    //element1->enroll(element2, 0, 0);
    //element2->enroll(element3, 0, 0);
    //element2->enroll(element4, 0, 1);
    //element2->enroll(element5, 0, 2);
    int x = WIDTH / 2;
    int y = 10;
    int w = 20;
    int h = 5;
    UIElement* element1 = Bean::getUIVerticalTextListElement(x- w/2, y, w, h, { "a" , "b", "c", "d"});
    

    //UIElement* element121 = new UIElement(0, 5, 10, 5, "hello");
    //UIElement* element122 = new UIScannerBlock(10, 5, 10, 5, new ScannerCreator());
    //element12->enroll(element121, 0, 0);
    //element12->enroll(element122, 1, 0);

    element1->draw();
    while (true) {
		Key key = Input::getKey();
		if (key != -1){
			element1->keyInputHandler(key);
            if (element1->endCheck())
                break;
        }
	}
    cout << element1->getSelectedElement()->getName();
    cout << element1->getState()[0].second;
}
