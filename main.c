/* 
 * @file
 * Dieses Modul dient zum Testen der implementierten Modulen und Funktionen.
 * 
 *
 * Created on 1. Dezember 2014, 15:46
 */

#include <stdio.h>
#include <stdlib.h>
#include<string.h>

#include "binary_heap.h"


static void test_heap(void){
    int index;
    char  letter = 0;
    
    char *letters = "112354333333333333331111";
    int size = (int) strlen(letters);
    
    printf("\nTest\n");
    
    /* Heap initialisieren */
    heap_init();
    
    /* Elemente einfügen */
    for (index = 0; index < size ; index++)
    {
        heap_insert(letters[index]);
    }
    
    /* Ausgabe auf den Monitor */

    heap_print();
    
    while(heap_extract_min(&letter))
    {
        printf("extrahiert: %c\n",letter);        
    }
    
    heap_destroy();
}


/*
 * 
 */
int main(void)
{
    test_heap();
    return (EXIT_SUCCESS);
}

