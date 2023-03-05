#ifndef _SPLINE_H
#define _SPLINE_H
#include "math.h"
#include <assert.h>
#include <stdlib.h>

//#include "stdafx.h"
#define DIV_FACTOR 50.0 //adjust this factor to adjust the curve smoothness
#define MAX_SPLINE_NP 30
#define Ndiv 4
class Curve
{
public:
	float  Ax,Ay,Az;
	float  Bx,By,Bz;
	float  Cx,Cy,Cz;
	//int    Ndiv;

	Curve(	float ax,
			float ay,
			float az,
			float bx,
			float by,
			float bz,
			float cx,
			float cy,
			float cz,
			int ndiv) 
	{
		Ax = ax;
		Ay = ay;
		Az = az;
		Bx = bx;
		By = by;
		Bz = bz;
		Cx = cx;
		Cy = cy;
		Cz = cz;
		//Ndiv = ndiv;
	}

	Curve(	float ax,
			float ay,
			float az,
			float bx,
			float by,
			float bz,
			float cx,
			float cy,
			float cz )
	{
		Ax = ax; 
		Ay = ay;
		Bx = bx; 
		By = by;
		Cx = cx; 
		Cy = cy;
		float f = max(abs((int)Ax),abs((int)Ay));
		f = max(f, abs((int)Az));
		//Ndiv = (int)(f/DIV_FACTOR);
	}
	Curve() 
	{	
	};

	void PutCurve(	float ax,
					float ay,
					float az,
					float bx,
					float by,
					float bz,
					float cx,
					float cy,
					float cz) 
	{
		Ax = ax;
		Ay = ay;
		Az = az;
		Bx = bx; 
		By = by;
		Bz = bz;
		Cx = cx; 
		Cy = cy;
		Cz = cz;
		float f = max(abs((int)Ax),abs((int)Ay));
		f = max( f, abs((int)Az) );
		//Ndiv = (int)(f/DIV_FACTOR);
	}

	int GetCount()
	{
		//if (Ndiv==0)
		//	Ndiv=1;
		int PointCount = 1;

		for(int i=1; i<=Ndiv ; i++)
		{
			PointCount++;
		}
		return PointCount;
	}
	void GetCurve(float x,float y,float z, float points[], int& nPointCount )
	{
		float X,Y,Z;
		float  t,f,g,h;
		//if (Ndiv==0)
		//	Ndiv=1;

		X = x; 
		Y = y;
		Z = z;

		//int nPoint = 0;
		points[nPointCount*3+0] = X;
		points[nPointCount*3+1] = Y;
		points[nPointCount*3+2] = Z;
		nPointCount++;

		for(int i=1; i<=Ndiv ; i++)
		{
			t = 1.0f / (float)Ndiv * (float)i;
			f = t*t*(3.0f-2.0f*t);
			g = t*(t-1.0f)*(t-1.0f);
			h = t*t*(t-1.0f);
			X = x + Ax*f + Bx*g + Cx*h;
			Y = y + Ay*f + By*g + Cy*h;
			Z = z + Az*f + Bz*g + Cz*h;
			points[nPointCount*3+0] = X;
			points[nPointCount*3+1] = Y;
			points[nPointCount*3+2] = Z;
			nPointCount++;
		}
	}
  
};

class Spline 
{

public:
	float* Px;
	float* Py;
	float* Pz;
	float* Ax;
	float* Ay;
	float* Az;
	float* Bx;
	float* By;
	float* Bz;
	float* Cx;
	float* Cy;
	float* Cz;
	float*  k;
	float*  Mat[3];

	int  NP;

	float* pfMemory;
	//float	pfMemory[MAX_SPLINE_NP*16];
	// constructor
	Spline(float pt[], int np)
	{
		NP = np;
		//if( np > MAX_SPLINE_NP )
		//{
		//	assert( false );
		//	np = MAX_SPLINE_NP;
		//}
		//memset( pfMemory, 0x00, sizeof(pfMemory));
		pfMemory = new float[16*NP];
		Px = &pfMemory[0*NP];// new float[NP];		// 0*NP
		Py = &pfMemory[1*NP];// new float[NP];		// 1*NP
		Pz = &pfMemory[2*NP];// new float[NP];		// 2*NP
		Ax = &pfMemory[3*NP];// new float[NP];		// 3*NP
		Ay = &pfMemory[4*NP];// new float[NP];		// 4*NP
		Az = &pfMemory[5*NP];// new float[NP];		// 5*NP
		Bx = &pfMemory[6*NP];// new float[NP];		// 6*NP
		By = &pfMemory[7*NP];// new float[NP];		// 7*NP
		Bz = &pfMemory[8*NP];// new float[NP];		// 8*NP
		Cx = &pfMemory[9*NP];// new float[NP];		// 9*NP
		Cy = &pfMemory[10*NP];// new float[NP];		// 10*NP
		Cz = &pfMemory[11*NP];// new float[NP];		// 11*NP
		k  = &pfMemory[12*NP];// new float[NP];		// 12*NP
		Mat[0] = &pfMemory[13*NP];// new float[NP];	// 13*NP
		Mat[1] = &pfMemory[14*NP];// new float[NP];	// 14*NP
		Mat[2] = &pfMemory[15*NP];// new float[NP];	// 15*NP

		for(int i=0;i<NP ;i++) 
		{
			Px[i] = pt[i*3];  
			Py[i] = pt[i*3+1];
			Pz[i] = pt[i*3+2];
		}

	}

