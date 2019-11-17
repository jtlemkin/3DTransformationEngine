//
// Created by James Lemkin on 11/3/19.
//

#include <iostream>
#include "Matrix4x4.h"

Matrix4x4::Matrix4x4() {
  for(int i = 0; i < 4; i++) {
    for(int j = 0; j < 4; j++) {
      m[i][j] = 0;
    }
  }
}

float &Matrix4x4::at(int i, int j) {
  return m[i][j];
}

Vertex Matrix4x4::mult(Vertex v) {
  Vertex vp(0,0,0);

  for(int row = 0; row < 4; row++) {
    for(int col = 0; col < 4; col++) {
      vp.pos[row] += at(col, row) * v.pos[col];
    }
  }

  return vp;
}

Matrix4x4 Matrix4x4::mult(Matrix4x4 m2) {
  Matrix4x4 m3;

  for(int row = 0; row < 4; row++) {
    for(int col = 0; col < 4; col++) {
      for(int k = 0; k < 4; k++) {
        m3.at(row, col) += this->at(row, k) * m2.at(k, col);
      }
    }
  }

  return m3;
}

Matrix4x4 Matrix4x4::transpose() {
  Matrix4x4 mT;

  for(int row = 0; row < 4; row++) {
    for(int col = 0; col < 4; col++) {
      mT.at(col, row) = this->at(row, col);
    }
  }

  return mT;
}

void Matrix4x4::display() {
  for(int row = 0; row < 4; row++) {
    for(int col = 0; col < 4; col++) {
      printf("%.3f ", this->at(col, row));
    }
    std::cout << "\n";
  }
  std::cout << "\n";
}
