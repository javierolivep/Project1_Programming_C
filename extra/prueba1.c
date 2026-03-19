#include <stdio.h>

int main(int argc, char *argv[])
{
    int i;
    printf("argc is: %d\n", argc);
    for( i = 0; i < argc; i++ )
    {
        printf("Parameter %d is: %s\n", i, argv[i]);  
    }
    
    return 0;
}
    
