#ifndef _INFRA_STATE_H_
#define _INFRA_STATE_H_

#include "../global.h"

namespace ai {

/**
 * State is the base class of the problem. 
 * It define a state of the problem like:
 *      ° Number of elements in each side of the river.
 *      ° Position of the boat (bank of the river).
 *      ° Define methods to move element from each side.
 *      ° Define a print method to show the state.
 *
 * @author      Eduardo Culau
 * @version     1.6
 * @since       1.1
 */
class State
{
public:

    /**
     * Simplest constructor
     *
     * @return      an empty State.
     */
    State (){
        this->_position = Position();
    }

    /**
     * Creates a State, setting the element to a specific position
     *
     * @param  posit position in the 3D cube
     * @return State an object of class State
     */
    State(const Position &posit){
        this->setPosition(posit);
    }

    /**
     * Creates a State, setting the element to a specific side defined by the boat position
     *
     * @param  x     x axis
     * @param  y     y axis
     * @param  z     z axis
     * @return State an object of class State
     */
    State(axis_t x, axis_t y, axis_t z){
        State(Position(x,y,z));
    }

    /**
     * Creates a State, copying an existing one
     *
     * @param  origin an existing State
     * @return State  an object of class State
     */
    State(const State &origin){
        this->_position = origin.getPosition();
    }

    /**
     * Destructor
     */
    ~State() {_position.~Position();}

    /**
     * Set the positon to the state.
     *
     * @param  posit 3D position of the state
     */    
    void setPosition (const Position &posit);

    /**
     * Aplly an action, cange the positon of the State, without checking if is valid.
     *
     * @param  action movement to be done
     */ 
    void applyAction (const action_t &action);

    /**
     * Operator ==. Compare if a State is equal to ohter one.
     *
     * @param  otherState   state to be compared to the implicit one
     * @return bool         true if the state is equal else false
     */  
    bool operator== (const State& otherState) const;

    /**
     * Get both sides of the river (State).
     *
     * @return Position the position of the state
     * @see Position
     */
    inline const Position& getPosition() const { return _position; }

    /**
     * Convert the state to string.
     *
     * @return std::string the position of the state
     */
    inline std::string toString() const { return _position.toString();}


    /**
     * Operator <<. So it's possible to print the state just put it on the std::cout method.
     *
     * @param  out           existing std::ostream
     * @param  state         state to be printed
     * @return std::ostream& std::ostream whith the State data
     * @see    std::ostream
     */  
    friend std::ostream& operator<< (std::ostream &out, const State& state);

private:
    /**
     * Position of the state in the 3D cube.
     */  
    Position  _position;      // Axis X, Y, Z.
};

}

#endif

