/*
  Source: https://github.com/99x/timercpp
*/
#pragma once
#include <iostream>
#include <thread>
#include <chrono>
#include <atomic>

// Custom Imple, added typedef for action lambdas
typedef void (*Elasped)();

class CustomTimer {
	std::atomic<bool> active{true};
	
  public:
      void setTimeout(Elasped function, int delay);
      void setInterval(Elasped function, int interval);
      void stop();
};