#include "global.h"
#include "setting.h"
#include "infra/problem.h"
#include "infra/state.h"
#include "infra/node.h"
#include "infra/solver.h"
#include "infra/cube.h"
#include "infra/queues.h"

using namespace ai;

/**
 * Data is a class that define an exchangable object fot the threads.
 *
 * @author      Eduardo Culau
 * @version     1.8
 * @since       1.7
 */
class Data
{
public:
    /**
     * Creates a Position, copying an existing one
     *
     * @param  origin an existing Position
     * @return State  an object of class Position
     */
    Data(problems_t::const_iterator start, problems_t::const_iterator end, ai::size_t id){
        this->_start = start; this->_end = end; this->_id = id;
    }

    /* Destructor */
    ~Data() {_results.clear(); _results.shrink_to_fit();};
    /**
     * Gets for members.
     */
    static problems_t* getProblems() { return _problems;}
    static void setProblems(problems_t* problems) { Data::_problems = problems;}
    problems_t::const_iterator getStart() { return _start;}
    problems_t::const_iterator getEnd() { return _end;}
    const results_t& getResults() {return _results;}
    void emplace_back(ai::size_t cost, double time) {_results.emplace_back(cost, time);}
    ai::size_t getId() {return _id;}

private:

    /**
     * Pointer to problems.
     */ 
    static problems_t* _problems;

    /**
     * Iterator for the problems.
     */ 
    problems_t::const_iterator _start, _end;

    /**
     * Results of the computations (problems).
     */ 
    results_t _results;

    /**
     * ID of the thread
     */
     ai::size_t _id; 
};

problems_t* Data::_problems = 0;

/**
 * A bunch of data
 */
typedef std::vector<Data> datas_t;

/**
 * A bunch of data
 */
typedef std::vector<std::thread> threads_t;

/**
 * Mutex
 */
std::mutex mutex_print;

/*Function of the threads */
void threadRun (Data* data){
    mutex_print.lock();
    std::cout <<"THREAD = " << data->getId() << " PROBLEMS = "<< data->getEnd() - data->getStart() << std::endl;
    mutex_print.unlock();
    
    /* Create the solver */
    Solver* solver; solution_t solution;
    int totalProblem = data->getEnd() - data->getStart();
    int counter = 1;

    /* Loop over the problems */
    for(auto pIt = data->getStart(); pIt != data->getEnd(); pIt++){
        /* Set a solver */
        Problem problem = *pIt;
        solver = new Solver(problem);

        /* Solver the problem and measure the time */
        auto start = std::chrono::high_resolution_clock::now();
            solution = solver->A_Star(false);
        auto finish = std::chrono::high_resolution_clock::now();
        std::chrono::duration<double> elapsed = finish - start;

        /* Print the solution */
        if( solution.empty() ){
            mutex_print.lock();
                std::cout << "THREAD = " << data->getId() << " | " << problem << " | NO SOLUTION" << " | COMPUTADOS " << counter << "/" << totalProblem << std::endl;
            mutex_print.unlock();
        }else{
            auto node = solution.back();
            mutex_print.lock();
                std::cout << "THREAD = " << data->getId() << " | " << problem << " | COST = " << node->getPathCost() << " | COMPUTADOS " << counter << "/" << totalProblem << std::endl;
            mutex_print.unlock();

            /* Save the result */
            data->emplace_back( node->getPathCost(), elapsed.count());
        }

        delete solver; counter++;
    }

    return;
}

/**
 * Main function that start all the process
 * using an existing infrastructure. 
 *
 * @author      Eduardo Culau
 * @version     1.7
 * @since       1.0
 */
int main(int argc, char **argv)
{   
    /* Read entries */
    if( !Setting::readArgs(argc, argv) )
        return 1;
    
    /* Check entries */
    if( !Setting::parseEntries() ){
        return 1;
    }

    /* Print the parameter */
    std::cout<<"		STARTING		"       <<std::endl
             <<"Size of the Cube = "            << Setting::cubeSize() << "x" << Setting::cubeSize() << "x" << Setting::cubeSize() <<std::endl
             <<"Percentage of obstructions  = " << Setting::obstructions() << "%" << std::endl
             <<"Routes = "                      << Setting::routes() << std::endl
             <<"Threads = "                     << Setting::threads() << std::endl << std::endl;

    /* Divide problems between the treads */
    ai::size_t ppt = (ai::size_t) std::ceil((float) Setting::routes() / Setting::threads());
    std::cout << "Problems per thread ~= " << ppt << std::endl << std::endl;

    /* Initialize the Cube with the obstructions percentage */
    Cube::InitializeCube(Setting::cubeSize(), Setting::obstructions());

    #ifdef PRINT_EXEC
        Cube::printCube2D();
    #endif

    /* Compute the problems */
    problems_t problems = Problem::createProblems(Setting::routes());

    if(problems.size() == 0){
        std::cout << "No problems were generated, obstructions are too high." << std::endl;
        return -1;
    }

    /* Set the problems to Data */
    datas_t datas; Data::setProblems(&problems);

    /* Divide the problems */
    auto start = problems.begin(); auto end = problems.begin();
    ai::size_t id = 0;
    for(end += ppt; start < problems.end(); start += ppt, end += ppt, id++){
        if(end >= problems.end() ) end = problems.end();
        datas.emplace_back(start, end, id);
    }

    /* Create and Initialize the thread */
    threads_t threads;
    for(ai::size_t it = 0; it < id; it++){
        threads.emplace_back(threadRun, &datas[it]);
    }

    /* Join the threads */
    for( auto t = threads.begin(); t != threads.end(); t++){
        t->join();
    }

    std::cout << std::endl << std::endl
              <<"-------------------------------------" << std::endl
              <<"              SOLUTIONS              " << std::endl
              <<"    COST; REPETITION; AVG_TIME       " << std::endl
              <<"-------------------------------------" << std::endl;

    /* Get the size of the datas */
    int totalSize = 0;
    for( auto d : datas)
        totalSize += d.getResults().size();

    /* Concatenate all datas in one */
    results_t allResults; allResults.reserve(totalSize);
    for( auto d : datas){
        allResults.insert(allResults.end(), d.getResults().begin(), d.getResults().end() );
    }

    /* Delete the datas */
    datas.clear(); datas.shrink_to_fit();

    #ifdef PRINT_EXEC
        /* Print all results */
        for( auto r : allResults){
            std::cout << r <<std::endl;
        }
    #endif

    /* Compact the data */
    compactResults_t compResults; compResults.resize(Setting::cubeSize()*4, compactResult_t(0,0,0.0));
    for( auto r : allResults){
        auto repet = std::get<1>(compResults[r.first]); auto time = std::get<2>(compResults[r.first]);
        compResults[r.first] = compactResult_t(r.first, repet+1, (double) (time * repet + r.second)/(repet+1));
    }

    /* Put compact results in a file to generate a grath later. */
    std::ofstream csvFile;
    csvFile.open(Setting::file());
    if(csvFile.is_open()){
        for( auto cr : compResults){
            /* Print all compact reulst */
            std::cout << cr <<std::endl;
            /* Put in the file */
            csvFile << cr <<std::endl;
        }
    }

    /* Cloese file */
    csvFile.close();

    /* End */
    return 0;
}


