/* Lab #6
 * Bob Rutsky, 2057/2
 * 12.12.2007
 */

/* Task 06
 * 8. Используя дерево двоичного поиска с дополнительной информацией 
 * реализовать структуру данных с операциями словаря с приоритетами 
 * + порядковый номер заданного элемента. Узлы дерева не должны содержать 
 * указатели на предков. Рекурсия должна быть раскрыта. 
 */

/* Task 05
 * 8. Написать процедуру удаления поддерева с корнем, содержащим заданный ключ.
 */

#include <iostream>
#include <sstream>
#include <limits>
#include <map>
#include <cstdlib>
#include <cassert>

#include "tree.h"

// #define DO_TEST

#ifdef DO_TEST
void doTest()
{
  Tree tree;
  typedef std::map<std::string, std::string> map_type;
  map_type map;
  size_t i;

  // Adding random elements
  for (i = 0; i < 1000; ++i)
  {
    std::ostringstream ostr;
    ostr << ::rand() % 100;

    bool treeResult = addNode(tree, ostr.str().c_str(), "bob");
    std::pair<map_type::iterator, bool> mapResult = map.insert(std::make_pair(ostr.str(), std::string("bob")));
    assert(!(treeResult ^ mapResult.second));
  }

  // Removing random elements
  for (i = 0; i < 50; ++i)
  {
    std::ostringstream ostr;
    ostr << ::rand() % 100;

    bool treeResult = removeNode(tree, ostr.str().c_str());
    map_type::iterator it = map.find(ostr.str());
    assert(!(treeResult ^ (it != map.end())));
    if (it != map.end())
      map.erase(it);
  }

  // Adding random elements
  for (i = 0; i < 1000; ++i)
  {
    std::ostringstream ostr;
    ostr << ::rand() % 100;

    bool treeResult = addNode(tree, ostr.str().c_str(), "bob");
    std::pair<map_type::iterator, bool> mapResult = map.insert(std::make_pair(ostr.str(), std::string("bob")));
    assert(!(treeResult ^ mapResult.second));
  }

  // Removing random elements
  for (i = 0; i < 1000; ++i)
  {
    std::ostringstream ostr;
    ostr << ::rand() % 100;

    bool treeResult = removeNode(tree, ostr.str().c_str());
    map_type::iterator it = map.find(ostr.str());
    assert(!(treeResult ^ (it != map.end())));
    if (it != map.end())
      map.erase(it);
  }

  // Adding random elements
  for (i = 0; i < 1000; ++i)
  {
    std::ostringstream ostr;
    ostr << ::rand() % 100;

    bool treeResult = addNode(tree, ostr.str().c_str(), "bob");
    std::pair<map_type::iterator, bool> mapResult = map.insert(std::make_pair(ostr.str(), std::string("bob")));
    assert(!(treeResult ^ mapResult.second));
  }

  // Removing random elements
  for (i = 0; i < 1000; ++i)
  {
    std::ostringstream ostr;
    ostr << ::rand() % 100;

    bool treeResult = removeNode(tree, ostr.str().c_str());
    map_type::iterator it = map.find(ostr.str());
    assert(!(treeResult ^ (it != map.end())));
    if (it != map.end())
      map.erase(it);
  }
}
#endif // DO_TEST

int main( void )
{
  Tree tree;

#ifdef DO_TEST
  doTest();
#endif // DO_TEST

  bool done = false;
  while (!done)
  {
    std::cout << "Tree:" << std::endl;
    if (tree.root == 0)
      std::cout << "empty" << std::endl;
    else
      printTreeAsTree(std::cout, tree);
    std::cout << std::endl;

    std::cout <<
      "Menu:\n" << 
      " 0 - exit\n" <<
      " 1 - add pair\n" <<
      " 2 - remove by key\n" <<
      " 3 - find by key\n" <<
      " 4 - remove subtree\n" <<
      " 5 - add random element\n" <<
      "Enter your choice:\n";

    int choice(-1);
    std::cin >> choice;
    std::cin.clear();
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

    if (choice == 0)
    {
      // Exit
      std::cout << "Bye!" << std::endl;
      done = true;
    }
    else if (choice == 1)
    {
      // Add pair
      std::cout << "Enter key and value delimited by space:" << std::endl;
      std::string key, value;
      std::cin >> key >> value;
      std::cin.clear();
      std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

      if (!addNode(tree, key.c_str(), value.c_str()))
        std::cout << "Element with key '" << key << "' already exists!" << std::endl;
      else
        std::cout << "Pair '" << key << "' => '" << value << "' successfully added." << std::endl;
    }
    else if (choice == 2)
    {
      // Remove by key
      std::cout << "Enter key of removing element:" << std::endl;
      std::string key;
      std::cin >> key;
      std::cin.clear();
      std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

      if (!removeNode(tree, key.c_str()))
        std::cout << "There is no element with '" << key << "' key!" << std::endl;
      else
        std::cout << "Successfully removed." << std::endl;
    }
    else if (choice == 3)
    {
      // Find by key
      std::cout << "Enter key:" << std::endl;
      std::string key;
      std::cin >> key;
      std::cin.clear();
      std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

      TreeNode *node = findNode(tree, key.c_str());
      if (node == 0)
        std::cout << "Element with key '" << key << "' not found." << std::endl;
      else
        std::cout << "Found element: " << renderNode(node) << "."  << std::endl;
    }
    else if (choice == 4)
    {
      // Remove subtree
      std::cout << "Enter key of removing subtree root:" << std::endl;
      std::string key;
      std::cin >> key;
      std::cin.clear();
      std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

      if (!removeSubTree(tree, key.c_str()))
        std::cout << "There is no element with '" << key << "' key!" << std::endl;
      else
        std::cout << "Successfully removed." << std::endl;
    }
    else if (choice == 5)
    {
      std::ostringstream key, value;
      key << char('a' + ::rand() % 26);
      value << ::rand() % 10;
      if (!addNode(tree, key.str().c_str(), value.str().c_str()))
        std::cout << "Element with key '" << key.str() << "' already exists!" << std::endl;
      else
        std::cout << "Pair '" << key.str() << "' => '" << value.str() << "' successfully added." << std::endl;
    }
    else
      std::cout << "Incorrect choice.\n";

    std::cout << std::endl;
  }

#ifdef WIN32
  getchar();
#endif

  return 0;
}
