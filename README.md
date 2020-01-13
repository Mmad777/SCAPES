# Scapes Project

Scapes for writing and compiling the programs in the SCAPL language. The SCAPL language is
a simplified subset of assembly language instructions.

## 1. Design Patterns used(GoF)

### Factory Method
We use the Factory Method in our SCAPES program to ensure the creation of all the statements are identical and they follow the same framework for each statement. We start by defining a base class (Statement) that will be inherited by each of our sub-classes individually.
Our (StatementFactory) class creates separate statement objects based on the programmers code that is in the current working space in SCAPES. These objects are created during the compilation phase of the program and are stored as JSON objects in permanent storage. 

We use a "Parameterized factory method" as mentioned in the Gang of Four as the second variation of the implementation of the Factory Method. This allows us to identify the kind of object we want to create, all while making sure they inherit from the same Statement interface used to create each unique object while assuring consistency.

![FactoryMethodPattern](images/FactoryMethodPattern.png)



## 2. Build and Run

Build

`$./build.sh`

Run

`$./run.sh`

Clean

`$./clean.sh`


######################################################################################
<br />
First untar the project. Switch directory to'$ cd SCAPES/Scapes'
<br />


After the build command "./build.sh" then run the executable file "./run.sh"
<br />
'user have to log into the system'
'user name: programmer'
'password: 1234'
'Then click on log in'
<br />

'You will be taken to a new UI "MainWindow". You can type all the statements or you can excess 2 sample.scapl files already stored in persistent storage.'
<br />
'To open test file click file -> open -> data -> simple.scapl / complex.scapl.'
<br />

'You can save the files to by this instructions: file -> save as -> Then choose the name of the file you want to save.'
<br />

'To create the new file click on file -> New.'
<br />

'To compile the program follow this instructions: click on program -> build. It will convert into "compiled.json". You can find that file in folder./Scapes with name "compiled.json". It will be keep on updating everytime you change the instructions.'
<br />
<br />
First the programmer need to build the program with command Program -> Build. Then will run the program with command Program -> run.
<br /> 
The result will be displayed in the bottom UI. Under name "Result".
<br />
<br />
2 complete SCAPL-Language programms are already stored in the persistent storage. Under name " simple.scapl, and complex.scapl". 
<br />
After it compiles, the compiled code is written to disk. To execute it, the compiler read the compiled one from the disk.
The bottom window is the result of the execution.
<br />
<br />
In "simple.scapl" The code calculate the sum of 1, 2, 3, 4, 5, 6, 7, 8, 9, 10. Then start up a=1, b=10. If a < b, then continue to sum and increases the value of a. Once a become 11, it is not true a < b. So, the loop finished. Sum = 1 + 2 + 3 + 4 + 5 + 6 + 7 + 8 + 9 + 10 = 55. 
The results of "Simple.scapl" are  "a = 11, b = 10, Total = 55".
<br />
<br />
In "complex.scapl" program file has one more outer loop. It uses the "repeat" variable and it is inputed using dialog. example: repeat *(sum 1~10).
 for(int i = 1; i< repeat ; i++) 
<br />	
for (int j= 1; j < 10; j++) {
<br />		
total = total + j;}
<br />
<br />

The loop of assembler is made by "jmp, cmp".  

##############################################################################




## 3. Screenshots

**User Name**: programmer

**User Password**: 1234



**Admin Name**: administrator

**Admin Password**: 5678

![screenshot](images/screenshot.png)
