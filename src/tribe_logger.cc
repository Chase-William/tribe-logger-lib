/*
  Authored by Chase Roth 8/1/2021
  See repository root directory for more information.
*/
#pragma once
#include "tribe_logger.h"

// Contructors

TribeLogger::TribeLogger() {
  windowStreamer = WindowImgStreamer();
}

TribeLogger::TribeLogger(std::string windowName) {
  windowStreamer = WindowImgStreamer(windowName);
}

// Functions

bool TribeLogger::Start(WindowImgStreamer::ErrorTypes &err) {

  // Delegate to window streamer
  return windowStreamer.Start(err);
}

void TribeLogger::Stop() {
  // Delegate to window streamer
  windowStreamer.Stop();
}