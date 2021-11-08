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

    FILE *fp;
    char *line = NULL;
    fp = fopen("complex.txt", "r"); // opening file in read mode.
    size_t len = 0;
    ssize_t read;
    if (fp == NULL)
    {
        perror("File : ");
        exit(EXIT_FAILURE);
    }

    read = getline(&line, &len, fp);
    size = atoi(line);

    printf("No. of complex numbers to multiply : %d\n", size);

    cn_array = (complex_number *)calloc(size, sizeof(complex_number));
    output = (complex_number *)calloc(ceil(size / 2), sizeof(complex_number));

    int count_temp = 0;
    while ((read = getline(&line, &len, fp)) != -1)
    {
        char *temp_line = line;
        int count = 0;
        char temp[256];
        while ((*temp_line) != '+')
        {
            temp[count++] = *temp_line;
            temp_line = temp_line + 1;
        }
        temp[count] = '\0';
        long long int real = atoi(temp);

        temp_line++; // crossed '+'
        temp_line++; // crossed 'i'

        char temp1[256];
        count = 0;
        while ((*temp_line) != '\n')
        {
            temp1[count++] = *temp_line;
            temp_line = temp_line + 1;
        }

        temp1[count] = '\0';
        long long int imaginary = atoi(temp1);

        complex_number cn;
        cn.real = real;
        cn.imaginary = imaginary;
        cn_array[count_temp++] = cn;
    }

    printf("Complex numbers are read from file, now gonna start multiplying them : \n");

    // Closing the file descriptor and freeing up the memory used to read lines from a file.
    fclose(fp);
    if (line)
        free(line);

    printf("Complex numbers read from file : \n");
    for (int i = 0; i < size; i++)
    {
        printf("Compex number %d => %lld+i%llFd\n", i, cn_array[i].real, cn_array[i].imaginary);
    }

    int q = size;
    int level = 1;
    while (q > 1)
    { // even number of elements
        if (q % 2 == 0)
        {
            q = q / 2;
            pthread_t tid_array[q];
            for (int i = 0; i < q; i++)
            {
                struct temp *temporary = (struct temp *)calloc(1, sizeof(struct temp));
                temporary->level = level;
                temporary->thread_number = i;
                pthread_create(tid_array + i, NULL, runner, temporary);
            }

            for (int i = 0; i < q; i++)
            {
                if (pthread_join(tid_array[i], NULL) != 0)
                {
                    perror("JOIN ");
                    exit(1);
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
            pthread_t tid_array[q];
            for (int i = 0; i < q; i++)
            {
                struct temp *temporary = (struct temp *)calloc(1, sizeof(struct temp));
                temporary->level = level;
                temporary->thread_number = i;
                pthread_create(tid_array + i, NULL, runner, temporary);
            }

            for (int i = 0; i < q; i++)
            {
                if (pthread_join(tid_array[i], NULL) != 0)
                {
                    perror("JOIN ");
                    exit(1);
                }
            }

            int i;
            for (i = 0; i < q; i++)
            {
                cn_array[i] = output[i];
            }

            cn_array[i] = cn_array[temp - 1];
            q++;
            level++;
        }
    }

    if (cn_array[0].imaginary < 0)
    {
        printf("Final output : %lld %lldi\n", cn_array[0].real, cn_array[0].imaginary);
    }
    else
    {
        printf("Final output : %lld +%lldi\n", cn_array[0].real, cn_array[0].imaginary);
    }

    free(output);
    free(cn_array);
}

void *runner(void *param)
{
    printf("My thread id : %ld\n", pthread_self());
    struct temp *temp = (struct temp *)param;

    complex_number first = cn_array[2 * temp->thread_number];
    complex_number second = cn_array[2 * temp->thread_number + 1];

    complex_number value;

    printf("from thread %d at level %d : first complex numer : %lld+i%lld\n", temp->thread_number, temp->level, first.real, first.imaginary);
    printf("from thread %d at level %d : second complex numer : %lld+i%lld\n", temp->thread_number, temp->level, second.real, second.imaginary);

    long long int xu = first.real * second.real;
    long long int yv = first.imaginary * second.imaginary;
    long long int xv = first.real * second.imaginary;
    long long int yu = first.imaginary * second.real;

    value.real = (xu - yv);
    value.imaginary = (xv + yu);

    output[temp->thread_number] = value;
    if (value.imaginary < 0)
    {
        printf("Intermdiate output from thread %d : %lld %lldi\n", temp->thread_number, value.real, value.imaginary);
    }
    else
    {
        printf("Intermdiate output from thread %d : %lld +%lldi\n", temp->thread_number, value.real, value.imaginary);
    }

    // char temp_string[256];
    // int count = 0;
    // int calculate = (temp->thread_number)*((int)pow(2, temp->level)) ;
    // for (int i = calculate ; i <= calculate + ((int)pow(2, temp->level)); i++)
    // {
    //     temp_string[count++] = 'C';
    //     temp_string[count++] = 'N';
    //     temp_string[count++] = ' ';
    //     temp_string[count++] = itoa(i);
    //     temp_string[count++] = ',';
    // }
    // temp_string[count] == '\0';
    // value->imaginary = 0;
    // value->real = 0;
    // printf("Thread_Number : %d%d will calculate the product of %s\n", temp->level, temp->thread_number, temp_string);
    // printf("%d\n",1);

    free(temp);
    pthread_exit(0);
}