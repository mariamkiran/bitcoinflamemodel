#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/*************************************
* Struct Type Definitions            *
*************************************/



struct xmachine_averager
{
	int id;
	int number_of_transactions;
       double average_price;
       double bitcoin_number_total;
	  double true_avg_price;
	int numbers;

	struct xmachine_averager * next;
};



typedef struct xmachine_averager xmachine_averager;

/*****************************************************************
* FUNCTIONS: linked list functions                               *
* PURPOSE: to allocate and free memory in linked lists           *
*****************************************************************/


void freeaveragers(xmachine_averager * head)
{
	/* Tempory element needed for loop */
	xmachine_averager * tmp;

	/* Loop while head is not NULL */
	while(head)
	{
		/* Make next in list tmp */
		tmp = head->next;
		/* Free memory of head */
		free(head);
		/* Make head the next in the list */
		head = tmp;
	}
}





xmachine_averager * addaverager(xmachine_averager ** pointer_to_averagers, xmachine_averager * current)
{
	/* The new tail of the linked list */
	xmachine_averager * tail;

	/* Allocate memory for new neighbour data */

	tail = (xmachine_averager *)malloc(sizeof(xmachine_averager));

	/* Check if current is not NULL */
	if(current)
	{
		/* Current exists therefore make its next point to tail */
		current->next = tail;
	}
	else
	{
		/* Current is NULL therefore make the cell neighbour_head point to tail */
		*pointer_to_averagers = tail;
	}
	/* Point next to NULL */
	tail->next = NULL;
	/* Return new neighbour data */
	return tail;
}




