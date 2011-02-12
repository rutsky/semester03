/* Lab #6
 * Bob Rutsky, 2057/2
 * 12.12.2007
 */

#include <string>
#include <cassert>
#include <stack>
#include <algorithm>
#include <list>
#include <cmath>
#include <iomanip>
#include <sstream>

#include "tree.h"

// hack
#undef min
#undef max

namespace std
{
  template< class T >
    T min( T a, T b ) { return a < b ? a : b; }
  template< class T >
    T max( T a, T b ) { return a > b ? a : b; }
}


// end of hack

// TreeNode class implementation

TreeNode::TreeNode()
  : left  ( 0 )
  , right ( 0 )
  , number( -1 )
{}

TreeNode::TreeNode( char const *newKey, char const *newValue )
  : key   ( newKey ) 
  , value ( newValue )
  , left  ( 0 )
  , right ( 0 )
  , number( -1 )
{}

TreeNode::TreeNode( char const *newKey, char const *newValue, TreeNode *newRight, TreeNode *newLeft )
  : key   ( newKey ) 
  , value ( newValue )
  , left  ( newLeft )
  , right ( newRight )
  , number( -1 )
{}

TreeNode::TreeNode( char const *newKey, char const *newValue, TreeNode *newRight, TreeNode *newLeft, size_t newNumber )
  : key   ( newKey ) 
  , value ( newValue )
  , left  ( newLeft )
  , right ( newRight )
  , number( newNumber )
{}

// Tree class implementation

Tree::Tree()
  : root( 0 )
{}

Tree::Tree( TreeNode * newRoot )
  : root( newRoot )
{}

Tree::~Tree()
{
  removeSubTree(root);
}

// Functions implementations

TreeNode * findNode( Tree const &tree, char const *key, TreeNode **parent )
{
  if (parent != 0)
    *parent = 0;

  TreeNode *node = tree.root, *p = 0;
  int cmp;
  while (node != 0 && (cmp = strcmp(node->key.c_str(), key)) != 0)
  {
    p = node;
    if (cmp > 0)
      node = node->left;
    else
      node = node->right;
  }

  if (parent != 0)
    *parent = p;

  if (!cmp)
    return node;
  else
    return 0;
}

struct renumerateFunc
{
  renumerateFunc()
    : number_( 0 )
  {}

  bool operator () ( TreeNode *node )
  {
    node->number = number_++;
    return false;
  }

private:
  size_t number_;
};

bool addNode( Tree &tree, char const *key, char const *value )
{
  TreeNode *node = new TreeNode(key, value);

  TreeNode *parent, *elem;
  elem = findNode(tree, key, &parent);
  if (elem != 0)
    return false;

  if (parent == 0)
  {
    node->number = 0;
    tree.root = node;
    return true;
  }

  if (strcmp(parent->key.c_str(), key) > 0)
  {
    assert(parent->left == 0);
    parent->left = node;
  }
  else
  {
    assert(parent->right == 0);
    parent->right = node;
  }

  infixTraverse(tree.root, renumerateFunc());

  return true;
}

struct printAsListFunc
{
  printAsListFunc( std::ostream &os )
    : os_( os )
  {}

  bool operator () ( TreeNode *node )
  {
    os_ << "#" << node->number << ": " << renderNode(node) << std::endl;
    return false;
  }

private:
  std::ostream &os_;
};

void printTreeAsList( std::ostream &os, Tree const &tree )
{
  infixTraverse(tree.root, printAsListFunc(os));
}

TreeNode *getMaxSubElem( TreeNode *node, TreeNode **parent = 0 )
{
  TreeNode *p = 0;
  while (node->right != 0)
  {
    p = node;
    node = node->right;
  }

  if (parent != 0)
    *parent = p;
  return node;
}

