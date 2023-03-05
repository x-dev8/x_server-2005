
//****************************************************************************//
// Includes                                                                   //
//****************************************************************************//

#include "Me3d/Quaternion.h"
#include "Me3d/Vector.h"

const float Quaternion::ms_fEpsilon = 1e-03;
const Quaternion Quaternion::ZERO(0.0,0.0,0.0,0.0);

/*****************************************************************************/
/** Constructs the quaternion instance.
*
* This function is the default constructor of the quaternion instance.
*****************************************************************************/

Quaternion::Quaternion() : x(0.0f), y(0.0f), z(0.0f), w(0.0f)
{
}

/*****************************************************************************/
/** Constructs the quaternion instance.
*
* This function is a constructor of the quaternion instance.
*
* @param q The quaternion to construct this quaternion instance from.
*****************************************************************************/

Quaternion::Quaternion(const Quaternion& q) : x(q.x), y(q.y), z(q.z), w(q.w)
{
}

/*****************************************************************************/
/** Constructs the quaternion instance.
*
* This function is a constructor of the quaternion instance.
*
* @param qx The x component.
* @param qy The y component.
* @param qz The z component.
* @param qw The w component.
*****************************************************************************/

Quaternion::Quaternion(float qx, float qy, float qz, float qw) : x(qx), y(qy), z(qz), w(qw)
{
}

/*****************************************************************************/
/** Destructs the quaternion instance.
*
* This function is the destructor of the quaternion instance.
*****************************************************************************/

Quaternion::~Quaternion()
{
}

/*****************************************************************************/
/** Provides access to the components of the quaternion instance.
*
* This function provides read and write access to the three components of the
* quaternion instance.
*
* @param index The index to the specific component.
*
* @return A reference to the specific component.
*****************************************************************************/

float& Quaternion::operator[](unsigned int index)
{
	return (&x)[index];
}

/*****************************************************************************/
/** Provides access to the components of the quaternion instance.
*
* This function provides read access to the three components of the quaternion
* instance.
*
* @param index The index to the specific component.
*
* @return A constant reference to the specific component.
*****************************************************************************/

const float& Quaternion::operator[](unsigned int index) const
{
	return (&x)[index];
}

/*****************************************************************************/
/** Equates the quaternion instance with another quaternion.
*
* This operator equates the quaternion instance with another quaternion.
*
* @param q The quaternion to equate the quaternion instance with.
*****************************************************************************/

void Quaternion::operator=(const Quaternion& q)
{
	x = q.x;
	y = q.y;
	z = q.z;
	w = q.w;
}

/*****************************************************************************/
/** Multiplies another quaternion to the quaternion instance.
*
* This operator multiplies another quaternion to the quaternion instance.
*
* @param q The quaternion to be multiplied.
*****************************************************************************/

void Quaternion::operator*=(const Quaternion& q)
{
	float qx, qy, qz, qw;
	qx = x;
	qy = y;
	qz = z;
	qw = w;
	
	x = qw * q.x + qx * q.w + qy * q.z - qz * q.y;
	y = qw * q.y - qx * q.z + qy * q.w + qz * q.x;
	z = qw * q.z + qx * q.y - qy * q.x + qz * q.w;
	w = qw * q.w - qx * q.x - qy * q.y - qz * q.z;
}

/*****************************************************************************/
/** Multiplies a vector to the quaternion instance.
*
* This operator multiplies a vector to the quaternion instance.
*
* @param v The vector to be multiplied.
*****************************************************************************/

void Quaternion::operator*=(const Vector& v)
{
	float qx, qy, qz, qw;
	qx = x;
	qy = y;
	qz = z;
	qw = w;
	
	x = qw * v.x            + qy * v.z - qz * v.y;
	y = qw * v.y - qx * v.z            + qz * v.x;
	z = qw * v.z + qx * v.y - qy * v.x;
	w =          - qx * v.x - qy * v.y - qz * v.z;
}

