/*
  Authored by Chase Roth 8/1/2021
  See repository root directory for more information.
*/

#include "window_img_streamer.h"

WindowImgStreamer::WindowImgStreamer() {

}

WindowImgStreamer::WindowImgStreamer(std::string windowName) {
  srcWindowName = srcWindowName;
}

bool WindowImgStreamer::Start(WindowImgStreamingErrors &err) {
  hwnd = FindWindowA(NULL, srcWindowName.c_str()); // Get source window handle
  if (!hwnd) { // Cannot find window, report error with info
    err = FailedToFindWindow;
    return false;
  }
  // Get source window dimensions as a rectangle
  if (!GetClientRect(hwnd, &srcWindowRect)) {
    err = FailedToGetSourceWindowRect;
    return false;
  }

  HDC hdcSrcWindow = GetDC(hwnd); // Source window device-context handle
  HDC hdcTarget = CreateCompatibleDC(NULL); // Get in-memory DC, not connected to a device
  //HBITMAP hbmpTarget; // Handle to target bmpBuffer
  BITMAP bmpObj; // Actual Bitmap object from GetObject()
  RECT srcClientRect; // Bitmap Dimensions
  DWORD dwSizeofDIB = 0;
  char* lpPixels = NULL;
  DWORD dwBmpSize = 0;

  width = srcClientRect.right - srcClientRect.left;
  height = srcClientRect.bottom - srcClientRect.top;

  // Create compatible bmpBuffer with the source window DC
  hbmpTarget = CreateCompatibleBitmap(hdcSrcWindow, width, height);
  if (!hbmpTarget) {
    err = FailedToCreateCompatibleBitmap;
    return false;
  }
  HGDIOBJ hgdiobj = SelectObject(hdcTarget, hbmpTarget);
  if (!hgdiobj || hgdiobj == HGDI_ERROR) {
    err = FailedToSelectObjectBitmapIntoDeviceContext;
    return false;
  }
}

void WindowImgStreamer::Stop() {
  DeleteObject(hbmpTarget); // cleanup bitmap
  ReleaseDC(NULL, hdcTarget); // Cleanup hdc target
  ReleaseDC(hwnd, hdcSrcWindow); // Cleanup hdc from the source window handle  
}