/*****************************************************************
* FUNCTION: getIteration                                         *
* PURPOSE: read iteration xml file                               *
*****************************************************************/
int getiteration(char * filepath, int itno,  xmachine_averager ** pointer_to_averagers)
{
	/* Pointer to file */
	FILE *file;
	/* Char and char buffer for reading file to */
	char c = ' ';
	char buffer[40];
	/* Variable to keep reading file */
	int reading = 1;
	/* Variables for checking tags */
	int i, initeration, inagent;
	int intag, instate, inname, inid;
	int inxpos, inypos;
	
	int innumber_of_transactions;
       int inaverage_price;
       int inbitcoin_number_total;
	int intrue_avg_price;
	int innumbers;
	
	/* Variables for model data */
	int id;
	int state;
	// prices for lux and non
	int sugars;
	double xpos;
	double ypos;
	int number_of_transactions;
       double average_price;
       double bitcoin_number_total;
	double true_avg_price;
	int numbers;
	
	printf("here");
	char name[100];
	
	
	xmachine_averager * current_averager, * tail_averager;
	tail_averager = *pointer_to_averagers;
	current_averager = NULL;
	
	
	

	/* Open config file to read-only */
	char data[200];
	sprintf(data, "%s%i%s", filepath, itno, ".xml");
	printf("%s", data);
	if((file = fopen(data, "r"))==NULL)
	{
		printf(" nent\n");
		return 0;
		/*exit(0);*/
	}
	else
	{

	printf("\n");
	/* Initialise variables */
	i = 0;
	intag = 0;
	initeration = 0;
	inagent = 0;
	instate = 0;
	inname = 0;
	inid = 0;
	inxpos=0;
	inypos=0;
	intrue_avg_price=0;
	innumbers=0;
		
	state = 0;
	id = 0;
	//a = 0.0;

	xpos=0.0;
	ypos=0.0;
		number_of_transactions=0;
        average_price=0.0;
       bitcoin_number_total=0.0;
	true_avg_price=0.0;
	numbers=0;
	
	//price = 0.0;
	//sold = 0;
		
	/* Read characters until the end of the file */
	/*while(c != EOF)*/
	/* Read characters until end of xml found */
	while(reading == 1)
	{
		/* Get the next char from the file */
		c = fgetc(file);
		
		/* If the end of a tag */
		if(c == '>')
		{
			/* Place 0 at end of buffer to make chars a string */
			buffer[i] = 0;
			if(strcmp(buffer, "states") == 0) { initeration = 1; }
			if(strcmp(buffer, "/states") == 0) { initeration = 0; reading = 0; }
			if(strcmp(buffer, "xagent") == 0) { inagent = 1; }
			if(strcmp(buffer, "/xagent") == 0)
			{
				inagent = 0;
				
				printf("Found agent ... ");
				
								
				if(strcmp(name, "Averager") == 0)
				{
				//	printf("Adding mall agent\n");
					
					/* check if tail is NULL */
					if(tail_averager == NULL)
					{
						//printf("tail is null allocate more memory\n");
						/* Allocate memory */
						tail_averager = addaverager(pointer_to_averagers, current_averager);
					}
					//else printf("tail exisits\n");
					
					/* Make tail the current element to add to */
					current_averager = tail_averager;
					
					current_averager->id = id;
					current_averager->number_of_transactions=number_of_transactions;
					current_averager->average_price=average_price;
					current_averager->bitcoin_number_total=bitcoin_number_total;
					current_averager->true_avg_price=true_avg_price;
					current_averager->numbers=numbers;
					
					/* Make tail the next element in the linked list */
					tail_averager = current_averager->next;
				}
					

								
				
					
				
				//else printf("Not adding agent\n");
			}
			if(strcmp(buffer, "name") == 0) { inname = 1; }
			if(strcmp(buffer, "/name") == 0) { inname = 0; }
			if(strcmp(buffer, "id") == 0) { inid = 1; }
			if(strcmp(buffer, "/id") == 0) { inid = 0; }
			if(strcmp(buffer, "xpos") == 0) { inxpos = 1; }
			if(strcmp(buffer, "/xpos") == 0) { inxpos = 0; }
			if(strcmp(buffer, "ypos") == 0) { inypos = 1; }
			if(strcmp(buffer, "/ypos") == 0) { inypos = 0; }
			
			
			if(strcmp(buffer, "number_of_transactions") == 0) { innumber_of_transactions = 1; }
			if(strcmp(buffer, "/number_of_transactions") == 0) { innumber_of_transactions = 0; }
			
			
			if(strcmp(buffer, "average_price") == 0) { inaverage_price = 1; }
			if(strcmp(buffer, "/average_price") == 0) { inaverage_price = 0; }
			
			
			if(strcmp(buffer, "bitcoin_number_total") == 0) { inbitcoin_number_total = 1; }
			if(strcmp(buffer, "/bitcoin_number_total") == 0) { inbitcoin_number_total = 0; }
			
			if(strcmp(buffer, "true_avg_price") == 0) { intrue_avg_price = 1; }
			if(strcmp(buffer, "/true_avg_price") == 0) { intrue_avg_price = 0; }
			
			if(strcmp(buffer, "numbers") == 0) { innumbers = 1; }
			if(strcmp(buffer, "/numbers") == 0) { innumbers = 0; }
		
			
					/* Make tail the next element in the linked list */
			/* End of tag and reset buffer */
			intag = 0;
			i = 0;
		}
		/* If start of tag */
		else if(c == '<')
		{
			/* Place /0 at end of buffer to end numbers */
			buffer[i] = 0;
			/* Flag in tag */
			intag = 1;
			/* If just read data into buffer retrieve it */
			if(inagent && inid) { id = atoi(buffer); }
			if(inagent && inname)  { strcpy(name, buffer); }
			if(inagent && inxpos)  {xpos  = atof(buffer); }
			if(inagent && inypos)  { ypos = atof(buffer); }
			
			if(inagent && innumber_of_transactions)  { number_of_transactions = atoi(buffer); }
			
			if(inagent && inaverage_price)  { average_price = atof(buffer); }
			
			if(inagent && inbitcoin_number_total)  { bitcoin_number_total = atof(buffer); }
			
				if(inagent && intrue_avg_price)  { true_avg_price = atof(buffer); }
				
					if(inagent && innumbers)  { numbers = atoi(buffer); }
				
				
			printf("w");
		

			
			/* Reset buffer */
			i = 0;
		}
		/* If in tag put read char into buffer */
		else if(intag)
		{
			buffer[i] = c;
			i++;
		}
		/* If in data read char into buffer */
		else if(inname || inid || inxpos || inypos ||  innumber_of_transactions ||  inaverage_price ||  inbitcoin_number_total || intrue_avg_price || innumbers)

		{
			buffer[i] = c;
			i++;
		}
	}
	
	/* Free memory for unused linked list elements */
	
	
	/* Free memory for unused linked list elements */
	if(tail_averager)
	{
		freeaveragers(tail_averager);
		/* Make pointer to tail equal NULL */
		if(current_averager) { current_averager->next = NULL; }
	}
	
	
	

	/* Close the file */
	fclose(file);
	
	/*printagentdata(pointer_to_cells);*/
	
	return 1;
	}
}

