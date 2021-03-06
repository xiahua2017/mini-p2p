/****************************************************************/
/* @file ds.c                                                   */
/*                                                              */
/* @brief Contains custom data structures built by the authors. */
/*                                                              */
/* @authors Fadhil Abubaker, Malek Anabtawi                     */
/****************************************************************/

#include "ds.h"

/* Linked list for storing bytes */

ll* create_ll()
{
  ll* new = malloc(sizeof(ll));

  new->first = NULL;
  new->last  = NULL;
  new->count = 0;

  return new;
}

void remove_ll(ll* list)
{
  if (list == NULL)
    return;

  node* current = list->first;
  node* next;

  for(size_t i = 0; i < list->count; i++)
    {
      next = current->next;
      free(current);
      current = next;
    }

  list->count = 0;
  list->first = NULL;
  list->last  = NULL;
  free(list);
}

void add_node(ll* list, uint8_t* data, size_t n, int type)
{
  node* prev;

  if(n >= DATA_SIZE)
    {
      return;
    }

  node* new = malloc(sizeof(node));
  bzero(new, sizeof(node));

  if(list->first == NULL)
    {
      list->first = new;
      list->last  = new;
    }
  else
    {
      prev = list->last;
      list->last = new;
      prev->next = new;

      list->last->next = NULL;
    }

  memmove(list->last->data, data, n);
  list->last->type = type;
  list->count++;
}


/***********************************************************/
/* @brief Deletes a node from the head of the linked list. */
/* @param list - The list to delete the node from.         */
/***********************************************************/
void delete_node(ll* list)
{
  node* killme;

  if (list == NULL)
    return;

  if (list->count == 0)
    {
      return;
    }

  killme      = list->first;
  list->first = list->first->next;

  if(list->count == 1)
    list->last = NULL;

  list->count--;
  free(killme);
}

void del_all_nodes(ll* list)
{
  while(list->count > 0)
    {
      delete_node(list);
    }
}

/*********************************************************************/
/* @brief Appends two linked lists. Can even append two linked lists */
/*        with different data                                        */
/* @param list1 - The prefix list.                                   */
/* @param list2 - The suffix list.                                   */
/*********************************************************************/
ll* append(ll* list1, ll* list2)
{
  if(!list1 || !list1->count)
    return list2;

  if(!list2 || !list2->count)
    return list1;

  list1->last->next = list2->first;
  list1->last = list2->last;
  list1->count += list2->count;
  free(list2);

  return list1;
}

/* #ifdef TESTING */
/* #include <stdlib.h> */
/* #include <stdio.h> */
/* #include <string.h> */

/* int main() */
/* { */
/*   uint8_t buf1[200] = {2,3,4,1,1,1,0}; */
/*   uint8_t buf2[200] = {1,3,2,1,1,1,0}; */
/*   uint8_t buf3[200] = {6,5,13,2,1,8,0}; */
/*   node* cur = NULL; */

/*   ll* test1 = create_ll(); */
/*   add_node(test1, buf1, 200); */
/*   add_node(test1, buf2, 200); */
/*   add_node(test1, buf3, 200); */
/*   add_node(test1, buf3, 200); */
/*   add_node(test1, buf3, 200); */
/*   add_node(test1, buf3, 200); */
/*   add_node(test1, buf3, 200); */
/*   add_node(test1, buf3, 200); */

/*   cur = test1->first; */

/*   for(size_t i = 0; i < test1->count; i++) */
/*     { */
/*       cur = cur->next; */
/*       /\* Check in GDB values of cur->data *\/ */
/*     } */

/*   remove_ll(test1); */
/* } */
/* #endif */

/* End Linked list */
