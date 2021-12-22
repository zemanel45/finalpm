#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>
#include <ctype.h>


typedef struct 
{
    char occupied;
    char name [100];
    char checked_in;
    int id_luggage;
    int id_reservation_code;    
}seat;

void clear()
{
    for(int i = 0; i < 60; i++)
    {
        printf("\n");
    }
}

int option_plane()
{
        int number_plane;
        int op;
		
        printf("----------- Menu of planes ----------- \n");
        printf("        (1) - Airbus 318 \n");
        printf("        (2) - Airbus 319 \n");
        printf("        (3) - Airbus 320 \n");
        printf("        (4) - Airbus 321 \n");
        printf("        Option: ");
        scanf(" %d", &op);
		printf("\n\n");

        switch (op)
    	{
    		case 1:
        		number_plane = 318;
        		break;
		
    		case 2:
        		number_plane = 319;
        		break;
    		
    		case 3:
        		number_plane = 320;
        		break;
    		
    		case 4:
        		number_plane = 321;
        		break;
    	}
    
    return number_plane;
}

int *check_max_seats(char n_flight[20], int number_plane, int *value) 
{
    char buffer[20], n_plane[20];
    char check_exec[10] = "abcd";
    char check_turist[10] = "abcdef";
    int turist = 0, exec = 0, seats = 0;
    FILE *plane;
    FILE *flight;
  
    if (!(n_flight == NULL)){
        
        flight = fopen(n_flight,"rb");
	    fread(&number_plane,sizeof(int),1,flight);
        sprintf(n_plane,"Airbus%d",number_plane);
        fclose(flight);
    }

    sprintf(n_plane,"Airbus%d",number_plane);
	plane = fopen(n_plane,"r");
		
    if (plane != NULL){
        
        while (fgets(buffer,20,plane) != NULL)
        {
            if (strstr(buffer, "\n"))
            {
                buffer[strlen(buffer)-1] = 0;
            }
            
            if (strstr(buffer,check_exec))
            {
                if (strstr(buffer,check_turist))
                {
                    turist = turist + 1;

                }else{
                    
                    exec = exec + 1;     
                }
            } 
        }

        seats = (exec*4) + (turist *6); 
 
        fclose(plane);

    }else 
    {
        printf("Erro no check max");
        exit(1);
    }

    value[0] = exec;
    value[1] = turist;
    value[2] = seats;

    return value;
}

void show_file()
{
    FILE *flight;
	seat all_seats[300];
    int number_plane = 0, max_seats, ocuppation = 0, *value, op_flight;
    int array[3];
    char n_flight[20];

    printf("Number of the flight: ");
    scanf(" %d", &op_flight);
    sprintf(n_flight,"TP%d",op_flight);  

    flight = fopen(n_flight,"rb");
    value = check_max_seats(n_flight,0,array);
    max_seats = value[2];
    
    fread(&number_plane,sizeof(int),1,flight);
    printf("%d \n", number_plane);
    for (int i = 0; i < max_seats; i++){

        fread(&all_seats[i],sizeof(seat),1,flight);
        printf("%c %s %c %d %d \n",all_seats[i].occupied, all_seats[i].name, all_seats[i].checked_in, all_seats[i].id_luggage, all_seats[i].id_reservation_code);
    }
}

void passenger_flight()
{
    FILE *flight;
	seat all_seats[300];
    int number_plane = 0, max_seats, op_flight, *values, fila = 0, coluna = 0;
    int array[3];
    char n_flight[20];
    
    printf("Number of the flight: ");
   	scanf(" %d", &op_flight);
    clear();
    sprintf(n_flight,"TP%d",op_flight);

    flight = fopen(n_flight,"rb");

    if(flight != NULL){

        printf("Name flight: %s\n", n_flight);
        
        values = check_max_seats(n_flight,0, array);
        max_seats = values[2];


        fread(&number_plane,sizeof(int),1,flight); 

        for (int i = 0; i < max_seats; i++){

            fread(&all_seats[i],sizeof(seat),1,flight);
            coluna++;
            
            if(((fila < values[0]) && (coluna == 4)))
            {
				fila++;
				coluna = 0;
				printf("\n");
            }
            
            if ((fila >= values[0]) && (coluna == 6))
            {
            	fila++;
				coluna = 0;
				printf("\n");
            }
            
            if (all_seats[i].occupied == '1')
            {
                printf("(%d/%d) - %s \n", fila, coluna, all_seats[i].name);
            }
        }

    }else{
        
        printf("Ficheiro invalido");

    }

    printf("\n\n");
    fclose(flight);
}

