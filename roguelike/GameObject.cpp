/* curses */
#include <curses.h>
/* strings */
#include <string>
/* srand, rand */
#include <stdlib.h>
//^^^^copy/pasted from Ioan's example


#include <ctime>
#include <cstdlib>
#include <iostream>

using namespace std;

class GameObject
{
protected: //protected for derived classes
    int locX, locY; //coordinates
public:
    GameObject();
    ~GameObject(){}
    int getLocX();
    int getLocY();
};

int main ()
{
    /*This is all for testing/debugging*/
    srand(time(NULL));
    GameObject test;
    cout<<test.getLocX()<<endl;
    cout<<test.getLocY()<<endl;
    return 0;
}

GameObject::GameObject()
{
    locX = (rand()% 10)+1;
    locY = (rand()% 10)+1;
}

int GameObject::getLocX()
{
    return locX;
}

int GameObject::getLocY()
{
    return locY;
}
