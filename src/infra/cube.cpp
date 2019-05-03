#include "cube.h"

using namespace ai;

Cube *Cube::_instance = 0;

void Cube::InitializeCube (size_t size, size_t percentage){
    get()->setSize(size);
    get()->setPercent(percentage);
    get()->createCube();
    get()->fillObstructionsCube();
}


void Cube::createCube(){
    /* Create the Cube */
    get()->_cube = CREATE_CUBE(get()->getSize());

    /* Put all positions to false*/
    for(int i = 0; i < get()->getSize(); i++){
        get()->_cube[0][0][i] = false;
    }

    for(int j = 1; j < get()->getSize(); j++){
        get()->_cube[0][j] = get()->_cube[0][0];
    }

    for(int k = 1; k < get()->getSize(); k++){
        get()->_cube[k] = get()->_cube[0];
    }
}

void Cube::fillObstructionsCube(){
    /* Fill the cube with the obstructions */
    int x, y, z;
    size_t obstrct = 0; 
    size_t obstMax = get()->numberOfObstructions();

    /* Use current time as seed for random generator */
    std::srand(std::time(0));

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

actions_t Cube::computeValidActions() {
    actions_t validActions;
    /* RIGHT >*/
    validActions.emplace_back( 1,  0,  0);
    /* LEFT <*/
    validActions.emplace_back(-1,  0,  0);
    /* FRONT x*/
    validActions.emplace_back( 0,  1,  0);
    /* BACK .*/
    validActions.emplace_back( 0, -1,  0);
    /* UP ^*/
    validActions.emplace_back( 0,  0,  1);
    /* DOWN v*/
    validActions.emplace_back( 0,  0, -1);

    return validActions;
}

bool Cube::isAxisInside (axis_t axi){
    return ( axi >= 0 && axi < get()->getSize() );
}

bool Cube::isPositionInside (const Position &posit){
    return ( get()->isAxisInside(posit.getX()) && get()->isAxisInside(posit.getY()) && get()->isAxisInside(posit.getZ()) );
}

bool Cube::canApplyAction (const Position &posit, const action_t &action){
    /* Aplly the action */
    Position result = posit + action;
    /* Check if is inside the cube and if is not obstructed */
    return ( get()->isPositionInside(result) && !get()->isObstructed(result) );
}


void Cube::printCube () {
    for(int x = 0; x < get()->getSize(); x++){
        for(int y = 0; y < get()->getSize(); y++){
            for(int z = 0; z < get()->getSize(); z++){
                std::cout <<"Cube [" << x << "][" << y << "][" << z << "] = " << get()->isObstructed(x,y,z) << std::endl;
            }  
        }
    }
    std::cout << std::endl;
}

void Cube::printCube2D (){
    /* Create the cube and put all positions to false*/
    for(int z = 0; z < get()->getSize(); z++){
        std::cout << "Cube [x][y][" << z << "]" << std::endl << " {" << std::endl;
            for(int y = 0; y < get()->getSize(); y++){
                std::cout << "\t";
                for(int x = 0; x < get()->getSize(); ++x, std::cout <<  " | "){
                    std::cout << get()->isObstructed(x,y,z);
                }
                std::cout << "\b\b " << std::endl;
            } 
        std::cout << "}" << std::endl; 
    }
    std::cout << std::endl;
}
