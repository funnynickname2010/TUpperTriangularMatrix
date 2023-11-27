#include "TUpperTriangularMatrix.h"
#include "TMatrix.cpp"


bool TUpperTriangularMatrix::IsInTriangle(int i, int j) const
{
	return (j >= i);
}

TUpperTriangularMatrix::TUpperTriangularMatrix(const unsigned int n) : TMatrix(n)
{
	for (int i = 1; i < size_lines; i++)
	{
		arr[i].SetSize(size_lines - i);
	}
}

const MyType TUpperTriangularMatrix::Get(int i, int j) const
{
	if (!IsInTriangle(i, j))
	{
		return 0;
	}
	else
	{
		return arr[i][j - i];
	}
}

MyType& TUpperTriangularMatrix::Get(int i, int j)
{
	if (!IsInTriangle(i, j))
	{
		throw std::exception("MyType& TUpperTriangularMatrix::Get(int i, int j) failure: indices not in the triangle.");
	}
	else
	{
		return arr[i][j - i];
	}
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
				result.Get(i, j) *= scalar;
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

	TMatrix result(size_lines, size_columns_2);

	if (size_columns != size_lines_2)
	{
		throw std::exception("TMatrix operator*(const TMatrix& matrix) failure. Size mismatch");
	}

	try
	{
		for (int i = 0; i < size_columns_2; i++)
		{
			for (int j = 0; j < size_lines; j++)
			{
				for (int k = 0; k < size_columns; k++)
				{
					result[i][j] += this->Get(i, k) * matrix[k][j];
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
	TUpperTriangularMatrix result(size_lines);

	if (size_columns != matrix.size_lines)
	{
		throw std::exception("TMatrix operator*(const TMatrix& matrix) failure. Size mismatch");
	}

	try
	{
		for (int i = 0; i < result.size_columns; i++)
		{
			for (int j = 0; j < result.size_lines; j++)
			{
				for (int k = 0; k < size_columns; k++)
				{
					result.Get(i, j) += this->Get(i, k) * matrix.Get(k, j);
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

TMatrix operator*(const TMatrix& matrix, const TUpperTriangularMatrix& UTmatrix)
{
	unsigned int size_lines_1 = matrix.GetSizeLines();
	unsigned int size_columns_1 = matrix.GetSizeColumns();

	TMatrix result(size_lines_1, UTmatrix.size_columns);

	if (size_columns_1 != UTmatrix.size_lines)
	{
		throw std::exception("TMatrix operator*(const TMatrix& matrix) failure. Size mismatch");
	}

	try
	{
		for (int i = 0; i < UTmatrix.size_columns; i++)
		{
			for (int j = 0; j < size_lines_1; j++)
			{
				for (int k = 0; k < size_columns_1; k++)
				{
					result[i][j] += matrix[i][k] * UTmatrix.Get(k, j);
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
	for (int i = 0; i < matrix.size_lines; i++)
	{
		for (int j = 0; j < matrix.size_columns; j++)
		{
			try
			{
				os << matrix.Get(i, j);
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
		for (int i = 0; i < matrix.size_lines && os.good(); i++)
		{
			for (int j = 0; j < matrix.size_columns; j++)
			{
				if (!matrix.IsInTriangle(i, j))
				{
					const TUpperTriangularMatrix temp_matrix(matrix);
					std::cout <<  matrix.Get(i, j);
				}
				else
				{
					os >> matrix.Get(i, j);
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