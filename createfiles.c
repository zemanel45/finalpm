#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>

int main()
{
    srand(time(0));
    FILE *ognames = fopen("original_names", "r");
    FILE *ogsubnames = fopen("original_surnames", "r");
    FILE *names = fopen ("names", "w");
    FILE *subnames = fopen ("surnames", "w");
    char buffer[30], trash[100]; 
    int random, true = 0;

    while (!(feof(ognames)))
    {
        random = rand() % 100; 

        fscanf(ognames, " %s ", buffer); 
        buffer[strcspn(buffer, "(")] = 0;
        strcat(buffer,"\n");
    
        fgets(trash,100,ognames);
        if(random < 50)
        {
            fputs(buffer,names);
        }
    }

    while(!(feof(ogsubnames)))
    {
        random = rand() % 100;

        fscanf(ogsubnames, " %s ", buffer); 
        buffer[strcspn(buffer, "(")] = 0;
        strcat(buffer,"\n");
        
        fgets(trash,100,ogsubnames);
        if(random < 50)
        {
            fputs(buffer,subnames);
        }     
    }

    fclose(ognames);
    fclose(names);
    fclose(ogsubnames);
    fclose(subnames);

    return 0;
}