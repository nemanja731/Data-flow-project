#pragma once

#include <iostream>
#include <string>
#include <vector>
#include "Operation.h"

using namespace std;

// execute imf file
class Machine
{
public:
  static Machine &getInstance();
  Machine(const Machine &machine) = delete;
  Machine &operator=(const Machine &) = delete;

  void readImf(string fileName);
  void schedule();
  void execute(string fileName);
  void updateAllOperations(string name, string value);

private:
  Machine() = default;

  vector<Operation *> waitingOperations, executingOperations;
};