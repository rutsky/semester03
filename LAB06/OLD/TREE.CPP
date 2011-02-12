/* Lab #6
 * Bob Rutsky, 2057/2
 * 12.12.2007
 */

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <assert.h>

#include "tree.h"
#include "stack.h"

TreeNode * allocateNode( char const *key, char const *value, TreeNode *left, TreeNode *right )
{
  TreeNode *node = NULL;

  if ((node = malloc(sizeof(TreeNode))) == NULL)
  {
    perror("malloc");
    return NULL;
  }

  if ((node->key = malloc(sizeof(char) * (strlen(key) + 1))) == NULL)
  {
    perror("malloc");
    free(node);
    return NULL;
  }

  if ((node->value = malloc(sizeof(char) * (strlen(value) + 1))) == NULL)
  {
    perror("malloc");
    free(node->key);
    free(node);
    return NULL;
  }

  strcpy(node->key, key);
  strcpy(node->value, value);
  node->right = right;
  node->left  = left;

  return node;
}

void freeTreeNode( TreeNode *node )
{
  if (node != NULL)
  {
    free(node->key);
    free(node->value);
    free(node);
  }
}

int less( char const *a, char const *b )
{
  return strcmp(a, b) < 0;
}

TreeNode * addNode( TreeNode *root, char const *key, char const *value )
{
  TreeNode *node;
  if ((node = allocateNode(key, value, NULL, NULL)) == NULL)
    return NULL;

  if (root == NULL)
  {
    node->number = 0;
    return node;
  }
  else
  {
    TreeNode *elem = root;
    StackElem *stack = NULL;

    while (1)
    {
      if (less(node->key, elem->key))
      {
        if (elem->left == NULL)
        {
          elem->left = node;
          node->number = elem->number;
          break;
        }
        else
        {
          push(stack, elem);
          elem = elem->left;
        }
      }
      else
      {
        if (elem->right == NULL)
        {
          elem->right = node;
          node->number = elem->number + 1;
          break;
        }
        else
        {
          push(stack, elem);
          elem = elem->right;
        }
      }
    }

    /*
    while (1)
    {
      TreeNode *current = (TreeNode *)pop(&stack);
      if (current == NULL)
        break;
      
      if (current->left == elem)
      {
        ++current->number;
        if (current->right != NULL) 
          push(&stack, current->right);
      }
      else // current->right == elem
      {
        
      }


      else
      {
        if (elem == parent->left)
        {
          parent->number
        }
      }
    }
    */

    return root;
  }
}
