#include "header.h"
#include "generator_agent_header.h"
#include "my_library_header.h"

#include <stdio.h>
#include <stdlib.h>
#include <math.h>




int generate_people()
{

	double inp=0.0;
	record_array record_list;
	
	init_record_array(&record_list);
	
	inp=(double)rand()/(double)RAND_MAX;
	
	if(inp<PROB_INTRO)
	{
		NUMBER_PEOPLE_GENERATED=NUMBER_PEOPLE_GENERATED+1;
		
		add_Person_agent(NUMBER_PEOPLE_GENERATED,1,1, 1,1,0.0,0,&record_list,1.0,0,0,0,0,0,0);
	}
	
	add_people_in_simulation_message(ID,NUMBER_PEOPLE_GENERATED);
	
	return 0;
}
