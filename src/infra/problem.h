#ifndef _INFRA_DB_H_
#define _INFRA_DB_H_

#include "../global.h"
#include "state.h"
#include "node.h"

namespace ai {

/**
 * Problem is a Class that define the problem.
 * It has argument and method used to solve the problem:
 *      ° Initial State
 *      ° Goal State
 *      ° Valid action (operators)
 *
 * @author      Eduardo Culau
 * @version     1.6
 * @since       1.2
 */
class Problem
{
public:
    /**
     * Get the initial state
     *
     * @return State the initial State
     * @see    State
     */
    static const State& getInitialState () { return get()->_initialState; }

    /**
     * Get the goal state
     *
     * @return State the goal State
     * @see    State
     */
    static const State& getGoalState () { return get()->_goalState; }

    /**
     * Get all valid actions (possible actions)
     *
     * @return actions_t a bunch of valid action
     */
    static const actions_t& getAllValidActions () { return get()->_validActions; }

    /**
     * Set the inital state of the problem
     *
     * @param  x coordinate
     * @param  y coordinate
     * @param  z coordinate
     */
    static void setInitialState (axis_t x, axis_t y, axis_t z);

    /**
     * Set the inital state of the problem
     *
     * @param  posit Position in the cube
     * @see    Position
     */
    static void setInitialState (const Position &posit);

    /**
     * Set the Goal state of the problem
     *
     * @param  x coordinate
     * @param  y coordinate
     * @param  z coordinate
     */
    static void setGoalState (axis_t x, axis_t y, axis_t z);

    /**
     * Set the Goal state of the problem
     *
     * @param  posit Position in the cube
     * @see    Position
     */
    static void setGoalState (const Position &posit);

    /**
     * Create a new state, applying an action. 
     * Don't check if the action is applicable.
     *
     * @param  state  existing state
     * @param  action action to be applied
     * @return State  new state
     * @see    State
     */
    static State Result ( const State &state, const action_t &action );

    /**
     * Compute the step cost of an action over a State. 
     * Currently is always 1.
     *
     * @param  state  existing state
     * @param  action action to be applied
     * @return elem_t the cost of aply this action.
     */
    static const elem_t StepCost ( const State &state, const action_t &action ) { return 1; }

    /**
     * Test if a state is the goal state. 
     *
     * @param  state  existing state
     * @return bool   true if the goal state else false
     */
    static bool goalTest (const State &state) { return (state == get()->_goalState); }

    /**
     * Test if is possible to apply and action to some state.
     * The number of missionaries in a side must be greater or equal the cannibals.
     *
     * @param  state  existing state to be tested
     * @param  action action to be applied
     * @return bool   true if is possible to apply the action else false
     */    
    inline static bool canApplyAction (const State &state, const action_t &action);

    /**
     * Check all valid action on a state and return just the applicable ones.
     *
     * @param  state     existing state to be tested
     * @return actions_t all applicable actions
     */  
    static actions_t actions (const State &state);

private:

    /**
     * Private Constructor 
     */    
    Problem(){}
    
    /**
     * Private Destructor
     */
    ~Problem(){}

    /**
     * The initial state of the problem
     */      
    State _initialState;

    /**
     * The goal state of the problem
     */      
    State _goalState;

    /**
     * All valid actions on the cube.
     */  
    static actions_t _validActions;
};

}

#endif

