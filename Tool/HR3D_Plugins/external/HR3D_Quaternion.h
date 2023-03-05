
#ifndef _HR3D_quaternion_h
#define _HR3D_quaternion_h

//****************************************************************************//
// Forward declarations                                                       //
//****************************************************************************//

class HR3D_Vector;

//****************************************************************************//
// Class declaration                                                          //
//****************************************************************************//

/*****************************************************************************/
/** The quaternion class.
*****************************************************************************/

class  HR3D_Quaternion
{
	// member variables
public:
	float x;
	float y;
	float z;
	float w;
	
	// constructors/destructor
public:
	HR3D_Quaternion();
	HR3D_Quaternion(const HR3D_Quaternion& q);
	HR3D_Quaternion(float qx, float qy, float qz, float qw);
	~HR3D_Quaternion();
	
	// member functions	
public:
	float& operator[](unsigned int index);
	const float& operator[](unsigned int index) const;
	void operator=(const HR3D_Quaternion& q);
	void operator*=(const HR3D_Quaternion& q);
	void operator*=(const HR3D_Vector& v);
	friend HR3D_Quaternion operator*(const HR3D_Quaternion& q, const HR3D_Quaternion& r);
	void blend(float d, const HR3D_Quaternion& q);
	void conjugate();
	void set(float qx, float qy, float qz, float qw);
};


#endif