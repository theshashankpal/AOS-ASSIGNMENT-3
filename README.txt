Name : Shashank Pal
Student ID : 2021H1030064G
-----------------------------------------------------------------------------------------------------------------------
List of Directories :

src : It contains all the needed source and header files.
-----------------------------------------------------------------------------------------------------------------------
List of Files :

All source and header files are included in directory src :

main.c : One file , which houses all the code required for this assignment.

project.h : Simple header file indicating what #includes are used,
             what functions and custom data structures that I'm using.
             And , what are the pre and post conditions of a particular function.
-----------------------------------------------------------------------------------------------------------------------
HOW TO COMPILE :

First run : make clean (to remove any unnecessary object and executable files)
Lastly run : make
-----------------------------------------------------------------------------------------------------------------------
HOW TO RUN :

To run program, type following with required amount of arguments : ./output <path of a file>

For ex : ./output src/complex.txt
-----------------------------------------------------------------------------------------------------------------------
Description Of The Structure Of My Program :

- First by running ./output (path of a a file) we start main.c.

- It reads n (total no. of complex numbers) from file whose path is provided in the arguments.
    - Go into a while loop which is governed by n until this very n becomes 1 or less than 1.
    - Inside this while at every iteration current number of n threads are created.
    - Threads which are created has the job to multiply the complex number and these complex numbers which have to be
        multiplied are taken from the global array. After multiplying the results are stored onto temp global output array.
    - Main waits for thread to finish using pthread_join().
    - After that transfers result from temp output array to input array.
    - Divides n by 2.
    - At the end result is printed.
-----------------------------------------------------------------------------------------------------------------------
BUGS :
If any intermediate ore final result exceeds the range of long long int , then the result will not be correct. 
Range of long long int : [−9,223,372,036,854,775,807, +9,223,372,036,854,775,807]

I couldn't have corrected it as long long int is the max size of int that we get in C. But I could've put a check for it , if given more time.

-----------------------------------------------------------------------------------------------------------------------