#ifndef CONFIG_HPP
#define CONFIG_HPP

#include <string>

class Config
{
  std::string loggerPath;
  bool muted;
protected:
  Config()
  {
    muted = false;
    loggerPath = "";
  }
public:
  static Config& Get()
  {
    static Config config;
    return config;
  }
  std::string getLoggerPath()
  {
    return loggerPath;
  }
  void setLoggerPath(std::string newPath)
  {
    loggerPath = newPath;
  }
  bool getMuted()
  {
    return muted;
  }
  void setMuted(bool newMuted)
  {
    muted = newMuted;
  }
};

#endif //CONFIG_HPP
