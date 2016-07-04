//--------------------------------------------------//
// File Name: Vect.h                              //
// Function: Vect calculation                     //
// Copyright(C) 2016 shoarai                        //
// The MIT License (MIT)                            //
//--------------------------------------------------//
#ifndef _Vect_H_
#define _Vect_H_

//------------------------------------------//
//              インクルード              		//
//------------------------------------------//

using namespace std;

namespace arith {

	//------------------------------------------//
	//              ク　ラ　ス                    //
	//------------------------------------------//
	class Vect{
	public:
	    Vect();                                   // コンストラクタ
	    Vect(                                     // コンストラクタ
		const double &x,
		const double &y,
		const double &z);
	    inline double getx() const;                 // ベクトル成分xの取得
	    inline double gety() const;                 // ベクトル成分yの取得
	    inline double getz() const;                 // ベクトル成分zの取得
	    void    set(                                // ベクトル成分の設定
		const double &x,
		const double &y,
		const double &z);
	    inline void setx(const double &x);          // ベクトルx成分の設定
	    inline void sety(const double &y);          // ベクトルy成分の設定
	    inline void setz(const double &z);          // ベクトルz成分の設定
	    Vect  operator+ (const Vect &vecArg);   // ベクトルの加算
	    Vect& operator+=(const Vect &vecArg);
	    Vect  operator- (const Vect &vecArg);   // ベクトルの減算
	    Vect& operator-=(const Vect &vecArg);
	    Vect  operator* (const double &val);      // 数値の乗算
	    Vect& operator*=(const double &val);
	    Vect  operator/ (const double &val);      // 数値の除算
	    Vect& operator/=(const double &val);
	    Vect  operator* (const Vect &vecArg);   // ベクトルの外積
	    double  operator% (const Vect &vecArg);   // ベクトルの内積
	    double  norm() const;                       // ノルム計算
	    Vect  normalize() const;                  // ベクトル正規化

	private:
	    double m_x;     // x成分
	    double m_y;     // y成分
	    double m_z;     // z成分
	};

	//------------------------------------------//
	//              インライン関数             //
	//------------------------------------------//
	// ベクトル成分xの取得
	inline double Vect::getx() const
	{
	    return m_x;
	}

	// ベクトル成分yの取得
	inline double Vect::gety() const
	{
	    return m_y;
	}

	// ベクトル成分zの取得
	inline double Vect::getz() const
	{
	    return m_z;
	}

	// ベクトル成分xの設定
	inline void Vect::setx(const double &x)
	{
	    m_x = x;
	}

	// ベクトル成分yの設定
	inline void Vect::sety(const double &y)
	{
	    m_y = y;
	}

	// ベクトル成分zの設定
	inline void Vect::setz(const double &z)
	{
	    m_z = z;
	}


	//------------------------------------------//
	//              関           数              //
	//------------------------------------------//
	// コンストラクタ
	Vect::Vect()
	    : m_x(0)
	    , m_y(0)
	    , m_z(0)
	{
	    // 処理なし
	}

	// コンストラクタ
	Vect::Vect(
	    const double &x,
	    const double &y,
	    const double &z)
	    : m_x(x)
	    , m_y(y)
	    , m_z(z)
	{
	    // 処理なし
	}

	// ベクトル成分の設定
	void Vect::set(
	    const double &x,
	    const double &y,
	    const double &z)
	{
	    m_x = x;
	    m_y = y;
	    m_z = z;
	}

	// ベクトルの加算
	Vect Vect::operator+(const Vect &vecArg)
	{
	    Vect vecAns;
	    vecAns.m_x = m_x + vecArg.m_x;
	    vecAns.m_y = m_y + vecArg.m_y;
	    vecAns.m_z = m_z + vecArg.m_z;

	    return vecAns;
	}

	// ベクトルの加算
	Vect& Vect::operator+=(const Vect &vecArg)
	{
	    m_x += vecArg.m_x;
	    m_y += vecArg.m_y;
	    m_z += vecArg.m_z;

	    return *this;
	}

	// ベクトルの減算
	Vect Vect::operator-(const Vect &vecArg)
	{
	    Vect vecAns;
	    vecAns.m_x = m_x - vecArg.m_x;
	    vecAns.m_y = m_y - vecArg.m_y;
	    vecAns.m_z = m_z - vecArg.m_z;

	    return vecAns;
	}

	// ベクトルの減算
	Vect& Vect::operator-=(const Vect &vecArg)
	{
	    m_x -= vecArg.m_x;
	    m_y -= vecArg.m_y;
	    m_z -= vecArg.m_z;

	    return *this;
	}

	// 数値の乗算
	Vect Vect::operator*(const double &val)
	{
	    Vect vecAns;
	    vecAns.m_x = m_x * val;
	    vecAns.m_y = m_y * val;
	    vecAns.m_z = m_z * val;

	    return vecAns;
	}

	// 数値の乗算
	Vect& Vect::operator*=(const double &val)
	{
	    m_x *= val;
	    m_y *= val;
	    m_z *= val;

	    return *this;
	}

	// 数値の除算
	Vect Vect::operator/(const double &val)
	{
	    Vect vecAns;
	    vecAns.m_x = m_x / val;
	    vecAns.m_y = m_y / val;
	    vecAns.m_z = m_z / val;

	    return vecAns;
	}

	// 数値の除算
	Vect& Vect::operator/=(const double &val)
	{
	    m_x /= val;
	    m_y /= val;
	    m_z /= val;

	    return *this;
	}

	// ベクトルの外積
	Vect Vect::operator*(const Vect &vecArg)
	{
	    Vect vecAns;
	    vecAns.m_x = m_y * vecArg.m_z - m_z * vecArg.m_y;
	    vecAns.m_y = m_z * vecArg.m_x - m_x * vecArg.m_z;
	    vecAns.m_z = m_x * vecArg.m_y - m_y * vecArg.m_x;

	    return vecAns;
	}

	// ベクトルの内積
	double Vect::operator%(const Vect &vecArg)
	{
	    return (m_x * vecArg.getx() + m_y * vecArg.gety() + m_z * vecArg.getz());
	}

	// ノルム計算
	double Vect::norm() const
	{
	    return sqrt((m_x * m_x) + (m_y * m_y) + (m_z * m_z));
	}

	// ベクトル正規化
	Vect Vect::normalize() const
	{
	    Vect vecAns = *this;
	    vecAns /= vecAns.norm();

	    return vecAns;
	}

}

#endif // _Vect_H_
