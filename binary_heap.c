/*==============================================================================
                                 Header
 =============================================================================*/

#include <stdlib.h>
#include <errno.h>
#include <stdio.h>

#include "binary_heap.h"
/*==============================================================================
                        Symbolische Konstanten
 =============================================================================*/

/**
 * Definiert die Schrittgröße in der Speicher angefordert bzw. freigegeben wird.
 */
#define BLOCK_SIZE 5

/*==============================================================================
                        Globale Variablen
 =============================================================================*/

/**
 * Der aktuelle Heap.
 */
static char *p_heap;

/**
 * Aktuelle Heapgröße.
 */
static int heap_size;

/*==============================================================================
                        Makrodefinitionen
 =============================================================================*/
/**
 * Prüft die Speicheralloziierung auf Fehler und bricht das Programm ggf. ab.
 * @param arg Speicherbereich bzw. die erhaltende Startadresse
 */
#define ALLOC_ERR(arg)\
{\
        if(arg == NULL)\
        {\
                fprintf(stderr,"Speicherallozierung fehlgeschlagen: %s\n",\
                strerror(errno));\
                \
                exit(EXIT_FAILURE);\
        }\
}

/**
 * Vertauscht 2 übergebene Elemente im Heap.
 */
#define SWAP_C(c0,c1)\
{\
        char tmp = *(c0);\
        *(c0) = *(c1);\
        *(c1) = tmp;\
}

/*==============================================================================
                        Funktionsprototypen
 =============================================================================*/

/**
 * Sortiert die Werte innerhalb des Heaps, sodass ein konsitenter Min-Heap 
 * entsteht.
 * @param child_node Dás zuletzt hinzugefügte Element.
 */
static void bottom_up_sort(char *child_node);

/**
 * Sortiert die Werte innerhalb des Heap, sodass ein konsistenter Min-Heap
 * entsteht.
 * @param parent_node Startknoten, ab dem sortiert werden soll.
 */
static void top_down_sort(char *parent_node);

/**
 * Gibt die jeweilige Stufe des Heaps auf dem Bildschirm aus.
 * @param pos Die Position des Knotens der betrachtet wird, muss >= 1 sein.
 * @param depth Die aktuelle Stufe die betrachtet wird, beginnt mit 0.
 * 
 */
static void heap_print_stage(int pos, int depth);

/*==============================================================================
                    externe Funktionendefinitionen
 =============================================================================*/

extern void heap_init(void)
{
    /*Dem Heap Speicher zuweisen*/
    p_heap = (char*) malloc(BLOCK_SIZE * sizeof (char));
    /* Fehlerbehandlung */
    ALLOC_ERR(p_heap);
}

extern void heap_destroy(void)
{
    /* Heapgröße zurücksetzen, da nach der "Zerstöung" ein Heap der Größe 0
     zurückbleibt.*/
    heap_size = 0;

    free(p_heap);
    /* Pointer auf Null setzen, damit dieser bei späterer Benutzung nicht 
       auf den alten Speicherbereich zeigen kann.*/
    p_heap = NULL;
}

extern void heap_insert(char element)
{
    /* Reicht der Speicherplatz aus ?*/
     if (heap_size % BLOCK_SIZE == 0)
    {
        /* Speicherbereich vergrößern um Block_size*/
        p_heap = (char*) realloc(p_heap, (size_t) (heap_size + BLOCK_SIZE));

        /* Fehlerbehandlung */
        ALLOC_ERR(p_heap);     
    }
    
    /* Position bestimmen und Wert zuweisen, der Wert ist damit in dem Heap 
     * aufgenohmen */
    char *child_node = p_heap + heap_size;
    *child_node = element;
    
    /* Schon hier erhöhen, da Element schon aufgenohmen*/
    heap_size++;

    /*
     * Fälle:
     * 1) Der Heap war leer => neues Element wird zur Wurzel. Also ist die 
     *    momentane Heapgröße 1, da beim hinzufügen direkt inkrementiert wurde. 
     * 2) Der Heap war ncht leer, also muss möglcherweise etwas vertauscht 
     *    werden.
     */
    
    /* 1. Fall */
    if (heap_size == 0)
    {
        *p_heap = *child_node;
    }

        /* 2.Fall */
    else
    {
        bottom_up_sort(child_node);
    }
}

