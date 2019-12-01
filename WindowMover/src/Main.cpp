#include "Lister.h"
#include "Mover.h"
#include "Resizer.h"
#include "Utils.h"
#include <iostream>
#include <vector>

bool run() {
  Lister lister = Lister();
  Lister::WindowList windows = lister.getWindowList();

  std::cout << "Usage:\n"
    << "  - Press Enter to reload list\n"
    << "  - Exit by typing \"q\", \"quit\", or \"exit\"\n"
    << "  - Start over by typing \"r\" or \"restart\"\n" << std::endl;

  // Select the window to move.
  std::vector<Lister::WindowListItem> windowInfo;
  int i = 0;
  for(auto& window : windows) {
    windowInfo.push_back(window.second);
    std::cout << i + 1 << ": " << WindowMoverUtils::getFormattedWindowInfo(window.second.info) << std::endl;
    i++;
  }

  std::string selectedWindow;
  do {
    std::cout << "Select a window to move: ";
    std::getline(std::cin, selectedWindow);
    if(WindowMoverUtils::shouldRestart(selectedWindow) || selectedWindow.empty()) {
      return true; // Refresh the list if blank input.
    }
  } while(!WindowMoverUtils::validSelection(selectedWindow, i));

  int windowNum = std::stoi(selectedWindow);
  windowNum--;

  // Resize the window.
  std::cout << "Change the size of the window? [y/N]: ";
  std::string shouldChangeSize;
  std::getline(std::cin, shouldChangeSize);
  if(WindowMoverUtils::shouldRestart(shouldChangeSize)) {
    return true;
  }
  else if(WindowMoverUtils::validYes(shouldChangeSize)) {
    Resizer resizer = Resizer(windowInfo[windowNum].info);

    std::string windowSize;
    do {
      WindowMoverUtils::WindowSize maxSize = WindowMoverUtils::getMaxWindowSize();
      std::cout << "Specify a size (max: " << maxSize.width << "x" << maxSize.height << "): ";
      std::getline(std::cin, windowSize);
      if(WindowMoverUtils::shouldRestart(windowSize)) {
        return true;
      }
    } while(!WindowMoverUtils::shouldExit(windowSize) && !resizer.parseSize(windowSize));

    resizer.resize(windowInfo[windowNum].handle);
  }

  // Select the Layout.
  Mover mover = Mover(windowInfo[windowNum].info);

  for(i = 0; i < (int)Mover::Layout::__LAST; i++) {
    std::cout << i + 1 << ": " << mover.getLayoutString((Mover::Layout)i) << std::endl;
  }

  std::string positionSelection;
  do {
    std::cout << "Select a layout: ";
    std::getline(std::cin, positionSelection);
    if(WindowMoverUtils::shouldRestart(positionSelection)) {
      return true;
    }
  } while(!WindowMoverUtils::validSelection(positionSelection, i));

  int windowPosition = std::stoi(positionSelection);
  windowPosition--;

  mover.move((Mover::Layout)windowPosition, windowInfo[windowNum].handle);

  system("pause");
  return true;
}

int main() {
  while(1) {
    if(run()) {
      system("cls"); // Clear the console on success or restart.
    }
  }

  return 0;
}
