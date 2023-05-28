#include <stdio.h>
#include <iostream>
#include "sculptor.h"
#include <fstream>
#include <sstream>
#include <string>
#include <vector>

int main (void){

Sculptor *sculptor;

//int a=200, b=200, c=200;

sculptor = new Sculptor(200,200,200);
sculptor->setColor(255,0,0,0.5);
sculptor->putSphere(25,51,35,3);

sculptor->writeOFF("filedoc5.off");

return 0;
}