/*****************************************************************************/
/** Calculates the product of two quaternions.
*
* This operator calculates the product of two quaternions.
*
* @param q The first quaternion.
* @param r The second quaternion.
*
* @return The product of the two quaternions.
*****************************************************************************/

Quaternion operator*(const Quaternion& q, const Quaternion& r)
{
	return Quaternion(
		r.w * q.x + r.x * q.w + r.y * q.z - r.z * q.y,
		r.w * q.y - r.x * q.z + r.y * q.w + r.z * q.x,
		r.w * q.z + r.x * q.y - r.y * q.x + r.z * q.w,
		r.w * q.w - r.x * q.x - r.y * q.y - r.z * q.z
		);
}

/*****************************************************************************/
/** Interpolates the quaternion instance to another quaternion.
*
* This function interpolates the quaternion instance to another quaternion by
* a given factor.
*
* @param d The blending factor in the range [0.0, 1.0].
* @param q The quaternion to be interpolated to.
*****************************************************************************/

void Quaternion::blend(float d, const Quaternion& q)
{
	float norm;
	norm = x * q.x + y * q.y + z * q.z + w * q.w;
	
	bool bFlip;
	bFlip = false;
	
	if(norm < 0.0f)
	{
		norm = -norm;
		bFlip = true;
	}
	
	float inv_d;
	if(1.0f - norm < 0.000001f)
	{
		inv_d = 1.0f - d;
	}
	else
	{
		float theta;
		theta = acosf(norm);
		
		float s;
		s = 1.0f / sinf(theta);
		
		inv_d = sinf((1.0f - d) * theta) * s;
		d = sinf(d * theta) * s;
	}
	
	if(bFlip)
	{
		d = -d;
	}
	
	x = inv_d * x + d * q.x;
	y = inv_d * y + d * q.y;
	z = inv_d * z + d * q.z;
	w = inv_d * w + d * q.w;
}

/*****************************************************************************/
/** Conjugates the quaternion instance.
*
* This function conjugates the quaternion instance.
*****************************************************************************/

void Quaternion::conjugate()
{
	x = -x;
	y = -y;
	z = -z;
}

/*****************************************************************************/
/** Sets MeNew values.
*
* This function sets MeNew values in the quaternion instance.
*
* @param qx The x component.
* @param qy The y component.
* @param qz The z component.
* @param qw The w component.
*****************************************************************************/

void Quaternion::set(float qx, float qy, float qz, float qw)
{
	x = qx;
	y = qy;
	z = qz;
	w = qw;
}

