#pragma once
#include "timer.h"

void CustomTimer::setTimeout(Elasped function, int delay) {
  active = true;
  std::thread t([=]() {
      if(!active.load()) return;
      std::this_thread::sleep_for(std::chrono::milliseconds(delay));
      if(!active.load()) return;
      function();
  });
  t.detach();
}

void CustomTimer::setInterval(Elasped function, int interval) {
  active = true;
  std::thread t([=]() {
      while(active.load()) {
          std::this_thread::sleep_for(std::chrono::milliseconds(interval));
          if(!active.load()) return;
          function();
      }
  });
  t.detach();
}

void CustomTimer::stop() {
  active = false;
}