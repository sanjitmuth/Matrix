#include <ostream>
#include "Matrix.h"
typedef unsigned int uint;

using namespace std;

Matrix::Matrix(uint rows, uint cols): rows(rows), cols(cols), values(new double * [rows]) {
  for(uint i = 0; i < rows; i++) {
    this->values[i] = new double[cols];
  }
} // constructor (all indices of 'values' initialized to 0)

Matrix::Matrix(double** values, int w, int h) {
  for(int i = 0; i < w; i++) {
    for(int j = 0; j < h; i++) {
      this->values[i][j] = values[i][j];
    }
  }
} //constructor (using copy of passed array)

Matrix::Matrix(const Matrix & m): Matrix::Matrix(m.numRows(), m.numCols()) {
  for(uint i = 0; i < rows; i++) {
    for(uint j = 0; j < cols; j++) {
      values[i][j] = m.at(i, j);
    }
  }
} //copy constructor

Matrix::~Matrix() {
  for(uint i = 0; i < rows; i++) {
    delete[] values[i];
  }
  delete[] values;
} //destructor

// ----- addition ------ //

Matrix Matrix::add(double s) const {
  Matrix temp(this->rows, this->cols);
  for(uint i = 0; i < this->rows; i++) {
    for(uint j = 0; j < this->cols; j++) {
      temp.at(i,j) = this->at(i,j) + s;
    }
  }
  return temp;
} //adding a scalar to matrix

Matrix Matrix::add(const Matrix & m) const {
  if(this->rows == m.numRows() && this->cols == m.numCols()) {
    Matrix temp(this->rows, this->cols);
    for(uint i = 0; i < this->rows; i++) {
      for(uint j = 0; j < this->cols; j++) {
	temp.at(i, j) = this->at(i,j) + m.at(i, j);
      }
    }
    return temp;
  } else {
    Matrix m1(*this);
    return m1;
  }
} //adding matrix to matrix

// --------- subtraction -------- //

Matrix Matrix::subtract(double s) const {
  Matrix temp(this->rows, this->cols);
  for(uint i = 0; i < this->rows; i++) {
    for(uint j = 0; j < this->cols; j++) {
      temp.at(i,j) = this->at(i,j) - s;
    }
  }
  return temp;
} //subtract scalar from this matrix

Matrix Matrix::subtract(const Matrix & m) const {
    Matrix temp(this->rows, this->cols);
    for(uint i = 0; i < this->rows; i++) {
      for(uint j = 0; j < this->cols; j++) {
	temp.at(i,j) = this->at(i,j) - m.at(i,j);
      }
    }
    return temp;
} //subtract another matrix from another matrix

// --------- multiplication ----------//

Matrix Matrix::multiply(double s) const {
  Matrix temp(this->rows, this->cols);
  for(uint i = 0; i < this->rows; i++) {
    for(uint j = 0; j < this->cols; j++) {
      temp.at(i,j) = this->at(i,j) * s;
    }
  }
  return temp;
} //multiply this matrix by a scalar

Matrix Matrix::multiply(const Matrix & m) const {
    Matrix temp(this->rows, m.numCols());
    double sum;
    for(uint i = 0; i < temp.numRows(); i++) {
      for(uint j = 0; j < temp.numCols(); j++) {
	sum = 0;
	for(uint k = 0; k < this->cols; k++) {
	  sum += this->at(i,k) * m.at(k,j);
	}
	temp.at(i,j) = sum;
      }
    }
    return temp;
} //multiply this matrix by another matrix

// ---------- division ---------//

Matrix Matrix::divide(double s) const {
    Matrix temp(this->rows, this->cols);
    for(uint i = 0; i < this->rows; i++) {
      for(uint j = 0; j < this->cols; j++) {
	temp.at(i,j) = this->at(i,j) / s;
      }
    }
    return temp;
} // divide this matrix by a scalar

// ------- transposition --------- //
Matrix Matrix::t() const {
  Matrix temp(this->cols, this->rows);
  for(uint i = 0; i < temp.numRows(); i++) {
    for(uint j = 0; j < temp.numCols(); j++) {
      temp.at(i,j) = this->at(j,i);
    }
  }
  return temp;
} //tramsposition of this matrix

// --------- numRows/Cols ---------- //

const uint Matrix::numRows() const {
  return this->rows;
} //returns the number of rows

const uint Matrix::numCols() const {
  return this->cols;
} //returns the number of columns

// ------- at() --------- //

double & Matrix::at(uint row, uint col) {
  return this->values[row][col];
} //get/set element at row/col

const double & Matrix::at(uint row, uint col) const {
  return this->values[row][col];
} // get elem at row/col when using const object

//_____________ member operator overloads _____________ //

// ---- ()

double& Matrix::operator()(uint row, uint col) {
  return this->at(row,col);
} 

// ---- =

Matrix& Matrix::operator=(const Matrix& param) {
  for(uint i = 0; i < rows; i++) {
    delete[] values[i];
  }
  delete[] values;  

  this->rows = param.numRows();
  this->cols = param.numCols();

  this->values = new double * [this->rows];
  for(uint i = 0; i < this->rows; i++) {
    this->values[i] = new double [this->cols];
    for(uint j = 0; j < this->cols; j++) {
      this->at(i,j) = param.at(i,j);
    }
  }
  return *this;
} 

// ---- unary -

Matrix Matrix::operator-() {
  Matrix temp(*this);
  return temp.multiply(-1);
} 

//_____________ non-member operator overloads _____________ //

// ---- +

Matrix operator+(const Matrix& left, double right) {
  return left.add(right);
} 

Matrix operator+(double left, const Matrix& right) {
  return right.add(left);
} 

Matrix operator+(const Matrix& left, const Matrix& right) {
  return left.add(right);
} 

// ---- -

Matrix operator-(const Matrix& left, double right) {
  return left.subtract(right);
} 

Matrix operator-(double left, const Matrix& right) {
  return right.multiply(-1) + left;
} 

Matrix operator-(const Matrix& left, const Matrix& right) {
  return left.subtract(right);
} 

// ---- *

Matrix operator*(const Matrix& left, double right) {
  return left.multiply(right);
} 

Matrix operator*(double left, const Matrix& right) {
  return right.multiply(left);
} 

Matrix operator*(const Matrix& left, const Matrix& right) {
  return left.multiply(right);
} 

// ---- /

Matrix operator/(const Matrix& left, double right) {
  return left.divide(right);
} 

Matrix operator/(double left, const Matrix& right) {
  Matrix temp(right.numRows(), right.numCols());
  bool foundZero = false;
  for(uint i = 0; i < temp.numRows(); i++) {
    for(uint j = 0; j < temp.numCols(); j++) {
      if(right.at(i,j) == 0) {
	foundZero = true;
	break;
      } else {
	temp.at(i,j) = left / right.at(i,j);
      }
    }
    if(foundZero) { break; }
  }
  if(foundZero) {
    Matrix same(right);
    return same;
  } else {
    return temp;
  }
} 

// ---- <<

ostream& operator<<(ostream& output, const Matrix& right) {
  for(uint i = 0; i < right.numRows(); i++) {
    output << "[ ";
    for(uint j = 0; j < right.numCols(); j++) {
      output << right.at(i,j);
      if(j < right.numCols()-1) { output << ", "; }
    }
    output << " ]" << "\n";
  }
  return output;
} 














