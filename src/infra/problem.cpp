#include "problem.h"

using namespace ai;

Cube Problem::_validActions = Cube::computeValidActions();

void Problem::setInitialState (size_t missionaries, size_t cannibals, size_t boatCapacity, bool boatPosition){
    _initialState.setData(missionaries, cannibals, boatPosition);
    _goalState.setData   (missionaries, cannibals, !boatPosition);
    computeValidActions(missionaries, cannibals, boatCapacity);
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
