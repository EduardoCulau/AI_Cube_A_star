#include "cube.h"

using namespace ai;

Cube *Cube::_instance = 0;

void Cube::InitialCube (size_t size, size_t percentage){
    get()->setSize(size);
    get()->setPercent(percentage);
    get()->createCube();
    get()->fillObstructionsCube();
}


void Cube::createCube(){
    /* Create the cube and put all positions to false*/
    for(i = 0; i < get->getSize(); i++){
        get()->_cube[0][0][i] = false;
    }

    for(j = 1; j < get->getSize(); j++){
        get()->_cube[0][j] = get->_cube[0][0];
    }

    for(k = 1; k < get->getSize(); k++){
        get()->_cube[k] = get->_cube[0];
    }
}

void Cube::fillObstructionsCube(){
    /* Fill the cube with the obistructions */
    int x, y, z;
    size_t obstrct = 0; 
    size_t obstMax = (size_t) std::ceil( std::pow( (float) get()->getSize(), 3) * ((float) get()->getPercent() ) / 100.0 );

    /* Use current time as seed for random generator */
    std::srand(std::time(nullptr))

    /* Stay here until the ob */
    while(obstrct < obstMax){
        x = std::rand() % get()->getSize();
        y = std::rand() % get()->getSize();
        z = std::rand() % get()->getSize();
        if( !get()->isObstructed(x,y,z) ){
            get()->_cube[x][y][z] = true;
            obstrct++;
        }

    }
}