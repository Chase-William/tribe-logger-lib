/*
  Authored by Chase Roth 8/1/2021
  See repository root directory for more information.
*/

#pragma once
#include <string>
#include <Windows.h>
#include "timer.h"

class WindowImgStreamer {
  public:
    enum ErrorTypes {
      FailedToFindWindow,
      FailedToGetSourceWindowRect,
      FailedToCreateCompatibleBitmap,
      FailedToSelectObjectBitmapIntoDeviceContext
    };

    // Create a default WindowImageStreamer
    WindowImgStreamer();
    /*
      Creates a WindowImgStreamer using the specififed parameters.
      Param - windowName, name of the window to search for and use as a source
    */
    WindowImgStreamer(std::string windowName);
    // Starts the window streaming, returns false if there is a failure
    bool Start(ErrorTypes &err);
    // Stops the window streaming
    void Stop();   
  private:
    void Init();

    HWND hwnd;
    std::string srcWindowName;
    bool isWindowValid;
    RECT srcWindowRect;

    std::shared_ptr<CustomTimer> timer;

    // Width & Height cache of window rectangle / bitmap
    int width, height;
    // Unmanaged streaming resources to be cleanup everytime streaming is stopped / started
    HBITMAP hbmpTarget; // Handle to target bmpBuffer
    HDC hdcSrcWindow; // Handle to device context of source window
    HDC hdcTarget; // Handle to device context of target in memory device context in our case
};