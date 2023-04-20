#pragma once

#include <iostream>
#include <string>
#include <vector>
#include "Operation.h"

using namespace std;

// Singleton class for simulation of 
// .imf file execution
class Machine{
 public:  

  // Returns instance of Machine
  static Machine& getInstance();

  Machine(const Machine& user) = delete;
  Machine& operator=(const Machine&) = delete;

  // Initialize machine with .imf file
  void init(string file);
  
  // Put operations ready for execution on scheduler
  void scheduale();

  // Execute initialized program
  void exec(string file);

  // Update all operations with given name-value pair
  void upadeState(string name, string value);

 private:
  Machine() = default;
  vector<Operation*> waiting_, executing_;
};