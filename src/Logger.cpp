#include "Logger.hpp"
#include "Timer.hpp"

Logger* Logger::m_instance = nullptr;
/// \brief Returns pointer to Logger.
Logger* Logger::Get()
{
    //Ensure single instance of Logger
    if(!m_instance)
    {
        m_instance = new Logger;
        Logger::Get()->log.open("log/GameLog.log");
    }
    return m_instance;
}
/// \brief Logs string to output file, with date and time when logging ocurred.
/// \param logText std::string : string that will be logged to file.
/// For logging, use macro LOG_STRING. Makes better code.
void Logger::Log(std::string logText)
{
    //Get current time
    Timer_Clock_System::time_point p = Timer_Clock_System::now();
    std::time_t t = Timer_Clock_System::to_time_t(p);
    //Get size of logText + colon, so we can remove newline char
    int sizeBefore = logText.size() + 2;
    logText.insert(0, ": ");
    //Create string with current time
    logText.insert(0, std::ctime(&t));
    //Remove newline
    logText[logText.size() - (sizeBefore + 1) ] = ' ';
    //Print. At last!
    log  << logText << std::endl;
}
Logger::~Logger()
{
    log.flush();
    log.close();
    delete m_instance;
    // You can never be sure
    m_instance = nullptr;
}
