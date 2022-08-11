#include <iostream>
#include <math.h>
#include <string>
#include <iomanip>

using namespace std;

template <class M>
class Matrix
{
private:
	class Row;
	int size;
	Row* R;

	class Row
	{
	public:
		M* v;

		Row();
		Row(int size);
		int& operator[] (int j) { return v[j]; }
		const int& operator[] (const int j) const { return v[j]; }
	};

public:

	Matrix();
	Matrix(int size) throw (out_of_range);
	Matrix(int size, Row* A);
	Matrix(const Matrix& A);
	~Matrix();

	int get_size() const { return size; }
	Row& operator[] (int i) { return R[i]; }
	const Row& operator [] (const int i) const { return R[i]; }

	Matrix& operator = (const Matrix& A);

	friend Matrix<M> operator + <>(const Matrix<M>& A, const Matrix<M>& B) throw (exception);
	friend Matrix<M> operator - <>(const Matrix<M>& A, const Matrix<M>& B) throw (exception);

	friend ostream& operator << <>(ostream& out, Matrix& A);
	friend istream& operator >> <>(istream& in, Matrix& A);
};

template <class M>
Matrix<M>::Row::Row()
{
	 v = new M[1];
	v[0] = 0;
}


template <class M>
Matrix<M>::Row::Row(int size)
{
	 v = new M[size];
	for (int j = 0; j < size; j++)
		v[j] = M();
}

template <class M>
Matrix<M>::Matrix()
{
	size = 1;
	R = new Row(size);
	R[0] = Row(size);
}

template <class M>
Matrix<M>::Matrix(int size) throw(out_of_range)
{
	if (size < 1)
		throw out_of_range("Size ought to be 1 or more than 1.");

	this->size = size;

	R = new Row[this->size];
	for (int i = 0; i < this->size; i++)
	{
		R[i] = Row(this->size);
	}
}

template <class M>
Matrix<M>::Matrix(int size, Row* A)
{
	this->size = size;
	R = A;
}

template <class M>
Matrix<M>::Matrix(const Matrix<M>& a) //
{
	size = a.size;

	R = new Row[this->size];
	for (int i = 0; i < this->size; i++)
	{
		R[i] = Row(this->size);
	}

	for (int i = 0; i < size; i++)
	{
		for (int j = 0; j < size; j++)
		{
			R[i][j] = a.R[i][j];
		}
	}
}

template <class M>
Matrix<M>::~Matrix()
{
	for (int i = 0; i < size; i++)
	{
		if (R[i].v != nullptr)
			delete[] R[i].v;
	}

	if (R != nullptr)
		delete[] R;
}

template <class M>
Matrix<M>& Matrix<M>::operator = (const Matrix<M>& a)
{
	for (int i = 0; i < size; i++)
	{
		if (R[i].v != nullptr)

			delete[] R[i].v;
	}

	if (R != nullptr)
	{
		delete[] R;
	}

	size = a.size;

	R = new Row[this->size];
	for (int i = 0; i < this->size; i++)
	{
		R[i] = Row(this->size);
	}

	for (int i = 0; i < size; i++)
	{
		for (int j = 0; j < size; j++)
		{
			R[i][j] = a.R[i][j];
		}
	}
	return *this;
}

template <class M>
Matrix<M> operator + (const Matrix<M>& A, const Matrix<M>& B) //
{
	if (A.size != B.size)
	{
		throw exception("The sizes ought to be equals.");
	}

	Matrix<M> tmp(A.get_size());

	for (int i = 0; i < A.get_size(); i++)
	{
		for (int k = 0; k < A.get_size(); k++)
		{

			tmp[i][k] = A[i][k] + B[i][k];
		}
	}
	return tmp;
}

template <class M>
Matrix<M> operator - (const Matrix<M>& A, const Matrix<M>& B) //
{
	if (A.size != B.size)
	{
		throw exception("The sizes ought to be equals.");
	}

	Matrix<M> tmp(A.get_size());

	for (int i = 0; i < A.get_size(); i++)
	{
		for (int k = 0; k < A.get_size(); k++)
		{

			tmp[i][k] = A[i][k] - B[i][k];
		}
	}
	return tmp;
}

template <class M>
ostream& operator << (ostream& out, Matrix<M>& a)
{
	for (int i = 0; i < a.get_size(); i++)
	{
		for (int k = 0; k < a.get_size(); k++)
		{
			out << setw(4) << a[i][k];
		}
		out << endl;
	}
	return out;
}

template <class M>
istream& operator >> (istream& in, Matrix<M>& n)
{
	for (int i = 0; i < n.get_size(); i++)
	{
		for (int j = 0; j < n.get_size(); j++)
		{
			cout << "Matrix[" << i << "][" << j << "] = "; in >> n[i][j];
		}
		cout << endl;
	}
	return in;
}

int main()
{
	try
	{
		int size1, size2;

		cout << "size1 = "; cin >> size1;
		Matrix<int> A(size1);
		cin >> A;

		cout << "size2 = "; cin >> size2;
		Matrix<int> B(size2);
		cin >> B;

		cout << "Matrix A:" << endl;
		cout << A << endl;

		cout << "Matrix B:" << endl;
		cout << B << endl;

		Matrix<int> C = A + B;
		cout << "Matrix C(+):" << endl;
		cout << C << endl;

		Matrix<int> D = A - B;
		cout << "Matrix D(-):" << endl;
		cout << D << endl;
	}
	catch (exception e)
	{
		cerr << e.what() << endl;
	}
	catch (out_of_range e)
	{
		cerr << e.what() << endl;
	}
}