//--------------------------------------------------//
// File Name: Matrix.h                              //
// Function: Matrix calculation                     //
// Copyright(C) 2016 shoarai                        //
// The MIT License (MIT)                            //
//--------------------------------------------------//
// https://github.com/shoarai/arith.git

#ifndef _MATRIX_H_
#define _MATRIX_H_

//------------------------------------------//
//              �C���N���[�h              	//
//------------------------------------------//

#include <iostream>
#include <cstring>
#include <math.h>

using namespace std;

namespace arith {

	//------------------------------------------//
	//              �N�@���@�X                   //
	//------------------------------------------//
	class Matrix{
	public:
	    unsigned int m_row;    // �s
	    unsigned int m_col;    // ��

	    double** val;   // �s��v�f�p�|�C���^
	//  vector< vector<double> > val;

	public:
	    explicit Matrix
		(unsigned int, unsigned int);   // �R���X�g���N�^
	    Matrix(const Matrix&);              // �R�s�[�R���X�g���N�^
	    virtual ~Matrix();                  // �f�X�g���N�^

	    // �s��v�f�����o��
	    double& operator()(unsigned int row, unsigned int col);

	    // �s��̑��
	    Matrix& operator= (const Matrix&);

	    // �s��Ƃ̉����Z
	    Matrix  operator+ (const Matrix&) const;
	    Matrix& operator+=(const Matrix&);
	    Matrix  operator- (const Matrix&) const;
	    Matrix& operator-=(const Matrix&);

	    // �s��Ƃ̐�
	    Matrix  operator* (const Matrix&) const;

	    // ���l�Ƃ̏揜�Z
	    Matrix  operator* (const double&) const;
	    Matrix& operator*=(const double&);
	    Matrix  operator/ (const double&) const;
	    Matrix& operator/=(const double&);

	    // �]�u�s��
	    Matrix transpose() const;

            // �s��ƒl�̉����Z
	    Matrix operator+(const double&) const;
	    Matrix& operator+=(const double&);
	    Matrix operator-(const double&) const;
	    Matrix& operator-=(const double&);

		// ��r
		bool operator==(const Matrix& mat) const;

	};

	// �s��v�f������������
	Matrix::Matrix(unsigned int row, unsigned int col) : m_row(row), m_col(col)
	{
		// �s�̗v�f����ݒ肷��
	/*  val.resize(m_row);
		for(unsigned int i = 0; i < m_row; i++)
		{
			// ��̗v�f����ݒ肷��
			val[i].resize(m_col);
		}
	*/
		// �s�v�f�𐶐�����
		val = new double*[m_row];

		for (unsigned int i = 0; i < m_row; i++)
		{
			// ��v�f�𐶐�����
			val[i] = new double[m_col];
		}

		// �s��v�f������������
		for(unsigned int i = 0; i < m_row; i++)
		{
			for(unsigned int j = 0; j < m_col; j++)
			{
				val[i][j] = 0;
			}
		}
	}

	// �s��v�f���I�u�W�F�N�g�ŏ���������
	Matrix::Matrix(const Matrix& mat) :
		m_row(mat.m_row), m_col(mat.m_col)
	{
		// �s�̗v�f����ݒ肷��
	/*  val.resize(m_row);
		for(unsigned int i = 0; i < m_row; i++)
		{
			// ��̗v�f����ݒ肷��
			val[i].resize(m_col);
		}
	*/
		// ��v�f����
		val = new double*[m_row];

		for (unsigned int i = 0; i < m_row; i++)
		{
			// �s�v�f����
			val[i] = new double[m_col];
		}

		// �l���
		for(unsigned int i = 0; i < m_row; i++)
		{
			for(unsigned int j = 0; j < m_col; j++)
			{
				val[i][j] = mat.val[i][j];
			}
		}
	}

	// �s��v�f��j������
	Matrix::~Matrix()
	{
		// �s��v�f�j��
		for (unsigned int i = 0; i < m_row; i++){
			delete[] val[i];
		}

		delete[] val;
	}

