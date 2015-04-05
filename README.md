# Parallel Collapse Set of Integers using MPICH
A solution for infamous parallel collapse set of integers problem with MPICH

#Problem Definition:
The collapse of a set of integers is defined to be the sum of the integers in the set. Similarly, the collapse of a single integer is defined to be the integer that is the sum of its digits.
The process of collapsing an integer to a single digit will be referred to herein as the ultimate collapse of an integer. This can clearly be carried out recursively, until a single digit results. For example, the collapse of the integer 134957 is 29. The collapse of 29 is 11, and its collapse followed by the result being collapsed recursively until only a single digit remains. In this example the ultimate collapse is 2.
Our task is to find the collapse sum of a set of integers using master/worker parallel programming paradigm. Read a stream of integers and find the sum of their digits using the master and workers in parallel.

#Things I used :
•	mpich.nt.1.2.5<br/>
•	Language: C++<br/>
•	Microsoft Visual Studio 2010<br/>
•	Windows Command Prompt<br/>
•	Windows 7 environment<br/>

#Parallel Algorithm design:
We’ve used the master/worker parallel programming paradigm. In our design there is a master process which controls the whole program. Master process is responsible to check if any input exists and then starts taking input from a file. It takes input block by block. Block size is pre-defined and adjustable. So if we instruct to take block input e.g. 10 integers at once, master process will read 10 integers and in next cycle another 10 integers and so on. Then master process will send these inputs to available parallel processes. If system is one processor trivial system master process itself will calculate total collapse result. Otherwise it’ll send block of numbers to worker processes and worker process will calculate the sum of those blocks and send them to the master process. Master process will collect all the results from workers and check for the input end. Then master process will calculate the final collapse result. Following diagram shows the structure of our algorithm:


<a href="https://drive.google.com/uc?export=view&id=0B7A_IjGiD0swdUlYYy1KbERHalk"><img src="https://drive.google.com/uc?export=view&id=0B7A_IjGiD0swdUlYYy1KbERHalk" style="width:500px; max-width: 100%; height: auto" title="Click for the larger version." /></a>

Here is a very effective way to set MPICH in Visual Studio 2010
<a href="http://nick-goodman.blogspot.com/2012/02/using-mpich-from-ms-visual-studio-2010.html" target="_blank">Using MPICH on Windows 7 with MS Visual Studio 2010</a>

If you successfully compile the program, here is a manual to run

#Manual (how to run the program, input and output)
1.	Put the .exe file and input file (in input.txt format) in same folder.<br/>
2.	Go to cmd.exe on the system and run as administrator<br/>
3.	Go to MPICH bin directory in command prompt. (i. e. C:\Program Files\MPICH\mpd\bin)<br/>
4.	Execute MPIRegister.exe<br/>
5.	Enter your windows credentials<br/>
6.	Check validity (i.e. mpiregister –validate –user [your account username])<br/>
7.	If it’s showing “SUCCESS”, then all ok. If not then repeat step 4-6.<br/>
8.	Go to the .exe file directory in command prompt. (i. e. [your computer directory to exe file])<br/>
9.	Execute command MPIRun.exe np -Y X.exe (X is the name of the .exe file, Y is number of processes)<br/>
10.	Get output in the command prompt.<br/>





