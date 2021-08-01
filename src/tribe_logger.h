/*
  Authored by Chase Roth 8/1/2021
  See repository root directory for more information.
*/

#include <Windows.h>
#include <string>

class TribeLogger {
  public:    
    TribeLogger(std::string srcWindowName);
    // Starts the TribeLogger
    void Start();
    // Stops the TribeLogger
    void Stop();
};