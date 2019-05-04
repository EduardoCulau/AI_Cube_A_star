#ifndef _GLOBAL_H_
#define _GLOBAL_H_

#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <iterator>
#include <ctime>
#include <cmath>
#include <limits>

/* Defined by the compiler */
//#define PRINT_EXEC

namespace ai {

/**
 * Size of something
 */
typedef int 	size_t;

/**
 * Cost of something
 */
typedef float 	cost_t;

/**
 * Axis ( x or y or z)
 */
typedef size_t	axis_t;

/**
 * Position is a class that defines a 3D position.
 * It has argument and method like:
 *      ° X, Y, Z axis
 *      ° getX, getY, getZ
 *
 * @author      Eduardo Culau
 * @version     1.6
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
	Position() { _x = 0; _y = 0; _z = 0;}

	/**
	 * Creates a positon, setting all the axis.
	 *
	 * @param  x         X axis
	 * @param  y         Y axis
	 * @param  z         Z axis
	 * @return Position  an object of class Position
	 */
	Position(axis_t x, axis_t y, axis_t z) { _x = x; _y = y; _z = z;}

	/**
	 * Creates a Position, copying an existing one
	 *
	 * @param  origin an existing Position
	 * @return State  an object of class Position
	 */
	Position(const Position &origin){
		this->_x = origin.getX();
		this->_y = origin.getY();
		this->_z = origin.getZ();
	}

	/**
	 * Destructor
	 */
	~Position() {};

	/**
	 * Get X axis
	 *
	 * @return axis_t X axis
	 */
	inline axis_t  getX() const { return _x; }

	/**
	 * Get Y axis
	 *
	 * @return axis_t Y axis
	 */
	inline axis_t  getY() const { return _y; }


	/**
	 * Get Z axis
	 *
	 * @return axis_t Z axis
	 */
	inline axis_t  getZ() const { return _z; }

	/**
	 * Set X axis
	 */
	inline void setX(axis_t x) { _x = x; }

	/**
	 * Set Y axis
	 */
	inline void setY(axis_t y) { _y = y; }

	/**
	 * Set Z axis
	 */
	inline void setZ(axis_t z) { _z = z; }

	/**
	 * Operator ==
	 */
	inline bool operator== (const Position &rhs) const {   
		return (this->getX() == rhs.getX() && this->getY() == rhs.getY() && this->getZ() == rhs.getZ());
	}

	/**
	 * Operator !=
	 */
	inline bool operator!= (const Position &rhs) const {   
		return !(this->operator==(rhs));
	}

	/**
	 * Operator + usend to Positon 
	 */
	inline Position operator+ (const Position &rhs) const {   
		return Position(this->getX() + rhs.getX(), this->getY() + rhs.getY(), this->getZ() + rhs.getZ());
	}

	/**
	 * Operator - usend to Positon 
	 */
	inline Position operator- (const Position &rhs) const {   
		return Position(this->getX() - rhs.getX(), this->getY() - rhs.getY(), this->getZ() - rhs.getZ());
	}

	/**
	 * Operator += usend to Positon. 
	 */
	inline Position& operator+= (const Position &rhs) {
		this->setX(this->getX() + rhs.getX()); this->setY(this->getY() + rhs.getY()); this->setZ(this->getZ() + rhs.getZ());
		return *this;   
	}

	/**
	 * Operator += usend to Positon. 
	 */
	inline Position& operator-= (const Position &rhs) {
		this->setX(this->getX() - rhs.getX()); this->setY(this->getY() - rhs.getY()); this->setZ(this->getZ() - rhs.getZ());
		return *this;   
	}

	/**
	 * Operator << (print) usend to Position. 
	 */
	friend inline std::ostream& operator<< (std::ostream &out, const Position &rhs) {
		out <<"(" << rhs.getX() << "," << rhs.getY() << "," << rhs.getZ() << ")";
		return out;
	}

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
 * An action is a postion with the direction to move.
 */
typedef Position 				action_t;

/**
 * A bunch of action
 */
typedef std::vector<action_t>	actions_t;

}

#endif

