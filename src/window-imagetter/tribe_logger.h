/*
  Authored by Chase Roth 8/7/2021
  See repository root directory for more information.
*/

#pragma once
#include <string>

/*
  Gets the text inside a tribe log.
  Param - windowName, Name of window to use as a source
*/
std::tuple<int*, const char*> InternalTryGetTribeLogText(
  std::string windowName, 
  int left, 
  int top, 
  int right, 
  int bottom
);