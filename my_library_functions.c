#include "my_library_header.h"
#include "header.h"


int random_int(int a, int b)//return number between a and b
{
	int c=0;
	int d=0;
	
	//printf("Value a %d and b %d", a, b);
	if(a==b)
		d=a;
	
	else if(a<b)
	{
		d= rand() % (b+1);
		//printf("val: %d \n", rand() % 2);//between (0,1) ->not 2
	}
	else
	{
		c=a-b;
		d=(rand() % a) + b;
	}
	//printf("Value d %d",d);
	return d;
}


double random_double(double a, double b)//return number between a and b
{
	double c=0.0;
	double d=0.0;
	if(a==b)
		d=a;
	else if(a<b)
	{
		c=b-a;
		d=(double)rand()/(double)RAND_MAX + a;
	}
	else
	{
		c=a-b;
		d=(double)rand()/(double)RAND_MAX + b;
	}
	return d;
}

int compare_arrays(int * first, int * second)
{
	int i;
	int flag=0;
	int a,b;
	for(i=0;i<LENGTH;i++)
	{
		a=first[i];
		b=second[i];
		if(a!=b)
		{
			flag=1;
		}
		//printf("array value-%d, %d\n",a,b );
	}
	//retruns 1 for false and 0 for true
	return flag;
	
}

