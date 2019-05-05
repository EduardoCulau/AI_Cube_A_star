#include "problem.h"

using namespace ai;

actions_t Problem::_validActions = Cube::computeValidActions();

void Problem::setInitialState (const Position &posit){
    _initialState.setPosition(posit);
}

void Problem::setGoalState (const Position &posit){
    _goalState.setPosition(posit);
}

State Problem::Result ( const State &state, const action_t &action ){
    State newState(state);
    newState.applyAction(action);
    return newState;
}

bool Problem::canApplyAction (const State &state, const action_t &action){
    return Cube::canApplyAction(state.getPosition(), action);
}

actions_t Problem::actions (const State &state){
    actions_t actions;
    /* Go throught all validActions */
    for(auto action : _validActions){
        if( canApplyAction(state, action) ){
            actions.push_back(action);
        }
    }
    return actions;
}

problems_t Problem::createProblems (size_t nProblems){
    /* Create the problems */
    problems_t problems;
    Position initialPosit, goalPosit;
    size_t problem = 0; size_t invalid = 0; 

    /* Stay here until the ob */
    while(problem < nProblems){
        initialPosit = Cube::getRandomPosition();
        goalPosit    = Cube::getRandomPosition();

        /* Check if both position aren't obtructed. */
        if( !Cube::isObstructed(initialPosit) && !Cube::isObstructed(goalPosit) && initialPosit != goalPosit){
            problems.emplace_back(initialPosit, goalPosit);
            problem++;
        }else{
            invalid++;
        }

        if(invalid > nProblems*100) break;
    }

    return problems;
}

bool Problem::operator== (const Problem& otherProblem) const {
    return ( this->getInitialState() == otherProblem.getInitialState() && this->getGoalState() == otherProblem.getGoalState() );
}

namespace ai {

    std::ostream& operator<< (std::ostream &out, const Problem& problem) {
        out << problem.getInitialState() << "~>" << problem.getGoalState();
        return out;
    }

}