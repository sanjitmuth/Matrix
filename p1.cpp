#include "Matrix.h"
#include <iostream>
using namespace std;

// -------- Main --------- //

int main() {
  Matrix m1(2,2);
  m1.at(0, 0) = 1;
  m1.at(0, 1) = 2;
  m1.at(1, 0) = 3;
  m1.at(1, 1) = 4;

  cout << "[" << m1.at(0,0) << "]" << endl;
  cout << "[" << m1.at(0,1) << "]" << endl;
  cout << "[" << m1.at(1,0) << "]" << endl;
  cout << "[" << m1.at(1,1) << "]" << endl;
}