int occupancy_flight(char buffer[20])
{
	FILE *flight;
	FILE *plane;
	seat all_seats[300];
    int number_plane, max_seats, ocuppation = 0, op_flight, *values, fila = 0, i = 0;
    int array[3];
    char n_flight[20], n_plane[20], letter;
    
    if(buffer == NULL){

        printf("Number of the flight: ");
        scanf(" %d", &op_flight);
        sprintf(n_flight,"TP%d",op_flight);   
    }else{

        strcpy(n_flight,buffer);
    }

    flight = fopen(n_flight,"rb");

    if(flight != NULL){

        values = check_max_seats(n_flight,0, array);
        max_seats = values[2];

        fread(&number_plane,sizeof(int),1,flight);
        sprintf(n_plane,"Airbus%d",number_plane);
		plane = fopen(n_plane,"r"); 
		
        for (int a = 0; a < max_seats; a++)
        {
            fread(&all_seats[a],sizeof(seat),1,flight);
        }
		
        while (!(feof(plane))){
        
           letter = fgetc(plane);

            if (letter != '\n'){
            
            	if (all_seats[i].occupied == '1')
            	{
                	letter = '*';
                    ocuppation++;                	
            	}
            	putchar(letter);
                i++;
            	
         	}else{printf("\n");} 		  
        }

        ocuppation =  (ocuppation * 100)/max_seats;
        fflush(stdin);
        printf("Ocupacao do voo %s e %d %", n_flight, ocuppation);

    }else{
        
        printf("Ficheiro invalido\n");
    }

    printf("\n\n");
    fclose(flight);  
    
}

void change_seat()
{
    FILE *flight;
	seat all_seats[300];
    int number_plane = 0, max_seats, ocuppation = 0, op_flight, fila = 0, lugar, *values, old_seat, new_seat;
    int array[3];
    char n_flight[20], first_name[20], last_name[20];
   
   
    printf("Number of the flight: ");
    scanf(" %d", &op_flight);
    sprintf(n_flight,"TP%d",op_flight);  
    flight = fopen(n_flight,"rb");

    if (flight != NULL)
    {
        ocuppation = occupancy_flight(n_flight);
        values = check_max_seats(n_flight,0,array);
        max_seats = values[2];

        fread(&number_plane,sizeof(int),1,flight); 
        for (int i = 0; i < max_seats; i++){

            fread(&all_seats[i],sizeof(seat),1,flight);
        }

        printf("A sua fila: ");
        scanf(" %d", &fila);
        printf("O seu lugar: ");
        scanf(" %d", &lugar);

        if(fila < values[0])
        {
            old_seat = ((fila-1)*4) + lugar;

        }else
        {
            old_seat = ((fila - (values[0] + 1))*6)+ lugar + (values[0]*4);
        }
    
        if (all_seats[old_seat].occupied == '1')
        {
            printf("Verify first and last name: ");
            scanf(" %s %s",first_name, last_name);
            strcat(first_name, " ");
            strcat(first_name,last_name);

            if (strstr(all_seats[old_seat].name,first_name))
            {
                printf("Fila que deseja: ");
                scanf(" %d", &fila);
                printf("Lugar que deseja: ");
                scanf(" %d", &lugar);

                if(fila < values[0])
                {
                    new_seat = ((fila-1)*4) + lugar;

                }else
                {
                    new_seat = ((fila - (values[0] + 1))*6)+ lugar + (values[0]*4);
                }

                if(all_seats[new_seat].occupied == '0')
                {
                    all_seats[new_seat].checked_in = all_seats[old_seat].checked_in;
                    all_seats[new_seat].id_luggage = all_seats[old_seat].id_luggage;
                    all_seats[new_seat].id_reservation_code = all_seats[old_seat].id_reservation_code;
                    strcpy(all_seats[new_seat].name,all_seats[old_seat].name);
                    all_seats[new_seat].occupied = '1';

                    all_seats[old_seat].occupied = '0';        
                    strcpy(all_seats[old_seat].name," ");
                    all_seats[old_seat].checked_in = ' ';   
                    all_seats[old_seat].id_luggage = 0;
                    all_seats[old_seat].id_reservation_code = 0;
                    

                    flight = fopen(n_flight,"wb");
                    fwrite(&number_plane,sizeof(int),1,flight);
                    for (int i = 0; i < max_seats; i++)
                    {
                        fwrite(&all_seats[i],sizeof(seat),1,flight);
                    }

                }else
                {
                    printf("Seat already occupied. Pick another one \n\n");
                }
            }

        }else{

            printf("Seat not already occupied. Pick another one \n\n");
        }
    
        fclose(flight);

    }else{

        printf("Ficheiro invalido\n\n");
    }
}

