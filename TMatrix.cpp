#include "TMatrix.h"

TMatrix::TMatrix(const unsigned int n = 1) : TVector<TVector<MyType>>(n)
{
	for (int i = 0; i < n; i++) 
	{ 
		val[i].SetSize(n);

		for (int j = 0; j < n; j++)
		{
			val[i][j] = 0;
		}
	}
}

TMatrix::TMatrix(const unsigned int n, const unsigned int m) : TVector<TVector<MyType>>(n)
{
	for (int i = 0; i < n; i++)
	{
		val[i].SetSize(m);

		for (int j = 0; j < m; j++)
		{
			val[i][j] = 0;
		}
	}
}

TMatrix::TMatrix(const TVector<TVector<MyType>>& vector) : TVector<TVector<MyType>>(vector.GetSize()) {}

const unsigned int& TMatrix::GetSizeLines() const
{
	return size;
}

const unsigned int& TMatrix::GetSizeColumns() const
{
	return val[0].GetSize();
}

TMatrix TMatrix::operator+(const TMatrix& matrix)
{
	return TVector<TVector<MyType>>::operator+(matrix);
}

TMatrix TMatrix::operator-(const TMatrix& matrix)
{
	return TVector<TVector<MyType>>::operator-(matrix);
}

TMatrix TMatrix::operator*(TMatrix& matrix)
{
	TMatrix result(size, matrix.val[0].GetSize());

	if (this->GetSizeColumns() != matrix.size)
	{
		throw std::exception("TMatrix operator*(const TMatrix& matrix) failure. Size mismatch");
	}

	try
	{
		for (int i = 0; i < result.GetSizeColumns(); i++)
		{
			for (int j = 0; j < result.size; j++)
			{
				for (int k = 0; k < this->GetSizeColumns(); k++)
				{
					result.val[i][j] += val[i][k] * matrix.val[k][j];
				}
			}
		}
	}
	catch (...)
	{
		throw std::exception("TMatrix operator*(const TMatrix& matrix) failure.");
	}

	return result;
}

TMatrix TMatrix::operator*(const double scalar)
{
	return TVector<TVector<MyType>>::operator*(scalar);
}

TMatrix TMatrix::operator/(const double scalar)
{
	return TVector<TVector<MyType>>::operator/(scalar);
}

TMatrix& TMatrix::operator+=(const TMatrix& matrix)
{
	TVector<TVector<MyType>>::operator+=(matrix);

	return *this;
}

TMatrix& TMatrix::operator-=(const TMatrix& matrix)
{
	TVector<TVector<MyType>>::operator-=(matrix);

	return *this;
}

TVector<MyType>& TMatrix::operator[](int index)
{
	return val[index];
}

TVector<MyType>& TMatrix::operator[](int index) const
{
	return val[index];
}

bool TMatrix::operator==(const TMatrix& matrix) const
{
	return TVector<TVector<MyType>>::operator==(matrix);
}

bool TMatrix::operator!=(const TMatrix& matrix) const
{
	return TVector<TVector<MyType>>::operator!=(matrix);
}

std::ostream& operator<<(std::ostream& os, const TMatrix& matrix)
{
	for (int i = 0; i < matrix.size; i++)
	{
		try
		{
			os << matrix.val[i] << std::endl;
		}
		catch (const std::exception& e)
		{
			std::cout << e.what();
			throw std::exception("TMatrix std::ostream& operator<< failure.");
		}
	}

	return os;
}

std::istream& operator>>(std::istream& os, TMatrix& matrix)
{
	try
	{
		for (int i = 0; i < matrix.size && os.good(); i++)
		{
			os >> matrix.val[i];
		}
	}
	catch (const std::exception& e)
	{
		std::cout << e.what();
		throw std::exception("TMatrix std::istream& operator>> failure.");
	}

	return os;
}
