#pragma once

//****************************************************************************//
// Forward declarations                                                       //
//****************************************************************************//

class HR3D_Quaternion;

//****************************************************************************//
// Class declaration                                                          //
//****************************************************************************//

/*****************************************************************************/
/** The vector class.
*****************************************************************************/

class HR3D_Vector
{
	// member variables
public:
	float x;
	float y;
	float z;
	
	// constructors/destructor
public:
	HR3D_Vector():x(0.0f), y(0.0f), z(0.0f){}
	HR3D_Vector(const HR3D_Vector& v): x(v.x), y(v.y), z(v.z){}
	HR3D_Vector(float vx, float vy, float vz): x(vx), y(vy), z(vz){}
	~HR3D_Vector(){}
	
	// member functions
public:
	float& operator[](unsigned int i);
	const float& operator[](unsigned int i) const;
	void operator=(const HR3D_Vector& v);
	void operator+=(const HR3D_Vector& v);
	void operator-=(const HR3D_Vector& v);
	void operator*=(const float d);
	void operator*=(const HR3D_Quaternion& q);
	void operator/=(const float d);
	friend HR3D_Vector operator+(const HR3D_Vector& v, const HR3D_Vector& u);
	friend HR3D_Vector operator-(const HR3D_Vector& v, const HR3D_Vector& u);
	friend HR3D_Vector operator*(const HR3D_Vector& v, const float d);
	friend HR3D_Vector operator*(const float d, const HR3D_Vector& v);
	friend HR3D_Vector operator/(const HR3D_Vector& v, const float d);
	friend float operator*(const HR3D_Vector& v, const HR3D_Vector& u);
	friend HR3D_Vector operator%(const HR3D_Vector& v, const HR3D_Vector& u);
	void blend(float d, const HR3D_Vector& v);
	void clear();
	float length();
	float normalize();
	void set(float vx, float vy, float vz);
	float dot( const HR3D_Vector& v );
	HR3D_Vector cross( const HR3D_Vector& v );
};
//-----------------------------------------------------------------------
// 
class HR3D_Vector2
{
public:
	float x;
	float y;
public:
	HR3D_Vector2(){ x = 0; y = 0; }
	HR3D_Vector2( float _x, float _y ){ x = _x; y = _y; }
	void operator = ( const HR3D_Vector2& v )
	{
		x = v.x;
		y = v.y;
	}
};

class HR3D_Ray
{
public:
	HR3D_Vector from;
	HR3D_Vector dir;
};

class HR3D_Point2
{
public:
	int x;
	int y;
};
