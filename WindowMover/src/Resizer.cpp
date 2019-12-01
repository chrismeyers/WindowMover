#include "Resizer.h"
#include <iostream>
#include <sstream>

Resizer::Resizer(const WindowMoverUtils::WindowInfo& info)
  : mWindowInfo(info), mWindowSize({})
{

}

Resizer::~Resizer() {

}

bool Resizer::parseSize(const std::string& size) {
  WindowMoverUtils::WindowSize maxSize = WindowMoverUtils::getMaxWindowSize();
  int i = 0;
  std::stringstream ss(size);
  std::string part;

  // Assume the input format is {{WIDTH}}x{{HEIGHT}}
  while(std::getline(ss, part, 'x')) {
    if(i == 0) {
      int width = std::stoi(part);
      if(width >= 0 && width <= maxSize.width) {
        mWindowSize.width = width;
      }
      else {
        std::cerr << "Width " << width << " is out of bounds!" << std::endl;
        return false;
      }
    }
    else if(i == 1) {
      int height = std::stoi(part);
      if(height >= 0 && height <= maxSize.height) {
        mWindowSize.height = height;
      }
      else {
        std::cerr << "Height " << height << " is out of bounds!" << std::endl;
        return false;
      }
    }
    else {
      std::cerr << "[WARN] There should only be 2 dimensions (skipping dimension " << (i + 1) << ")!" << std::endl;
    }
    i++;
  }

  return true;
}

void Resizer::resize(const HWND& hwnd) {
  std::cout << std::endl;

  if(!hwnd) {
    std::cerr << "[WARN] \"" << WindowMoverUtils::getFormattedWindowInfo(mWindowInfo)
              << "\" is not currently running." << std::endl << std::endl;
    return;
  }

  if(!IsWindow(hwnd)) {
    std::cerr << "[WARN] \"" << WindowMoverUtils::getFormattedWindowInfo(mWindowInfo)
              << "\" no longer exists." << std::endl << std::endl;
    return;
  }

  WindowMoverUtils::bringToFront(hwnd);

  std::cout << "Resizing \"" << WindowMoverUtils::getFormattedWindowInfo(mWindowInfo) << "\"...\n"
            << "  - Window Size: " << mWindowSize.width << "x" << mWindowSize.height << "\n" << std::endl;

  // TODO: The sizes are a little off when set this way. The adjustments
  // should be removed if an issue with SetWindowPos() exists.
  int wAdjustment = 14;
  int hAdjustment = 7;
  SetWindowPos(hwnd, 0, 0, 0, mWindowSize.width + wAdjustment, mWindowSize.height + hAdjustment, SWP_NOMOVE | SWP_NOOWNERZORDER | SWP_NOZORDER);
}