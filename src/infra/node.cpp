#include "node.h"

using namespace ai;

Node::Node(const State& state, const size_t pathCost, const cost_t heuristic){
    this->_parent = NULL;
    this->_state  = state;
    this->_pathCost = pathCost;
    this->_FCost    = (cost_t) this->_pathCost + heuristic;
    this->_action   = action_t();
}

Node::Node(Node* parent, const State& state, const action_t& action, const size_t pathCost, const cost_t heuristic){
    this->_parent = parent;
    this->_state  = state;
    this->_action = action;
    this->_pathCost = pathCost;
    this->_FCost    = (cost_t) this->_pathCost + heuristic;
}

Node::Node(Node* parent, const action_t& action, const Problem& Problem){
    this->_parent = parent;
    this->_action = action;
    this->_state  = Problem::Result(parent->getState(), action);
    this->_pathCost = parent->getPathCost() + Problem::StepCost(parent->getState(), action);
    this->_FCost    = (cost_t) this->_pathCost + Problem.HeuristicCost(this->_state);
}

Node* Node::childNode(Node* parent, const action_t& action, const Problem& Problem) {
    Node* cNode = new Node(parent, action, Problem);
    return cNode; 
}

void Node::printCurrentNode(const Node* node){
    std::cout << std::endl << "CURRENT STATE: COST = "<< node->getPathCost() << std::endl;
    std::cout << node->getState() << std::endl;
}

void Node::printChieldNode_Start(){
    std::cout << std::endl << "CHILD NODES {"<< std::endl; 
}

void Node::printChieldNode(const Node* child){
    std::cout <<"   COST = " << child->getPathCost() << "	ACTION = " << child->getAction() << std::endl << child->getState() << std::endl << std::endl;
}

void Node::printChieldNode_End(){
    std::cout <<"}"<< std::endl << std::endl; 
}

void Node::printSolutionNode (const Node* node){
	std::cout <<"   COST = " << node->getPathCost() << "	ACTION = " << node->getAction() << std::endl << node->getState() << std::endl << std::endl;
}

std::string Node::toStringFCost (){
    return std::string( this->getState().toString() + " | TOTAL_COST = " + std::to_string(this->getFCost()) );
}

void Node::update(Node* refNode){
    this->_parent = refNode->getParent();
    this->_action = refNode->getAction();
    this->_pathCost = refNode->getPathCost();
    this->_FCost  = refNode->getFCost();
}