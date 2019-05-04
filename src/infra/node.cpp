#include "node.h"

using namespace ai;

Node::Node(const State& state, const size_t pathCost){
    this->_parent = NULL;
    this->_state  = state;
    this->_pathCost = pathCost;
    this->_action   = action_t();
}

Node::Node(Node* parent, const State& state, const action_t& action, const size_t pathCost){
    this->_parent = parent;
    this->_state  = state;
    this->_action = action;
    this->_pathCost = pathCost;
}

Node::Node(Node* parent, const action_t& action, const Problem& problem){
    this->_parent = parent;
    this->_action = action;
    this->_state  = Problem::Result(parent->getState(), action);
    this->_pathCost = parent->getPathCost() + Problem::StepCost(parent->getState(), action);
    this->_FCost    = this->_pathCost + 
}

Node* Node::childNode(Node* parent, const action_t& action) {
    Node* cNode = new Node(parent, action);
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