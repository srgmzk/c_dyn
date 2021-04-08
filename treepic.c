#include <stdio.h>
#include <string.h>
#include <stdlib.h>
int main()
{
	#if 0
	          10        20        30     
	0123456789012345678901234567890
                                  [ 1200 ]
                                     |           	
	                       +---------+--------+
                           |                  |
    	             +-----+-----+            +---      
                     |           |
                 [ 1200 ]    [ 1200 ]  [ 1200 ]    [ 1200 ]

	#endif	

	char fullstr[5][256];//=malloc(sizeof(char)*1000);

 	char ch1[] = "   |\n+--+--+\n|     |";
	char ch2[] = "";

	int i = 0, j = 0;
	int val = 0;
	while(i < 5)
 	{
		j = i; 
		while(j) 
		{ 
			scanf("%d", &val);
			sprintf(&fullstr[i][j], "%d", &val);	
			j--;
		}
		i++;
	}
		for (i=0; i<5; i++)		
		{
			for (j=i; j < ; j++)
				printf("%c \n", fullstr[i][j]);
		}

	return 0;	
}
