
//****************************************************************************//
// Includes                                                                   //
//****************************************************************************//

#include "hr3d_quaternion.h"
#include "hr3d_vector.h"

#include <math.h>

/*****************************************************************************/
/** Constructs the quaternion instance.
*
* This function is the default constructor of the quaternion instance.
*****************************************************************************/

HR3D_Quaternion::HR3D_Quaternion() : x(0.0f), y(0.0f), z(0.0f), w(0.0f)
{
}

/*****************************************************************************/
/** Constructs the quaternion instance.
*
* This function is a constructor of the quaternion instance.
*
* @param q The quaternion to construct this quaternion instance from.
*****************************************************************************/

HR3D_Quaternion::HR3D_Quaternion(const HR3D_Quaternion& q) : x(q.x), y(q.y), z(q.z), w(q.w)
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

HR3D_Quaternion::HR3D_Quaternion(float qx, float qy, float qz, float qw) : x(qx), y(qy), z(qz), w(qw)
{
}

/*****************************************************************************/
/** Destructs the quaternion instance.
*
* This function is the destructor of the quaternion instance.
*****************************************************************************/

HR3D_Quaternion::~HR3D_Quaternion()
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

float& HR3D_Quaternion::operator[](unsigned int index)
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

const float& HR3D_Quaternion::operator[](unsigned int index) const
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

void HR3D_Quaternion::operator=(const HR3D_Quaternion& q)
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

void HR3D_Quaternion::operator*=(const HR3D_Quaternion& q)
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

void HR3D_Quaternion::operator*=(const HR3D_Vector& v)
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

HR3D_Quaternion operator*(const HR3D_Quaternion& q, const HR3D_Quaternion& r)
{
	return HR3D_Quaternion(
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
* @param v The quaternion to be interpolated to.
*****************************************************************************/

void HR3D_Quaternion::blend(float d, const HR3D_Quaternion& q)
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

void HR3D_Quaternion::conjugate()
{
	x = -x;
	y = -y;
	z = -z;
}

/*****************************************************************************/
/** Sets new values.
*
* This function sets new values in the quaternion instance.
*
* @param qx The x component.
* @param qy The y component.
* @param qz The z component.
* @param qw The w component.
*****************************************************************************/

void HR3D_Quaternion::set(float qx, float qy, float qz, float qw)
{
	x = qx;
	y = qy;
	z = qz;
	w = qw;
}

//****************************************************************************//
