# BIUAdvancedProgramming1-MS-2
By: Amit Twito

link :
https://github.com/AmitTwito/BIUAdvanedProg1-MS-2

## Background on the project
This project is a 2 parts assignment as a part of a course called Advanced Programming 1 in our Computer Seince degree of second year in Bar Ilan University, written in c++ (c++14 and bellow).

## Miles stone 2 - Problem solving server
In this second milestone of the project, we'll build a tcp server that accepts clients that will send problems and the server 
will send back solutions. The implementation of the proggram will be according to the s.o.l.i.d principles through making everything generic as possible and open to extensions.

### Getting Started and Prerequisites

To get started and operate the program, follow the next steps.

1.Download the following files to your computer and place it under one new folder:
```
main.cpp
CacheManager.h, ClientHandler.h, ClientHandler.cpp
Matrix.h, MyPriorityQueue.h
Searchable.h, Searcher.h
Server.cpp, Server.h
Solver.h, State.h
StateValueContainer.h, StringBuilder.h

matrices folder
auto_client.py
parallel_tester.py
txt files with matrices according to the following instuctions.

```

2.Now we need to compile the code. Open a terminal or a cmd through the new folder we created in the first instuction and type the following line:
```
g++ -std=c++14 *.cpp -pedantic -o a.out -pthread
```
Make sure you have a g++ compiler installed : 
windows:
https://www.tutorialspoint.com/How-to-Install-Cplusplus-Compiler-on-Windows
linux:
Open terminal and run the following:
```sudo apt install g++```
(The program works on c++14 and bellow).

3.Once a file called a.out is created, run the line (from the folder that contains the files):
```./a.out PORT_NUM ```  as ```PORT_NUM``` needs to be the port to open a tcp server at.

4.The program is waiting for a client(s) to connect to a server that wis opened, then we'll need to open a new terminal window
from the folder with the py files and run the wanted python script by : ``` python3 SCRIPT_NAME.py``` or  ```python SCRIPT_NAME.py```.


### General explanations on the code - how does it work
```main.cpp``` accepts through an argument a port number for the server to open
and then uses the ```main``` funcion of the Main calls in ```boot``` namespace to start the program.
```
void boot::Main::main(string port) {
  //Current cache manager.
  CacheManager<Matrix<double>, string> *cm = new FileCacheManager<Matrix<double>>();
  //Here i choose the Astar algoritm as the best one for the OA solver.
  Solver<Matrix<double>, string> *solver = new MatrixProblemSolverOA<double>(new AStar<double>);
  //Client handler.
  ClientHandler *ch = new MatrixSearchingClientHandler(solver, cm);
  Server *server = new MyParallelServer();
  try {
    int p = stoi(port);
    server->open(p, ch);
  } catch (const char *e) {
    cout << e << endl;
    server->stop();
  }
}
```
First, we create a new object of ```ClientHandler``` which has 2 objects : ```Solver<Solution,Problem>``` and
A
we open the server:
There are 2 kinds of servers in this project :
* ```MySerialServer``` is for accepting clients in a serial way- handling one client each time
* ```MyParallelServer``` is for accepting clients in a parallel way - can handle 10 clients in the same time.




### Possible changes / improvements
-Configuring the problems that the clients send to the server with identifiers to problems so we can choose the right 
templates to work with - can be with enum.

