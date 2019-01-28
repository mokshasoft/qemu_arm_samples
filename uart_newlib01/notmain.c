#include <stdio.h>
#include <malloc.h>

int notmain(void)
{
    printf("ARM bare-metal newlib\n");
    int *ptr1 = malloc(100);
    int *ptr2 = malloc(1000);
    printf("got memory pointer %p\n", ptr1);
    printf("got memory pointer %p\n", ptr2);
    free(ptr1);
    free(ptr2);
    printf("free'd pointers\n");
    return 0;
}
