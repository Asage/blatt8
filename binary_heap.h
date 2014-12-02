/* 
 * File:   binary_heap.h
 * Author: Marc
 *
 * Created on 1. Dezember 2014, 15:47
 */

#ifndef BINARY_HEAP_H
#define	BINARY_HEAP_H

/*==============================================================================
                                 Header
 =============================================================================*/

#include <stdbool.h>

/*==============================================================================
                          Funktionsprototypen
 =============================================================================*/

/**
 * Erzeugt einen Heap, mit der Anfangsgröße.
 */
extern void heap_init(void);

/**
 * Löscht einen Heap, indem der gesamte Speicher freigegeben wird.
 */
extern void heap_destroy(void);

/**
 * Fügt ein Element dem Heap hinzu und erhält die Heapeigenschaft.
 * @param element einzufügendes Element
 */
extern void heap_insert(char element);

/**
 * Entfernt das kleineste Element aus dem Heap (die Wurzel), auch hier wird die 
 * Heapeigenschaft aufrecht erhalten.
 * @param min_element Speicherort für das Minimum
 * @return Das Minimum in dem übergebenden Speicherplatz.
 *         True, sofern das Minimum erfolgreich extrahiert werden konnte.
 *         False, falls der Heap bereits leer war.
 */
extern bool heap_extract_min(char *min_element);

/**
 * Gibt den Heap auf dem Bildschirm aus.
 */
extern void heap_print(void);

#endif	/* BINARY_HEAP_H */

