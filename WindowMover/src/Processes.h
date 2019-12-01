#pragma once

#include <windows.h>
#include <utility>
#include <vector>
#include <string>

// This isn't needed for the window mover.  However, this is how
// you can get process data.

class Processes {
public:
  typedef std::vector<std::pair<std::string, DWORD>> ProcessMap; // vector<sting name, DWORD pid>
public:
  Processes();
  ~Processes();
  void buildProcessMap();
  DWORD getPidFromName(std::string name);
  std::string getNameFromPid(DWORD pid);
  void printProcessMap();
  inline ProcessMap getProcessMap() const { return mProcessMap; }
private:
  ProcessMap mProcessMap;
};