//****************************************************************************//
bool Quaternion::equals( const Quaternion& rhs, float tolerance /*= 1e-03*/ ) const
{
	//float fCos = dot(rhs);
	//float angle = acosf(fCos);

	//return (fabs(angle) <= tolerance)
	//	|| (fabs(angle - D3DX_PI) <= tolerance);
	return (fabs(x - rhs.x) < tolerance &&
			fabs(y - rhs.y) < tolerance &&
			fabs(z - rhs.z) < tolerance &&
			fabs(w - rhs.w) < tolerance
			);
}
//****************************************************************************//
float Quaternion::dot (const Quaternion& rkQ) const
{
	return w*rkQ.w+x*rkQ.x+y*rkQ.y+z*rkQ.z;
}
//****************************************************************************//
Quaternion Quaternion::Squad (float fT,
							  const Quaternion& rkP, const Quaternion& rkA,
							  const Quaternion& rkB, const Quaternion& rkQ, bool shortestPath)
{
	float fSlerpT = 2.0f*fT*(1.0f-fT);
	Quaternion kSlerpP = Slerp(fT, rkP, rkQ, shortestPath);
	Quaternion kSlerpQ = Slerp(fT, rkA, rkB);
	return Slerp(fSlerpT, kSlerpP ,kSlerpQ);
}
//****************************************************************************//
Quaternion Quaternion::Slerp (float fT, const Quaternion& rkP,
							  const Quaternion& rkQ, bool shortestPath)
{
	float fCos = rkP.dot(rkQ);
	Quaternion rkT;

	// Do we need to invert rotation?
	if (fCos < 0.0f && shortestPath)
	{
		fCos = -fCos;
		rkT = -rkQ;
	}
	else
	{
		rkT = rkQ;
	}

	if (fabs(fCos) < 1 - ms_fEpsilon)
	{
		// Standard case (slerp)
		float fSin = sqrt(1 - fCos*fCos);
		float fAngle = atan2(fSin, fCos);
		float fInvSin = 1.0f / fSin;
		float fCoeff0 = sin((1.0f - fT) * fAngle) * fInvSin;
		float fCoeff1 = sin(fT * fAngle) * fInvSin;
		return rkP * fCoeff0 + rkT * fCoeff1;
	}
	else
	{
		// There are two situations:
		// 1. "rkP" and "rkQ" are very close (fCos ~= +1), so we can do a linear
		//    interpolation safely.
		// 2. "rkP" and "rkQ" are almost inverse of each other (fCos ~= -1), there
		//    are an infinite number of possibilities interpolation. but we haven't
		//    have method to fix this case, so just use linear interpolation here.
		Quaternion t = rkP * (1.0f - fT) + rkT * fT;
		// taking the complement requires renormalisation
		t.normalise();
		return t;
	}
}
//****************************************************************************//
Quaternion Quaternion::operator- () const
{
	return Quaternion(-x,-y,-z,-w);
}
//****************************************************************************//
Quaternion Quaternion::operator* (float fScalar) const
{
	return Quaternion(fScalar*x,fScalar*y,fScalar*z,fScalar*w);
}
//****************************************************************************//
Quaternion Quaternion::operator+ (const Quaternion& rkQ) const
{
	return Quaternion(x+rkQ.x,y+rkQ.y,z+rkQ.z,w+rkQ.w);
}
//****************************************************************************//
Quaternion Quaternion::operator- (const Quaternion& rkQ) const
{
	return Quaternion(x-rkQ.x,y-rkQ.y,z-rkQ.z,w-rkQ.w);
}
//****************************************************************************//
float Quaternion::normalise(void)
{
	float len = sqrt(NormSqr());
	float factor = 1.0f / len;
	*this = *this * factor;
	return len;
}
//****************************************************************************//
float Quaternion::NormSqr () const
{
	return w*w+x*x+y*y+z*z;
}
//****************************************************************************//
Quaternion Quaternion::UnitInverse () const
{
	float fNormSqr = w*w+x*x+y*y+z*z;
	if ( fNormSqr > 0.0 )
	{
		float fInvNorm = 1.0f/sqrt(fNormSqr);
		return Quaternion(-x*fInvNorm,-y*fInvNorm,-z*fInvNorm,w*fInvNorm);
	}
	else
	{
		// return an invalid result to flag the error
		return ZERO;
	}
}
//****************************************************************************//
Quaternion Quaternion::Log () const
{
	// If q = cos(A)+sin(A)*(x*i+y*j+z*k) where (x,y,z) is unit length, then
	// log(q) = A*(x*i+y*j+z*k).  If sin(A) is near zero, use log(q) =
	// sin(A)*(x*i+y*j+z*k) since sin(A)/A has limit 1.

	Quaternion kResult;
	kResult.w = 0.0;

	if ( fabs(w) < 1.0 )
	{
		float fAngle ( cos(w) );
		float fSin = sin(fAngle);
		if ( fabs(fSin) >= ms_fEpsilon )
		{
			float fCoeff = fAngle/fSin;
			kResult.x = fCoeff*x;
			kResult.y = fCoeff*y;
			kResult.z = fCoeff*z;
			return kResult;
		}
	}

	kResult.x = x;
	kResult.y = y;
	kResult.z = z;

	return kResult;
}
//****************************************************************************//
Quaternion Quaternion::Exp () const
{
	// If q = A*(x*i+y*j+z*k) where (x,y,z) is unit length, then
	// exp(q) = cos(A)+sin(A)*(x*i+y*j+z*k).  If sin(A) is near zero,
	// use exp(q) = cos(A)+A*(x*i+y*j+z*k) since A/sin(A) has limit 1.

	float fAngle ( sqrt(x*x+y*y+z*z) );
	float fSin = sin(fAngle);

	Quaternion kResult;
	kResult.w = cos(fAngle);

	if ( fabs(fSin) >= ms_fEpsilon )
	{
		float fCoeff = fSin/fAngle;
		kResult.x = fCoeff*x;
		kResult.y = fCoeff*y;
		kResult.z = fCoeff*z;
	}
	else
	{
		kResult.x = x;
		kResult.y = y;
		kResult.z = z;
	}

	return kResult;
}
//****************************************************************************//
Vector Quaternion::operator* (const Vector& v) const
{
	// nVidia SDK implementation
	//Vector uv, uuv;
	//Vector qvec(x, y, z);
	//uv = qvec.crossProduct(v);
	//uuv = qvec.crossProduct(uv);
	//uv *= (2.0f * w);
	//uuv *= 2.0f;

	//return v + uv + uuv;
	float qx, qy, qz, qw;
	qx = x;
	qy = y;
	qz = z;
	qw = w;

	Vector rv;
	rv.x = qw * v.x            + qy * v.z - qz * v.y;
	rv.y = qw * v.y - qx * v.z            + qz * v.x;
	rv.z = qw * v.z + qx * v.y - qy * v.x;
	//w =          - qx * v.x - qy * v.y - qz * v.z;
	return rv;
}

