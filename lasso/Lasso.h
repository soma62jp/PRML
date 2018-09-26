#ifndef _LASSO_H_
#define _LASSO_H_

#include "Matrix.h"
#include "numpy.h"

using namespace arith;
using namespace std;

	//------------------------------------------//
	//              �N�@���@�X                   //
	//------------------------------------------//
	class Lasso{

		private:

			double alpha_;				// ���������̌W��
			int max_iter_;				// �J��Ԃ��̉�
			bool fit_intercept_;		// �ؕ�(i.e., \beta_0)��p���邩
			Matrix coef_;				// ��A�W��(i.e., \beta)�ۑ��p�ϐ�
			double intercept_;			// �ؕЕۑ��p�ϐ�

		public:
			// �R���X�g���N�^
			explicit Lasso(double alpha, int max_iter, bool fit_intercept);

			// �f�X�g���N�^
			virtual ~Lasso();

			void soft_thresholding_operator(double x, double lambda);

			void fit(const Matrix& X, const Matrix& y);

			Matrix predict(const Matrix& X);

	};

		// �s��v�f���������
	Lasso::Lasso(double alpha, int max_iter, bool fit_intercept) : alpha_(1.0), max_iter_(1000),fit_intercept_(true)
	{
		alpha_ = alpha ;
		max_iter_ = max_iter ;
		fit_intercept_ = fit_intercept ;
		coef_ = 0 ;
		intercept_ = 0;
	}

	void Lasso::soft_thresholding_operator(double x, double lambda){

		if ((x > 0) && (lambda < abs(x))){
		  return x - lambda;
		}else if ((x < 0) && (lambda < abs(x))){
		  return x + lambda;
		}else{
		  return 0;
		}

	}

	void Lasso::fit(const Matrix& X, const Matrix& y){

		//fit_intercept_=true
		Matrix calcX(X.m_row, X.m_col + 1);

		for(int i=0;i<X.m_row;i++){
			for(int j=0;j<X.m_col;j++){
				calcX(i,j + 1) = X(i,j);
			}
		}

		if (fit_intercept_){
			//XX = np.column_stack((np.ones(len(X)),X))
			for(int i=0;i<calcX.m_col;i++){
				calcX(i,0)=1;
			}
		}

		//numpy::print(calcX);


	}

	Matrix Lasso::predict(const Matrix& X){

		Matrix y = numpy::mult(X,coef_);   // ���
		Matrix wrk(1, y.m_col);

		//np.ones(len(y))
		for(int i=0;i<y.m_col;i++){
			wrk(0,i)=1;
		}

		if (fit_intercept_){
			y += intercept_ * wrk;
		}

		return y;
	}

#endif // _LASSO_H_

