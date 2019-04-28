#include "problem.h"

using namespace ai;

Cube Problem::_validActions = Cube::computeValidActions();

void Problem::setInitialState (elem_t missionaries, elem_t cannibals, elem_t boatCapacity, bool boatPosition){
    get()->_initialState.setData(missionaries, cannibals, boatPosition);
    get()->_goalState.setData   (missionaries, cannibals, !boatPosition);
    get()->computeValidActions(missionaries, cannibals, boatCapacity);
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
    for(auto action : get()->_validActions){
        if( get()->canApplyAction(state, action) ){
            actions.push_back(action);
        }
    }
    return actions;
}