	// �s��v�f���擾����
	double& Matrix::operator()(unsigned int row, unsigned int col)
	{
		return val[row][col];
	}

	// ������Z�q
	Matrix& Matrix::operator=(const Matrix& mat)
	{
		// �s�񓯎m�̍s���Ɨ񐔂��������Ȃ��Ƃ�
		if(m_row != mat.m_row || m_col != mat.m_col)
		{
			string err = "Matrix can't be substituted";
			throw err;
		}

		for(unsigned int i = 0; i < m_row; i++)
		{
			for(unsigned int j = 0; j < m_col; j++)
			{
				val[i][j] = mat.val[i][j];
			}
		}

		return *this;
	}

	// +���Z�q
	Matrix Matrix::operator+(const Matrix& mat) const
	{
		// �s�񓯎m�̍s���Ɨ񐔂��������Ȃ��Ƃ�
		if(m_row != mat.m_row || m_col != mat.m_col){
			string err = "Matrix can't be added";
			throw err;
		}

		// ���ƂȂ�s��
		Matrix matAns(m_row, m_col);

		// �󂯎����2�̍s������Z����
		for(unsigned int i = 0; i < m_row; i++)
		{
			for(unsigned int j = 0; j < m_col; j++)
			{
				matAns.val[i][j] = val[i][j] + mat.val[i][j];
			}
		}

		return matAns;
	}

	// +=���Z�q
	Matrix& Matrix::operator+=(const Matrix& mat)
	{
		// �s�񓯎m�̍s���Ɨ񐔂��������Ȃ��Ƃ�
		if(m_row != mat.m_row || m_col != mat.m_col){
			string err = "Matrix can't be added";
			throw err;
		}

		// �󂯎����2�̍s������Z����
		for(unsigned int i = 0; i < m_row; i++)
		{
			for(unsigned int j = 0; j < m_col; j++)
			{
				val[i][j] += mat.val[i][j];
			}
		}

		return *this;
	}

	// -���Z�q
	Matrix Matrix::operator-(const Matrix& mat) const
	{
		// �s�񓯎m�̍s���Ɨ񐔂��������Ȃ��Ƃ�
		if(m_row != mat.m_row || m_col != mat.m_col){
			string err = "Matrix can't be subtracted";
			throw err;
		}

		// ���ƂȂ�s��
		Matrix matAns(m_row, m_col);

		// �s�񌸎Z
		for(unsigned int i = 0; i < m_row; i++)
		{
			for(unsigned int j = 0; j < m_col; j++)
			{
				matAns.val[i][j] = val[i][j] - mat.val[i][j];
			}
		}

		return matAns;
	}


	// -=���Z�q
	Matrix& Matrix::operator-=(const Matrix& mat)
	{
		// �s�񓯎m�̍s���Ɨ񐔂��������Ȃ��Ƃ�
		if(m_row != mat.m_row || m_col != mat.m_col){
			string err = "Matrix can't be subtracted";
			throw err;
		}

		// �s����Z
		for(unsigned int i = 0; i < m_row; i++){
			for(unsigned int j = 0; j < m_col; j++)
			{
				val[i][j] -= mat.val[i][j];
			}
		}

		return *this;
	}

	// �s�񓯎m�̏�Z
	Matrix Matrix::operator*(const Matrix& mat) const
	{
		// ��搔�̍s��̗񐔁��搔�̍s��̍s��
		if(m_col != mat.m_row){
			string err = "Matrix can't be producted";
			throw err;
		}

		// ���ƂȂ�s��i��搔�̍s��̗񐔁A�搔�̍s��̍s���j
		Matrix matAns(m_row, mat.m_col);

		// �s��̏�Z
		for(unsigned int i = 0; i < m_row; i++){
			for(unsigned int j = 0; j < mat.m_col; j++)
			{
				//for(unsigned int k = 0; k < m_row; k++)   //bug
				for(unsigned int k = 0; k < mat.m_row; k++)
				{
					matAns.val[i][j] += val[i][k] * mat.val[k][j];
				}
			}
		}

		return matAns;
	}

