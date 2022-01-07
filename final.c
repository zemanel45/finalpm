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

void wait()
{
    printf("\nEnter [Enter] key to continue.\n");
    getchar();
    while((getchar() != '\n'));
    clear();
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
  
    if (n_flight != NULL){
        
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
        printf("Invalid File");
        return 1;
    }

    value[0] = exec;
    value[1] = turist;
    value[2] = seats;

    return value;
}

void mostar_avioes(char buffer[])
{
    int array[3]; 
    int  number_plane, turist = 0, exec = 0, *values;

    if(buffer == NULL){

        number_plane = option_plane();

    }else{

        number_plane = atoi(buffer);
    }

    if ((number_plane >= 318) && (number_plane <= 321))
    {
        values = check_max_seats(0,number_plane,array);
        exec = values[0];
        turist = values[1];
        
        printf("\nExecutive rows: %d\n", exec);
        printf("Turist rows: %d\n", turist);
    }else
    {
        printf("\nInvalid option\n");
    }
    
    wait();
}

int occupancy_flight(char buffer[20])
{
	FILE *flight;
	FILE *plane;
	seat all_seats[300];
    int number_plane, max_seats, ocuppation = 0, op_flight, *values, fila = 1, i = 0, coluna = 1;
    int array[3];
    char n_flight[20], n_plane[20], letter;
    
    if(buffer == NULL){

        printf("Name of the flight: ");
        scanf(" %s", n_flight);
        
        printf("\n");   
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
		
        while (!(feof(plane)))
        {
            
            if(((fila < (values[0]+1)) && (coluna == 3)) || ((fila >= (values[0]+1)) && (coluna == 4)))
            {
                printf("  |%d|  ",fila);

            }else
            {  
                letter = fgetc(plane);

                if ((letter != '\n') && (letter != EOF)){
    
                    if (all_seats[i].occupied == '1')
                    {
                        letter = '*';
                        ocuppation++;                	
                    }
                    putchar(letter);
                    i++;

                }else{
                    fila++;
                    coluna = 0;
                    printf("\n");
                }
            }
           
            coluna++;
        }

        ocuppation =  (ocuppation * 100)/max_seats;
        printf("\nFlight occupation percentage of %s is %d%% \n", n_flight, ocuppation);
        fclose(flight); 

    }else{
        
        printf("Invalid File\n");
    }

    return ocuppation;
}

void passenger_flight()
{
    FILE *flight;
	seat all_seats[300];
    int number_plane = 0, max_seats, op_flight, *values, fila = 1, coluna = 1;
    int array[3];
    char n_flight[20];
    
    printf("Name of the flight: ");
   	scanf(" %s", n_flight);
    clear();
    
    flight = fopen(n_flight,"rb");

    if(flight != NULL){

        printf("Name flight: %s\n", n_flight);
        
        values = check_max_seats(n_flight,0, array);
        max_seats = values[2];
        clear();

        printf("Name of flight: %s (%d)\n\n", n_flight, values[0]);
        

        fread(&number_plane,sizeof(int),1,flight); 

        for (int i = 0; i < max_seats; i++){

            fread(&all_seats[i],sizeof(seat),1,flight);

            if ((fila == 1) && (coluna == 1)) {printf("Executive seats \n\n");printf("Row\tSeat\t     Name\n");}
            
            if ((fila == (values[0]+1)) && (coluna == 1)) {printf("\nTurist seats \n\n");printf("Row\tSeat\t     Name\n");}
            
            if (all_seats[i].occupied == '1')
            {
                printf(" %d \t %c \t%s \n", fila, (coluna+96), all_seats[i].name);
            }
            
            if ((fila < (values[0]+1)) && (coluna == 4)) {fila++;coluna = 0;}
            
            if ((fila >= (values[0]+1)) && (coluna == 6)) {fila++;coluna = 0;}

            coluna++;
        }

    }else{
        
        printf("Invalid File\n\n");

    }

    wait();
    fclose(flight);
}

void reserve_seat()
{
    FILE *flight;
	seat all_seats[300];
    int number_plane = 0, max_seats, ocuppation = 0, op_flight, fila = 0, lugar, *values, a, valid=0;
    int array[3];
    char n_flight[20], first_name[20], last_name[20], c_lugar;
   
   
    printf("Name of the flight: ");
    scanf(" %s", n_flight);
      

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

        printf("Select row number: ");
        scanf(" %d", &fila);
        printf("Select seat letter (a-f): ");
        scanf(" %c", &c_lugar);
        lugar = c_lugar - 96;
        
		if((lugar >= 0) && (lugar <= 6) && (fila >= 1) && (fila <= values[0]+1))
		{
        	if(fila == 1)
        	{
            	a = lugar - 1;
        	}
        	else if(fila < (values[0]+1))
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
	
            	flight = fopen(n_flight,"wb");
	
            	fwrite(&number_plane,sizeof(int),1,flight);
            	for (int i = 0; i < max_seats; i++)
            	{
                	fwrite(&all_seats[i],sizeof(seat),1,flight);
            	}
        	
        	}else{
	
            	printf("Seat already occupied. Pick another one \n\n");
        	}
    	
    	}else{
    	
    		printf("Seat invalid");
    	}
        	
        fclose(flight);
               
    }else{

        printf("Invalid File\n\n");
    }

    wait();
}

