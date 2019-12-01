#include "Lister.h"
#include <iostream>
#include <algorithm>

Lister::Lister()
  : mWindowList(WindowList())
{
  list();
}

Lister::~Lister() {

}

BOOL CALLBACK EnumWindowsProcListerCallback(HWND hwnd, LPARAM lParam) {
  return reinterpret_cast<Lister*>(lParam)->EnumWindowsProc(hwnd);
}

void Lister::list() {
  mWindowList.clear();
  EnumWindows(EnumWindowsProcListerCallback, reinterpret_cast<LPARAM>(this));
}

bool Lister::EnumWindowsProc(const HWND& hwnd) {
  char buff[255];

  if(IsWindowVisible(hwnd)) {
    GetWindowText(hwnd, (LPSTR)buff, 254);

    DWORD pid = -1;
    GetWindowThreadProcessId(hwnd, &pid);

    if(strcmp(buff, "") != 0 && pid > 0) {
      mWindowList[buff] = { { buff, pid }, hwnd };
    }
  }

  return true;
}

void Lister::printWindowList() {
  for(auto win : mWindowList) {
    std::cout << WindowMoverUtils::getFormattedWindowInfo(win.second.info) << std::endl;
  }
}