static float Sqrt( float x ) { return sqrtf( x ); } // use a native instruction here
static float RecipSqrt( float x ) { return 1.0f / sqrtf( x ); } // use a native instruction here
static float Recip( float x ) { return 1.0f / x; }
static float Max( float x, float y ) { return ( x + y + fabsf( x - y ) ) * 0.5f; }
static float Min( float x, float y ) { return ( x + y - fabsf( x - y ) ) * 0.5f; }
static float Arccos( float x ) { return acosf( x ); }
static float Sin( float x ) { return sinf( x ); }
static float ArccosFast( float x ) { return Sqrt( 2.218480716f - 2.441884385f * x + .2234036692f * x * x )  - Sqrt( 2.218480716f + 2.441884385f * x + .2234036692f * x * x ) + 1.570796327f + .6391287330f * x; }
static float SinFast( float x ) { return -.67044e-5f + ( 1.000271283f + (  -.17990919e-2f + (  -.1621365372f + (  -.556099983e-2f + ( .1198086481e-1f - .1271209213e-2f * x ) * x ) * x ) * x ) * x ) * x; }
Quaternion Quaternion::SlerpMatrix( float t, const Quaternion& mA, const Quaternion& mB )
{
	float adotb = mA.x * mB.x + mA.y * mB.y + mA.z * mB.z + mA.w * mB.w;
	float mRecipOnePlusAdotB = 1.0f / (1 + adotb);
	float mC1 = 1.570994357f+(.5642929859f+( -.1783657717f+.4319949352e-1f*adotb)*adotb)*adotb;
	float mC3 = -.6461396382f+(.5945657936f+(.8610323953e-1f -.3465122928e-1f*adotb)*adotb)*adotb;
	float mC5 = .7949823521e-1f+( -.1730436931f+(.1079279599f -.1439397801e-1f*adotb)*adotb)*adotb;
	float mC7 = -.4354102836e-2f+(.1418962736e-1f+( -.1567189691e-1f+.5848706227e-2f*adotb)*adotb)*adotb;

	float T = 1 - t, t2 = t * t, T2 = T * T;
	float alpha = (mC1+(mC3+(mC5+mC7*T2)*T2)*T2)*T * mRecipOnePlusAdotB;
	float beta = (mC1+(mC3+(mC5+mC7*t2)*t2)*t2)*t * mRecipOnePlusAdotB;
	return Quaternion( alpha * mA.x + beta * mB.x, alpha * mA.y + beta * mB.y, alpha * mA.z + beta * mB.z, alpha * mA.w + beta * mB.w );
}

