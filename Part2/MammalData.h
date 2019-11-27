//
// Created by euro on 2017-12-10.
//

#ifndef CPPVERSION1_MAMMALDATA_H
#define CPPVERSION1_MAMMALDATA_H


#include <fstream>
#include "Location.h"

/*
 * This is a simple class to represent mammal data - location and type
 */
class MammalData {

private:
    Location location =  Location(0,0);
    char mammalType;

public:
    MammalData(Location l , char t);
    char getMammalType(){return mammalType;}
    Location getLocation(){ return  location;}

};


#endif //CPPVERSION1_MAMMALDATA_H
