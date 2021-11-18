//
// Created by shashank on 9/27/21.
//

#ifndef ASSIGNMENT_H
#define ASSIGNMENT_H


#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <pthread.h>
#include <string.h>
#include <limits.h>

#define RED   "\x1B[31m"
#define GRN   "\x1B[32m"
#define YEL   "\x1B[33m"
#define BLU   "\x1B[34m"
#define MAG   "\x1B[35m"
#define CYN   "\x1B[36m"
#define WHT   "\x1B[37m"
#define RESET "\x1B[0m"

typedef struct _complex
{
    long long int real;
    long long int imaginary;
} complex_number;

struct temp
{
    int level;
    int thread_number;
};


#endif //ASSIGNMENT_H