Quaternion Quaternion::SlerpDirect( float t, const Quaternion& mA, const Quaternion& mB )
{
	float mTheta;
	float mRecipSqrt;	
	float adotb = mA.x * mB.x + mA.y * mB.y + mA.z * mB.z + mA.w * mB.w;
	adotb = Min( adotb, 0.995f );
	float even = 2.218480716f + .2234036692f * adotb * adotb;
	float odd = 2.441884385f * adotb;
	mTheta = sqrtf( even - odd ) - sqrtf( even + odd ) + 1.570796327f + .6391287330f * adotb;
	mRecipSqrt = 1.0f / sqrtf( 1 - adotb * adotb );

	float A = ( 1 - t ) * mTheta - 1.570796327f; A = A * A;
	float B = t * mTheta - 1.570796327f; B = B * B;
	float sinA = .9999999535f+(-.4999990537f+(.4166358517e-1f+(-.1385370794e-2f+.2315401401e-4f*A)*A)*A)*A;
	float sinB = .9999999535f+(-.4999990537f+(.4166358517e-1f+(-.1385370794e-2f+.2315401401e-4f*B)*B)*B)*B;
	float alpha = sinA * mRecipSqrt;
	float beta = sinB * mRecipSqrt;
	return Quaternion( alpha * mA.x + beta * mB.x, alpha * mA.y + beta * mB.y, alpha * mA.z + beta * mB.z, alpha * mA.w + beta * mB.w );
}

Quaternion Quaternion::SlerpRenormal( float t, const Quaternion& mA, const Quaternion& mB )
{
	float mTheta;
	float adotb = mA.x * mB.x + mA.y * mB.y + mA.z * mB.z + mA.w * mB.w;
	adotb = Min( adotb, 0.995f );
	float even = 2.218480716f + .2234036692f * adotb * adotb;
	float odd = 2.441884385f * adotb;
	mTheta = Sqrt( even - odd ) - Sqrt( even + odd ) + 1.570796327f + .6391287330f * adotb;

	float T = 1 - t, t2 = t * t, T2 = T * T;
	float A = ( 1 - t ) * mTheta;
	float B = t * mTheta;
	float sinA =  -.67044e-5f + ( 1.000271283f + (  -.17990919e-2f + (  -.1621365372f + (  -.556099983e-2f + ( .1198086481e-1f - .1271209213e-2f * A ) * A ) * A ) * A ) * A ) * A;
	float sinB =  -.67044e-5f + ( 1.000271283f + (  -.17990919e-2f + (  -.1621365372f + (  -.556099983e-2f + ( .1198086481e-1f - .1271209213e-2f * B ) * B ) * B ) * B ) * B ) * B;
	float recipAB = Recip( sinA + sinB );
	float alpha = sinA * recipAB;
	float beta = sinB * recipAB;

	// renormalise
	Quaternion result( alpha * mA.x + beta * mB.x, alpha * mA.y + beta * mB.y, alpha * mA.z + beta * mB.z, alpha * mA.w + beta * mB.w );
	float recip = RecipSqrt( result.x * result.x + result.y * result.y + result.z * result.z + result.w * result.w );
	return Quaternion( result.x * recip, result.y * recip, result.z * recip, result.w * recip );
}

Quaternion Quaternion::SlerpSimpleRenormal( float t, const Quaternion& mA, const Quaternion& mB )
{
	float alpha = 1 - t;
	float beta = t;
	Quaternion result( alpha * mA.x + beta * mB.x, alpha * mA.y + beta * mB.y, alpha * mA.z + beta * mB.z, alpha * mA.w + beta * mB.w );
	float recip = RecipSqrt( result.x * result.x + result.y * result.y + result.z * result.z + result.w * result.w );
	return Quaternion( result.x * recip, result.y * recip, result.z * recip, result.w * recip );
}
