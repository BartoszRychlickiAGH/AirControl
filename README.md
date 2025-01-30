# AirControl - Air Traffic Controll written in C++

## In this repo you can spot a solution for Air Traffic Control System written by myself. 

So, why did I write this project. My mian purpose was that I had to build final project for my lectures from OOP on AGH University of Krakow. 

Main dictionary includes CMakeLists.txt and dictionary named: src. In the dictionary named: src you can find all header files and source files with are necessary to run program in correct way.
Names of header files reflect what is included in such a file, for example, IDatabase.hpp includes interface with all methods implemented in Database class (Database class is included in Database.hpp). 
For all classes I created source files (.cpp), to implement functions' in them.

Storing data can be solved in various ways (files handling operations, Databases). 
I choose SQL Database because in my opinion, extensions that Microsoft gave to Visual Studio 17 really helps to build project with this type of Database. 
Second cause of why I choose SQL is less technological (I completed SQL Course on Udemy). 
All SQL connection with py program was made in Database.cpp file.

At current level of program developement, my project does not fulfill SOLID principles, but I'm going to work on it for next week (19.01.2025r. - 24.01.2025r.).

Moving to next necessary information: validation.hpp is made just to store a Validation class (made up with Singleton desing pattern), just to store methods that can validate some basics (if given number is a number and so on).

For all tips I will be thankfull. 
