#include "solver.h"

using namespace ai;

solution_t Solver::Breadth_First_Search (bool path){
    //Inital node
    Node* node = new Node(problem.getInitialState(), 0, 0.0);
    Node* child;
    deque_t frontier;

    //Inital Test.
    if( problem.goalTest(node->getState()) ){
        solution_t result; result.push_back(new Node(NULL, problem.getGoalState(), action_t(0,0,0), 0, 0.0));
        return result; //Nothing to be done
    }

    //Add node to the fifo
    frontier.push_back(node);
    //Empty explored.
    deque_t explored; // Deque to store the Nodes* that was explored. Used to solve the problem.

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
            child = Node::childNode(node, action, problem, path);

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

solution_t Solver::A_Star (bool path){
    //Inital node
    Node* node = new Node(problem.getInitialState(), 0, problem.HeuristicCost(problem.getInitialState()));
    Node* child, *aux;
    priorityQueue_t frontier;

    //Inital Test.
    if( problem.goalTest(node->getState()) ){
        solution_t result; result.push_back(new Node(NULL, problem.getGoalState(), action_t(0,0,0), 0, 0.0));
        return result; //Nothing to be done
    }

    //Add node to the priority queue
    frontier.push(node);
    //Empty explored.
    deque_t explored; // Deque to store the Nodes* that was explored. Used to solve the problem.    

    //Loop over the problem space.
    while( true ){
        if( frontier.empty() ) {
            explored.clear();
            return Solution(NULL, path);
        }
        /* Avoid memory leak */
        //delete node;

        //Remove from queue.
        node = frontier.top(); frontier.pop();
        explored.push_back(node);

        #ifdef PRINT_EXEC
             Node::printCurrentNode(node);
             Node::printChieldNode_Start();
        #endif

        //Apply all action
        for(auto action : problem.actions(node->getState())){
            //Create a new node (updateing its F, G and H cost).
            child = Node::childNode(node, action, problem, path);

            //Print the new child node.
            #ifdef PRINT_EXEC
                Node::printChieldNode(child);
            #endif

            //Check if it was explored
            if( !explored.contains(child->getState()) ){

                //Check if the node is in the frontier.
                auto fPointer = frontier.find(child->getState());
                if( fPointer != frontier.cend() ){
                    //Compare the cost of the child with the one in the frontier.
                    if( child->getFCost() < (*fPointer)->getFCost() ){
                        //If child has less cost, update this node in the frontier.
                        aux = *fPointer; *fPointer = child;
                        delete aux; /* Avoid memory leaks */                     
                    }else{
                        delete child; /* Avoid memory leaks */
                    }
                }else{
                    //Check if the new node is the solution.
                    if( problem.goalTest(child->getState()) ) {
                        explored.clear();
                        return Solution(child, path);
                    }
                    frontier.push(child);
                }

            }else{
                delete child; /* Avoid memory leaks */
            }
        }

        #ifdef PRINT_EXEC
            Node::printChieldNode_End();
        #endif
    }

}


solution_t Solver::Solution (const Node* node, bool path){
    solution_t solution;
    if( node == NULL) return solution;
    //Following Parrents pointes to extract all actions.
    if(path == false) solution.push_back(node);
    else
        while(node->getParent() != NULL){
            auto it = solution.begin();
            solution.insert(it, node);
            node = node->getParent();
        }
    return solution;
}

bool Solver::stateFind(const deque_t &dq, const State &state) {
    auto nodeIt = dq.begin();
    //Findo the state insede the deque.
    for( ; nodeIt != dq.end(); ++nodeIt ){
        if( (*nodeIt)->getState() == state ){
            return true;
        }
    }
    return false;
}