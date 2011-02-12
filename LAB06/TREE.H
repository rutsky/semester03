/* Lab #6
 * Bob Rutsky, 2057/2
 * 12.12.2007
 */

#ifndef TREE_H
#define TREE_H

#include <string>
#include <ostream>

struct TreeNode
{
public:
  TreeNode();

  TreeNode( char const *newKey, char const *newValue );

  TreeNode( char const *newKey, char const *newValue, TreeNode *newRight, TreeNode *newLeft );

  TreeNode( char const *newKey, char const *newValue, TreeNode *newRight, TreeNode *newLeft, size_t newNumber );

public:
  std::string key, value; 
  size_t number;
  
  TreeNode *left, *right;
};

struct Tree
{
public:
  Tree();

  Tree( TreeNode * newRoot );

  ~Tree();

public:
  TreeNode *root;
};

TreeNode * findNode( Tree const &tree, char const *key, TreeNode **parent = 0 );

bool addNode( Tree &tree, char const *key, char const *value );

bool removeNode( Tree &tree, char const *key );

void removeSubTree( TreeNode *node );

bool removeSubTree( Tree &tree, char const *key );

// Left subtree, node, right subtree
template< class FuncType >
bool infixTraverse( TreeNode *root, FuncType &func );

// Node, left subtree, right subtree
template< class FuncType >
bool prefixTraverse( TreeNode *root, FuncType &func );

// Left subtree, right subtree, node
template< class FuncType >
bool postfixTraverse( TreeNode *root, FuncType &func );

std::string renderNode( TreeNode *node );

void printTreeAsList( std::ostream &os, Tree const &tree );
void printTreeAsTree( std::ostream &os, Tree const &tree, size_t elemWidth = -1 );

// Templates implementations

namespace
{
  struct funcState
  {
    funcState()
      : node ( 0 )
      , nCall( 0 )
    {}

    funcState( TreeNode *newNode )
      : node ( newNode )
      , nCall( 0 )
    {}

    TreeNode *node;  
    size_t    nCall;
  };
} // End of anonymous namespace

// Left subtree, node, right subtree
template< class FuncType >
bool infixTraverse( TreeNode *root, FuncType &func )
{
  std::stack<funcState> stack;

  stack.push(funcState(root));

  while (!stack.empty())
  {
    funcState &state = stack.top();

    if (state.node == 0 || state.nCall >= 2)
      stack.pop();
    else
    {
      if (state.nCall == 0)
        stack.push(funcState(state.node->left));
      else if (state.nCall == 1)
      {
        if (func(state.node))
          return true;
        stack.push(funcState(state.node->right));
      }
      ++state.nCall;
    }
  }

  return false;
}

// Node, left subtree, right subtree
template< class FuncType >
bool prefixTraverse( TreeNode *root, FuncType &func )
{
  std::stack<funcState> stack;

  stack.push(funcState(root));

  while (!stack.empty())
  {
    funcState &state = stack.top();

    if (state.node == 0 || state.nCall >= 2)
      stack.pop();
    else
    {
      if (state.nCall == 0)
      {
        if (func(state.node))
          return true;
        stack.push(funcState(state.node->left));
      }
      else if (state.nCall == 1)
        stack.push(funcState(state.node->right));
      ++state.nCall;
    }
  }

  return false;
}

// Left subtree, right subtree, node
template< class FuncType >
bool postfixTraverse( TreeNode *root, FuncType &func )
{
  std::stack<funcState> stack;

  stack.push(funcState(root));

  while (!stack.empty())
  {
    funcState &state = stack.top();

    if (state.node == 0 || state.nCall >= 3)
      stack.pop();
    else 
    {
      if (state.nCall == 0)
        stack.push(funcState(state.node->left));
      else if (state.nCall == 1)
        stack.push(funcState(state.node->right));
      else if (state.nCall == 2)
      {
        if (func(state.node))
          return true;
      }
      ++state.nCall;
    }
  }

  return false;
}

#endif // TREE_H
