/*******************************************************************************
 * 
 *  @file:    list.c
 *  @author:  IllogicalOR
 *  @brief:   List implementation with a linked list.
 * 
 *******************************************************************************
 */

/***** Includes *****/
#include <string.h>
#include "list.h"

/***** Error checking *****/

/***** Definitions *****/
#define NODE_UNUSED   0
#define NODE_IN_USE   1

/***** Local Variables *****/
static int initialized = 0;
static pNode_t head;
static pNode_t tail;
static int size;

#if ( defined LIST_USE_MALLOC && LIST_USE_MALLOC == 0 )
static Node_t nodes[MAX_LIST_SIZE];
#else
static fnptrFreeNode_t free_node;
#endif /* LIST_USE_MALLOC */

/***** Function Prototypes *****/
static Node_t *get_next_free_node( void );

/***** Function Definitions *****/
// ---------- Overflow Functions ----------
/**
 *  @brief  Initialize the list
 */
#if ( defined LIST_USE_MALLOC && LIST_USE_MALLOC == 0 )
void list_init( void )
#else
void list_init( fnptrFreeNode_t fptr )
#endif
{
  head = tail = NULL;
  size = 0;

#if ( defined LIST_USE_MALLOC && LIST_USE_MALLOC == 0 )
  memset( nodes, 0, sizeof( nodes ) );
#else
  // Must have provided a valid "free_node()" function.
  if ( fptr )
  {
    free_node = fptr;
  }
  else
  {
    // List is unitialized!
    initialized = 0;
    return;
  }
#endif /* LIST_USE_MALLOC */

  // Set internal flag that list is initialized.
  initialized = 1;
}

/**
 *  @brief  Deinitialize the list
 */
void list_deinit( void )
{
  //
  // If LIST_USE_MALLOC is 0, then just clear the memory contents
  // of the array of nodes. If LIST_USE_MALLOC is 1, we need to
  // go through the entire list and free any allocated nodes.
  //
#if ( defined LIST_USE_MALLOC && LIST_USE_MALLOC == 0 )
  memset( nodes, 0, sizeof( nodes ) );
  head = tail = NULL;
  size = 0;
#else
  pNode_t temp;
  while ( head )
  {
    temp = head;
    head = head->next;
    // TODO what about nodes that have pointers to data structs?
    // Need a generic way to call a custom "free()" function.
    free_node( temp );
  }
  tail = NULL;
  free_node = NULL;
  size = 0;
#endif /* LIST_USE_MALLOC */


  // Clear internal flag that list is initialized.
  initialized = 0;
}

/**
 *  @brief  Determined if list was initialized or not.
 *  @return 1 if list is initialized, 0 otherwise.
 */
int list_initialized( void )
{
  return initialized;
}

/**
 *  @brief  Return iterator to beginning of list.
 *  @return Iterator (pointer) to the beginning of the list.
 */
pNode_t list_begin( void )
{
  return head;
}

/**
 *  @brief  Return iterator to end of the list.
 *  @return Iterator (pointer) to the end of the list.
 */
pNode_t list_end( void )
{
  return tail;
} 
/**
 *  @brief  Advance iterator forward to next node.
 */
void list_iterate( pNode_t it )
{
  if ( it != NULL )
  {
    it = it->next;
  }
}

/**
 *  @brief  Advance iterator backwards to previous node.
 */
void list_riterate( pNode_t it )
{
  if ( it != NULL )
  {
    it = it->prev;
  }
}

/**
 *  @brief  See if the list is empty.
 *  @return 1 if list is empty. 0 otherwise.
 */
int list_empty( void )
{
  return ( size == 0 );
}

/**
 *  @brief  Get the size of the list.
 *  @return Size of the list.
 */
int list_size( void )
{
  return size;
}

/**
 *  @brief  Get the maximum possible list size.
 *  @return Maximum list size possible.
 */
int list_max_size( void )
{
  return MAX_LIST_SIZE;
}

/***** Private Functions *****/
static Node_t *get_next_free_node( void )
{
#if ( defined LIST_USE_MALLOC && LIST_USE_MALLOC == 0 )
  int idx;

  // Loop through the statically-allocated nodes to find
  // an unused node.
  for ( idx = 0; idx < MAX_LIST_SIZE; idx++ )
  {
    if ( nodes[idx].in_use == NODE_UNUSED )
    {
      nodes[idx].in_use = NODE_IN_USE;
      return &nodes[idx];
    }
  }

  // No free node found.
  return NULL;
#else
  if ( size < MAX_LIST_SIZE )
  {
    Node_t *new_node = (Node_t *)malloc( sizeof( Node_t ) );
    return new_node;
  }

  // Max size reached. Don't allocated anymore memory.
  return NULL;
#endif /* LIST_USE_MALLOC */
}

