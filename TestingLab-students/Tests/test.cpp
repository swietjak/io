#include "pch.h"

TEST(Rank, CheckRankInitializerFunc)
{
	int width = 5, height = 5;
	Matrix A(height, width, [](int i, int j) { return (double)i; });
	ASSERT_EQ(A.rank(), 1);
}

TEST(constructors, Check1DLambdaFuncCtr)
{
	int width = 3;
	Matrix A(width, [](int i, int j) { return (double)i; });
	EXPECT_EQ(A.rows, width) << "zla ilosc rzedow";
	EXPECT_EQ(A.columns, width) << "zla ilosc kolumn";
	for (size_t i = 0; i < width; i++)
	{
		for (size_t j = 0; j < width; j++)
		{
			EXPECT_EQ(A(i, j), i) << "wartości na pozycji nie są takie same";
		}
	}
}

TEST(constructors, Check2DLambdaFuncCtr)
{
	int width = 3, height = 3;
	Matrix A(height, width, [](int i, int j) { return i * 0.1; });
	EXPECT_EQ(A.rows, height) << "zla ilosc rzedow";
	EXPECT_EQ(A.columns, width) << "zla ilosc kolumn";
	for (size_t i = 0; i < width; i++)
	{
		for (size_t j = 0; j < height; j++)
		{
			EXPECT_EQ(A(i, j), i*0.1) << "wartości na pozycji nie są takie same";
		}
	}
}

TEST(constructors, Check1DShapeCtr)
{
	int width = 3;
	double value = 0.2;
	Matrix A(width, value);
	EXPECT_EQ(A.rows, width) << "zla ilosc rzedow";
	EXPECT_EQ(A.columns, width) << "zla ilosc kolumn";
	for (size_t i = 0; i < width; i++)
	{
		for (size_t j = 0; j < width; j++)
		{
			EXPECT_EQ(A(i, j), value) << "wartości na pozycji nie są takie same";
		}
	}
}

TEST(constructors, Check2DShapeCtr)
{
	int width = 3, height = 3;
	double value = 0.1;
	Matrix A(height, width, value);
	EXPECT_EQ(A.rows, height) << "zla ilosc rzedow";
	EXPECT_EQ(A.columns, width) << "zla ilosc kolumn";
	for (size_t i = 0; i < width; i++)
	{
		for (size_t j = 0; j < height; j++)
		{
			EXPECT_EQ(A(i, j), value) << "wartości na pozycji nie są takie same";
		}
	}
}

TEST(constructors, Check1DVectorCtr)
{
	int width = 2;
	std::vector<double> v;

	for (size_t i = 0; i < 4; i++)
	{
		v.push_back((i + 1) * 0.1);
	}

	Matrix A(width, v);
	EXPECT_EQ(A.rows, width) << "zla ilosc rzedow";
	EXPECT_EQ(A.columns, width) << "zla ilosc kolumn";
	int x = 0;
	for (size_t i = 0; i < width; i++)
	{
		for (size_t j = 0; j < width; j++)
		{
			EXPECT_EQ(A(i, j), v[x]) << "wartości na pozycji nie są takie same";
			x++;
		}
	}
	EXPECT_ANY_THROW(Matrix(width * (-1), v)) << "Brak wyjątku w przypadku ujemnych wymiarów";
	EXPECT_ANY_THROW(Matrix(++width, v)) << "Brak wyjątku w przypadku złych wymiarów";
}

TEST(constructors, Check2DVectorCtr)
{
	int width = 1, height = 4;
	double value = 3.0;
	std::vector<double> v = { 0.1, 0.2, 0.3, 0.4 };
	Matrix A(height, width, v);
	EXPECT_EQ(A.rows, height) << "zla ilosc rzedow";
	EXPECT_EQ(A.columns, width) << "zla ilosc kolumn";
	int x = 0;
	for (size_t i = 0; i < width; i++)
	{
		for (size_t j = 0; j < height; j++)
		{
			EXPECT_EQ(A(i, j), v[x]) << "wartości na pozycji nie są takie same";
			x++;
		}
	}
	int h = height * (-1);
	int w = width * (-1);
	EXPECT_ANY_THROW(Matrix( ++height, ++width, v )) << "Brak wyjątku w przypadku złych wymiarów";
	EXPECT_ANY_THROW(Matrix(h, w, v)) << "Brak wyjątku w przypadku ujemnych wymiarów";

}

TEST(constructors, CheckCopyCtr)
{
	int width = 3, height = 3;
	Matrix A(height, width, [](int i, int j) { return i * 0.1; });
	Matrix B(A);
	for (size_t i = 0; i < width; i++)
	{
		for (size_t j = 0; j < height; j++)
		{
			EXPECT_EQ(A(i, j), B(i, j)) << "wartości na pozycji nie są takie same";
		}
	}
}

double **init_values(int rows=3, int cols=3)
{
	double **values = new double *[rows];

	for (size_t i = 0; i < rows; i++)
	{
		values[i] = new double[cols];
		for (size_t f = 0; f < cols; f++)
		{
			values[i][f] = f*1.0;
		}
	}
	return values;
}

TEST(loadDataFuncs, CheckArrLoad)
{
	int width = 3, height = 3;
	Matrix A(height, width, [](int i, int j) { return (double)i; });
	EXPECT_EQ(A.load_data(init_values(4, 4)), false) << "brak wyjątku przy załadowaniu za dużej tablicy";
	EXPECT_EQ(A.load_data(init_values(2, 2)), false) << "brak wyjątku przy załadowaniu za małej tablicy";
}

TEST(loadDataFuncs, CheckVectorLoad)
{
	int width = 3, height = 3;
	std::vector<double> v;
	for (size_t i = 0; i < 9; i++)
	{
		v.push_back(i * 10.0);
	}
	Matrix A(3);
	EXPECT_EQ(A.load_data(v, width, height), true) << "Błąd w ładowaniu danych";
	
	int x = 0;
	for (size_t i = 0; i < width; i++)
	{
		for (size_t j = 0; j < height; j++)
		{
			EXPECT_EQ(A(i, j), v[x]) << "wartości na pozycji nie są takie same";
			x++;
		}
	}
	EXPECT_EQ(A.load_data(v, -1, -1), false) << "Brak wyjątku w przypadku ujemnych wymiarów";
	EXPECT_EQ(A.rows, height) << "nieoczekiwana zmiana ilości wierszy";
	EXPECT_EQ(A.columns, width) << "nieoczekiwana zmiana ilości kolumn";
	ASSERT_EQ(A.load_data(v, width + 1, height + 1), false) << "Brak wyjątku w przypadku za dużych wymiarów";
	ASSERT_EQ(A.load_data(v, width - 1, height - 1), false) << "Brak wyjątku w przypadku za małych wymiarów";

}

TEST(loadDataFuncs, CheckFuncLoad)
{
	int width = 3;
	Matrix A(width);
	A.load_data([](int i, int j) { return (double)i * j; });
	for (size_t i = 0; i < width; i++)
	{
		for (size_t j = 0; j < width; j++)
		{
			EXPECT_EQ(A(i, j), i * j) << "wartości na pozycji nie są takie same";
		}
	}
}

