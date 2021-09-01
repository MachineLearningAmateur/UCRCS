#include "Tree.h"
#include <iostream>

using namespace std;

#define A "Aliens"
#define B "Clerks"
#define C "Die Hard"
#define D "Enemy of the State"
#define E "Gladiator"
#define F "Happy Gilmore"
#define G "Kill Bill Volume 1"
#define H "Kill Bill Volume 2"
#define I "Matrix"
#define J "Meet the Parents"
#define K "Pirates of the Caribbean"
#define L "Silence of the Lambs"
#define M "Spaceballs"
#define N "Star Wars"
#define O "Terminator"
#define P "The Lord of the Rings"
#define Q "The Usual Suspects"
#define R "Top Gun"

void printOrders(Tree *tree) {
  cout << "Preorder = ";
  tree->preOrder( );
  cout << "Inorder = ";
  tree->inOrder( );
  cout << "Postorder = ";
  tree->postOrder( );
}

int main( ) {

  Tree tree;


  //------------------------------------------------------------------------
  // Test simple inserting from page 1
  cout << "Test 1" << endl;
  tree.insert(C);
  printOrders(&tree);
  cout << "----------------------------------------------------" << endl;
  cout << "Test 2" << endl;
  tree.insert(O);
  printOrders(&tree);
  cout << "----------------------------------------------------" << endl;
  cout << "Test 3" << endl;
  tree.insert(G);
  printOrders(&tree);
  cout << "----------------------------------------------------" << endl;
  cout << "Test 4" << endl;
  tree.insert(K);
  tree.insert(P);
  printOrders(&tree);
  cout << "----------------------------------------------------" << endl;
  cout << "Test 5" << endl;
  tree.insert(N);
  tree.insert(E);
  printOrders(&tree);
  cout << "----------------------------------------------------" << endl;
  cout << "Test 6" << endl;
  tree.insert(I);
  printOrders(&tree);
  cout << "----------------------------------------------------" << endl;
  cout << "Test 7" << endl;
  if (!tree.search(C) 
      || !tree.search(O) 
      || !tree.search(G) 
      || !tree.search(K) 
      || !tree.search(P) 
      || !tree.search(N)
      || !tree.search(E) 
      || !tree.search(I) 
      || tree.search("z")) {
    cout << "Seach phase failed" << endl;
  } else {
    cout << "Search phase passed" << endl;
  }
  cout << "----------------------------------------------------" << endl;

  //------------------------------------------------------------------------
  // Test simple inserting and removing from pages 1b and 2b
  Tree tree2;
  cout << "Test 8" << endl;
  tree2.remove(C);
  printOrders(&tree2);
  tree2.insert(C);
  tree2.remove(C);
  printOrders(&tree2);
  tree2.insert(C);
  tree2.insert(O);
  tree2.remove(O);
  printOrders(&tree2);
  cout << "----------------------------------------------------" << endl;
  cout << "Test 9" << endl;
  tree2.insert(O);
  tree2.insert(G);
  tree2.remove(G);
  printOrders(&tree2);
  cout << "----------------------------------------------------" << endl;
  cout << "Test 10" << endl;
  tree2.insert(G);
  tree2.remove(C);
  printOrders(&tree2);
  cout << "----------------------------------------------------" << endl;

  return 0;
}
