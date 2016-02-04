/********************************************************************************
 * 
 *  @file:    list.c
 *  @author:  IllogicalOR
 *  @brief:   List implementation with a linked list.
 * 
 ********************************************************************************
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
#endif /* LIST_USE_MALLOC */

/***** Function Prototypes *****/
static Node_t *get_next_free_node( void );

/***** Function Definitions *****/
// ---------- Overflow Functions ----------
/**
 *  @brief  Initialize the list
 */
void list_init( void )
{
  head = tail = NULL;

#if ( defined LIST_USE_MALLOC && LIST_USE_MALLOC == 0 )
  memset( nodes, 0, sizeof( nodes ) );
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
#else
  // TODO
#endif /* LIST_USE_MALLOC */

  // Make sure head and tail pointers are null.
  head = tail = NULL;

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
  Node_t *new_node = (Node_t *)malloc( sizeof( Node_t ) );
  return new_node;
#endif /* LIST_USE_MALLOC */
}

