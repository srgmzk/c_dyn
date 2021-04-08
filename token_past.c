#include <stdio.h>
#define MERGE(token1, token2) token1##token2  
#define AAAA 
//#undef AAAA
int main(void)
{
    int var1 = 10;
    int var2 = 20;
    int var3 = 30;
    
    printf("%d\n", MERGE(var, 1));
        
    printf("%d\n", MERGE(var, 2));
    printf("%d\n", MERGE(var, 3));
    #ifdef AAAA
		printf("DEFINE! %s\n", AAAA);
	#endif
    return 0;
}
