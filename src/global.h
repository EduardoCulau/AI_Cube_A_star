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
#include <thread>
#include <mutex>
#include <chrono>
#include <fstream>
#include <tuple>

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
 * Pair <cost, time> that is the result
 */
typedef std::pair<size_t, double> result_t;

/**
 * A bunch of result_t
 */
typedef std::vector<result_t> results_t;

/**
 * Template to operator << (print) usend to std::pair. 
 */
template <typename T, typename U>
std::ostream& operator<< (std::ostream &out, const std::pair<T,U> &pair) {
    out << pair.first << ";" << std::to_string(pair.second);
    return out;
}

/**
 * Tuple <cost, repetition, time>
 */
typedef std::tuple<size_t, size_t, double> compactResult_t;

/**
 * A bunch of compactResult_t
 */
typedef std::vector<compactResult_t> compactResults_t;

template <typename T, typename U, typename V>
std::ostream& operator<< (std::ostream &out, const std::tuple<T,U,V> &tuple) {
    out << std::get<0>(tuple) << "; " << std::get<1>(tuple) << "; " << std::to_string(std::get<2>(tuple));
    return out;
}

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
	 * To string
	 */
	inline std::string toString () const {
		return std::string("(" + std::to_string(getX()) + "," + std::to_string(getY()) + "," + std::to_string(getZ()) + ")" ); 
	}

	/**
	 * Operator << (print) usend to Position. 
	 */
	friend inline std::ostream& operator<< (std::ostream &out, const Position &rhs) {
		out << rhs.toString();
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

