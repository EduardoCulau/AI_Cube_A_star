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
     * Get the number of missionaries
     *
     * @return      number of missionaries
     */
    static const size_t missionaries () { return get()->_missionaries; }

    /**
     * Get the number of cannibals
     *
     * @return      number of cannibals
     */
    static const size_t cannibals    () { return get()->_cannibals;    }

    /**
     * Get the boat capacity
     *
     * @return      boat capacity
     */
    static const size_t boatCapacity () { return get()->_boatCapacity; }

    /**
     * Set the number of missionaries
     *
     * @param  miss number of missionaries
     */
    static void missionaries (int miss) { get()->_missionaries = miss; }

    /**
     * Set the number of cannibals
     *
     * @param  cann number of cannibals
     */
    static void cannibals    (int cann) { get()->_cannibals    = cann; }

    /**
     * Set the boat caácity
     *
     * @param  bCap boat capacity
     */
    static void boatCapacity (int bCap) { get()->_boatCapacity = bCap; }

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
                Setting::missionaries(std::atoi(argv[i++]));

            /* Percentage of obstructions */
            } else if( arg == "-o" && i < argc ) {
                Setting::cannibals(std::atoi(argv[i++]));

            /* Number of paths */
            } else if( arg == "-p" && i < argc ) {
                Setting::boatCapacity(std::atoi(argv[i++]));

            /* Number of threads */
            } else if( arg == "-t" && i < argc ) {
                Setting::boatCapacity(std::atoi(argv[i++]));

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
                     <<"-c [INT] : size of the cube"<<std::endl
                     <<"-o [INT] : percentage of obstructions"<<std::endl
                     <<"-p [INT] : number of paths"<<std::endl
                     <<"-t [INT] : number of threads"<<std::endl
                     <<"-h       : show this text"<<std::endl;
            return false;
        }

        /* Check arguments values */
        if( get()->_cubeSize < 3 ){
            std::cout<<"The cube musto to be at least 3x3x3."<<std::endl; valid = false;
        }

        if( get()->_ < 1 ){
            std::cout<<"Must to have at least 1 cannibal."<<std::endl; valid = false;
        }

        if( get()->_boatCapacity < 2 ){
            std::cout<<"The boat capacity must to be at least 2."<<std::endl; valid = false;
        }

        /* Must not have more cannibals than missionaries. */
        if( get()->_cannibals > get()->_missionaries ){
             std::cout<<"The number of missionaries must to be equal or greater the number of cannibals."<<std::endl; valid = false;
        }

        return valid;
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
     * Number of missionaries.
     */
    size_t  _cubeSize = 0;

    /**
     * Number of cannibals.
     */    
    size_t  _obstructions = 0;

    /**
     * Boar capacity.
     */ 
    size_t  _paths = 0;

    /**
     * Boar capacity.
     */ 
    size_t  _threads = 0;

    /**
     * Show help text.
     */ 
    bool _help            = false;
};

/* Set the instance to 0, so only one object can be create. */
Setting *Setting::_instance = 0;

}

#endif

