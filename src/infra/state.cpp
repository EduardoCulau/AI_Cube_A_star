#include "state.h"

using namespace ai;

void State::setPosition (const Position &posit){
    this->_position = posit;
}

void State::applyAction (const action_t &action){
    this->_position += action;
}

bool State::operator== (const State& otherState) const {
    return ( this->getPosition() == otherState.getPosition() );
}

namespace ai {

    std::ostream& operator<< (std::ostream &out, const State& state) {
        out << state.getPosition() << std::endl;
        return out;
    }

}