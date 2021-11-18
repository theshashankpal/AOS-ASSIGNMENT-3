#include "project.h"

int size;

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

complex_number *cn_array;
complex_number *output;

void *runner(void *param);

int main(int argc, char *argv[])
{
    printf("\n");

    if (argc != 2)
    {
        printf("You've entered too many or too few arguments.\nPlease start the program with 1 single argument containtg path to the file \n");
        exit(0);
    }
    FILE *fp;
    char *line = NULL;
    fp = fopen("src/complex.txt", "r"); // opening file in read mode.
    size_t len = 0;
    ssize_t read;
    if (fp == NULL)
    {
        perror("File : ");
        exit(EXIT_FAILURE);
    }

    read = fscanf(fp,"%d", &size); // reading first line that containts total number of complex mumber there are.

    printf("No. of complex numbers to multiply : %d\n", size);

    cn_array = (complex_number *)calloc(size, sizeof(complex_number)); // Allocating array of size equivalent to total number of complex numbers.

    int count_temp = 0;

    // reading complex numbers from file.
    while (1)
    {
        long long int real;
        long long int imaginary;
        read = fscanf(fp, "%lld+i%lld", &real, &imaginary);
        if (read == -1)
            break;
        complex_number cn;
        cn.real = real;
        cn.imaginary = imaginary;
        cn_array[count_temp++] = cn;
    }

    printf("Complex numbers are read from file, now gonna start multiplying them : \n");
    printf("\n\n");

    // Closing the file descriptor and freeing up the memory used to read lines from a file.
    fclose(fp);

    int q = size;
    int level = 0;
    
    while (q > 1)
    { // even number of elements
        if (q % 2 == 0)
        {
            q = q / 2;
            output = (complex_number *)calloc(q, sizeof(complex_number));
            pthread_t tid_array[q];
            for (int i = 0; i < q; i++)
            {
                struct temp *temporary = (struct temp *)malloc(sizeof(struct temp));
                temporary->level = level;
                temporary->thread_number = i;
                 if (pthread_create(tid_array + i, NULL, runner, temporary) != 0)
                {
                    perror("CREATION OF THREAD ");
                    exit(EXIT_FAILURE);
                }
            }

            for (int i = 0; i < q; i++)
            {
                if (pthread_join(tid_array[i], NULL) != 0)
                {
                    perror("JOINING OF THREAD ");
                    exit(EXIT_FAILURE);
                }
            }

            for (int i = 0; i < q; i++)
            {
                cn_array[i] = output[i];
            }
            level++;
        }
        else
        { // odd number of elements.
            int temp = q;
            q = q / 2;
            output = (complex_number *)calloc(q, sizeof(complex_number));
            pthread_t tid_array[q];
            for (int i = 0; i < q; i++)
            {
                struct temp *temporary = (struct temp *)malloc(sizeof(struct temp));
                temporary->level = level;
                temporary->thread_number = i;
               if (pthread_create(tid_array + i, NULL, runner, temporary) != 0)
                {
                    perror("CREATION OF THREAD ");
                    exit(EXIT_FAILURE);
                }
            }

            for (int i = 0; i < q; i++)
            {
                if (pthread_join(tid_array[i], NULL) != 0)
                {
                    perror("JOINING OF THREAD ");
                    exit(EXIT_FAILURE);
                }
            }

            int i;
            for (i = 0; i < q; i++)
            {
                cn_array[i] = output[i];
            }

            cn_array[i] = cn_array[temp - 1];
            q++; // Increasing size to match the extra transferred complex number as previoulsy, array size was odd.
            level++;
        }

        free(output);
    }

    printf("\n\n");

    if (cn_array[0].imaginary < 0)
    {
        printf(GRN "Final output : %lld %lldi\n" RESET, cn_array[0].real, cn_array[0].imaginary);
    }
    else
    {
        printf(GRN "Final output : %lld +%lldi\n" RESET, cn_array[0].real, cn_array[0].imaginary);
    }

    fflush(stdout);
    free(cn_array);
}

void *runner(void *param)
{
    struct temp *temp = (struct temp *)param;

    complex_number first = cn_array[2 * temp->thread_number];
    complex_number second = cn_array[2 * temp->thread_number + 1];

    complex_number value;

    // Multiplying the complex numbers.
    long long int xu = first.real * second.real;
    long long int yv = first.imaginary * second.imaginary;
    long long int xv = first.real * second.imaginary;
    long long int yu = first.imaginary * second.real;

    value.real = (xu - yv);
    value.imaginary = (xv + yu);

    output[temp->thread_number] = value;
    if (value.imaginary < 0)
    {
        printf("Intermdiate output from thread %d at level %d with thread id : %ld " CYN "=>" RESET " %lld %lldi\n", temp->thread_number, temp->level, pthread_self(), value.real, value.imaginary);
    }
    else
    {
        printf("Intermdiate output from thread %d at level %d with thread id : %ld " CYN "=>" RESET " %lld +%lldi\n", temp->thread_number, temp->level, pthread_self(), value.real, value.imaginary);
    }

    fflush(stdout);
    free(temp);
    pthread_exit(0);
}