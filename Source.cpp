#include "TUpperTriangularMatrix.h"
#define MyTypeScalar int

void ExpectedInput(int& target_variable, const char* text)
{
	do
	{
		std::cout << text;
		std::cin >> target_variable;
	} while (target_variable <= 0);
}

int main()
{
	int matrix_1_temp_size = 0;
	int matrix_2_temp_size = 0;

	ExpectedInput(matrix_1_temp_size, "Input matrix_1 size: ");
	ExpectedInput(matrix_2_temp_size, "Input matrix_2 size: ");

	std::cin.clear();

	TUpperTriangularMatrix matrix1(matrix_1_temp_size);
	TUpperTriangularMatrix matrix2(matrix_2_temp_size);

	try
	{
		std::cout << "Input matrix1: " << std::endl;
		std::cin >> matrix1;
	}
	catch (const std::exception& e)
	{
		std::cout << e.what();
	}

	try
	{
		std::cout << "Input matrix2: " << std::endl;
		std::cin >> matrix2;
	}
	catch (const std::exception& e)
	{
		std::cout << e.what();
	}

	std::cout << '\n' << matrix1 << '\n';

	std::cout << "+" << std::endl;
	try
	{
		TUpperTriangularMatrix matrix_temp = (matrix1 + matrix2);
		std::cout << matrix1 + matrix2 << std::endl;
		std::cout << matrix_temp << std::endl;
	}
	catch (const std::exception& ex)
	{
		std::cout << ex.what() << std::endl;
	}

	std::cout << "-" << std::endl;
	try
	{
		std::cout << matrix1 - matrix2 << std::endl;
	}
	catch (const std::exception& ex)
	{
		std::cout << ex.what() << std::endl;
	}

	std::cout << "*" << std::endl;
	try
	{
	//	std::cout << matrix1 * matrix2 << std::endl;
	}
	catch (const std::exception& ex)
	{
		std::cout << ex.what() << std::endl;
	}

	std::cout << "* (scalar)" << std::endl;
	try
	{
		MyTypeScalar temp_scalar;
		std::cout << std::endl << "Input scalar: ";
		std::cin >> temp_scalar;
		std::cout << (matrix1 * temp_scalar) << std::endl;
		std::cout << (matrix2 * temp_scalar) << std::endl;
	}
	catch (const std::exception& ex)
	{
		std::cout << ex.what() << std::endl;
	}

	std::cout << "/" << std::endl;
	try
	{
		MyTypeScalar temp_scalar;
		std::cout << std::endl << "Input scalar: ";
		std::cin >> temp_scalar;
		std::cout << matrix1 / temp_scalar << std::endl;
		std::cout << matrix2 / temp_scalar << std::endl;
	}
	catch (const std::exception& ex)
	{
		std::cout << ex.what() << std::endl;
	}

	/*
	std::cout << "+=" << std::endl;
	try
	{
		std::cout << matrix1 << std::endl << matrix2 << std::endl;
		TUpperTriangularMatrix res(matrix_1_temp_size);

		res += matrix1 + matrix2;
		std::cout << res << std::endl;
	}
	catch (const std::exception& ex)
	{
		std::cout << ex.what() << std::endl;
	}

	std::cout << "-=" << std::endl;
	try
	{
		TUpperTriangularMatrix res(matrix1);
		res -= matrix2;
		std::cout << res << std::endl;
	}
	catch (const std::exception& ex)
	{
		std::cout << ex.what() << std::endl;
	}*/
	;
	std::cout << "operator()(i, j)" << std::endl;
	try
	{
		unsigned int temp_lines_index1, temp_columns_index1;
		std::cout << "Input lines index for matrix_1: ";
		std::cin >> temp_lines_index1;
		std::cout << "Input columns index for matrix_1: ";
		std::cin >> temp_columns_index1;

		std::cout << matrix1(temp_lines_index1, temp_columns_index1) << std::endl;
		/*
		std::cout << "Input lines index for matrix_2: ";
		std::cin >> temp_lines_index2;
		std::cout << "Input columns index for matrix_2: ";
		std::cin >> temp_columns_index2;

		std::cout << matrix2[temp_lines_index2][temp_columns_index2] << std::endl;*/
	}
	catch (const std::exception& ex)
	{
		std::cout << ex.what() << std::endl;
	}

	std::cout << "==" << std::endl;
	try
	{
		std::cout << (matrix1 == matrix2) << std::endl;
	}
	catch (const std::exception& ex)
	{
		std::cout << ex.what() << std::endl;
	}

	std::cout << "!=" << std::endl;
	try
	{
		std::cout << (matrix1 != matrix2) << std::endl;
	}
	catch (const std::exception& ex)
	{
		std::cout << ex.what() << std::endl;
	}
}
