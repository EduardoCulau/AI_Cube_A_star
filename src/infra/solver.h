#ifndef _INFRA_SOLVER_H_
#define _INFRA_SOLVER_H_

#include "../global.h"
#include "problem.h"
#include "node.h"

namespace ai {

/**
 * Deque to store the Nodes pointers.
 */
typedef std::deque<Node*>  deque_t;

/**
 * Priority queue to store the Nodes pointers.
 */
typedef std::priority_queue<Node*, std::vector<Node*>, Node>  priorityQueue_t;


/**
 * Vector of Node pointers which are the solution.
 */
typedef std::vector<const Node*> solution_t;


/**
 * Solver is a Singleton Class that defines the solver of the problem.
 * It has argument and method like:
 *      ° Frontier
 *      ° Explored
 *      ° Breadth_First_Search
 *      ° A*
 *
 * @author      Eduardo Culau
 * @version     1.6
 * @since       1.4
 */
class Solver
{
public:
    /**
     * Applies the Breadth First Search on the problem and solve it.
     *
     * @return solution_t solution of the problem
     */
    solution_t Breadth_First_Search ();

    /**
     * Applies the A* on the problem and solve it.
     *
     * @return solution_t solution of the problem.
     */
    solution_t A_Star ();

    /**
     * Travel back to the origin to get all solution nodes.
     *
     * @param  node       pointer of the last node
     * @return solution_t solution of the problem
     */
    solution_t Solution (const Node* node);

    /**
     * Travel back to the origin to get all solution nodes.
     *
     * @param  node       pointer of the last node
     * @return solution_t solution of the problem
     */
    const Problem& getProblem () const {return problem;}


private:

    /**
     * Private Constructor 
     */   
    Solver(){}

    /**
     * Private Destructor
     */
    ~Solver(){}

    /**
     * Applies the Breadth First Search on the problem and solve it.
     *
     * @param  node       pointer of the last node
     * @return solution_t solution of the problem
     */
    static bool stateFind (const deque_t& dq, const State& state);

    /**
     * Deque to store the Nodes* that was explored. Used to solve the problem.
     */  
    deque_t explored;

    /**
     * Problem to be solved.
     */  
    Problem problem;
};

}

#endif

