#ifndef _quadric_h
#define _quadric_h

//----------------------------------------------------------------------------//
// Class declaration                                                          //
//----------------------------------------------------------------------------//

class Quadric
{
// member variables
protected:
	double m_aa, m_ab, m_ac, m_ad;
	double       m_bb, m_bc, m_bd;
	double             m_cc, m_cd;
	double                   m_dd;
	double m_area;

// constructors/destructor
public:
	Quadric();
	Quadric(double nx, double ny, double nz, double d, double area);
	Quadric(double x1, double y1, double z1, double x2, double y2, double z2, double nx, double ny, double nz);
	Quadric(const Quadric& q);
	virtual ~Quadric();

// member functions
public:
	void Add(const Quadric& q);
	double Evaluate(double x, double y, double z);
	double GetArea();
	void Scale(double factor);
	void Set(double nx, double ny, double nz, double d, double area);
	void Set(double x1, double y1, double z1, double x2, double y2, double z2, double nx, double ny, double nz);
	void Set(const Quadric& q);

protected:
};

#endif

//----------------------------------------------------------------------------//
