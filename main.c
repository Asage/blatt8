/* 
 * @file
 * Dieses Modul dient zum Testen der implementierten Modulen und Funktionen.
 * 
 *
 * Created on 1. Dezember 2014, 15:46
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>


#include "binary_heap.h"

/*
static void test1()
{
    int i;
    char min_element;
    char string[] = "abcde";
    char ergebnis[5];



    for (i = 0; string[i] != '\0'; i++)
    {
        heap_insert(string[i]);
    }

    for (i = 0; heap_extract_min(&min_element); i++)
    {
        ergebnis[i] = min_element;
    }



}

static void test2()
{
    int i;
    char string[] = "abcdgijnhp";
    char ergebnis[10];
    char min_element;

    for (i = 0; string[i] != '\0'; i++)
    {
        heap_insert(string[i]);
    }

    for (i = 0; heap_extract_min(&min_element); i++)
    {
        ergebnis[i] = min_element;
    }

   
}

static void test3()
{
    int i;
    char string[] = "phnjigdcba";
    char ergebnis[10];
    char min_element;

    for (i = 0; string[i] != '\0'; i++)
    {
        heap_insert(string[i]);
    }

    for (i = 0; heap_extract_min(&min_element); i++)
    {
        ergebnis[i] = min_element;
    }

    
}

static void test4()
{
    int i;
    char string[] = "Donaudampfschifffahrtsgesellschaftskapitaen";
    char ergebnis[43];
    char min_element;

    for (i = 0; string[i] != '\0'; i++)
    {
        heap_insert(string[i]);
    }

    for (i = 0; heap_extract_min(&min_element); i++)
    {
        ergebnis[i] = min_element;
    }

   
}

static void test5()
{
    int i;
    char string[] = "2134";
    char ergebnis[4];
    char min_element;

    for (i = 0; string[i] != '\0'; i++)
    {
        heap_insert(string[i]);
    }

    for (i = 0; heap_extract_min(&min_element); i++)
    {
        ergebnis[i] = min_element;
    }

    
}

static void test6()
{
    int i;
    char string[] = "a";
    char ergebnis[1];
    char min_element;

    for (i = 0; string[i] != '\0'; i++)
    {
        heap_insert(string[i]);
    }

    for (i = 0; heap_extract_min(&min_element); i++)
    {
        ergebnis[i] = min_element;
    }

    for (i = 0; string[i] != '\0'; i++)
    {
        heap_insert(string[i]);
    }

    for (i = 0; heap_extract_min(&min_element); i++)
    {
        ergebnis[i] = min_element;
    }

    
}

static void test7()
{

    int i;
    char string[] = "a";
    char ergebnis[1];
    char min_element;

    for (i = 0; string[i] != '\0'; i++)
    {
        heap_insert(string[i]);
    }

    for (i = 0; heap_extract_min(&min_element); i++)
    {
        ergebnis[i] = min_element;
    }

    for (i = 0; string[i] != '\0'; i++)
    {
        heap_insert(string[i]);
    }

    for (i = 0; heap_extract_min(&min_element); i++)
    {
        ergebnis[i] = min_element;
    }

   
}
*/

static void test_heap(void)
{
    int index;
    char letter = 0;

    char *letters = "112354333333333333331111";
    int size = (int) strlen(letters);

    printf("\nTest\n");

    /* Heap initialisieren */
    heap_init();

    /* Elemente einfügen */
    for (index = 0; index < size; index++)
    {
        heap_insert(letters[index]);
    }

    /* Ausgabe auf den Monitor */

    heap_print();

    while (heap_extract_min(&letter))
    {
        printf("extrahiert: %c\n", letter);
    }

    heap_destroy();
}

/*
 * 
 */
int main(void)
{
            test_heap();
/*
    heap_init();
    test1();
    test2();
    test3();
    test4();
    test5();
    test6();
    
    test7();
    heap_destroy();
*/
    return (EXIT_SUCCESS);
}

