#pragma once

#include <windows.h>
#include <string>

namespace WindowMoverUtils {
  struct WindowSize {
    int width;
    int height;
  };

  struct Position {
    int X;
    int Y;
  };

  struct WindowInfo {
    std::string name;
    DWORD pid;
  };

  WindowSize getWindowSize(const HWND& hwnd);
  WindowSize getMaxWindowSize();
  bool shouldExit(std::string s);
  bool shouldRestart(std::string s);
  bool validYes(std::string s);
  bool validSelection(const std::string& s, int max);
  void bringToFront(const HWND& hwnd);
  std::string getFormattedWindowInfo(const WindowInfo& info);
}