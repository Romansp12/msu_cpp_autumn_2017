#pragma once
#ifndef MATRIX_H
#define MATRIX_H

//========================================================================

#include <vector>
#include <iostream>
#include <exception>
#include <stdlib.h>
#include <memory.h>

//========================================================================

//#define DEBUG(x) std::cout << x << std::endl;
#define DEBUG(x)

//========================================================================

namespace Constants
{
	const double epsiol = 1e-9;
}

double Abs(double arg);

//========================================================================

class Matrix
{
	private:
		class MatrixRow //��������� ���������, ����� ��� ������� �� ����� ��������� ��� Matrix
		{
			private:
				double* row_;
				size_t max_column_;

			public:
				MatrixRow(double* row, size_t max_columns);

				double& operator[] (size_t column);
				const double& operator[] (size_t column) const;

				//�������� � ������ ������������ �� �����
		};

	private:
		//����� ���� �� ������������ vector, �� ����� �� ������� ������ ����� (������-����� �� �����)
		//����� ����, ����� �� ����������� ��������� �������
		double* matrix_; 

		//����� �������
		std::pair<size_t, size_t> shape_;

		void CreateAndCopy_(size_t size, const double* data);

	public:
		Matrix(std::pair<size_t, size_t> shape, const std::vector<double>& data);

		//���������� ������ � ������� ������ - �������� ��������������.
		//������ ����� ��������� ��������: �� ������ ����� �������� ������ �������.
		Matrix(const std::vector<double>& data);
		Matrix(std::pair<size_t, size_t> shape, double fill_value = 0);
		Matrix(const Matrix& matrix);

		Matrix& operator= (const Matrix& arg);

		//���������, ������������ ��������� �������
		Matrix operator+ (const Matrix& arg) const;
		Matrix operator- () const;
		Matrix operator- (const Matrix& arg) const;
		Matrix operator* (const Matrix& arg) const;
		Matrix operator* (double arg) const;

		//���������, ������������ ���������� ������
		Matrix& operator+= (const Matrix& arg);
		Matrix& operator-= (const Matrix& arg);
		Matrix& operator*= (const Matrix& arg);
		Matrix& operator*= (double arg);

		bool operator== (const Matrix& arg) const;
		bool operator!= (const Matrix& arg) const;

		MatrixRow operator[] (size_t row);
		const MatrixRow operator[] (size_t row) const;

		//����������, ������� ����� ���� "���������"
		~Matrix();

		size_t Rows() const { return shape_.first; }
		size_t Columns() const { return shape_.second; }
};

//========================================================================

#endif