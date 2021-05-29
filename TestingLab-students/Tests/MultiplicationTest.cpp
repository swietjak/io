#include "pch.h"


class MultiplicationByIntTests : public ::testing::TestWithParam<tuple<Matrix, int, Matrix>>
{
};
TEST_P(MultiplicationByIntTests, CheckMultiplication)
{
	Matrix A = get<0>(GetParam());
	int multiplier = get<1>(GetParam());
	Matrix expected_result = get<2>(GetParam());
	A = A * multiplier;
	ASSERT_TRUE(A == expected_result) << "multiplier: " << multiplier;
}

INSTANTIATE_TEST_CASE_P(MultiplicationByIntTest, MultiplicationByIntTests,
						::testing::Values(
							make_tuple(Matrix(2, 0.1), 2, Matrix(2, 0.2)),
							make_tuple(Matrix(5, 3, 1.0), 2, Matrix(5, 3, 2.0)),
							make_tuple(Matrix(5, 1.0), 10, Matrix(5, 10.0)),
							make_tuple(Matrix(5, 1.0), 0, Matrix(5, 0.0)),
							make_tuple(Matrix(5, 1.0), -1, Matrix(5, -1.0)),
							make_tuple(Matrix(2, 1.0), 4, Matrix(2, 4.0)),
							make_tuple(Matrix(2, 2.0), 2, Matrix(2, 4.0)),
							make_tuple(Matrix(2, 3.0), 2, Matrix(2, 6.0))));

class AddingMatrixesTests : public ::testing::TestWithParam<tuple<Matrix, Matrix, Matrix>>
{
};

TEST_P(AddingMatrixesTests, CheckAdding)
{
	Matrix A = get<0>(GetParam());
	Matrix B = get<1>(GetParam());
	Matrix C = get<2>(GetParam());

	if ((A.columns == B.columns) && (A.rows == B.rows))
	{
		auto res = A + B;
		res.print();
		ASSERT_TRUE(C == res);
	}
	else
	{
		ASSERT_ANY_THROW(A + B) << "Brak zwracanego wyjatku";
	}
}

INSTANTIATE_TEST_CASE_P(AddingMatrixesTest, AddingMatrixesTests,
						::testing::Values(
							make_tuple(Matrix(2, 1.0), Matrix(2, 3.0), Matrix(2, 4.0)),
							make_tuple(Matrix(5, [](int i, int j) { return (double)i * j; }), Matrix(5, 10.0), Matrix(5, [](int i, int j) { return (double)(i * j + 10); })),
							make_tuple(Matrix(10, -10), Matrix(100, -10.0), Matrix(100, [](int i, int j) { return (double)(i * j - 10); })),
							make_tuple(Matrix(10, 0.1), Matrix(10, 0.1), Matrix(10, 0.2)))); //

class MultiplyingMatrixesTests : public ::testing::TestWithParam<tuple<Matrix, Matrix, Matrix>>
{
};

TEST_P(MultiplyingMatrixesTests, CheckMultiplying)
{
	Matrix A = get<0>(GetParam());
	Matrix B = get<1>(GetParam());
	Matrix C = get<2>(GetParam());

	if (A.columns == B.rows)
	{
		auto res = A * B;
		res.print();
		ASSERT_TRUE(C == res);
	}
	else
	{
		ASSERT_ANY_THROW(A*B) << "Brak zwracanego wyjatku1";
	}


}

double **identity(int n)
{
	double **matrix = new double *[n];
	for (size_t i = 0; i < n; i++)
	{
		matrix[i] = new double[n];
		for (size_t j = 0; j < n; j++)
		{
			matrix[i][j] = 0;
		}
		matrix[i][i] = 1.0;
	}
	return matrix;
}

Matrix I = Matrix(10);
auto _ = I.load_data(identity(10));

INSTANTIATE_TEST_CASE_P(MultiplyingMatrixesTest, MultiplyingMatrixesTests,
						::testing::Values(
							make_tuple(Matrix(100, 1.0), Matrix(100, 1.0), Matrix(100, 100.0)),
							make_tuple(Matrix(2, 2.1), Matrix(2, std::vector<double>({1, 0, 0, 1})), Matrix(2, 2.1)),
							make_tuple(Matrix(100, 1.0), Matrix(100, 0), Matrix(100, 0)),
							make_tuple(Matrix(2, 3, 3), Matrix(2, 3, 3), Matrix(2, 3))));

class DeterminantTests : public ::testing::TestWithParam<tuple<Matrix, double>>
{
};
TEST_P(DeterminantTests, CheckDeterminants)
{
	Matrix A = get<0>(GetParam());
	double det = get<1>(GetParam());
	auto res = A.determinant();
	A.print();
	ASSERT_EQ(det, res);
}
Matrix I1 = Matrix(4);
auto __ = I1.load_data(identity(4));

Matrix M2 = Matrix(3);
INSTANTIATE_TEST_CASE_P(DeterminantTest, DeterminantTests,
						::testing::Values(
							make_tuple(Matrix(4, [](int i, int j) { return (double)(i + 1) * (j + 1)*0.1; }), 0),
							make_tuple(Matrix(2, [](int i, int j) { return (double)((i + 1) + (j + 2)); }), -1),
							make_tuple(I1, 1),
							make_tuple(Matrix(2, std::vector<double>({10, 4.1, 4.1, 10})), 83.19),
							make_tuple(Matrix(3, std::vector<double>({0.1, 0.2, 0.3, 0.2, 0.3, 0.1, 0.3, 0.2, 0.1})), -0.012)
							));
//rzutowanie na unsigned