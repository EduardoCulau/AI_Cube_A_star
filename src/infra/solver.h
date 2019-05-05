#ifndef _INFRA_SOLVER_H_
#define _INFRA_SOLVER_H_

#include "../global.h"
#include "problem.h"
#include "node.h"
#include "queues.h"

namespace ai {

/**
 * Deque to store the Nodes pointers.
 */
typedef ai::deque<Node*>  deque_t;

/**
 * Priority queue to store the Nodes pointers.
 */
typedef ai::priority_queue<Node*, std::vector<Node*>, Node>  priorityQueue_t;


/**
 * Vector of Node pointers which are the solution.
 */
typedef std::vector<const Node*> solution_t;


/**
 * Solver is a Class that defines the solver of the problem.
 * It has argument and method like:
 *      ° Frontier
 *      ° Explored
 *      ° Breadth_First_Search
 *      ° A*
 *
 * @author      Eduardo Culau
 * @version     1.7
 * @since       1.4
 */
class Solver
{
public:

    /**
     * Private Constructor 
     */   
    Solver(){}

    /**
     * Private Constructor 
     */   
    Solver(const Problem &problem){
        this->problem = problem;
    }

    /**
     * Private Destructor
     */
    ~Solver(){problem.~Problem();}

    /**
     * Applies the Breadth First Search on the problem and solve it.
     *
     * @return solution_t solution of the problem
     */
    solution_t Breadth_First_Search (bool path = true);

    /**
     * Applies the A* on the problem and solve it.
     *
     * @return solution_t solution of the problem.
     */
    solution_t A_Star (bool path = true);

    /**
     * Travel back to the origin to get all solution nodes.
     *
     * @param  node       pointer of the last node
     * @return solution_t solution of the problem
     */
    solution_t Solution (const Node* node, bool path = true);

    /**
     * Get the problem to be solved
     *
     * @return Problem& the problem to be solved
     * @see    Problem  
     */
    inline const Problem& getProblem () const {return problem;}

    /**
     * Set the problem to be solved
     *
     * @param  problem the problem to be solved
     */
    inline void setProblem (const Problem &problem) { this->problem = problem; }


private:

    /**
     * Find a state inside the queue
     *
     * @param  dq    a deque
     * @param  state the state
     * @return bool  true if the state is inside the deque
     */
    static bool stateFind (const deque_t& dq, const State& state);

    /**
     * Problem to be solved.
     */  
    Problem problem;
};

}

#endif

