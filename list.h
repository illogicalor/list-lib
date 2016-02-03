/********************************************************************************
 * 
 *  @file:    list.h
 *  @author:  IllogicalOR
 *  @brief:   Header file for generic list library.
 * 
 ********************************************************************************
 */

#ifndef __LIST_H__
#define __LIST_H__

/***** Includes *****/
#include <stdlib.h> // Needed for NULL define. Change accordingly.

/***** Definitions *****/
//
// Configure whether list uses malloc or a statically-
// defined number of elements.
//
#define LIST_USE_MALLOC   0

//
// Configure the maximum size of the list
//
#define MAX_LIST_SIZE     32

//
// Node data structure. This must be defined!
// Default type is an int.
//
typedef int listnode_data_t;

//
// !!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
// !! --- Remaining code should not be modified --- !!
// !!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
//

//
// Node structure.
//
typedef struct listnode_t
{
  // Node data
  listnode_data_t   data;
  // Node pointers
  struct listnode_t *next;
  struct listnode_t *prev;
#if ( defined LIST_USE_MALLOC && LIST_USE_MALLOC == 0 )
  int in_use;
#endif
} Node_t, *pNode_t;

/***** Function Prototypes *****/
//
// Init function
//
void list_init( void );

//
// Iterators
//
pNode_t list_begin( void );
pNode_t list_end( void );
void list_iterate( pNode_t it );
void list_riterate( pNode_t it );

//
// Capacity
//
int list_empty( void );
int list_size( void );
int list_max_size( void );

//
// Element access
//
listnode_data_t list_front( void );
listnode_data_t list_back( void );

//
// Modifiers
//
void list_push_front( listnode_data_t val );
void list_pop_front( void );
void list_push_back( listnode_data_t val );
void list_pop_back( void );

#endif /* __LIST_H__ */

