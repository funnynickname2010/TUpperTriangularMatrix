#pragma once
#include "TMatrix.h"

class TUpperTriangularMatrix : public TMatrix
{
public:

	bool IsInTriangle(int i, int j) const;
	explicit TUpperTriangularMatrix(int n);

	MyType& Get(int i, int j) const;
	MyType& Get(int i, int j);

	friend std::ostream& operator <<(std::ostream& os, const TUpperTriangularMatrix& matrix);
	friend std::istream& operator >>(std::istream& os, TUpperTriangularMatrix& matrix);
};

