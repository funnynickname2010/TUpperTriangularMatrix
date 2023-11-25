#pragma once
#include "TVector.h"
#define MyType long long int

class TMatrix
{
protected:

	TVector<TVector <MyType>> arr;
	unsigned int size_lines, size_columns;

public:

	explicit TMatrix(const unsigned int n);
	TMatrix(const unsigned int n, const unsigned int m);

	const unsigned int& GetSizeLines() const;
	const unsigned int& GetSizeColumns() const;
	
	TMatrix operator +(const TMatrix& matrix);
	TMatrix operator -(const TMatrix& matrix);
	TMatrix operator *(TMatrix& matrix);
	TMatrix operator *(const double scalar);
	TMatrix operator /(const double scalar);
	TMatrix& operator +=(const TMatrix& matrix);
	TMatrix& operator -=(const TMatrix& matrix);
	TVector<MyType>& operator [](int index);
	TVector<MyType>& operator [](int index) const;

	bool operator ==(const TMatrix& matrix) const;
	bool operator !=(const TMatrix& matrix) const;

	friend std::ostream& operator <<(std::ostream& os, const TMatrix& matrix);
	friend std::istream& operator >>(std::istream& os, TMatrix& matrix);
};

