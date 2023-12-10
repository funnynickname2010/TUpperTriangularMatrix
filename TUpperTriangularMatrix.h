#pragma once
#include "TMatrix.h"

class TUpperTriangularMatrix : public TMatrix
{
public:

	bool IsInTriangle(int i, int j) const;
	explicit TUpperTriangularMatrix(const unsigned int n);

	friend MyType& TVector<MyType>::operator [](const int index);

	const MyType operator()(const int i, const int j) const;
	MyType& operator()(const int i, const int j);

	TUpperTriangularMatrix operator *(const double scalar) const;
	TMatrix operator *(const TMatrix& matrix);
	TUpperTriangularMatrix operator *(const TUpperTriangularMatrix& matrix);
	friend TMatrix operator*(const TMatrix& matrix, const TUpperTriangularMatrix& UTmatrix);

	friend std::ostream& operator <<(std::ostream& os, const TUpperTriangularMatrix& matrix);
	friend std::istream& operator >>(std::istream& os, TUpperTriangularMatrix& matrix);
};

