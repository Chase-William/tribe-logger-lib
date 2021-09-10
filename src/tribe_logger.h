/*
  Authored by Chase Roth 8/7/2021
  See repository root directory for more information.
*/

#pragma once
#include <string>
#include "types.h"

/*
  Gets the text inside a tribe log.
  Param - windowName, Name of window to use as a source
*/
TribeLogResult InternalTryGetTribeLogText(
  std::string windowName, 
  std::string tessData,
  int left, 
  int top, 
  int width, 
  int height
);