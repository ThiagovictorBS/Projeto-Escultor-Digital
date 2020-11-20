#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include "sculptor.h"

using namespace std;

char* teste = "filename.off";

int main()
{
    Sculptor a(5,5,5);
    cout <<"deu certo at aq 1 " << "\n";
    a.setColor(230,0,050,0.5);
    cout <<"deu certo at aq 2" << "\n";
    a.putBox(0,0,0,3,4,5);
    a.putBox(2,0,0,4,0,0);
    cout <<"deu certo at aq 3" << "\n";
    a.writeOFF(teste);
    cout <<"deu certo at aq 4" << "\n";
    return 0;
}
