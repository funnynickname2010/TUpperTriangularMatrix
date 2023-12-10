#pragma once
#include "TMatrix.h"

class TUpperTriangularMatrix : public TMatrix
{
public:

	bool IsInTriangle(int i, int j) const;
	explicit TUpperTriangularMatrix(const unsigned int n);

	const MyType Get(int i, int j) const;
	MyType& Get(int i, int j);

	TUpperTriangularMatrix operator *(const double scalar) const;
	TMatrix operator *(const TMatrix& matrix);
	TUpperTriangularMatrix operator *(const TUpperTriangularMatrix& matrix);
	friend TMatrix operator*(const TMatrix& matrix, const TUpperTriangularMatrix& UTmatrix);

	friend std::ostream& operator <<(std::ostream& os, const TUpperTriangularMatrix& matrix);
	friend std::istream& operator >>(std::istream& os, TUpperTriangularMatrix& matrix);
};

