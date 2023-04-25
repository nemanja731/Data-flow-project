# Data-flow-project

## About project

The project realizes the simulation of data flow processing. Two input files **config.txt** and **test.txt** are loaded.
</br></br>
In the file **config.txt** there is the configuration of the project, which determines how the project will function:

<p align="left">
  <img src="images/configTxt.png" width="30%">
</p>

In the file **test.txt** there are mathematical expressions that include basic operations, where each expression can have several operations, and it is separated in a separate line:

<p align="left">
  <img src="images/testTxt.png" width="30%">
</p>

In addition to the two input files, a static library **lib** with an already designed data processing tool is provided. The goal of the project is to load the input files, use the attached static library and implement the compiler. The compiler needs to divide mathematical expressions into the smallest operations and execute them individually. Some operations in parallel, some not, and as a final result, it should return a test.mem file that contains in each row, sorted by the time of the start of execution, the operation that was executed and their duration in ns.

## Main parts of the project

### Read configuration

### Infix to Postfix

<p align="left">
  <img src="images/infixToPostfix.png" width="30%">
</p>

### Creation of imf file

<p float="left">
  <img src="images/testTxt.png" width="30%" />
  <img src="images/arrow.png" width="10%" />
  <img src="images/testImf.png" width="30%" />
</p>
test.txt        ->        test.imf

### Start Scheduler

### Make mem file
