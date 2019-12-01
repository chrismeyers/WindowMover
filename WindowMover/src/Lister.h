#pragma once

#include "Utils.h"
#include <windows.h>
#include <map>
#include <string>

class Lister {
public:
  struct WindowListItem {
    WindowMoverUtils::WindowInfo info;
    HWND handle;
  };
  typedef std::map<std::string, WindowListItem> WindowList; // map<string name, WindowListItem item>
public:
  Lister();
  ~Lister();
  void list();
  bool EnumWindowsProc(const HWND& hwnd);
  void printWindowList();
  inline WindowList getWindowList() { return mWindowList; }
private:
  WindowList mWindowList;
};

