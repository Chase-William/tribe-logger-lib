#pragma once
#include <tuple>
//#include <nan.h>

enum WinImgGetError : int {
  FailedToFindWindow = 1,
  FailedToGetClientRect = 2,
  BitBlockTransferFailed = 3,
  TesseractInitializationFailure = 4
};

typedef std::tuple<int*, char*> WinImgRtrn;
typedef std::tuple<int*, const char*> WinImgTextRtrn;