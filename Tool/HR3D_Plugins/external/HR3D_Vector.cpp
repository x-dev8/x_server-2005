
#include "hr3d_vector.h"
#include "HR3D_Quaternion.h"

#include <math.h>

/*****************************************************************************/
/** Transforms the vector instance by a quaternion.
*
* This function transforms the vector instance by a given quaternion.
*
* @param q The quaternion to be used for the transformation.
*****************************************************************************/

void HR3D_Vector::operator*=(const HR3D_Quaternion& q)
{
	HR3D_Quaternion temp(-q.x, -q.y, -q.z, q.w);
	temp *= *this;
	temp *= q;

	x = temp.x;
	y = temp.y;
	z = temp.z;
}

/*****************************************************************************/
/** Provides access to the components of the vector instance.
*
* This function provides read and write access to the three components of the
* vector instance.
*
* @param i The index to the specific component.
*
* @return A reference to the specific component.
*****************************************************************************/

float& HR3D_Vector::operator[](unsigned int i)
{
	return (&x)[i];
}

/*****************************************************************************/
/** Provides access to the components of the vector instance.
*
* This function provides read access to the three components of the vector
* instance.
*
* @param i The index to the specific component.
*
* @return A constant reference to the specific component.
*****************************************************************************/

const float& HR3D_Vector::operator[](unsigned int i) const
{
	return (&x)[i];
}

/*****************************************************************************/
/** Equates the vector instance with another vector.
*
* This operator equates the vector instance with another vector.
*
* @param v The vector to equate the vector instance with.
*****************************************************************************/

void HR3D_Vector::operator=(const HR3D_Vector& v)
{
	x = v.x;
	y = v.y;
	z = v.z;
}

/*****************************************************************************/
/** Adds another vector to the vector instance.
*
* This operator adds another vector to the vector instance.
*
* @param v The vector to be added.
*****************************************************************************/

void HR3D_Vector::operator+=(const HR3D_Vector& v)
{
	x += v.x;
	y += v.y;
	z += v.z;
}

/*****************************************************************************/
/** Subtracts another vector from the vector instance.
*
* This operator subtracts another vector from the vector instance.
*
* @param v The vector to be subtracted.
*****************************************************************************/

void HR3D_Vector::operator-=(const HR3D_Vector& v)
{
	x -= v.x;
	y -= v.y;
	z -= v.z;
}

/*****************************************************************************/
/** Scales the vector instance.
*
* This operator scales the vector instance by multiplying its components by
* a specific factor.
*
* @param d The factor to multiply the vector components by.
*****************************************************************************/

void HR3D_Vector::operator*=(const float d)
{
	x *= d;
	y *= d;
	z *= d;
}


/*****************************************************************************/
/** Scales the vector instance.
*
* This operator scales the vector instance by dividing its components by a
* specific factor.
*
* @param d The factor to divide the vector components by.
*****************************************************************************/

void HR3D_Vector::operator/=(const float d)
{
	x /= d;
	y /= d;
	z /= d;
}

/*****************************************************************************/
/** Calculates the sum of two vectors.
*
* This operator calculates the sum of two vectors.
*
* @param v The first vector to be added.
* @param u The second vector to be added.
*
* @return The sum of the two vectors.
*****************************************************************************/

HR3D_Vector operator+(const HR3D_Vector& v, const HR3D_Vector& u)
{
	return HR3D_Vector(v.x + u.x, v.y + u.y, v.z + u.z);
}

/*****************************************************************************/
/** Calculates the difference of two vectors.
*
* This operator calculates the difference of two vectors.
*
* @param v The first vector to be added.
* @param u The second vector to be subtracted.
*
* @return The difference of the two vectors.
*****************************************************************************/

HR3D_Vector operator-(const HR3D_Vector& v, const HR3D_Vector& u)
{
	return HR3D_Vector(v.x - u.x, v.y - u.y, v.z - u.z);
}

/*****************************************************************************/
/** Calculates a scaled vector.
*
* This operator calculates the vector multiplied by a factor.
*
* @param v The vector to be scaled.
* @param d The factor to multiply the vector with.
*
* @return The scaled vector.
*****************************************************************************/

