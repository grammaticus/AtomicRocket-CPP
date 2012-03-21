/* 
 * File:   ship.cpp
 * Author: grammaticus
 * 
 * Created on March 19, 2012, 2:51 PM
 */

#include "ship.h"
#include <cstdlib>
using namespace std;
ship::ship() {
    this->a=-1;
    this->ev=-1;
    this->mr=-1;
    this->pTime=-1;
}

ship::ship(const ship& orig) {
}

ship::~ship() {
}