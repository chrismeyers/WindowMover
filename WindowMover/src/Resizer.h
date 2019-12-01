#pragma once

#include "Utils.h"
#include <string>

class Resizer {
public:
  Resizer(const WindowMoverUtils::WindowInfo& info);
  ~Resizer();

  bool parseSize(const std::string& size);
  void resize(const HWND& hwnd);
  inline std::string getWindowName() { return mWindowInfo.name; }
  inline DWORD getWindowPid() { return mWindowInfo.pid; }
private:
  WindowMoverUtils::WindowInfo mWindowInfo;
  WindowMoverUtils::WindowSize mWindowSize;
};

