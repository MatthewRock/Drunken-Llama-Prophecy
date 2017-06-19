#include "GameEngine.hpp"
#include "Config.hpp"
#include <getopt.h>
#include <iostream>
#include <string>

using namespace Llama;

int main(int argc, char* argv[])
{
  int choice;
  static struct option long_options[] =
    {
      {"silent", no_argument, 0, 's'},
      {"logger", required_argument, 0, 'l'},
      {"swear", optional_argument, 0, 'w'},
      {0,0,0,0}
    };
  int silence = false;
  int option_index = 0;
  std::string curses[] = {"You stink, ", "I don't like you, ", "You are so ugly, ", "Workout some time, ", "You look like Windows user, "};
  int random_number = 4; // dice says so
  std::string& curse = curses[random_number];
  std::string name;

  while ((choice = getopt_long(argc, argv, ":sl:w::", 
                          long_options, &option_index)) != -1)
    {
      switch(choice)
        {
        case 0:
          break;
        case 's':
          Config::Get().setMuted(true);
          break;
        case 'w':
            if(optarg)
              {
                name = std::string(optarg);
              }
            else
              {
                name = "User";
              }
            std::cout << curse << name << "!" << std::endl;
            break;
        case 'l':
          Config::Get().setLoggerPath(optarg);
          break;
        case '?':
          std::cout << "Unknown option" << std::endl;
          break;
        }
    }

    GameEngine DrunkenLlamaProphecy;
    DrunkenLlamaProphecy.Run();

    return 0;
}
