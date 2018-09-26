#ifndef numpyH
#define numpyH
//---------------------------------------------------------------------------
#include <cmath>
#include <cstdlib>      // srand,rand
#include <string>

#include "Matrix.h"

using namespace arith;

class numpy;

	class numpy
	{
	public :
		// np.argmax
		static Matrix argmax(Matrix& mat,int axis);
		static Matrix sum(Matrix& mat,int axis);
		static Matrix random_choice(int a,int num);
		static Matrix mult(Matrix mat, Matrix mat2);
		static Matrix add(Matrix mat, Matrix mat2);

		static void print(const Matrix& mat);	// デバッグ用
	};


	// np.argmax相当
	Matrix numpy::argmax(Matrix& mat,int axis)
	{
		unsigned int m_col = mat.m_col;
		unsigned int m_row = mat.m_row;

		double max=0;
		double cnt=0;

		if(axis==0){
			Matrix matAns(1,m_col);
			for(unsigned int i = 0;i < m_col ; i++){
				max=mat(0,i);
				for(unsigned int j=0 ; j< m_row  ; j++){
					if(max<mat(j,i)){
						max=mat(j,i);
						matAns(0,i) = (double)j;
					}
				}
			}
			return matAns;

		}else if(axis==1){
			Matrix matAns(m_row,1);
			for(unsigned int i = 0;i < m_row ; i++){
				max=mat(i,0);
				for(unsigned int j=0 ; j < m_col ; j++){
					if(max<mat(i,j)){
						max=mat(i,j);
						matAns(i,0) = (double)j;
					}
				}
			}
			return matAns;
		}else{
			Matrix matAns(1,1);
			for(unsigned int i = 0;i < m_row ; i++){
				for(unsigned int j=0 ; j< m_col ; j++){
					if(max<mat(i,j)){
						max=mat(i,j);
						matAns(0,0) = cnt;
						cnt++;
					}
				}
			}
			return matAns;
		}

	}

	// np.sum相当
	Matrix numpy::sum(Matrix& mat,int axis)
	{
		unsigned int m_col = mat.m_col;
		unsigned int m_row = mat.m_row;

		double sum=0;

		if(axis==0){
			Matrix matAns(1,m_col);
			for(unsigned int i = 0;i < m_col ; i++){
				sum=0;
				for(unsigned int j=0 ; j< m_row  ; j++){
					sum+=mat(j,i);
				}
				matAns(0,i) = sum;
			}
			return matAns;

		}else if(axis==1){
			Matrix matAns(m_row,1);
			for(unsigned int i = 0;i < m_row ; i++){
				sum=0;
				for(unsigned int j=0 ; j < m_col ; j++){
					sum+=mat(i,j);
				}
				matAns(i,0) = sum;
			}
			return matAns;
		}else{
			Matrix matAns(1,1);
			for(unsigned int i = 0;i < m_row ; i++){
				for(unsigned int j=0 ; j< m_col ; j++){
					sum+=mat(i,j);
				}
			}
			matAns(0,0) = sum;
			return matAns;
		}

	}

	// np.random.choice相当
	Matrix numpy::random_choice(int a,int num)
	{
		srand((unsigned int)time(NULL));

		Matrix matAns(1,num);

		for(int i=0 ; i< num ;i++){
			matAns(0,i) =  rand() % (a - 0 + 1) + 0;
		}

		return matAns;
	}

	// np.* 相当
	Matrix numpy::mult(Matrix mat,Matrix mat2)
	{
		unsigned int m_col = mat.m_col;
		unsigned int m_row = mat.m_row;

		// 行列同士の行数と列数が等しくないとき
		if(mat.m_row != mat2.m_row || mat.m_col != mat2.m_col){
			std::string err = "Matrix can't be added";
			throw err;
		}

		// 解となる行列
		Matrix matAns(m_row, m_col);

		// 受け取った2つの行列の要素を乗算する
		for(unsigned int i = 0; i < m_row; i++)
		{
			for(unsigned int j = 0; j < m_col; j++)
			{
				matAns.val[i][j] = mat.val[i][j] * mat2.val[i][j];
			}
		}

		return matAns;

	}

	// np.+ 相当
	// 1行or1列のみ対応(暫定)
	Matrix numpy::add(Matrix mat,Matrix mat2)
	{
		unsigned int m_col = mat.m_col;
		unsigned int m_row = mat.m_row;

		// 行列同士の行数も列数も1ではないとき
		if(mat2.m_row != 1 && mat2.m_col != 1){
			std::string err = "Matrix can't be added";
			throw err;
		}

		// 解となる行列
		Matrix matAns(m_row, m_col);

		// 受け取った2つの行列の要素を加算する(行)
		if(mat2.m_row == 1){
			for(unsigned int i = 0; i < m_row; i++)
			{
				for(unsigned int j = 0; j < m_col; j++)
				{
					matAns.val[i][j] = mat.val[i][j] + mat2.val[0][j];
				}
			}
		}else if(mat2.m_col == 1){
			for(unsigned int i = 0; i < m_row; i++)
			{
				for(unsigned int j = 0; j < m_col; j++)
				{
					matAns.val[i][j] = mat.val[i][j] + mat2.val[i][0];
				}
			}
		}

		return matAns;

	}

	// デバッグ
	void numpy::print(const Matrix& mat)
	{
		unsigned int m_col = mat.m_col;
		unsigned int m_row = mat.m_row;

		for(unsigned int i = 0; i < m_row; i++)
		{
			for(unsigned int j = 0; j < m_col; j++)
			{
			   	cout << mat.val[i][j] << " ";
			}
			cout << endl;
		}

	}

#endif
