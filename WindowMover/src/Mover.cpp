#include "Mover.h"
#include <iostream>

Mover::Mover(const WindowMoverUtils::WindowInfo& info)
  : mWindowInfo(info), mLayout(Layout::CENTER), mTaskbarHeight(0),
    mWindowSize({}), mDesktopSize({})
{
  setTaskbarHeight();
}

Mover::~Mover() {

}

void Mover::move(const Layout& layout, HWND hwnd) {
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

  mLayout = layout;

  if(mLayout == Layout::CURRENT) {
    std::cout << "Keeping \"" << WindowMoverUtils::getFormattedWindowInfo(mWindowInfo)
              << "\" where it is..." << std::endl << std::endl;
    return;
  }

  WindowMoverUtils::bringToFront(hwnd);

  mWindowSize = WindowMoverUtils::getWindowSize(hwnd);
  mDesktopSize = WindowMoverUtils::getMaxWindowSize();
  WindowMoverUtils::Position coords = { 0, 0 };

  if(mLayout == Layout::CENTER) {
    coords = getCenterCoords(hwnd);
  }
  else if(mLayout == Layout::LEFT_CENTER) {
    coords = getLeftCenterCoords(hwnd);
  }
  else if(mLayout == Layout::RIGHT_CENTER) {
    coords = getRightCenterCoords(hwnd);
  }

  std::cout << "Moving \"" << WindowMoverUtils::getFormattedWindowInfo(mWindowInfo) << "\"...\n"
            << "  - Window Size: " << mWindowSize.width << "x" << mWindowSize.height << "\n"
            << "  - Desktop Size: " << mDesktopSize.width << "x" << mDesktopSize.height << "\n"
            << "  - Moved Location: " << coords.X << ", " << coords.Y << "\n" << std::endl;

  SetWindowPos(hwnd, 0, coords.X, coords.Y, 0, 0, SWP_NOSIZE | SWP_NOOWNERZORDER | SWP_NOZORDER);
}

WindowMoverUtils::Position Mover::getCenterCoords(const HWND& hwnd) {
  int x, y;
  x = (mDesktopSize.width - mWindowSize.width) / 2;
  y = ((mDesktopSize.height - mTaskbarHeight) - mWindowSize.height) / 2;

  return { x, y };
}

WindowMoverUtils::Position Mover::getLeftCenterCoords(const HWND& hwnd) {
  int x, y;
  x = ((mDesktopSize.width / 2) - mWindowSize.width) / 2;
  y = ((mDesktopSize.height - mTaskbarHeight) - mWindowSize.height) / 2;

  return { x, y };
}

WindowMoverUtils::Position Mover::getRightCenterCoords(const HWND& hwnd) {
  int x, y;
  x = (mDesktopSize.width / 2) + (((mDesktopSize.width / 2) - mWindowSize.width) / 2);
  y = ((mDesktopSize.height - mTaskbarHeight) - mWindowSize.height) / 2;

  return { x, y };
}

void Mover::setTaskbarHeight() {
  APPBARDATA data;
  data.cbSize = sizeof(data);
  SHAppBarMessage(ABM_GETTASKBARPOS, &data);
  mTaskbarHeight = data.rc.bottom - data.rc.top;
}

std::string Mover::getLayoutString(const Layout& layout) {
  if(layout == Layout::LEFT_CENTER) {
    return "Centered - Left Half";
  }
  else if(layout == Layout::CENTER) {
    return "Centered - Middle";
  }
  else if(layout == Layout::RIGHT_CENTER) {
    return "Centered - Right Half";
  }
  else if(layout == Layout::CURRENT) {
    return "Keep the current position";
  }

  return "";
}