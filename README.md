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

matrices folder with:
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

4.The program is waiting for a client(s) to connect to a server that wis opened, then we'll need to open a new cmd or terminal window
from the folder with the py files and run the wanted python script by : ``` python SCRIPT_NAME.py```.
make sure you have python 2.7 installed.

### General explanations on the code - how does it work
This proggram opens a server of the following types:
* ```MySerialServer``` is for accepting clients in a serial way- handling one client each time
* ```MyParallelServer``` is for accepting clients in a parallel way - can handle 10 clients in the same time.
Once it is opened, it waits for clients to connect. In this proggram the clients send matrices of numbers and an entering point and an exiting point, and the server will use A ```Searcher``` - the best algorithm that was (algorithm AStar) and send a shortest path (cheapest path) from the entering to the exiting point in the matric, as the numbers in every cell are the costs of stepping on the current cell.
Example:
```
Down (12) ,Down (13) ,Right (18) ,Down (24) ,Right (26) ,Down (28) ,Down (30)...
```
The matrices are read from a txt file - lines of numbers separated by comma (each line is separated by ```\n```), the next 2 lines after the matrice are the entering point and the exiting point- 2 numbers separted by a comma that the first number is the nubmer of row and the second is the number of column. When the clients wants to stop, it send us the word "end" so we know to stop reading form them. 
* you can create matrices of your own and try the program on it (in the fromat explained above,in the last line is "end".
* you can use ```matrixbuilder.py``` to create matrices and choose 10 of them (needs to be in files named ```Matrix[1-10].txt```)
* parallel_tester.py read the files of matrices with name of ```Matrix[1-10].txt```.



```main.cpp``` accepts through an argument a port number for the server to open
and then uses the ```main``` funcion of the ```Main``` class in ```Server.cpp``` in ```boot``` namespace to start the program.
The function looks like that:
```
void boot::Main::main(string port) {
  //Current cache manager.
  CacheManager<Matrix<double>, string> *cm = new FileCacheManager<Matrix<double>>();
  
  //Here i choose the Astar algoritm as the best one for the OA solver.
  Solver<Matrix<double>, string> *solver = new MatrixProblemSolverOA<double>(new AStar<double>);
  
  //Client handler.
  ClientHandler *ch = new MatrixSearchingClientHandler(solver, cm);
  
  //Declaring the wanted server
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

The ```CacheManage``` interface is a template class that accepts 2 arguments : ```CacheManage<Problem,Soltion>```
and its role is to get solution to the problem with ```O(1)``` time and store new solutions as a generic cache.
```FileCacheManager``` implements the interface ```CacheManager<Matrix<double>, string>``` and its role is to check, store and get solutions from files. As you can see, here the Problem is of a ```Matrix``` (class) of double values in its cells and the solution is of a string kind.

The ```Solver``` is a template interface as well and its role is to solve the given problem.
```MatrixProblemSolverOA``` implements ```Solver<Matrix<double>, string>``` and using the  ObjectAdapter DP , it has a ```Searcher```
member and it connects the problem to the solver by using its ```Searcher``` 's function ```Seacher``` on a given problem.

The ```ClientHandler``` is an abstract class for client handlers.Its role is to be used to handle the cilents given that we know the problem.```MatrixSearchingClientHandler``` inherits it and is used for our problem of searching the shortest(cheapest path)
in a matrix.

The server that is opened is using the client handler to handle the clients.

As you can see, we can create more classes to implement the interfaces and keep the generic way of working to match the problems that the clients send to us, as well the solution that we send to the clients.


### Possible changes / improvements
-Configuring the problems that the clients send to the server with identifiers to problems so we can choose the right 
templates to work with - can be with enum.

