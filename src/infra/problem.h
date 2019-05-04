#ifndef _INFRA_PROBLEM_H_
#define _INFRA_PROBLEM_H_

#include "../global.h"
#include "cube.h"
#include "state.h"

namespace ai {

/* Fowording of the class Problem */
class Problem;

/**
 * A bunch of problems
 */
typedef std::vector<Problem> problems_t;

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
     * Constructor 
     */    
    Problem(){}

    /**
     * Constructor 
     */    
    Problem( Position &initialPosit, Position &goalPosit ){
        this->setInitialState(initialPosit);
        this->setGoalState(goalPosit);
    }
    
    /**
     * Destructor
     */
    ~Problem(){}

    /**
     * Get the initial state
     *
     * @return State the initial State
     * @see    State
     */
    const State& getInitialState () const { return _initialState; }

    /**
     * Get the goal state
     *
     * @return State the goal State
     * @see    State
     */
    const State& getGoalState () const { return _goalState; }

    /**
     * Get all valid actions (possible actions)
     *
     * @return actions_t a bunch of valid action
     */
    const actions_t& getAllValidActions () { return _validActions; }

    /**
     * Set the inital state of the problem
     *
     * @param  posit Position in the cube
     * @see    Position
     */
    void setInitialState (const Position &posit);

    /**
     * Set the Goal state of the problem
     *
     * @param  posit Position in the cube
     * @see    Position
     */
    void setGoalState (const Position &posit);

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
     * @return size_t the cost of aply this action.
     */
    inline static size_t StepCost ( const State &state, const action_t &action ) { return 1; }

    /**
     * Compute the heuristic cost a State. 
     * Currently is always 1.
     *
     * @param  state  existing state
     * @return cost_t the cost of aply this action.
     */
    inline cost_t HeuristicCost ( const State &state) const { return Cube::linearDistance(state.getPosition(), this->getGoalState().getPosition()); }

    /**
     * Test if a state is the goal state. 
     *
     * @param  state  existing state
     * @return bool   true if the goal state else false
     */
    bool goalTest (const State &state) { return (state == _goalState); }

    /**
     * Test if is possible to apply and action to some state.
     * The number of missionaries in a side must be greater or equal the cannibals.
     *
     * @param  state  existing state to be tested
     * @param  action action to be applied
     * @return bool   true if is possible to apply the action else false
     */    
    inline bool canApplyAction (const State &state, const action_t &action);

    /**
     * Check all valid action on a state and return just the applicable ones.
     *
     * @param  state     existing state to be tested
     * @return actions_t all applicable actions
     */  
    actions_t actions (const State &state);

    /**
     * Criates all problems (initial and goal state) to perform.
     *
     * @param  nProblems  number of problems to be create
     * @return problems_t a bunch of Problems
     */  
    static problems_t createProblems (size_t nProblems);

    /**
     * Operator <<. So it's possible to print the Problem just put it on the std::cout method.
     *
     * @param  out           existing std::ostream
     * @param  problem       problem to be printed
     * @return std::ostream& std::ostream whith the State data
     * @see    std::ostream
     */  
    friend std::ostream& operator<< (std::ostream &out, const Problem& problem);

    /**
     * Operator ==. Compare if a Problem is equal to ohter one.
     *
     * @param  otherProblem  state to be compared to the implicit one
     * @return bool         true if the state is equal else false
     */  
    bool operator== (const Problem& otherProblem) const;

private:

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

