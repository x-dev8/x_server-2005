#pragma once

#include "Me3d.h"
#include "Me3d/Quaternion.h"
#include "MeFoundation/MeAllocatedObject.h"
//****************************************************************************//
// Forward declarations                                                       //
//****************************************************************************//

//class Quaternion;

//****************************************************************************//
// Class declaration                                                          //
//****************************************************************************//

/*****************************************************************************/
/** The vector class.
*****************************************************************************/

class ENGINEAPI Vector : public MeCommonAllocObj<Vector>
{
	// member variables
public:
	float x;
	float y;
	float z;
	
	// constructors/destructor
public:
	Vector():x(0.0f), y(0.0f), z(0.0f){}
	Vector(const Vector& v): x(v.x), y(v.y), z(v.z){}
	Vector(float vx, float vy, float vz): x(vx), y(vy), z(vz){}
	~Vector(){}
	
	static const Vector ZERO;
	static const Vector UNIT_X;
	static const Vector UNIT_Y;
	static const Vector UNIT_Z;
	static const Vector UNIT_ALL;

	// member functions
public:
	inline float& operator[](unsigned int i);
	inline const float& operator[](unsigned int i) const;
	inline void operator=(const Vector& v);
	inline void operator+=(const Vector& v);
	inline void operator-=(const Vector& v);
	inline void operator*=(const float d);
	inline void operator*=(const Quaternion& q);
	inline void operator/=(const float d);
	inline bool operator==(const Vector& v);
	inline bool operator!=(const Vector& v);
	inline friend Vector operator+(const Vector& v, const Vector& u);
	inline friend Vector operator-(const Vector& v, const Vector& u);
	inline friend Vector operator*(const Vector& v, const float d);
	inline friend Vector operator*(const float d, const Vector& v);
	inline friend Vector operator/(const Vector& v, const float d);
	inline friend float operator*(const Vector& v, const Vector& u);
	inline friend Vector operator%(const Vector& v, const Vector& u);
	inline void blend(float d, const Vector& v);
	inline void clear();
	inline float length();
	inline float lengthsq();
	inline float normalize();
	inline void set(float vx, float vy, float vz);
	inline float dot( const Vector& v );
	inline Vector cross( const Vector& v );
	inline bool positionEquals(const Vector& rhs, float tolerance = 1e-04) const;
	inline Vector crossProduct( const Vector& rkVector ) const;
	inline Vector operator-() const;

};
//-----------------------------------------------------------------------
// 
class Vector2 : public MeCommonAllocObj<Vector2>
{
public:
	float x;
	float y;
public:
	Vector2() :x(0.f), y(0.f) {}
	Vector2( float _x, float _y ) :x(_x), y(_y) {}
	void operator = ( const Vector2& v )
	{
		x = v.x;
		y = v.y;
	};

	float length()
	{
		return sqrtf(x * x + y * y );
	}


	Vector2& operator*=(const Vector2& vec)
	{
		x *= vec.x;
		y *= vec.y;

		return *this;
	}

	Vector2& operator/=(const Vector2& vec)
	{
		x /= vec.x;
		y /= vec.y;

		return *this;
	}

	Vector2& operator+=(const Vector2& vec)
	{
		x += vec.x;
		y += vec.y;

		return *this;
	}

	Vector2& operator-=(const Vector2& vec)
	{
		x -= vec.x;
		y -= vec.y;

		return *this;
	}

	Vector2	operator+(const Vector2& vec) const
	{
		return Vector2(x + vec.x, y + vec.y);
	}

	Vector2	operator-(const Vector2& vec) const
	{
		return Vector2(x - vec.x, y - vec.y);
	}

	Vector2	operator*(const Vector2& vec) const
	{
		return Vector2(x * vec.x, y * vec.y);
	}

	bool positionEquals(const Vector2& rhs, float tolerance = 1e-04) const
	{
		return (fabs(rhs.x-x) <= tolerance) &&
			(fabs(rhs.y-y) <= tolerance);
	}

	bool	operator==(const Vector2& vec) const
	{
		//return ((x == vec.x) && (y == vec.y));
		return positionEquals(vec);
	}

	bool	operator!=(const Vector2& vec) const
	{
		//return !(operator==(vec));
		return !positionEquals(vec);
	}

	Vector2 operator*(const int scale) const
	{
		return Vector2( x * scale, y * scale );
	}

	Vector2 normalize(float Tolerance=1.e-8)
	{
		const FLOAT Mag = length();
		if(Mag < Tolerance)
		{
			x = 0.0f;
			y = 0.0f;
		}
		else
		{
			const FLOAT RecipMag = 1.f/Mag;
			x *= RecipMag;
			y *= RecipMag;
		}
		return Vector2( x, y );
	}

	Vector2 operator-() const
	{
		return Vector2(-x, -y);
	}
};

#include "Vector.inl"