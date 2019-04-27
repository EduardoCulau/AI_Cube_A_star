#ifndef _INFRA_SOLVER_H_
#define _INFRA_SOLVER_H_

#include "../global.h"

namespace ai {

/**
 * Obstruction 0D
 */
typedef bool                         obstruction_t; //0=unobstructed, 1=obstructed

/**
 * Obstruction 1D
 */
typedef std::vector<obstruction_t>   obstruction1D_t;

/**
 * Obstruction 2D
 */
typedef std::vector<obstruction1D_t> obstruction2D_t;

/**
 * Obstruction 3D
 */
typedef std::vector<obstruction2D_t> obstruction3D_t;

/**
 * Cube is a Singleton Class that defines the Cube of the problem.
 * It has argument and method like:
 *      ° Cube with obstructions
 *      ° Percent of obstrutions
 *      ° Fill the cube.
 *
 * @author      Eduardo Culau
 * @version     1.5
 * @since       1.5
 */
class Cube
{
public:

    /**
     * Return the current instance or create one if it don't exist.
     *
     * @return Cube* Setting pointer
     */
    static Cube* get(){
        if ( !_instance ) {
            _instance = new Cube;
        }
        return _instance;
    }        

    /**
     * Set the inital state of the problem
     *
     * @param  size         size of the cube
     * @param  percentage   percentage of blocked
     */
    static void InitialCube (size_t size, size_t percentage);

    /**
     * Get the size
     *
     * @param size_t size of the cube.
     */
    static size_t getSize (size_t size) { return get()->_size; };

    /**
     * Get the percentage of blockeds
     *
     * @return size_t percentage of blockeds
     */
    static size_t getPercent (size_t percent) { return get()->_percent; };

    /**
     * Get the percentage of blockeds
     *
     * @return obstruction3D_t& 3D cube
     */
    static const obstruction3D_t& getCube () const { return get()->_cube; };

    static bool isObstructed (axis_t x, axis_t y, axis_t z) const { return get()->_cube[x][y][z]; };

private:

    /**
     * The single instance of the class.
     */   
    static Cube *_instance;

    /**
     * Private Constructor 
     */   
    Cube(){}

    /**
     * Private Destructor
     */
    ~Cube(){}

    /**
     * Set the size
     *
     * @param size_t size of the cube.
     */
    static void setSize (size_t size) { _size = size; };

    /**
     * Set the percentage of blockeds
     *
     * @param size_t percentage
     */
    static void setPercent(size_t percent) { _percent = percent; };

    /**
     * Creates the cube whit the size specified.
     */
    static void createCube();

    /**
     * Fill the cube with the obstructions.
     */
    static void fillObstructionsCube();

    /**
     * Size of the cube, e.g. 3x3x3, 5x5x5;
     */ 
    size_t          _size;

    /**
     * The percentage of the obistructions.
     */ 
    size_t          _percent;

    /**
     * A 3D cube with the obistructions.
     */ 
    obstruction3D_t _cube;
};

}

#endif

