#ifndef _INFRA_CUBE_H_
#define _INFRA_CUBE_H_

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
 * Define para criar o cubo.
 */
#define CREATE_CUBE(X) obstruction3D_t(X, obstruction2D_t(X, obstruction1D_t(X)))

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
    static void InitializeCube (size_t size, size_t percentage);

    /**
     * Get the size
     *
     * @param size_t size of the cube.
     */
    inline static size_t getSize () { return get()->_size; };

    /**
     * Get the percentage of blockeds
     *
     * @return size_t percentage of blockeds
     */
    inline static size_t getPercent () { return get()->_percent; };

    /**
     * Get the percentage of blockeds
     *
     * @return obstruction3D_t& 3D cube
     */
    inline static const obstruction3D_t& getCube () { return get()->_cube; };

    /**
     * Check if position is obstructed.
     *
     * @return bool true if is obstructed else false.
     */
    inline static bool isObstructed (axis_t x, axis_t y, axis_t z) { return get()->_cube[x][y][z]; };

    /**
     * Check if position is obstructed.
     *
     * @return bool true if is obstructed else false.
     */
    inline static bool isObstructed (const Position &posit) { return get()->isObstructed( posit.getX(), posit.getY(), posit.getZ() ); };

    /**
     * Check if an axis is inside the axis of the cube.
     *
     * @return bool true if is inside else false.
     */
    inline static bool isAxisInside (axis_t axi);

    /**
     * Check if a position is inside the cube.
     *
     * @return bool true if is inside else false.
     */
    inline static bool isPositionInside (const Position &posit);

    /**
     * Check if a position is inside the cube.
     *
     * @return bool true if is inside else false.
     */
    static bool canApplyAction (const Position &posit, const action_t &action);

    /**
     * Compute all valid actions.
     */    
    static actions_t computeValidActions();

    /**
     * Print the value of a postition of the Cube
     */
    static void printCube ();

    /**
     * Print the value of a postition of the Cube in many matrices.
     */
    static void printCube2D ();

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
    static void setSize (size_t size) { get()->_size = size; };

    /**
     * Set the percentage of blockeds
     *
     * @param size_t percentage
     */
    static void setPercent(size_t percent) { get()->_percent = percent; };

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