void savedatatofile(int itno, xmachine_averager ** pointer_to_averagers)
{
	FILE *file;
	char data[100];
	xmachine_averager * current_averager;
	
	current_averager = *pointer_to_averagers;
	
	
	double payavg=0.0;
	double payavgsug=0.0;
	int numb=0;
	
	//double ave_price = 0.0;
	while(current_averager)
	{
			//	printf("nope");
			file = fopen("data_averager.xls", "a");
			sprintf(data, "%i", itno);
			fputs(data, file);
			fputs("\t", file);			
			sprintf(data, "%i", current_averager->id);
			fputs(data, file);
			fputs("\t", file);
			sprintf(data, "%i", current_averager->number_of_transactions);
			fputs(data, file);
			fputs("\t", file);
			sprintf(data, "%f", current_averager->average_price);
			fputs(data, file);
			
			fputs("\t", file);
			sprintf(data, "%f", current_averager->bitcoin_number_total );
			fputs(data, file);
			
			fputs("\t", file);
			sprintf(data, "%f", current_averager->true_avg_price );
			fputs(data, file);
			
			fputs("\t", file);
			sprintf(data, "%i", current_averager->numbers);
			fputs(data, file);
			
			fputs("\n", file);
			fclose(file);
		
		current_averager = current_averager->next;
	}

	
	
}

int main( int argc, char **argv )
{
	int position = 0;
	int lastd = 0;
	int i;
	char * filepath;
	xmachine_averager * averagers, * current_averager;
	
	xmachine_averager ** p_averagers;
	

	int iteration_number = 0;
	int stilldata = 1;
	FILE *file;
	
	file = fopen("data_averager.xls", "w");
	fputs("itno", file);
	fputs("\t", file);			
	fputs("id", file);
	fputs("\t", file);
	fputs("number transactions", file);
	fputs("\t", file);
	fputs("price", file);
	fputs("\t", file);
	fputs("bitcoins no", file);
	fputs("\t", file);
	fputs("vwap", file);
	fputs("\t", file);
	fputs("numbers", file);
	fputs("\n", file);
			
	fclose(file);
	
	
	
	/* Read initial states of x-machines */
	/* advance argument pointer to next argument */
	*argv++;
	if(*argv == NULL)
	{
		printf("No intial states defined\n");
		exit(0);
	}
	printf("Initial states: %s\n", *argv);
	/*readinitialstates(*argv, p_iteration_number, p_xmemory);*/
	while(**argv != 0)
	{
		/* For windows directories */
		if(**argv == '\\') lastd=position;
		/* For windows directories */
		if(**argv == '/') lastd=position;
		(*argv)++;
		position++;
	}
	for(i=position; i>0; i--)
	{
		if(i==lastd+1) **argv = 0;
		(*argv)--;
	}
	filepath = *argv;
	printf("Ouput dir: %s\n", filepath);
	
	/* Initialise pointers */
	averagers = NULL;
	p_averagers = &averagers;
	

	
	while(stilldata)
	{
		stilldata = getiteration(filepath, iteration_number, p_averagers);
		
		if(stilldata) savedatatofile(iteration_number, p_averagers);
		
		iteration_number++;
		
	}
	
	/* Should never get here */
	return( 0 );
}


