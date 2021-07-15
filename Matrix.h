#ifndef MATRIX_H
#define MATRIX_H

#include <ostream>
#include <cstdlib>

typedef unsigned int uint;
using namespace std;

class Matrix {
  public:
    Matrix(uint rows, uint cols);
    Matrix(double** values, int w, int h);
    Matrix(const Matrix & m);
    ~Matrix();
    
    Matrix add(double s) const;
    Matrix add(const Matrix & m) const;
    
    Matrix subtract(double s) const;
    Matrix subtract(const Matrix & m) const;
    
    Matrix multiply(double s) const;
    Matrix multiply(const Matrix & m) const;
    
    Matrix divide(double s) const;
    Matrix t() const;
    
    const uint numRows() const;
    const uint numCols() const;

    double & at(uint row, uint col);              // get/set element at row,col
    const double & at (uint row, uint col) const; // get element at row,col (when using a const object)

  double & operator()(uint row, uint col);
  Matrix & operator=(const Matrix & param);

  Matrix operator-();

  friend Matrix operator+(const Matrix& left, double right);
  friend Matrix operator+(double left, const Matrix& right);
  friend Matrix operator+(const Matrix& left, const Matrix& right);

  friend Matrix operator-(const Matrix& left, double right);
  friend Matrix operator-(double left, const Matrix& right);
  friend Matrix operator-(const Matrix& left, const Matrix& right);

  friend Matrix operator*(const Matrix& left, double right);
  friend Matrix operator*(double left, const Matrix& right);
  friend Matrix operator*(const Matrix& left, const Matrix& right);

  friend Matrix operator/(const Matrix& left, double right);
  friend Matrix operator/(double left, const Matrix& right);

  friend ostream& operator<<(ostream& output, const Matrix& right);

  private:
    uint rows;
    uint cols;
    double ** values;
}; // Matrix
#endif
