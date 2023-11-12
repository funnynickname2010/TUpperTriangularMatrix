#include "TMatrix.h"

TMatrix::TMatrix(int n) : arr(n)
{
	for (int i = 0; i < n; i++) 
	{ 
		arr[i].SetSize(n);

		for (int j = 0; j < n; j++)
		{
			arr[i][j] = 0;
		}
	}

	size_columns = n;
	size_lines = n;
}

TMatrix::TMatrix(int n, int m) : arr(n)
{
	for (int i = 0; i < n; i++)
	{
		arr[i].SetSize(m); 

		for (int j = 0; j < m; j++)
		{
			arr[i][j] = 0;
		}
	}

	size_columns = m;
	size_lines = n;
}

TMatrix TMatrix::operator+(const TMatrix& matrix)
{
	TMatrix result(size_lines, size_columns);

	if (size_lines != matrix.size_lines || size_columns != matrix.size_columns)
	{
		throw std::exception("TMatrix operator+ failure. Size mismatch");
	}

	try
	{
		result.arr = arr + matrix.arr;
	}
	catch (...)
	{
		throw std::exception("TMatrix operator+ failure.");
	}

	return result;
}

TMatrix TMatrix::operator-(const TMatrix& matrix)
{
	TMatrix result(size_lines, size_columns);

	if (size_lines != matrix.size_lines || size_columns != matrix.size_columns)
	{
		throw std::exception("TMatrix operator- failure. Size mismatch");
	}

	try
	{
		result.arr = arr - matrix.arr;
	}
	catch (...)
	{
		throw std::exception("TMatrix operator- failure.");
	}

	return result;
}

TMatrix TMatrix::operator*(TMatrix& matrix)
{
	TMatrix result(size_lines, matrix.size_columns);

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
					result.arr[i][j] += arr[i][k] * matrix.arr[k][j];
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
	TMatrix result(this->size_lines, this->size_columns);

	result.arr = this->arr * scalar;

	return result;
}

TMatrix TMatrix::operator/(const double scalar)
{
	TMatrix result(this->size_lines, this->size_columns);

	if (scalar != 0)
	{
		result.arr = this->arr / scalar;
	}
	else
	{
		throw std::exception("TMatrix::operator/ (const double scalar) failure: division by zero.");
	}

	return result;
}

TMatrix& TMatrix::operator+=(const TMatrix& matrix)
{
	*this = *this + matrix;

	return (*this);
}

TMatrix& TMatrix::operator-=(const TMatrix& matrix)
{
	*this = *this - matrix;

	return *this;
}

TVector<MyType>& TMatrix::operator[](int index)
{
	return arr[index];
}

TVector<MyType>& TMatrix::operator[](int index) const
{
	return arr[index];
}

bool TMatrix::operator==(const TMatrix& matrix) const
{
	bool flag = 1;

	if (size_lines != matrix.size_lines || size_columns != matrix.size_columns)
	{
		throw std::exception("TMatrix operator== failure. Size mismatch");
	}

	for (int i = 0; i < size_lines; i++)
	{
		if (arr != matrix.arr)
		{
			flag = 0;
			break;
		}
	}

	return flag;
}

bool TMatrix::operator!=(const TMatrix& matrix) const
{
	bool flag = 1;

	if (size_lines != matrix.size_lines || size_columns != matrix.size_columns)
	{
		throw std::exception("TMatrix operator== failure. Size mismatch");
	}

	for (int i = 0; i < size_lines; i++)
	{
		if (arr != matrix.arr)
		{
			flag = 0;
			break;
		}
	}

	return !flag;
}

std::ostream& operator<<(std::ostream& os, const TMatrix& matrix)
{
	for (int i = 0; i < matrix.size_lines; i++)
	{
		try
		{
			os << matrix.arr[i] << std::endl;
		}
		catch (...)
		{
			throw std::exception("TMatrix std::ostream& operator<< failure.");
		}
	}

	return os;
}

std::istream& operator>>(std::istream& os, TMatrix& matrix)
{
	try
	{
		for (int i = 0; i < matrix.size_lines && os.good(); i++)
		{
			os >> matrix.arr[i];
		}
	}
	catch (...)
	{
		throw std::exception("TMatrix std::istream& operator>> failure.");
	}

	return os;
}