extern bool heap_extract_min(char *min_element)
{

    /* Sonderfall der Heap ist leer/existiert nicht */
    if (heap_size == 0)
    {
        return false;
    }
    else
    {
        /* Minimum(Wurzel) sichern */
        *min_element = *p_heap;

        /* Letztes Element wird zur neuen Wurzel */
        *p_heap = *(p_heap + (heap_size - 1));

        /* Heap wurde um ein Element reduziert */
        heap_size--;

        /*Gebe Speicher frei,falls Speicher in der Größe BLOCK_SIZE leer steht*/
        if ((heap_size % BLOCK_SIZE) == 0)
        {
            p_heap = (char*) realloc(p_heap, (size_t) sizeof (char) * heap_size);
        }
        /* Sichere die Heap Eigenschaft */
        top_down_sort(p_heap);
        return true;
    }
}

extern void heap_print(void)
{
    /* Fehlerbehandlung: Es existiert kein Heap/dieser ist leer */
    if (heap_size == 0)
    {
        fprintf(stderr, "Es existiert kein Heap oder dieser ist momentan leer.");
        return;
    }
    else
    {
        heap_print_stage(1, 0);
    }
}

/*==============================================================================
                   interne Funktionendefinitionen
 =============================================================================*/

static void bottom_up_sort(char *child_node)
{

    /* Berechne Index des parent */
    int parent_pos = (((child_node - p_heap - 1) / 2));

    /* Adresse des Parent Knotens */
    char *p_parent = p_heap + parent_pos;

    /*
     * Fälle die eintreten können:
     * 
     * 1)Child muss mit Parent getauscht werden (child < parents), da wir hier 
     * einen Min- Heap haben.
     * 
     * 2)Abbruch, falls Child und Parent den gleichen Wert besitzen.
     * 
     * 3)Die Speicheradresse des child Knotens ist ungültig (child < p_heap),
     * dies tritt beim letzten Vergleich auf, also dem Vergleich ob die Wurzel
     * im Vergleich zu ihrem Parent richtig eingeordnet wurde. Dies ist 
     * sinngemäß nicht möglich, da die Wurzel kein Parent besitzt 
     * (Wurzeleigenschaft).
     */

    if (*p_parent > *child_node)
    {
        SWAP_C(p_parent, child_node);
        /* Überprüfe den Heap rekursiv, stoppt falls Fall 1 oder 3 eintreffen */
        bottom_up_sort(p_parent);
    }

    else if (*p_parent == *child_node)
    {
        return;
    }

    else if (child_node <= p_heap)
    {
        return;
    }


}

static void top_down_sort(char *parent_node)
{
    /* Position des linken childs */
    int left_child_pos = (parent_node - p_heap)*2 + 1;
    /* Position des rechten childs */
    int right_child_pos = (parent_node - p_heap)*2 + 2;
    /* Pointer auf das linke child */
    char *p_left_child = p_heap + left_child_pos;
    /* Pointer auf das rechte child */
    char *p_right_child = p_heap + right_child_pos;

    /* Position des aktuellen Minimums (childs) */
    int minIndex = 0;
    /* Pointer auf das aktuelle Minimum (childs) */
    char *p_minIndex;

    /* Prüfe ob diese childs im heap existieren */
    if (right_child_pos >= heap_size)
    {
        if (left_child_pos >= heap_size)
        {
            return;
        }
            /* Nur das linke child liegt im Heap */
        else
        {
            minIndex = left_child_pos;
        }
    }
        /* Beide childs liegen im Heap */
    else
    {
        if (*p_left_child <= *p_right_child)
        {
            minIndex = left_child_pos;
        }
        else
        {
            minIndex = right_child_pos;
        }
    }
    /* Weise Pointer auf das Minimum der Childs zu */
    p_minIndex = p_heap + minIndex;

    /* Prüfe ob getauscht werden muss */
    if (*parent_node > *p_minIndex)
    {
        SWAP_C(parent_node, p_minIndex);
        top_down_sort(p_minIndex);
    }
}

static void heap_print_stage(int pos, int depth)
{

    /* Zähler für die Leerzeichen */
    int i;

    /* Ausgabe Einrückung */
    for (i = 0; i < depth; i++)
    {
        printf("   ");
    }

    /* Gebe aktuelles Zeichen aus */
    printf("|--%c\n", p_heap[pos - 1]);

    depth++;

    /* Prüfe linkes child auf Existenz */
    if (pos * 2 <= heap_size)
    {
        heap_print_stage(pos * 2, depth);
    }

    /* Prüfe rechtes child auf Existenz */
    if (pos * 2 + 1 <= heap_size)
    {
        heap_print_stage(pos * 2 + 1, depth);
    }
}