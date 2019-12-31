# Interpreter-Flight-Simulator-language
Interpreter for a flight simulator coding language, made with CPP. 

## General Description

This program interprets a programming language that was created in order to control "[_FlightGear_]" (https://www.flightgear.org/) flight simulator. 
The program connects to the flight simulator both as client and server.
The client will send the simulator instructions that were coded in the script. That allows us to control our flight vessel with code.
The server will get live data about the flight. 

## Collaborators

This program was developed by Gadi Didi and Ori Levy, CS students from Bar-Ilan university, Israel.


## Features

1. Connect to the simulator as a client:

2. Connect the simulator as client:

3. Interpret code and translate it into flight insructions.

4. Interpret arithmetic expressions (Divide, Multiply, Plus, Minus) using Shunting-Yard algorithm.

5. Function definition and usage of functions are supported. 

6. Nested loops and if statements are supported.


## Setup and execute

1. Insert the file generic_small.xml into the following path:
    ```bash
    [FlightGear installation path]/‫‪data/protocol
    ```

2. Start with adding the following lines into the additional setting in FlightGear:

    ```bash
    --generic=socket,out,10,127.0.0.1,5400,tcp,generic_small
    --telnet=socket,in,10,127.0.0.1,5402,tcp
    ```
You can choose IP and Port as desired, but you should keep LocalHost IP if you're running both the program and the simulator on the same PC.

3. Complie the program code:

    ```bash
    g++ -std=c++14 *.cpp -Wall -Wextra -Wshadow -Wnon-virtual-dtor -pedantic -o a.out
    ```

4. Run a.out with the relative path of the code you want to execute as the first argument (Should be in txt file).

5. The program will wait for you to open the FlightGear simulator and start a flight.

6. Look at the simulator and enjoy your flight.

