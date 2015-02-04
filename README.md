# parallel_collapse_set_of_integers
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

<a href="https://drive.google.com/open?id=0B7A_IjGiD0swdUlYYy1KbERHalk&authuser=0" target="_blank">Algorithm</a>

Here is a very effective way to set MPICH in Visual Studio 2010
<a href="http://nick-goodman.blogspot.com/2012/02/using-mpich-from-ms-visual-studio-2010.html" target="_blank">Using MPICH on Windows 7 with MS Visual Studio 2010</a>




