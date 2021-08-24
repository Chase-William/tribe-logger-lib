/*
  Authored by Chase Roth 7/25/2021
  See repository root directory for more information.
*/

#pragma once
#include <string>
#include <Windows.h>
#include "error.h"

/*
  Gets a bitmap buffer from a specific window.
  Param - srcWindowName, name of window to find and get bitmap from
  Param - size, size of the bitmap buffer being returned
  Return, pointer to the head of the bitmap buffer
*/
WinImgRtrn GetNativeWindowBitmap(std::string windowName, unsigned long &size);

/*
  Finalizer callback for releasing unmanaged resources.
*/
void DisposeNativeBitmap(char *data, void *hint);