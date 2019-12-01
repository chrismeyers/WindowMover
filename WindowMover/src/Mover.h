#pragma once

#include "Utils.h"
#include <string>

class Mover {
public:
  enum class Layout {
    LEFT_CENTER, CENTER, RIGHT_CENTER, CURRENT, __LAST
  };
public:
  Mover(const WindowMoverUtils::WindowInfo& info);
  ~Mover();
  void move(const Layout& layout, HWND hwnd);
  std::string getLayoutString(const Layout& layout);
  inline std::string getWindowName() { return mWindowInfo.name; }
  inline DWORD getWindowPid() { return mWindowInfo.pid; }
private:
  WindowMoverUtils::Position getCenterCoords(const HWND& hwnd);
  WindowMoverUtils::Position getLeftCenterCoords(const HWND& hwnd);
  WindowMoverUtils::Position getRightCenterCoords(const HWND& hwnd);
  void setTaskbarHeight();
private:
  WindowMoverUtils::WindowInfo mWindowInfo;
  Layout mLayout;
  int mTaskbarHeight;
  WindowMoverUtils::WindowSize mWindowSize;
  WindowMoverUtils::WindowSize mDesktopSize;
};