	~Spline()
	{
		delete[] pfMemory;
		//delete[] Px;
		//delete[] Py;
		//delete[] Pz;
		//delete[] Ax;
		//delete[] Ay;
		//delete[] Az;
		//delete[] Bx;
		//delete[] By;
		//delete[] Bz;
		//delete[] Cx;
		//delete[] Cy;
		//delete[] Cz;
		//delete[] k;
		//delete[] Mat[0];
		//delete[] Mat[1];
		//delete[] Mat[2];
	}

	void Generate() 
	{
		float AMag , AMagOld;
		int i = 0;
    	// vector A
		for( i= 0 ; i<=NP-2 ; i++ ) 
		{
			Ax[i] = Px[i+1] - Px[i];
			Ay[i] = Py[i+1] - Py[i];
			Az[i] = Pz[i+1] - Pz[i];
		}
		// k
		AMagOld = sqrtf(Ax[0]*Ax[0] + Ay[0]*Ay[0] + Az[0]*Az[0]);
		for(i=0 ; i<=NP-3 ; i++) 
		{
			AMag = sqrtf(Ax[i+1]*Ax[i+1] + Ay[i+1]*Ay[i+1] + Az[i+1]*Az[i+1]);
			if( AMag == 0.0f )
			{
				if( AMagOld == 0.0f )
					k[i] = 1.0f;
				else
					k[i] = 10000000.0f;
			}
			else
				k[i] = AMagOld / AMag;
			AMagOld = AMag;
		}
		k[NP-2] = 1.0f;

		// Matrix
		for(i=1; i<=NP-2;i++) 
		{
			Mat[0][i] = 1.0f;
			Mat[1][i] = 2.0f*k[i-1]*(1.0f + k[i-1]);
			Mat[2][i] = k[i-1]*k[i-1]*k[i];
		}
		Mat[1][0] = 2.0f;
		Mat[2][0] = k[0];
		Mat[0][NP-1] = 1.0f;
		Mat[1][NP-1] = 2.0f*k[NP-2];

		// 
		for(i=1; i<=NP-2;i++) 
		{
			Bx[i] = 3.0f*(Ax[i-1] + k[i-1]*k[i-1]*Ax[i]);
			By[i] = 3.0f*(Ay[i-1] + k[i-1]*k[i-1]*Ay[i]);
			Bz[i] = 3.0f*(Az[i-1] + k[i-1]*k[i-1]*Az[i]);
		}
		Bx[0] = 3.0f*Ax[0];
		By[0] = 3.0f*Ay[0];
		Bz[0] = 3.0f*Az[0];
		Bx[NP-1] = 3.0f*Ax[NP-2];
		By[NP-1] = 3.0f*Ay[NP-2];
		Bz[NP-1] = 3.0f*Az[NP-2];

		//
		MatrixSolve(Bx);
		MatrixSolve(By);
		MatrixSolve(Bz);

		for(i=0 ; i<=NP-2 ; i++ ) 
		{
			Cx[i] = k[i]*Bx[i+1];
			Cy[i] = k[i]*By[i+1];
			Cz[i] = k[i]*Bz[i+1];
		}
	}

	void MatrixSolve(float B[]) 
	{
		float* Work = new float[NP];
		float* WorkB = new float[NP];
		for(int i=0;i<=NP-1;i++) 
		{
			Work[i] = B[i] / Mat[1][i];
			WorkB[i] = Work[i];
		}

		for(int j=0 ; j<1 ; j++) 
		{ ///  need convergence judge
			Work[0] = (B[0] - Mat[2][0]*WorkB[1])/Mat[1][0];
			for(int i=1; i<NP-1 ; i++ ) 
			{
				Work[i] = (B[i]-Mat[0][i]*WorkB[i-1]-Mat[2][i]*WorkB[i+1])
							/Mat[1][i];
			}
			Work[NP-1] = (B[NP-1] - Mat[0][NP-1]*WorkB[NP-2])/Mat[1][NP-1];

			for(int i=0 ; i<=NP-1 ; i++ ) 
			{
				WorkB[i] = Work[i];
			}
		}
		for(int i=0 ; i<=NP-1 ; i++ ) 
		{
			B[i] = Work[i];
		}
		delete[] Work;
		delete[] WorkB;
	}

