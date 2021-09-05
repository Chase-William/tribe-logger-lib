#pragma once
#include <tuple>

enum WinImgGetError : int {
  Success = 0,
  FailedToFindWindow = 1,
  FailedToGetClientRect = 2,
  BitBlockTransferFailed = 3,
  TesseractInitializationFailure = 4
};

/**
 * I will need to change this later because this is getting out of hand...
 * error int, pixel-data (may contain 54 byte header), size in bytes, width (in pixels), height (in pixels)
 */
//typedef std::tuple<int*, char*, unsigned long, long, long> WinImgRtrn;
//typedef std::tuple<int*, const char*> WinImgTextRtrn;

class WindowReturn {
  public:

  int* ErrorCode;

  WindowReturn(int* errorCode) : ErrorCode(errorCode) { }
};

class WindowBitmapResult : public WindowReturn {
  public:
  
  char* BitmapBuffer;
  unsigned long Size;
  long Width;
  long Height;

  WindowBitmapResult(int* errorCode, char* bitmapBuffer, unsigned long size, long width, long height) 
    : WindowReturn(errorCode), 
      BitmapBuffer(bitmapBuffer),
      Size(size),
      Width(width),
      Height(height)
  { }
};

class TribeLogResult : public WindowReturn {
  public:

  std::string TribeLogText;

  TribeLogResult(int* errorCode, std::string text) : WindowReturn(errorCode), TribeLogText(text) { }
};