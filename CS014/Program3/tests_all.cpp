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
  cout << "Test 11" << endl;
  tree2.insert(C);
  tree2.remove(O);
  printOrders(&tree2);
  cout << "----------------------------------------------------" << endl;
  cout << "Test 12" << endl;
  tree2.insert(O);
  tree2.insert(K);
  tree2.remove(K);
  printOrders(&tree2);
  cout << "----------------------------------------------------" << endl;
  cout << "Test 13" << endl;
  tree2.insert(K);
  tree2.insert(P);
  tree2.remove(P);
  printOrders(&tree2);
  cout << "----------------------------------------------------" << endl;
  cout << "Test 14" << endl;
  tree2.insert(H);
  tree2.remove(H);
  printOrders(&tree2);
  cout << "----------------------------------------------------" << endl;
  cout << "Test 15" << endl;
  tree2.insert(H);
  tree2.remove(C);
  printOrders(&tree2);
  cout << "----------------------------------------------------" << endl;

  //------------------------------------------------------------------------
  // Test more difficult inserting
  cout << "Test 16" << endl;
  Tree tree3;
  tree3.insert(C);
  tree3.insert(O);
  tree3.insert(G);
  tree3.insert(K);
  tree3.insert(P);
  tree3.insert(N);
  tree3.insert(E);
  tree3.insert(I);
  tree3.insert(B);
  tree3.insert(Q);
  printOrders(&tree3);
  cout << "----------------------------------------------------" << endl;
  cout << "Test 17" << endl;
  tree3.insert(L);
  tree3.insert(D);
  tree3.insert(A);
  printOrders(&tree3);
  cout << "----------------------------------------------------" << endl;
  cout << "Test 18" << endl;
  tree3.insert(M);
  printOrders(&tree3);
  cout << "----------------------------------------------------" << endl;
  cout << "Test 19" << endl;
  tree3.insert(F);
  printOrders(&tree3);
  cout << "----------------------------------------------------" << endl;
  cout << "Test 20" << endl;
  tree3.insert(R);
  printOrders(&tree3);
  cout << "----------------------------------------------------" << endl;
  cout << "Test 21" << endl;
  tree3.insert(J);
  tree3.insert(H);
  printOrders(&tree3);
  cout << "----------------------------------------------------" << endl;

  //------------------------------------------------------------------------
  // Test more difficult removing from page 1c
  cout << "Test 22" << endl;
  Tree tree4;
  tree4.insert(A);
  tree4.insert(D);
  tree4.insert(E);
  tree4.insert(H);
  tree4.insert(I);
  tree4.insert(F);
  tree4.insert(J);
  tree4.remove(A);
  printOrders(&tree4);
  Tree tree5;
  tree5.insert(A);
  tree5.insert(D);
  tree5.insert(E);
  tree5.insert(H);
  tree5.insert(I);
  tree5.insert(J);
  tree5.remove(A);
  printOrders(&tree5);
  Tree tree6;
  tree6.insert(A);
  tree6.insert(D);
  tree6.insert(E);
  tree6.insert(H);
  tree6.insert(I);
  tree6.insert(J);
  tree6.remove(E );
  printOrders(&tree6);
  cout << "----------------------------------------------------" << endl;
  cout << "Test 23" << endl;
  Tree tree7;
  tree7.insert(A);
  tree7.insert(D);
  tree7.insert(E);
  tree7.insert(H);
  tree7.insert(I);
  tree7.insert(B);
  tree7.remove(E);
  printOrders(&tree7);
  cout << "----------------------------------------------------" << endl;
  cout << "Test 24" << endl;
  Tree tree8;
  tree8.insert(A);
  tree8.insert(D);
  tree8.insert(E);
  tree8.insert(H);
  tree8.insert(I);
  tree8.insert(B);
  tree8.remove(I);
  printOrders(&tree8);
  cout << "----------------------------------------------------" << endl;
  cout << "Test 25" << endl;
  Tree tree9;
  tree9.insert(A);
  tree9.insert(D);
  tree9.insert(E);
  tree9.insert(H);
  tree9.insert(I);
  tree9.insert(B);
  tree9.insert(F);
  tree9.remove(I);
  printOrders(&tree9);
  cout << "----------------------------------------------------" << endl;

  return 0;
}
