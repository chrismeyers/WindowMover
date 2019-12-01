#include "Utils.h"
#include <iostream>
#include <algorithm>

namespace WindowMoverUtils {
  WindowSize getWindowSize(const HWND& hwnd) {
    RECT window;
    GetWindowRect(hwnd, &window);
    int windowWidth = window.right - window.left;
    int windowHeight = window.bottom - window.top;

    return { windowWidth, windowHeight };
  }

  WindowSize getMaxWindowSize() {
    // TODO: Add support for multiple monitors.
    RECT desktop;
    const HWND hDesktop = GetDesktopWindow();
    GetWindowRect(hDesktop, &desktop);

    return { desktop.right, desktop.bottom };
  }

  bool shouldExit(std::string s) {
    std::transform(s.begin(), s.end(), s.begin(), ::tolower);
    if(s == "q" || s == "quit" || s == "exit") {
      exit(0);
    }
    return false;
  }

  bool shouldRestart(std::string s) {
    std::transform(s.begin(), s.end(), s.begin(), ::tolower);
    if(s == "r" || s == "restart") {
      return true;
    }
    return false;
  }

  bool validYes(std::string s) {
    std::transform(s.begin(), s.end(), s.begin(), ::tolower);
    if(s == "y" || s == "yes") {
      return true;
    }
    return false;
  }

  bool validSelection(const std::string& s, int max) {
    shouldExit(s);

    try {
      int value = std::stoi(s);

      if((value <= max) && value > 0) {
        return true;
      }
      else {
        std::cerr << "[ERROR] Input out of bounds";
      }
    }
    catch(std::invalid_argument e) {
      std::cerr << "[ERROR] Invalid input";
    }

    std::cerr << " - enter a number between 1 and " << max << std::endl;
    return false;
  }

  void bringToFront(const HWND& hwnd) {
    // Save a handle to the command prompt.
    HWND cmdPrompt = GetForegroundWindow();

    // Restore the window if minimized.
    SendMessage(hwnd, WM_SYSCOMMAND, SC_RESTORE, 0);

    // Make sure the window is in front.
    SetActiveWindow(hwnd);
    SetForegroundWindow(hwnd);

    // Give control back to the command prompt.
    SetForegroundWindow(cmdPrompt);
  }

  std::string getFormattedWindowInfo(const WindowInfo& info) {
    return info.name + " [" + std::to_string(info.pid) + "]";
  }
}