HR3D_Vector operator*(const HR3D_Vector& v, float d)
{
	return HR3D_Vector(v.x * d, v.y * d, v.z * d);
}

/*****************************************************************************/
/** Calculates a scaled vector.
*
* This operator calculates the vector multiplied by a factor.
*
* @param d The factor to multiply the vector with.
* @param v The vector to be scaled.
*
* @return The scaled vector.
*****************************************************************************/

HR3D_Vector operator*(float d, const HR3D_Vector& v)
{
	return HR3D_Vector(v.x * d, v.y * d, v.z * d);
}

/*****************************************************************************/
/** Calculates a scaled vector.
*
* This operator calculates the vector divided by a factor.
*
* @param v The vector to be scaled.
* @param d The factor to divide the vector with.
*
* @return The scaled vector.
*****************************************************************************/

HR3D_Vector operator/(const HR3D_Vector& v, float d)
{
	return HR3D_Vector(v.x / d, v.y / d, v.z / d);
}

/*****************************************************************************/
/** Calculates the dot product of two vectors.
*
* This operator calculates the dot product of two vectors.
*
* @param v The first vector.
* @param u The second vector.
*
* @return The dot product of the two vectors.
*****************************************************************************/

float operator*(const HR3D_Vector& v, const HR3D_Vector& u)
{
	return v.x * u.x + v.y * u.y + v.z * u.z;
}

/*****************************************************************************/
/** Calculates the vector product of two vectors.
*
* This operator calculates the vector product of two vectors.
*
* @param v The first vector.
* @param u The second vector.
*
* @return The vector product of the two vectors.
*****************************************************************************/

HR3D_Vector operator%(const HR3D_Vector& v, const HR3D_Vector& u)
{
	return HR3D_Vector(v.y * u.z - v.z * u.y, v.z * u.x - v.x * u.z, v.x * u.y - v.y * u.x);
}

/*****************************************************************************/
/** Interpolates the vector instance to another vector.
*
* This function interpolates the vector instance to another vector by a given
* factor.
*
* @param d The blending factor in the range [0.0, 1.0].
* @param v The vector to be interpolated to.
*****************************************************************************/

void HR3D_Vector::blend(float d, const HR3D_Vector& v)
{
	x += d * (v.x - x);
	y += d * (v.y - y);
	z += d * (v.z - z);
}

/*****************************************************************************/
/** Clears the vector instance.
*
* This function clears the vector instance.
*****************************************************************************/

void HR3D_Vector::clear()
{
	x = 0.0f;
	y = 0.0f;
	z = 0.0f;
}

/*****************************************************************************/
/** Returns the length of the vector instance.
*
* This function returns the length of the vector instance.
*
* @return The length of the vector instance.
*****************************************************************************/

float HR3D_Vector::length()
{
	return sqrtf(x * x + y * y + z * z);
}

/*****************************************************************************/
/** Normalizes the vector instance.
*
* This function normalizes the vector instance and returns its former length.
*
* @return The length of the vector instance before normalizing.
*****************************************************************************/

float HR3D_Vector::normalize()
{
	// calculate the length of the vector
	float length;
	length =sqrtf(x * x + y * y + z * z);

	// normalize the vector
	x /= length;
	y /= length;
	z /= length;

	return length;
}

/*****************************************************************************/
/** Sets new values.
*
* This function sets new values in the vector instance.
*
* @param x The x component.
* @param y The y component.
* @param z The z component.
*****************************************************************************/

void HR3D_Vector::set(float vx, float vy, float vz)
{
	x = vx;
	y = vy;
	z = vz;
}

//****************************************************************************//

float HR3D_Vector::dot( const HR3D_Vector& v )
{
	return x*v.x+y*v.y+z*v.z;
}

HR3D_Vector HR3D_Vector::cross( const HR3D_Vector& v )
{
	return HR3D_Vector( y*v.z-z*v.y, z*v.x-x*v.z, x*v.y-y*v.x );
}
