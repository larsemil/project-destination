#include <iostream>
#include <cerrno>
#include <boost/program_options.hpp>
#include "GameEngine.hpp"

namespace po = boost::program_options;

int main(int argc, char ** argv)
{
  // Check for command line options
  po::options_description desc("Allowed options");
  desc.add_options()
    ("help", "show this help message")
    ("port", po::value<std::string>(), "set the listen port")
    ;
  po::variables_map vm;
  po::store(po::parse_command_line(argc, argv, desc), vm);
  po::notify(vm);    

  if (vm.count("help"))
  {
    std::cout << desc << std::endl;
    return 1;
  }

  GameEngine* gameEngine = GameEngine::Instance();

  try
  {
    gameEngine->Initialize();
    gameEngine->Start();
  }
  catch (const char* e)
  {
    std::cout << "Caught error: " << e << std::endl;
    std::cout << "Errno says '" << strerror(errno) << "'" << std::endl;
  }
}
