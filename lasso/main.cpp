//--------------------------------------------------//
// File Name: main.cpp                              //
// Function: Arithmetic calculation                 //
// Copyright(C) 2016 shoarai                        //
// The MIT License (MIT)                            //
//--------------------------------------------------//

#include <iostream>
#include <cstring>
#include <math.h>
#include <stdio.h>

#include "Matrix.h"
#include "numpy.h"
#include "Lasso.h"

using namespace arith;
using namespace std;

int main(int argc, char* argv[])
{

  Matrix X(4,2);
  Matrix test(4,2);
  Matrix ans(1,4);
  X(0,0)=0;
  X(0,1)=0;
  X(1,0)=1;
  X(1,1)=100;
  X(2,0)=2;
  X(2,1)=200;
  X(3,0)=3;
  X(3,1)=300;

	Matrix y(1,4);
  y(0,0)=1;
  y(0,1)=2;
	y(0,2)=4;
	y(0,3)=8;

  test=X;

  Lasso model(1.0,1000,true);
  model.fit(X,y);
  ans = model.predict(test);

  //
  cout << "X--" << endl;
  numpy::print(X);
  cout << "y--" << endl;
  numpy::print(y);
  cout <<	"intercept_--" << endl;
  cout << model.intercept_ << endl;
  cout <<	"coef_--" << endl;
  numpy::print(*model.coef_);
  cout << "predict--" << endl;
  numpy::print(ans);

  //for(unsigned int l=0;l<2;l++){
  //	cout <<	model.coef_->val[0][l] << " ";
  //}

  return 0;
}

/*
import numpy as np
from sklearn.base import BaseEstimator, RegressorMixin
from copy import deepcopy
#https://satopirka.com/2017/10/lasso%E3%81%AE%E7%90%86%E8%AB%96%E3%81%A8%E5%AE%9F%E8%A3%85--%E3%82%B9%E3%83%91%E3%83%BC%E3%82%B9%E3%81%AA%E8%A7%A3%E3%81%AE%E6%8E%A8%E5%AE%9A%E3%82%A2%E3%83%AB%E3%82%B4%E3%83%AA%E3%82%BA%E3%83%A0-/
class Lasso(BaseEstimator, RegressorMixin):
  def __init__(self, alpha=1.0, max_iter=1000, fit_intercept=True):
    self.alpha = alpha # 正則化項の係数
    self.max_iter = max_iter # 繰り返しの回数
    self.fit_intercept = fit_intercept # 切片(i.e., ¥beta_0)を用いるか
    self.coef_ = None # 回帰係数(i.e., ¥beta)保存用変数
    self.intercept_ = None # 切片保存用変数
  def _soft_thresholding_operator(self, x, lambda_):
    if x > 0 and lambda_ < abs(x):
      return x - lambda_
    elif x < 0 and lambda_ < abs(x):
      return x + lambda_
    else:
      return 0
  def fit(self, X, y):
    if self.fit_intercept:
      X = np.column_stack((np.ones(len(X)),X)) #１次行列の組み合わせなら２次元行列を作り、多次元の組みならhstackと同じ振る舞いをする。np.hstack((行列1, 行列2)) : 水平方向に合体する。
      #print(np.ones(len(X)))
      #print(X)
    beta = np.zeros(X.shape[1])	#行数
    #print(beta)
    #print(X[:, 1:])
    #print(X)
    #print(beta[1:])
    #print(X.shape[0])	#列数
    if self.fit_intercept:
      beta[0] = np.sum(y - np.dot(X[:, 1:], beta[1:]))/(X.shape[0])
    for iteration in range(self.max_iter):
      start = 1 if self.fit_intercept else 0	#三項演算子
      #print(start)
      #print(len(beta))
      for j in range(start, len(beta)):
        tmp_beta = deepcopy(beta)
        tmp_beta[j] = 0.0
        r_j = y - np.dot(X, tmp_beta)
        arg1 = np.dot(X[:, j], r_j)
        arg2 = self.alpha*X.shape[0]
        beta[j] = self._soft_thresholding_operator(arg1, arg2)/(X[:, j]**2).sum()
        if self.fit_intercept:
          beta[0] = np.sum(y - np.dot(X[:, 1:], beta[1:]))/(X.shape[0])
    if self.fit_intercept:
      self.intercept_ = beta[0]
      self.coef_ = beta[1:]
    else:
      self.coef_ = beta
    return self
  def predict(self, X):
    y = np.dot(X, self.coef_)
    if self.fit_intercept:
      y += self.intercept_*np.ones(len(y))
    return y
X = [[0,0], [1, 100], [2, 200]]
y = [1, 2, 4]
test =[[0,0], [1, 100], [2, 200]]
model = Lasso(alpha=1.0, max_iter=1000)
model.fit(X, y)
ans = model.predict(test)
print("Lasso")
print(model.intercept_)
print(model.coef_)
print(ans)
print("")
import sklearn.linear_model as lm
model = lm.Lasso(alpha=1.0, max_iter=1000, tol=0.0) # tol=0.0で収束判定なし(上の実装とほぼ同条件?)
model.fit(X, y)
ans = model.predict(test)
print("")
print("scikit-learnのLasso")
print(model.intercept_)
print(model.coef_)
print(ans)
*/