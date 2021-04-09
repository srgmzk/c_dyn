/*
 * =====================================================================================
 *
 *       Filename:  strln.c
 *
 *    Description:  
 *
 *        Version:  1.0
 *        Created:  09.04.2021 03:11:17
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  YOUR NAME (), 
 *   Organization:  
 *
 * =====================================================================================
 */

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
int main()
{
	char *s;
	char cs[10] = "abc";
	s = malloc(sizeof(char)*10);

	printf("stln: %d\n", strlen(s));
	s[0] = '\0';
	printf("stln: %d\n", strlen(s));

	printf("%s\n", cs);
	sprintf(s, "%s", cs);
	printf("stln: %d\n", strlen(s));


	return 0;
}
