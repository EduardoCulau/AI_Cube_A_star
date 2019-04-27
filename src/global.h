#ifndef _GLOBAL_H_
#define _GLOBAL_H_

#include <iostream>

#include <string>
#include <vector>
#include <deque>
#include <algorithm>
#include <iterator>
#include <cstring>

/* Defined by the compiler */
//#define PRINT_EXEC

namespace ai {

/**
 * Size of something
 */
typedef unsigned int size_t;

/**
 * Axis ( x or y or z)
 */
typedef size_t		 axis_t;

/**
 * Position is a class that defines a 3D position.
 * It has argument and method like:
 *      ° X, Y, Z axis
 *      ° getX, getY, getZ
 *
 * @author      Eduardo Culau
 * @version     1.5
 * @since       1.5
 */
class Position
{
public:
	/**
     * Simplest constructor
     *
     * @return      an zero position.
     */
	Position(){ _x = 0; _y = 0; _z = 0};

	/**
     * Creates a positon, setting all the axis.
     *
     * @param  x         X axis
     * @param  y         Y axis
     * @param  z         Z axis
     * @return Position  an object of class Position
     */
	Position(axis_t x, axis_t y, axis_t z){ _x = x; _y = y; _z = z;}

	/**
     * Creates a Position, copying an existing one
     *
     * @param  origin an existing Position
     * @return State  an object of class Position
     */
	Position(const State &origin){
		this->_x = origin.getX();
		this->_y = origin.getY();
		this->_z = origin.getZ();
	}

	/**
     * Destructor
     */
	~Position();

    /**
     * Get X axis
     *
     * @return axis_t X axis
     */
    inline axis_t  getX() const { return _x; };

    /**
     * Get Y axis
     *
     * @return axis_t Y axis
     */
    inline axis_t  getY() const { return _y; };


    /**
     * Get Z axis
     *
     * @return axis_t Z axis
     */
    inline axis_t  getZ() const { return _z; };

private:
	/**
     * X axis.
     */ 
	axis_t _x;

	/**
     * Y axis.
     */ 
	axis_t _y;

	/**
     * Z axis.
     */ 
	axis_t _z;
};

/**
 * An action is a movement of some quantity of miss and cann
 */
typedef side_t                    action_t;

/**
 * Two sides <left Side, Right Side> of the river
 */
typedef std::pair<side_t, side_t> sides_t;

/**
 * A bunch of action
 */
typedef std::vector<action_t>     actions_t;

using namespace ai;

/**
 * Template to operator + usend to std::pair. 
 */
template <typename T, typename U>
std::pair<T,U> operator+ (const std::pair<T,U> &lhs, const std::pair<T,U> &rhs) {   
    return std::make_pair(lhs.first + rhs.first, lhs.second + rhs.second);
}

/**
 * Template to operator - usend to std::pair. 
 */
template <typename T, typename U>
std::pair<T,U> operator- (const std::pair<T,U> &lhs, const std::pair<T,U> &rhs) {   
    return std::make_pair(lhs.first - rhs.first, lhs.second - rhs.second);
}

/**
 * Template to operator += usend to std::pair. 
 */
template <typename T, typename U>
std::pair<T,U>& operator+= (std::pair<T,U> &lhs, const std::pair<T,U> &rhs) {
    lhs.first += rhs.first; lhs.second += rhs.second;
    return lhs;   
}

/**
 * Template to operator -= usend to std::pair. 
 */
template <typename T, typename U>
std::pair<T,U>& operator-= (std::pair<T,U> &lhs, const std::pair<T,U> &rhs) {   
    lhs.first -= rhs.first; lhs.second -= rhs.second;
    return lhs;   
}

/**
 * Template to operator << (print) usend to std::pair. 
 */
template <typename T, typename U>
std::ostream& operator<< (std::ostream &out, const std::pair<T,U> &side) {
    out <<"< " << side.first << " , " << side.second << " >";
    return out;
}

/**
 * Make a pair. 
 */
#define M_PAIR(lhs, rhs) std::make_pair(lhs, rhs)

}

#endif

