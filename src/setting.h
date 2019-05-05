#ifndef _SETTING_H_
#define _SETTING_H_

#include <iostream>

namespace ai
{

/**
 * Setting is a Singleton Class to read and parse all paramenter (the settiong of the program). 
 *
 * @author      Eduardo Culau
 * @version     1.5
 * @since       1.0
 */
class Setting
{
public:
    /**
     * Return the current instance or create one if it don't exist.
     *
     * @return      Setting pointer
     */
    static Setting* get(){
        if( !_instance ) {
            _instance = new Setting;
        }
        return _instance;
    }

    /**
     * Get the size of the cube
     *
     * @return size_t size of the cube NxNxN
     */
    static const size_t cubeSize () { return get()->_cubeSize; }

    /**
     * Get the percentage of obstructions
     *
     * @return size_t percentage of obstructions
     */
    static const size_t obstructions () { return get()->_obstructions; }

    /**
     * Get the number of routes to be tested.
     *
     * @return size_t number of routes
     */
    static const size_t routes () { return get()->_routes; }

    /**
     * Get the number of threads
     *
     * @return size_t number of threads
     */
    static const size_t threads () { return get()->_threads; }

    /**
     * Set the size of the cube
     *
     * @param  size size of the cube
     */
    static void cubeSize (int size) { get()->_cubeSize = size; }

    /**
     * Set the percentage of obstructions
     *
     * @param  obs percentage of obstructions
     */
    static void obstructions (int obs) { get()->_obstructions = obs; }

    /**
     * Set the number of routes
     *
     * @param  routes number of routes, 0 to all
     */
    static void routes (int routes) { get()->_routes = routes; }

    /**
     * Set the number of threads
     *
     * @param  threads number of threads, 0 to all
     */
    static void threads (int threads) { get()->_threads = threads; }

    /**
     * Set File
     */
    static void file (std::string file) { get()->_file = file; }

    /**
     * Get File
     */
    static const std::string& file () { return get()->_file; }

    /**
     * Read the arguments sent to the program.
     *
     * @param  argc number of arguments
     * @param  argv vector of arguments
     * @return      true if all is OK else false if some argumento is unknown
     */
    static bool readArgs(int argc, char **argv)
    {   
        /* All entries */
        for( int i = 1; i < argc; ) {
            /* Get an argument. */
            std::string arg(argv[i++]);

            /* Numer of missionaries */
            if( arg == "-h") {
                Setting::setHelp();

            /* Size of the cube */
            } else if( arg == "-c" && i < argc ) {
                Setting::cubeSize(std::atoi(argv[i++]));

            /* Percentage of obstructions */
            } else if( arg == "-o" && i < argc ) {
                Setting::obstructions(std::atoi(argv[i++]));

            /* Number of routes */
            } else if( arg == "-r" && i < argc ) {
                Setting::routes(std::atoi(argv[i++]));

            /* Number of threads */
            } else if( arg == "-t" && i < argc ) {
                Setting::threads(std::atoi(argv[i++]));

            /* Number of threads */
            } else if( arg == "-f" && i < argc ) {
                Setting::file(std::string(argv[i++]));

            } else {
                std::cerr<<"Unknown option: "<<arg<<std::endl;
                return false;
            }
        }
        return true;
    }


    /**
     * Parse all the entries (the arguments sent to the program)
     *
     * @return      true if all is OK else false if some argumento is unknown
     */
    static bool parseEntries(){
        bool valid = true;

        if( Setting::getHelp() ){
            std::cout<<"    Program Argumments  "<<std::endl
                     <<"-c [INT]  : size of the cube"<<std::endl
                     <<"-o [INT]  : percentage of obstructions"<<std::endl
                     <<"-r [INT]  : number of routes, 0 to all"<<std::endl
                     <<"-t [INT]  : number of threads, 0 to all"<<std::endl
                     <<"-f [FILE] : file to receive the results"<<std::endl
                     <<"-h        : show this text"<<std::endl;
            return false;
        }

        /* Check arguments values */
        if( get()->_cubeSize < 3 ){
            std::cout<<"The cube must to be at least 3x3x3."<<std::endl; valid = false;
        }

        if( get()->_obstructions < 0 ){
            std::cout<<"Obstructions must to be at least of 0%."<<std::endl; valid = false;
        }

        if( get()->_obstructions >= 100 ){
            std::cout<<"Obstructions must to be at maximum of 99%."<<std::endl; valid = false;
        }

        if( get()->_routes < 1 ){
            std::cout<<"Must to have at least 1 path do be done."<<std::endl; valid = false;
        }

        if( get()->_routes > get()->maxRoutes("permutation") && get()->maxRoutes("permutation") >= 0){
            std::cout<<"The max number of routes in that cube is "<<  get()->maxRoutes("permutation") << "." << std::endl; valid = false;
        }

        if( get()->_threads < 1 || get()->_threads >  (int) std::thread::hardware_concurrency()){
            std::cout<<"Must to have at least 1 and a maximum of "<< std::thread::hardware_concurrency() << " threads." << std::endl; valid = false;
        }

        if( get()->_file.empty()){
            std::cout<<"Please insert a file." << std::endl; valid = false;
        }


        return valid;
    }

    /**
     * Return the max number of routes
     * Combination or Permutation for (n,s). N is the number of available positions in the cube and s = 2 is the pair (initial and goal state)
     * P = n! / (n-s)! , for s = 2  P = n! / (n-2)! = (n*(n-1)*(n-2)*...)/((n-2)*...), so P = n*(n-1).
     * C = n! / (s! * (n-s)! ), for s = 2 C = P/2, so C = n*(n-1)/2.
     *
     * @return size_t number of obstructions
     */    
    static size_t maxRoutes(const std::string &type) {
        /* Calculate the permutation */
        long double n      = (long double) std::floor(std::pow( (long double) get()->_cubeSize, 3) * (100.0 - (long double) get()->_obstructions ) / 100.0);
        long double permut = n * (n-1);
        /* Return the chosen type */
        if( type == "permutation")
            return (size_t) permut;
        if( type == "combination")
            return (size_t) (permut / 2.0);
        else
            return 0;
    }


private:
    /**
     * The single instance of the class.
     */
    static Setting *_instance;
    
    /**
     * Private Constructor 
     */
    Setting() {
    }
    
    /**
     * Private Destructor
     */
    ~Setting(){}

    /**
     * Set help, so the class know that the user want to show the help text.
     */
    static void setHelp    () { get()->_help = true; }

    /**
     * Get the help argument.
     *
     * @return      help option (true or false)
     */
    static bool getHelp    () { return get()->_help; }

    /**
     * Cube size
     */
    size_t  _cubeSize = 0;

    /**
     * Obstructions
     */    
    size_t  _obstructions = -1;

    /**
     * Routes
     */ 
    size_t  _routes = 0;

    /**
     * Threads
     */ 
    size_t  _threads = 0;

    /**
     * File
     */ 
    std::string  _file;

    /**
     * Show help text.
     */ 
    bool _help = false;
};

/* Set the instance to 0, so only one object can be create. */
Setting *Setting::_instance = 0;

}

#endif