	// �s��ƒl�̏�Z
	Matrix Matrix::operator*(const double& in_val) const
	{
		// ���ƂȂ�s��
		Matrix matAns(m_row, m_col);

		for(unsigned int i = 0; i < m_row; i++)
		{
			for(unsigned int j = 0; j < m_col; j++)
			{
				matAns.val[i][j] = val[i][j] * in_val;
			}
		}

		return matAns;
	}

	// �s��ƒl�̏�Z
	Matrix& Matrix::operator*=(const double& in_val)
	{
		for(unsigned int i = 0; i < m_row; i++)
		{
			for(unsigned int j = 0; j < m_col; j++)
			{
				val[i][j] *= in_val;
			}
		}

		return *this;
	}

	// �s��ƒl�̏��Z
	Matrix Matrix::operator/(const double& in_val) const
	{
		// ���ƂȂ�s��
		Matrix matAns(m_row, m_col);

		for(unsigned int i = 0; i < m_row; i++)
		{
			for(unsigned int j = 0; j < m_col; j++)
			{
				matAns.val[i][j] = val[i][j] / in_val;
			}
		}

		return matAns;
	}

	// �s��ƒl�̏��Z
	Matrix& Matrix::operator/=(const double& in_val)
	{
		for(unsigned int i = 0; i < m_row; i++)
		{
			for(unsigned int j = 0; j < m_col; j++)
			{
				val[i][j] /= in_val;
			}
		}

		return *this;
	}

	// �]�u�s������߂�
	Matrix Matrix::transpose() const
	{
		// ���ƂȂ�s��i�s�Ɨ�𔽑΂ɐݒ�j
		Matrix matAns(m_col, m_row);

		for(unsigned int i = 0; i < m_row; i++)
		{
			for(unsigned int j = 0; j < m_col; j++)
			{
				matAns.val[j][i] = val[i][j];
			}
		}

		return matAns;
	}

		// �s��ƒl�̉��Z
	Matrix Matrix::operator+(const double& in_val) const
	{
		// ���ƂȂ�s��
		Matrix matAns(m_row, m_col);

		for(unsigned int i = 0; i < m_row; i++)
		{
			for(unsigned int j = 0; j < m_col; j++)
			{
				matAns.val[i][j] = val[i][j] + in_val;
			}
		}

		return matAns;
	}

	// �s��ƒl�̉��Z
	Matrix& Matrix::operator+=(const double& in_val)
	{
		for(unsigned int i = 0; i < m_row; i++)
		{
			for(unsigned int j = 0; j < m_col; j++)
			{
				val[i][j] += in_val;
			}
		}

		return *this;
	}

	// �s��ƒl�̌��Z
	Matrix Matrix::operator-(const double& in_val) const
	{
		// ���ƂȂ�s��
		Matrix matAns(m_row, m_col);

		for(unsigned int i = 0; i < m_row; i++)
		{
			for(unsigned int j = 0; j < m_col; j++)
			{
				matAns.val[i][j] = val[i][j] - in_val;
			}
		}

		return matAns;
	}

	// �s��ƒl�̌��Z
	Matrix& Matrix::operator-=(const double& in_val)
	{
		for(unsigned int i = 0; i < m_row; i++)
		{
			for(unsigned int j = 0; j < m_col; j++)
			{
				val[i][j] -= in_val;
			}
		}

		return *this;
	}

	// ���ꂩ�ǂ�����r
	bool Matrix::operator==(const Matrix& mat) const
	{
		bool ret = true;

		for(unsigned int i = 0; i < m_row; i++)
		{
			for(unsigned int j = 0; j < m_col; j++)
			{
				if(val[i][j] != mat.val[i][j])
				{
					ret = false;
					return ret;
				}
			}
		}

		return ret;
	}


}

#endif // _MATRIX_H_
