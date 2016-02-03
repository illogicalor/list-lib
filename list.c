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
static pNode_t head;
static pNode_t tail;
static int list_size;

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
 *  @brief  
 */
pNode_t list_end( void )
{
  return tail;
}

/**
 *  @brief  
 */
void list_iterate( pNode_t it )
{

}

/**
 *  @brief  
 */
void list_riterate( pNode_t it )
{

}

/**
 *  @brief  
 */
int list_empty( void )
{

}

/**
 *  @brief  
 */
int list_size( void )
{

}

/**
 *  @brief  
 */
int list_max_size( void )
{

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

