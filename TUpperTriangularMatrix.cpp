#include "TUpperTriangularMatrix.h"
#include "TMatrix.cpp"

bool TUpperTriangularMatrix::IsInTriangle(int i, int j) const
{
	return (j >= i);
}

TUpperTriangularMatrix::TUpperTriangularMatrix(const unsigned int n) : TMatrix(n)
{
	for (int i = 1; i < this->size; i++)
	{
		val[i].SetSize(size - i);
	}
}

TUpperTriangularMatrix::TUpperTriangularMatrix(const TVector<TVector<MyType>>& vector) : TMatrix(vector.GetSize()) 
{
	for (int i = 0; i < this->GetSize(); i++)
	{
		for (int j = 0; j < this->GetSize(); j++)
		{
			if (IsInTriangle(i, j))
			{
				this->val[i][j - i] = vector[i][j - i];
			}
		}
	}
}

const MyType TUpperTriangularMatrix::operator()(const int i, const int j) const
{
	MyType result = 0;

	if (IsInTriangle(i, j))
	{
		result = val[i][j - i];
	}

	return result;
}

MyType& TUpperTriangularMatrix::operator()(const int i, const int j)
{
	if (!IsInTriangle(i, j))
	{
		throw std::exception("MyType& TUpperTriangularMatrix::operator()(const int i, const int j) failure: indices not in the triangle.");
	}
	else
	{
		return val[i][j - i];
	}
}

TUpperTriangularMatrix TUpperTriangularMatrix::operator+(const TUpperTriangularMatrix& matrix)
{
	TUpperTriangularMatrix result(TVector<TVector<MyType>>::operator+(matrix));
	return result;
}

TUpperTriangularMatrix TUpperTriangularMatrix::operator-(const TUpperTriangularMatrix& matrix)
{
	return TUpperTriangularMatrix(TVector<TVector<MyType>>::operator-(matrix));
}

TUpperTriangularMatrix TUpperTriangularMatrix::operator*(const double scalar) const
{
	TUpperTriangularMatrix result(*this);

	try
	{
		for (int i = 0; i < result.GetSizeLines(); i++)
		{
			for (int j = 0; j < result.GetSizeColumns(); j++)
			{
				result(i, j) *= scalar;
			}
		}
	}
	catch (...)
	{
		throw std::exception("TUpperTriangularMatrix::operator*(const double scalar) const failure.");
	}

	return result;
}

TMatrix TUpperTriangularMatrix::operator*(const TMatrix& matrix)
{
	unsigned int size_lines_2 = matrix.GetSizeLines();
	unsigned int size_columns_2 = matrix.GetSizeColumns();

	TMatrix result(size, size_columns_2);

	if (this->GetSizeColumns() != size_lines_2)
	{
		throw std::exception("TMatrix operator*(const TMatrix& matrix) failure. Size mismatch");
	}

	try
	{
		for (int i = 0; i < size_columns_2; i++)
		{
			for (int j = 0; j < size; j++)
			{
				for (int k = 0; k < this->GetSizeColumns(); k++)
				{
					result[i][j] += this->operator()(i, j) * matrix[k][j];
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

TUpperTriangularMatrix TUpperTriangularMatrix::operator*(const TUpperTriangularMatrix& matrix)
{
	TUpperTriangularMatrix result(size);

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
					result(i, j) += this->operator()(i, k) * matrix(k, j);
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

TUpperTriangularMatrix TUpperTriangularMatrix::operator*(const double scalar)
{
	return TUpperTriangularMatrix(TVector<TVector<MyType>>::operator*(scalar));
}

TUpperTriangularMatrix TUpperTriangularMatrix::operator/(const double scalar)
{
	return TUpperTriangularMatrix(TVector<TVector<MyType>>::operator/(scalar));
}

TMatrix operator*(const TMatrix& matrix, const TUpperTriangularMatrix& UTmatrix)
{
	unsigned int size_lines_1 = matrix.GetSizeLines();
	unsigned int size_columns_1 = matrix.GetSizeColumns();

	TMatrix result(size_lines_1, UTmatrix.GetSizeColumns());

	if (size_columns_1 != UTmatrix.size)
	{
		throw std::exception("TMatrix operator*(const TMatrix& matrix) failure. Size mismatch");
	}

	try
	{
		for (int i = 0; i < UTmatrix.GetSizeColumns(); i++)
		{
			for (int j = 0; j < size_lines_1; j++)
			{
				for (int k = 0; k < size_columns_1; k++)
				{
					result[i][j] += matrix[i][k] * UTmatrix(k, j);
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

std::ostream& operator<<(std::ostream& os, const TUpperTriangularMatrix& matrix)
{
	for (int i = 0; i < matrix.size; i++)
	{
		for (int j = 0; j < matrix.GetSizeColumns(); j++)
		{
			try
			{
				os << matrix(i, j) << " ";
			}
			catch (...)
			{
				throw std::exception("TMatrix std::ostream& operator<< failure.");
			}
		}
		os << std::endl;
	}

	return os;
}

std::istream& operator>>(std::istream& os, TUpperTriangularMatrix& matrix)
{
	try
	{
		for (int i = 0; i < matrix.size && os.good(); i++)
		{
			for (int j = 0; j < matrix.GetSizeColumns(); j++)
			{
				if (!matrix.IsInTriangle(i, j))
				{
					const TUpperTriangularMatrix temp(matrix);
					std::cout << temp(i, j) << " ";
				}
				else
				{
					os >> matrix(i, j);
				}
			}

			//std::cout << std::endl;
		}
	}
	catch (std::exception& e)
	{
		std::cout << e.what() << std::endl;

		throw std::exception("TMatrix std::istream& operator>> failure.");
	}

	return os;
}
