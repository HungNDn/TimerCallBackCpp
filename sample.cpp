#include <iostream>
#include "timercpp.h"

using namespace std;

void hello()
{
    cout << "Hello World" << endl;
}

int main() {
    Timer t;
    void (*ptr)() = &hello;
    t.setInterval(ptr, 1000);
    t.stop();
   // t.setTimeout(ptr,3200);
    cout <<"End"<< endl;
    while(true); // Keep mail thread active
    //cout <<"End"<< endl;
}