void reserve_seat()
{
    FILE *flight;
	seat all_seats[300];
    int number_plane = 0, max_seats, ocuppation = 0, op_flight, fila = 0, lugar, *values, a, valid=0;
    int array[3];
    char n_flight[20], first_name[20], last_name[20];
   
   
    printf("Number of the flight: ");
    scanf(" %d", &op_flight);
    sprintf(n_flight,"TP%d",op_flight);  

    flight = fopen(n_flight,"rb");

    if (flight != NULL)
    {
        occupancy_flight(n_flight);
        values = check_max_seats(n_flight,0,array);
        max_seats = values[2];

        fread(&number_plane,sizeof(int),1,flight); 
        for (int i = 0; i < max_seats; i++){

            fread(&all_seats[i],sizeof(seat),1,flight);
        }

        printf("Fila que deseja: ");
        scanf(" %d", &fila);
        printf("Lugar que deseja: ");
        scanf(" %d", &lugar);

        if(fila < values[0])
        {
            a = (((fila - 1) * 4) + lugar) - 1;

        }else
        {
            a = (((fila - (values[0] + 1)) * 6) + lugar + (values[0] * 4)) - 1;
        }
    
        if (all_seats[a].occupied == '0')
        {
            printf("First and last name: ");
            scanf(" %s %s",first_name, last_name);
            strcpy(all_seats[a].name,first_name);
            strcat(all_seats[a].name, " ");
            strcat(all_seats[a].name,last_name);

            printf("Have you did checked in yes(y) and no(n): ");
            scanf(" %c", &all_seats[a].checked_in);

            printf("Id luggage: ");
            scanf(" %d", &all_seats[a].id_luggage);

            printf("Id reservation code: ");
            scanf(" %d", &all_seats[a].id_reservation_code);
            
            all_seats[a].occupied = '1';

            valid = 1;

            flight = fopen(n_flight,"wb");

            fwrite(&number_plane,sizeof(int),1,flight);
            for (int i = 0; i < max_seats; i++)
            {
                fwrite(&all_seats[i],sizeof(seat),1,flight);
            }
        
        }else{

            printf("Seat already occupied. Pick another one \n\n");
        }
    
        fclose(flight);

    }else{

        printf("Ficheiro invalido\n\n");
    }
}

void create_flight()
{
    FILE *flight;
    seat all_seats[300];
    char n_flight[20], n_plane[20];
    int op_plane, op_flight,number_plane, max_seats, *values;
    int array[3];

    printf("Number of the flight: ");
    scanf(" %d", &op_flight);

    number_plane = option_plane();

    if((number_plane >= 318) && (number_plane <= 321))
    {
        sprintf(n_flight,"TP%d",op_flight);
        flight = fopen(n_flight,"wb");
        fwrite(&number_plane,sizeof(int),1,flight);

        values = check_max_seats(0,number_plane, array);
        max_seats = values[2];
        
        for (int i = 0; i < max_seats; i++)
        {
            all_seats[i].occupied = '0';        
            strcpy(all_seats[i].name," ");
            all_seats[i].checked_in = ' ';   
            all_seats[i].id_luggage = 0;
            all_seats[i].id_reservation_code = 0;
            fwrite(&all_seats[i],sizeof(seat),1,flight);
        }
        fclose(flight);

    }else{
        printf("Opcao invalida\n\n");
    }

    clear();  
}