	//void draw(HDC hdc) 
	//{
	//	Curve c;
	//	for(int i=0; i<NP-1 ; i++) 
	//	{
	//		c.PutCurve(Ax[i],Ay[i],Az[i],Bx[i],By[i],Bz[i],Cx[i],Cy[i],Cz[i]);
	//		c.draw(hdc,Px[i],Py[i]);
	//	}
	//	
	//}
	int GetCurveCount()
	{
		Curve c;
		int count = 0;
		for(int i=0; i<NP-1 ; i++) 
		{
			c.PutCurve(Ax[i],Ay[i],Az[i],Bx[i],By[i],Bz[i],Cx[i],Cy[i],Cz[i]);
			count += c.GetCount();
		}
		return count;
	}
	void GetCurve(float points[], int& PointCount)
	{
		Curve c;
		for(int i=0; i<NP-1 ; i++) 
		{
			c.PutCurve(Ax[i],Ay[i],Az[i],Bx[i],By[i],Bz[i],Cx[i],Cy[i],Cz[i]);
			c.GetCurve(Px[i],Py[i],Pz[i], points, PointCount);
		}
	}
  //////////// closed cubic spline ////////////////////
	void GenClosed() 
	{
		float AMag , AMagOld , AMag0;
        // vector A
		for(int i= 0 ; i<=NP-2 ; i++ ) 
		{
			Ax[i] = Px[i+1] - Px[i];
			Ay[i] = Py[i+1] - Py[i];
		}
		Ax[NP-1] = Px[0] - Px[NP-1];
		Ay[NP-1] = Py[0] - Py[NP-1];

		// k
		AMag0 = AMagOld = (float)sqrt(Ax[0]*Ax[0] + Ay[0]*Ay[0]);
		for(int i=0 ; i<=NP-2 ; i++) 
		{
			AMag = (float)sqrt(Ax[i+1]*Ax[i+1] + Ay[i+1]*Ay[i+1]);
			k[i] = AMagOld / AMag;
			AMagOld = AMag;
		}
		k[NP-1]=AMagOld/AMag0; 

		// Matrix
		for(int i=1; i<=NP-1;i++) 
		{
			Mat[0][i] = 1.0f;
			Mat[1][1] = 2.0f*k[i-1]*(1.0f + k[i-1]);
			Mat[2][i] = k[i-1]*k[i-1]*k[i];
		}
		Mat[0][0] = 1.0f;
		Mat[1][0] = 2.0f*k[NP-1]*(1.0f + k[NP-1]);
		Mat[2][0] = k[NP-1]*k[NP-1]*k[0];

		// 
		for(int i=1; i<=NP-1;i++) 
		{
			Bx[i] = 3.0f*(Ax[i-1] + k[i-1]*k[i-1]*Ax[i]);
			By[i] = 3.0f*(Ay[i-1] + k[i-1]*k[i-1]*Ay[i]);
		}
		Bx[0] = 3.0f*(Ax[NP-1] + k[NP-1]*k[NP-1]*Ax[0]);
		By[0] = 3.0f*(Ay[NP-1] + k[NP-1]*k[NP-1]*Ay[0]);

		//
		MatrixSolveEX(Bx);
		MatrixSolveEX(By);

		for(int i=0 ; i<=NP-2 ; i++ ) 
		{
			Cx[i] = k[i]*Bx[i+1];
			Cy[i] = k[i]*By[i+1];
		}
		Cx[NP-1] = k[NP-1]*Bx[0];
		Cy[NP-1] = k[NP-1]*By[0];
	}

  ///// tridiagonal matrix + elements of [0][0], [N-1][N-1] //// 
	void MatrixSolveEX(float B[]) 
	{
		float* Work = new float[NP];
		float* WorkB = new float[NP];

		for(int i=0;i<=NP-1;i++) 
		{
			Work[i] = B[i] / Mat[1][i];
			WorkB[i] = Work[i];
		}

		for(int j=0 ; j<10 ; j++) 
		{  // need judge of convergence
			Work[0] = (B[0]-Mat[0][0]*WorkB[NP-1]-Mat[2][0]*WorkB[1])
				/Mat[1][0];
			for(int i=1; i<NP-1 ; i++ ) 
			{
				Work[i] = (B[i]-Mat[0][i]*WorkB[i-1]-Mat[2][i]*WorkB[i+1])
					/Mat[1][i];
			}
			Work[NP-1] = (B[NP-1]-Mat[0][NP-1]*WorkB[NP-2]-Mat[2][NP-1]*WorkB[0])
				/Mat[1][NP-1];

			for(int i=0 ; i<=NP-1 ; i++ ) 
			{
				WorkB[i] = Work[i];
			}
		}

		for(int i=0 ; i<=NP-1 ; i++ ) 
		{
			B[i] = Work[i];
		}
	}

	//void drawClosed(HDC hdc) 
	//{
	//	Curve c;
	//	for(int i=0; i<NP ; i++) 
	//	{
	//		c.PutCurve(Ax[i],Ay[i],Bx[i],By[i],Cx[i],Cy[i]);
	//		c.draw(hdc ,Px[i],Py[i]);
	//	}
	//}


};

#endif