bool removeNode( Tree &tree, char const *key )
{
  TreeNode *parent, *node;
  node = findNode(tree, key, &parent);
  if (node == 0)
    return false;

  // TODO
  if (node->left != 0)
  {
    if (node->left->right == 0)
    {
      if (parent != 0)
      {
        if (parent->left == node)
          parent->left = node->left;
        else
          parent->right = node->left;
      }
      else
        tree.root = node->left;
      node->left->right = node->right;
    }
    else
    {
      TreeNode *max, *maxParent;
      max = getMaxSubElem(node->left, &maxParent);
      assert(maxParent != 0);
      maxParent->right = max->left;
      max->left  = node->left;
      max->right = node->right;

      if (parent != 0)
      {
        if (parent->left == node)
          parent->left  = max;
        else
          parent->right = max;
      }
      else
        tree.root = max;
    }
  }
  else
  {
    if (parent == 0)
    {
      assert(tree.root == node);
      tree.root = node->right;
    }
    else
    {
      if (parent->left == node)
        parent->left = node->right;
      else
        parent->right = node->right;
    }
  }

  delete node;

  infixTraverse(tree.root, renumerateFunc());

  return true;
}

struct removeSubTreeFunc
{
  bool operator () ( TreeNode *node )
  {
    delete node;
    return false;
  }
};

void removeSubTree( TreeNode *node )
{
  postfixTraverse(node, removeSubTreeFunc());
}

bool removeSubTree( Tree &tree, char const *key )
{
  TreeNode *parent, *node;
  node = findNode(tree, key, &parent);
  if (node == 0)
    return false;

  if (parent == 0)
    tree.root = 0;
  else
  {
    if (parent->left == node)
      parent->left = 0;
    else
      parent->right = 0;
  }

  removeSubTree(node);

  return true;
}

struct getLongestNodeLengthFunc
{
  getLongestNodeLengthFunc()
    : length_( 0 )
  {}  

  bool operator () ( TreeNode *node )
  {
    std::string str = renderNode(node);
    if (str.size() > length_)
      length_ = str.size();
    return false;
  }

  size_t length()
  {
    return length_;
  }

private:
  size_t length_;
};

struct countNodesFunc
{
  countNodesFunc()
    : nodes_( 0 )
  {}  

  bool operator () ( TreeNode *node )
  {
    ++nodes_;
    return false;
  }

  size_t nodes()
  {
    return nodes_;
  }

private:
  size_t nodes_;
};

size_t subtreeDepth( TreeNode *node, size_t depth = 0 )
{
  if (node == 0)
    return depth;

  return std::max(subtreeDepth(node->left), subtreeDepth(node->right)) + 1;
}

void printTreeAsTree( std::ostream &os, Tree const &tree, size_t elemWidth )
{
  if (elemWidth == -1)
  {
    getLongestNodeLengthFunc func;
    infixTraverse(tree.root, func);
    elemWidth = func.length() + 1;
  }

  size_t depth = subtreeDepth(tree.root);

  typedef std::list<TreeNode *> nodes_list;
  nodes_list nodes;
  nodes.push_back(tree.root);
  size_t nNodes(tree.root != 0 ? 1 : 0);

  size_t level(0);
  while (nNodes > 0)
  {
    //size_t nSpaces = (::pow(2, depth - 1) - ::pow(2, level)) * elemWidth / 2;
    size_t nSpaces = (::pow(2, depth - 1 - level) - 1) * elemWidth / 2;
    for (size_t i = 0; i < nSpaces; ++i)
      os << ' ';

    for (nodes_list::const_iterator cit = nodes.begin(); cit != nodes.end(); ++cit)
    {
      if (*cit != 0)
        os << std::setw(elemWidth) << renderNode(*cit);
      else
      {
        for (size_t j = 0; j < elemWidth; ++j)
          os << ' ';
      }

      for (size_t i = 0; i < ::pow(2, depth - 1 - level) - 1; ++i)
        for (size_t j = 0; j < elemWidth; ++j)
          os << ' ';
    }

    for (nodes_list::iterator it = nodes.begin(); it != nodes.end();)
    {
      TreeNode *node = *it;
      it = nodes.erase(it);
      if (node != 0)
      {
        --nNodes;

        it = nodes.insert(it, node->right);
        it = nodes.insert(it, node->left);

        if (node->left != 0)
          ++nNodes;
        if (node->right != 0)
          ++nNodes;
      }
      else
      {
        it = nodes.insert(it, 0);
        it = nodes.insert(it, 0);
      }
      ++it;
      ++it;
    }

    ++level;

    os << std::endl;
  }
}

std::string renderNode( TreeNode *node )
{
  std::ostringstream ostr;
  //ostr << "'" << node->key << "'=>'" << node->value << "'";
  ostr << node->key << "," << node->value;
  return ostr.str();
}
