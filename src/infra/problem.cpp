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
