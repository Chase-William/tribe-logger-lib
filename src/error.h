#pragma once
#include <tuple>

enum WinImgGetError : int {
  Success = 0,
  FailedToFindWindow = 1,
  FailedToGetClientRect = 2,
  BitBlockTransferFailed = 3,
  TesseractInitializationFailure = 4
};

typedef std::tuple<int*, char*> WinImgRtrn;
typedef std::tuple<int*, const char*> WinImgTextRtrn;