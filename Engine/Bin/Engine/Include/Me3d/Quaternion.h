
#ifndef _quaternion_h
#define _quaternion_h
#include "Me3d.h"
//****************************************************************************//
// Forward declarations                                                       //
//****************************************************************************//

class Vector;

//****************************************************************************//
// Class declaration                                                          //
//****************************************************************************//

/*****************************************************************************/
/** The quaternion class.
*****************************************************************************/

class ENGINEAPI Quaternion : public MeCommonAllocObj<Quaternion>
{
	// member variables
public:
	float x;
	float y;
	float z;
	float w;
	
	// constructors/destructor
public:
	Quaternion();
	Quaternion(const Quaternion& q);
	Quaternion(float qx, float qy, float qz, float qw);
	~Quaternion();
	
	// member functions	
public:
	// cutoff for sine near zero
	static const float ms_fEpsilon;
	static const Quaternion ZERO;

	float& operator[](unsigned int index);
	const float& operator[](unsigned int index) const;
	void operator=(const Quaternion& q);
	void operator*=(const Quaternion& q);
	void operator*=(const Vector& v);
	Quaternion operator- () const;
	Quaternion operator* (float fScalar) const;
	Quaternion operator+ (const Quaternion& rkQ) const;
	Quaternion operator- (const Quaternion& rkQ) const;
	friend Quaternion operator*(const Quaternion& q, const Quaternion& r);
	// rotation of a vector by a quaternion
	Vector operator* (const Vector& rkVector) const;
	inline bool operator== (const Quaternion& rhs) const
	{
		return (rhs.x == x) && (rhs.y == y) &&
			(rhs.z == z) && (rhs.w == w);
	}
	void blend(float d, const Quaternion& q);
	void conjugate();
	void set(float qx, float qy, float qz, float qw);
	/// Equality with tolerance (tolerance is max angle difference)
	bool equals(const Quaternion& rhs, const float tolerance = 1e-03) const;
	float dot (const Quaternion& rkQ) const;
	// spherical quadratic interpolation 球面二次插值
	static Quaternion Squad (float fT, const Quaternion& rkP,
		const Quaternion& rkA, const Quaternion& rkB,
		const Quaternion& rkQ, bool shortestPath = false);
	// spherical linear interpolation 球面线性插值
	static Quaternion Slerp (float fT, const Quaternion& rkP,
		const Quaternion& rkQ, bool shortestPath = false);
	// spherical linear matrix interpolation 矩阵Slerp插值
	static Quaternion SlerpMatrix (float fT, const Quaternion& rkP,
		const Quaternion& rkQ);
	// Not bad, simple to understand and quite accurate
	// The arccos and sin can be cut down to improve speed over accuracy.
	static Quaternion SlerpDirect( float t, const Quaternion& mA, const Quaternion& mB );
	// Improvement on the simple lerp and renormalise, accurate but slow.
	static Quaternion SlerpRenormal( float t, const Quaternion& mA, const Quaternion& mB );
	// If you have the luxury of error tolerence, use this!
	// Fine for fingers, toes and all small joints. accuracy 4-8 bits
	static Quaternion SlerpSimpleRenormal( float t, const Quaternion& mA, const Quaternion& mB );
	float NormSqr () const;  // squared-length
	// Normalises this quaternion, and returns the previous length
	float normalise(void); 
	Quaternion UnitInverse () const;  // apply to non-zero quaternion
	Quaternion Log () const;
	Quaternion Exp () const;
	static Quaternion Quaternion::UnitInverse(const Quaternion& p)
	{
		// assert:  p is unit length
		return Quaternion(-p.x, -p.y, -p.z, p.w);
	}
protected:
};


#endif