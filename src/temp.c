#include "project.h"

int main()
{
    FILE *fp;
    fp = fopen("complex.txt", "r");
    char *line = NULL;
    size_t len = 0;
    ssize_t read;
    read = getline(&line, &len, fp);
    int size = atoi(line);
    while ((read = getline(&line, &len, fp)) != -1)
    {
        char *temp_line = line;
        int count = 0;
        printf("No. of characters in this line : %ld\n", read);
        printf("%s", line);

        char temp[256];
        while ((*temp_line) != '+')
        {
            temp[count++] = *temp_line;
            temp_line = temp_line + 1;
        }
        temp[count] = '\0';
        printf("Real : %s\n", temp);
        int real = atoi(temp);
        printf("Real_Integer : %d\n", real);
        fflush(stdout);

        temp_line++;
        temp_line++;
        char temp1[256];
        count = 0;
        while ((*temp_line) != '\n')
        {
            temp1[count++] = *temp_line;
            temp_line = temp_line + 1;
        }

        temp1[count] = '\0';
        printf("Imaginary : %s\n", temp1);
        int imaginary = atoi(temp1);
        printf("Imaginary_Integer : %d\n", imaginary);
        fflush(stdout);
    }
    printf("\n");
    fclose(fp);
    if (line)
        free(line);
}