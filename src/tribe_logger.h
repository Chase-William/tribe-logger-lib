/*
  Authored by Chase Roth 8/1/2021
  See repository root directory for more information.
*/
#pragma once
#include <Windows.h>
#include <string>
#include "window_img_streamer.h"

class TribeLogger {
  public:    
    TribeLogger();
    TribeLogger(std::string windowName);
    // Starts the TribeLogger
    bool Start(WindowImgStreamer::ErrorTypes &err);
    // Stops the TribeLogger
    void Stop();

  private:
    // Used for streaming bitmaps from the source window
    WindowImgStreamer windowStreamer;
};