#include "TUpperTriangularMatrix.h"

bool TUpperTriangularMatrix::IsInTriangle(int i, int j) const
{
	return (j >= i);
}

TUpperTriangularMatrix::TUpperTriangularMatrix(int n) : TMatrix(n)
{
	for (int i = 1; i < size_lines; i++)
	{
		arr[i].SetSize(size_lines - i);
	}
}

MyType& TUpperTriangularMatrix::Get(int i, int j) const
{
	MyType result;

	if (!IsInTriangle(i, j))
	{
		result = 0;
	}
	else
	{
		result = arr[i][j - i];
	}

	return result;
}

MyType& TUpperTriangularMatrix::Get(int i, int j)
{
	MyType result;

	if (!IsInTriangle(i, j))
	{
		result = 0;
	}
	else
	{
		result = arr[i][j - i];
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
				os << matrix.Get(i, j) << std::endl;
			}
			catch (...)
			{
				throw std::exception("TMatrix std::ostream& operator<< failure.");
			}
		}
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
					std::cout << matrix.Get(i, j);
				}
				else
				{
					os >> matrix.Get(i, j);
				}
			}
		}
	}
	catch (...)
	{
		throw std::exception("TMatrix std::istream& operator>> failure.");
	}

	return os;
}