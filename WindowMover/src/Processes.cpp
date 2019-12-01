#include "Processes.h"
#include <stdio.h>
#include <tchar.h>
#include <psapi.h>
#include <sstream>
#include <iostream>

// This isn't needed for the window mover.  However, this is how
// you can get process data.

Processes::Processes()
  : mProcessMap(ProcessMap())
{
  buildProcessMap();
}

Processes::~Processes() {

}

void Processes::buildProcessMap() {
  // https://msdn.microsoft.com/en-us/library/windows/desktop/ms682623(v=vs.85).aspx

  // Get the list of process identifiers.
  DWORD processes[1024], cbNeeded, numProcesses;

  if(!EnumProcesses(processes, sizeof(processes), &cbNeeded)) {
    // TODO: Handle this error properly.
    return;
  }

  // Calculate how many process identifiers were returned.
  numProcesses = cbNeeded / sizeof(DWORD);

  for(unsigned int i = 0; i < numProcesses; i++) {
    if(processes[i] != 0) {
      TCHAR processName[MAX_PATH] = TEXT("<unknown>");

      // Get a handle to the process.
      HANDLE hProcess = OpenProcess(PROCESS_QUERY_INFORMATION | PROCESS_VM_READ, FALSE, processes[i]);

      // Get the process name.
      if(hProcess != NULL) {
        HMODULE hMod;
        DWORD cbNeeded;

        if(EnumProcessModules(hProcess, &hMod, sizeof(hMod), &cbNeeded)) {
          GetModuleBaseName(hProcess, hMod, processName, sizeof(processName) / sizeof(TCHAR));
        }

        // Update the map.
        mProcessMap.push_back(std::make_pair(processName, processes[i]));

        // Release the handle to the process.
        CloseHandle(hProcess);
      }
    }
  }
}

DWORD Processes::getPidFromName(std::string name) {
  for(auto& proc : mProcessMap) {
    if(proc.first == name) {
      return proc.second;
    }
  }

  return -1;
}

std::string Processes::getNameFromPid(DWORD pid) {
  for(auto& proc : mProcessMap) {
    if(proc.second == pid) {
      return proc.first;
    }
  }

  return "";
}

void Processes::printProcessMap() {
  for(auto& proc : mProcessMap) {
    std::cout << proc.first << " (" << proc.second << ")" << std::endl;
  }
}
