#ifndef LOGGER_HPP
#define LOGGER_HPP

#include <fstream>
#include <string>

//Macro making logging easier, and code more readable.
#define LOG_STRING Logger::Get()->Log

/// \brief A logger class made as Singleton. Prints all logs into a single log file. Each program run will clear log file.
class Logger
{
protected:
    Logger() = default;

    std::ofstream log;
    static Logger* m_instance;
public:
    ~Logger();

    static Logger* Get();
    void Log(std::string logText);
    inline void Log(int num) { Log(std::to_string(num));};
};
#endif //LOGGER_HPP
