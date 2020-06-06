subbmited by Anna Sandler 208749648
gcc version 9.2.1 20190827 (Red Hat 9.2.1-1) (GCC)

IPC:
in this part I was asked to make a father-son processes communication through a pipe and implement a SIGUSR1 signal too.
The first one to write to the pipe is the son, after writing he sends a SIGUSR1 signal to the father process, when the father gets the signal
he reads from the pipe, increses he number by 1 , writes the new number to the pipe and sends a SIGUSR1 to the son process
and so on untill the number in 5, then the son process is terminated and after him the father process is terminated
to run type make in the terminal and then ./pingpong
the expected output is:  
0  
1  
2  
3  
4  
5  
Child is going to be terminated  
Parent is going to be terminated  

SYNC:
in this part I was asked to demonstrate 3 cases and their solutions, for each one of them there is a code:
- deadlock (2_1_1) - each philisoph picks the fork on the left and waiting for the fork on the right to be
released by the profesor on the right. no one is eating
- no-deadlock(2_1_2) - all philisophs are eating simultaneously
- starvation (2_2_1) - only the philosops that their number in even are eating (2,4) so the odd onces are starving (1,3,5)
- no-starvation (2_2_2) - they eat in pairs - philosopher i eats with (i+2)%5 and so on. nobody is starving
- livelock (2_3_1) - they dont pick no fork if the 2 forks on two sides aren't free. no fork is picked and no philisofer is eating
- no-livelock (2_3_2) - all philisophs are eating simultaneously

to run the code type make and then ./ withe the number of the case (ex. ./2_2_2)

GDB:
in this part I was asked to use GDB to explore a compiled C file and change the variables in it to
generate a key this my name and my ID.
to do that is ran GDB on the secret file and put a break point at line 44, to check the name and ID I used the info
locals and to change them I used the set command. after changing the variables I typed continue and got a key. the key
is saved in the key.txt file
