#include <stdio.h>
#include <stdlib.h>

int main()
{
    FILE *ognames = fopen("original_names", "r");
    FILE *ogsubnames = fopen("original_subnames", "r");
    FILE *names = fopen ("names", "w");
    FILE *subnames = fopen ("subnames", "w");
    char buffer[30]; 


    while (!feof(ognames))
    {
        fgets(buffer, 30, ognames);
        printf("%s", buffer);
        fputs(buffer,names);
    }

    fclose(ognames);
    fclose(names);
    fclose(ogsubnames);
    fclose(subnames);

    return 0;
}