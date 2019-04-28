#include "solver.h"

using namespace ai;

Solver *Solver::_instance = 0;

solution_t Solver::Breadth_First_Search (){
    //Inital node
    Node* node = new Node(problem.getInitialState(), 0);
    Node* child;

    deque_t frontier;

    //Inital Test.
    if( problem.goalTest(node->getState()) ){
        solution_t result; result.push_back(new Node(NULL, problem.getGoalState(), M_PAIR(0,0), 0));
        return result; //Nothing to be done
    }

    //Add node to the fifo
    frontier.push_back(node);
    //Empty explored.

    //Loop over the problem space.
    while( true ){
        if( frontier.empty() ) return Solution(NULL);

        //Remove from queue.
        node = frontier.front(); frontier.pop_front();
        explored.push_back(node);

        #ifdef PRINT_EXEC
             Node::printCurrentNode(node);
             Node::printChieldNode_Start();
        #endif

        //Apply all action
        for(auto action : problem.actions(node->getState())){
            child = Node::childNode(node, action);

            #ifdef PRINT_EXEC
                Node::printChieldNode(child);
            #endif

            //Test if the node is not in explored or frontier the
            if( !stateFind(frontier, child->getState()) and !stateFind(explored, child->getState()) ){
                if( problem.goalTest(child->getState()) ) return Solution(child);
                frontier.push_back(child);
            }else{
                child->~Node();
            }
        }

        #ifdef PRINT_EXEC
            Node::printChieldNode_End();
        #endif
    }

}

solution_t Solver::A_Star (){
    //Inital node
    Node* node = new Node(problem.getInitialState(), 0);
    Node* child;

    //Inital Test.
    if( problem.goalTest(node->getState()) ){
        solution_t result; result.push_back(new Node(NULL, problem.getGoalState(), M_PAIR(0,0), 0));
        return result; //Nothing to be done
    }

    //Add node to the fifo
    frontier.push_back(node);
    //Empty explored.

    //Loop over the problem space.
    while( true ){
        if( frontier.empty() ) return Solution(NULL);

        //Remove from queue.
        node = frontier.front(); frontier.pop_front();
        explored.push_back(node);

        #ifdef PRINT_EXEC
             Node::printCurrentNode(node);
             Node::printChieldNode_Start();
        #endif

        //Apply all action
        for(auto action : problem.actions(node->getState())){
            child = Node::childNode(node, action);

            #ifdef PRINT_EXEC
                Node::printChieldNode(child);
            #endif

            //Test if the node is not in explored or frontier the
            if( !stateFind(frontier, child->getState()) and !stateFind(explored, child->getState()) ){
                if( problem.goalTest(child->getState()) ) return Solution(child);
                frontier.push_back(child);
            }else{
                child->~Node();
            }
        }

        #ifdef PRINT_EXEC
            Node::printChieldNode_End();
        #endif
    }

}


solution_t Solver::Solution (const Node* node){
    solution_t solution;
    if( node == NULL) return solution;
    //Following Parrents pointes to extract all actions.
    while(node->getParent() != NULL){
        auto it = solution.begin();
        solution.insert(it, node);
        node = node->getParent();
    }
    return solution;
}

bool Solver::stateFind(const store_t& dq, const State& state) {
    auto nodeIt = dq.begin();
    //Findo the state insede the deque.
    for( ; nodeIt != dq.end(); ++nodeIt ){
        if( (*nodeIt)->getState() == state ){
            return true;
        }
    }
    return false;
}