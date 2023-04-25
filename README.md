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

First you need to load the configuration. There are several things in the configuration. At the beginning of the file are the times required to perform each of the mathematical operations. After that, there is a number that tells us how many operations can be performed in parallel. At the end, there is a compilation that talks about the strategy we use, and it can be **Simple** or **Advance**.
The strategy should divide each expression into simple mathematical operations that will be passed to the static library for processing. The Advance strategy, in contrast to the Simple strategy, sorts the operations so that the simplest ones are executed first and those that will take the least amount of time to execute. The operation can be performed only when the values of its operands have been calculated.
</br></br>
The **Configuration** class is responsible for this part.

---

### Creation of imf file

The **test.imf** file is created by the Compiler. It works so that the Compiler reads the test.txt file, converts the expressions into postfix form, divides each such expression into the smallest mathematical expressions made up of only one operation, and finally attaches it in a certain format.

#### Infix to Postfix

The program can hardly distinguish and resolve parentheses and mathematical operations in infix notation. Mathematical operations as well as parentheses have their own priority, which determines the order in which the operations will be performed. It is necessary to create a form that the computer can understand and that will work even without brackets. It is a postfix form. An example of switching expressions from infix notation to postfix is ​​given in the following image:

<p align="left">
  <img src="images/infixToPostfix.png" width="30%">
</p>

The **Compiler** and **Strategy** classes are responsible for this part. After converting the expression into postfix notation, it is necessary to single out each command that makes up that expression, and this will represent one line of the test.imf file. When it is finished, it is possible to see the transformation of the **test.txt** file into a **test.imf** file:

<p float="left">
  <img src="images/testTxt.png" width="30%" />
  <img src="images/arrow.png" width="10%" />
  <img src="images/testImf.png" width="30%" />
</p>

---

### Start Scheduler

---

### Make mem file