void change_seat()
{
    FILE *flight;
	seat all_seats[300];
    int number_plane = 0, max_seats, ocuppation = 0, op_flight, fila = 0, lugar, *values, old_seat, new_seat;
    int array[3];
    char n_flight[20], first_name[20], last_name[20], c_lugar;
   
   
    printf("Name of the flight: ");
    scanf(" %s", n_flight);  
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

        printf("Select row number: ");
        scanf(" %d", &fila);
        printf("Select seat letter (a-f): ");
        scanf(" %c", &c_lugar);
        lugar = c_lugar - 96;
        
        if((lugar >= 0) && (lugar <= 6) && (fila >= 1) && (fila <= values[0]+1))
        {
        	if(fila == 1)
        	{
            	old_seat = lugar;
        	}
        	else if(fila < (values[0]+1))
        	{
            	old_seat = (((fila - 1) * 4) + lugar) - 1;
	
        	}else
        	{
            	old_seat = (((fila - (values[0] + 1)) * 6) + lugar + (values[0] * 4)) - 1;
        	}
    	
        	if (all_seats[old_seat].occupied == '1')
        	{
            	printf("Verify first and last name: ");
            	scanf(" %s %s",first_name, last_name);
            	strcat(first_name, " ");
            	strcat(first_name,last_name);
	
            	if (strstr(all_seats[old_seat].name,first_name))
            	{
                	printf("Select row number: ");
                	scanf(" %d", &fila);
                	printf("Select seat letter (a-f): ");
                	scanf(" %c", &c_lugar);
                	lugar = c_lugar - 96;
					
					if((lugar >= 0) && (lugar <= 6) && (fila >= 1) && (fila <= values[0]+1))
					{
                		if(fila == 1)
                		{
                    		new_seat = lugar;
                		}
                		else if(fila < (values[0]+1))
                		{
                    		new_seat = (((fila - 1) * 4) + lugar) - 1;
		
                		}else
                		{
                    		new_seat = (((fila - (values[0] + 1)) * 6) + lugar + (values[0] * 4)) - 1;
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
		
                    		printf("Seat changed successfully \n\n");
		
                		}else
                		{
                    		printf("Seat already occupied. Pick another one \n\n");
                		}
                		
                	}else{
                	
                		printf("Invalid Seat");
                	}	
            		
            	}else{
            	
            		printf("Wrong name\n\n");
            	}
	
        	}else{
	
            	printf("Seat is empty \n\n");
        	}
    
        }else{
        	
        	printf("Invalid Seat\n\n");
        }
        
        fclose(flight);

    }else{

        printf("Invalid File\n\n");
    }
    wait();
}

void create_flight(char buffer_f[],char buffer_p[])
{
    FILE *flight;
    seat all_seats[300];
    char n_flight[20], n_plane[20];
    int op_plane, op_flight,number_plane, max_seats, *values;
    int array[3];

    if((buffer_f == NULL) && (buffer_p == NULL))
    {
        printf("Name of the flight: ");
        scanf(" %s", n_flight);
        number_plane = option_plane();

    }else{

        strcpy(n_flight,buffer_f);
        number_plane = atoi(buffer_p);
    }

    if((number_plane >= 318) && (number_plane <= 321))
    {
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
        printf("Invalid option\n\n");
    }

    clear();  
}