void fill_flight()
{
    FILE *flight;
    seat all_seats[300];
    int ocuppation_percent, min = 1, random_seat = 0, random_postion_names, random_postion_subnames, max_seats, number_plane, op_flight, *values;
    int array[3];
    char nome[30],subnome[30],n_flight[12], full_name[40];
    FILE *nomes = fopen("nomes", "r"); 
    FILE *subnomes = fopen("apelidos", "r");
    
    printf("Number of the flight: ");
    scanf(" %d", &op_flight);
    
    number_plane = option_plane();

    if ((number_plane >= 318) && (number_plane <= 321))
    {    
        values = check_max_seats(0,number_plane, array);
        max_seats = values[2];

        sprintf(n_flight,"TP%d",op_flight); 
        flight = fopen(n_flight,"wb");
        fwrite(&number_plane,sizeof(int),1,flight);
        
        ocuppation_percent = (rand() % (max_seats - min + 1)) + min;
        
        for (int i = 0; i < max_seats; i++)
        {        
            random_seat = (rand() % (max_seats - min + 1)) + min;

            if (random_seat < ocuppation_percent)
            {
                random_postion_names = (rand() % (6147 - min + 1)) + min;
                random_postion_subnames = (rand() % (5845 - min + 1)) + min;

                all_seats[i].id_luggage = (rand() % (200 - 1 + 1)) + 1;
                all_seats[i].id_reservation_code = (rand() % (200 - 1 + 1)) + 1;
                all_seats[i].occupied = '1';
                all_seats[i].checked_in = '1';

                fseek(nomes,random_postion_names,SEEK_SET);
                fgets(nome,30,nomes); 
                fgets(nome,30,nomes); 
                nome[strcspn(nome, "\r\n")] = 0;

                fseek(subnomes,random_postion_subnames,SEEK_SET);
                fgets(subnome,20,subnomes); 
                fgets(subnome,20,subnomes); 
                subnome[strcspn(subnome, "\r\n")] = 0;
                
                strcpy(all_seats[i].name,nome);
                strcat(all_seats[i].name, " ");
                strcat(all_seats[i].name,subnome);

            }else{

                all_seats[i].occupied = '0';        
                strcpy(all_seats[i].name," ");
                all_seats[i].checked_in = ' ';   
                all_seats[i].id_luggage = 0;
                all_seats[i].id_reservation_code = 0;
                
            }
            
            fwrite(&all_seats[i],sizeof(seat),1,flight);
        }

        fclose(flight);

    }else
    {
        printf("Opcao invalida\n\n");
    }

    fclose(nomes);
    fclose(subnomes);
        
}

void mostar_avioes()
{
    int array[3]; 
    int  number_plane, turist = 0, exec = 0, *values;

    number_plane = option_plane();
    
    if ((number_plane >= 318) && (number_plane <= 321))
    {
        values = check_max_seats(0,number_plane,array);
        exec = values[0];
        turist = values[1];
        
        printf("Filas executivas: %d\n", exec);
        printf("Filas turisticas: %d\n\n\n", turist);
    }else
    {
        printf("Opcao invalida\n\n");
    }
}

void menu()
{
    seat all_seats[sizeof(seat)];
    int op;
    for(;;)
    {
        printf("----------- Aircraft Business ----------- \n");
        printf("        0 - Exit\n");
        printf("        1 - Show the structure of a plane \n");
        printf("        2 - Show the occupancy of a flight\n");
        printf("        3 - Show the passenger names with a reservation for this flight\n\n");
        printf("        4 - Reserve a flight with seat number\n");
        printf("        5 - Change the seat of a reservation\n");
        printf("        6 - Assign a plane to a specific flight (opening of a flight)\n\n");
        printf("        7 - Fill in a flight with random passengers\n\n");
        printf("        8 - Histogram of flight occupancy per type of seat\n");
        printf("        9 - Generation of the files names and surnames  \n\n");
        printf("        Option: ");
        scanf(" %d", &op);
        getchar();

        switch(op){   
            
            case 0:
                clear();
                exit(1);
                break;
                
            case 1:
                clear();
                mostar_avioes();
                break;

            case 2: 
                clear();
                occupancy_flight(0);
                break;

            case 3:
                clear();
                passenger_flight();
                break;

            case 4:
                clear();
                reserve_seat();
                break;

            case 5:
                clear();
                change_seat();
                break;

            case 6:
                clear();
                create_flight();
                break;
            
            case 7:
                clear();
                fill_flight();
                break;

            case 10:
                show_file();
                break;

        }
    }
}

int main(int argc, char *argv[])
{    
    srand(time(0));
    menu();
    return 0;
}