void fill_flight()
{
    FILE *flight;
    seat all_seats[300];
    int ocuppation_percent, min = 1, random_seat = 0, random_postion_names, random_postion_subnames, max_seats, number_plane, op_flight, *values;
    int max_namefile = 0, max_subnamefile = 0;
    int array[3];
    char nome[30],subnome[30],n_flight[12], full_name[40], a;
    FILE *nomes = fopen("names", "r"); 
    FILE *subnomes = fopen("surnames", "r");
    
    printf("Name of the flight: ");
    scanf(" %s", n_flight);
    
    number_plane = option_plane();

    while((a = fgetc(nomes)) != EOF)
    {
        if((a != '\n') && (a != EOF))
        {
            max_namefile++;
        }
    }

    while((a = fgetc(subnomes)) != EOF)
    {
        if((a != '\n') && (a != EOF))
        {
            max_subnamefile++;
        }
    }

    if ((number_plane >= 318) && (number_plane <= 321))
    {    
        values = check_max_seats(0,number_plane, array);
        max_seats = values[2];
 
        flight = fopen(n_flight,"wb");
        fwrite(&number_plane,sizeof(int),1,flight);
        
        ocuppation_percent = (rand() % (max_seats - min + 1)) + min;
        
        for (int i = 0; i < max_seats; i++)
        {        
            random_seat = (rand() % (max_seats - min + 1)) + min;

            if (random_seat < ocuppation_percent)
            {
                random_postion_names = (rand() % (max_namefile - min + 1)) + min;
                random_postion_subnames = (rand() % (max_subnamefile - min + 1)) + min;

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
        printf("Invalid option\n\n");
    }

    fclose(nomes);
    fclose(subnomes);
        
}

void histogram()
{
    FILE *flight;
    seat all_seats[300];
    int op_flight, ocuppation, s_window = 0, s_aisle = 0, s_mid = 0, s_exec = 0, s_turist = 0, row, max_seats, i=0, s= 0, number_plane, pos = 0;
    int *values;
    int array[3];
    int n_buffer[6];
    char n_flight[20];
    char c_buffer[6][30] = {"Occupation percentage", "Seats executive", "Seats turist", "Seats window", "Seats middle", "Seats aisle"};
    
    printf("Name of the flight: ");
    scanf(" %s", n_flight);
    printf("\n");  

    flight = fopen(n_flight, "rb");

    ocuppation = occupancy_flight(n_flight);
    fread(&number_plane,sizeof(int),1,flight);

    values = check_max_seats(n_flight,0,array);
    max_seats = values[2];

    for (int a = 0; a < max_seats; a++){

        fread(&all_seats[a],sizeof(seat),1,flight);
    }

    
    for(i = 1; i < (values[0]+1); i++)
    {
        for(;s < (i*4); s++){
            
            pos = (i*4)-s-1;
            

            if(all_seats[s].occupied == '1')
            {
                if (!(pos%3))
                {
                    s_window++;

                }else if(!(pos%1) || !(pos%2))
                {
                    s_aisle++;
                }

                s_exec++;
            }
        }
    }


    for(i = 1; i < (values[1]+1); i++)
    {
        for(;s < (i*6); s++){
            
            pos = (i*6)-s-1;

            if(all_seats[s].occupied == '1')
            {
                if (!(pos%5))
                {
                    s_window++;

                }else if(!(pos%2) || !(pos%3))
                {
                    s_aisle++;

                }else if(!(pos%1) || !(pos%4))
                {
                    s_mid++;
                }

                s_turist++;
            }
        }
    }

    n_buffer[0] = ocuppation;
    n_buffer[1] = s_exec;
    n_buffer[2] = s_turist;
    n_buffer[3] = s_window;
    n_buffer[4] = s_mid;
    n_buffer[5] = s_aisle; 

    printf("\t\t\t");
    for(i = 3;i < 104; i+=3)
    {
        printf("[%d]", i);
    }
    printf("\n");

    for(i = 0; i < 6; i++)
    {
        if(i == 0){

            printf("%s\t", c_buffer[i]);

        }else{

            printf("%s\t\t", c_buffer[i]);
        }

        for(int a = 3; a < (n_buffer[i]+1); a+=3)
        {
            if(a >= 10)
            {
                printf("  * ");
            }else{

                printf(" * ");
            }
        }  

        printf("\n");
    }

    wait();
    fclose(flight);
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
                mostar_avioes(0);
                break;

            case 2: 
                clear();
                occupancy_flight(0);
                wait();
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
                create_flight(0,0);
                break;
            
            case 7:
                clear();
                fill_flight();
                break;

            case 8:
                clear();
                histogram();
                break;
                
            case 9:
            	printf("Run another program to create files names and surnames\n\n");
            	wait();
            	break;

        }
    }
}

void help(char *argv[])
{
    printf("\n\t Sintaxe: %s Flight_name Plane_name\n", argv[0]);
    printf("\t Example: %s TP341 A320\n\n", argv[0]);
    printf("\t Also works with only Plane_name\n");
    printf("\t Example: %s A321\n\n", argv[0]);
    wait();
}

void check_arg(int argc, char *argv[])
{
    char *n_plane;
    int pos = 0;
    
    switch(argc)
    {
        case 2:

            n_plane = argv[1];
            while(n_plane[pos] != '\0')
            {
                if(n_plane[pos] == 'A')
                {
                    for(int i = pos; i < strlen(n_plane); i++)
                    {
                        n_plane[i] = n_plane[i+1];
                    }
                }
                
                pos++;
            }

            mostar_avioes(argv[1]);
            break;
        
        case 3:

            n_plane = argv[1];
            while(n_plane[pos] != '\0')
            {
                if(n_plane[pos] == 'A')
                {
                    for(int i = pos; i < strlen(n_plane); i++)
                    {
                        n_plane[i] = n_plane[i+1];
                    }
                }

                pos++;
            }

            create_flight(argv[1],n_plane);
            break;
    }
}

int main(int argc, char *argv[])
{    
    srand(time(0));
    clear(); 

    if(argc >= 2)
    { 
        if(strstr(argv[1],"-h"))
        {
            help(argv);

        }else{

            check_arg(argc,argv);
            menu();
        }
        
    }else{
  
        menu();
    }

    return 0;
}
