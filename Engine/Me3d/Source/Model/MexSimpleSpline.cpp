#include "Me3d/Model/MexSimpleSpline.h"
#include "Me3d/Vector.h"
#include "Me3d/Platform.h"
#include "Me3d/Vector4.h"

//---------------------------------------------------------------------
SimpleSpline::SimpleSpline()
{
    // Set up matrix
    // Hermite polynomial
    mCoeffs.m[0][0] = 2;
    mCoeffs.m[0][1] = -2;
    mCoeffs.m[0][2] = 1;
    mCoeffs.m[0][3] = 1;
    mCoeffs.m[1][0] = -3;
    mCoeffs.m[1][1] = 3;
    mCoeffs.m[1][2] = -2;
    mCoeffs.m[1][3] = -1;
    mCoeffs.m[2][0] = 0;
    mCoeffs.m[2][1] = 0;
    mCoeffs.m[2][2] = 1;
    mCoeffs.m[2][3] = 0;
    mCoeffs.m[3][0] = 1;
    mCoeffs.m[3][1] = 0;
    mCoeffs.m[3][2] = 0;
    mCoeffs.m[3][3] = 0;

    mAutoCalc = true;
}
//---------------------------------------------------------------------
SimpleSpline::~SimpleSpline()
{
}
//---------------------------------------------------------------------
void SimpleSpline::addPoint(const Vector& p)
{
    mPoints.push_back(p);
    if (mAutoCalc)
    {
        recalcTangents();
    }
}
//---------------------------------------------------------------------
Vector SimpleSpline::interpolate(float t) const
{
    // Currently assumes points are evenly spaced, will cause velocity
    // change where this is not the case
    // TODO: base on arclength?

    
    // Work out which segment this is in
    float fSeg = t * (mPoints.size() - 1);
    unsigned int segIdx = (unsigned int)fSeg;
    // Apportion t 
    t = fSeg - segIdx;

    return interpolate(segIdx, t);

}
//---------------------------------------------------------------------
Vector SimpleSpline::interpolate(int fromIndex, float t) const
{
    // Bounds check
    assert (fromIndex < mPoints.size() &&
        "fromIndex out of bounds");

    if ((fromIndex + 1) == mPoints.size())
    {
        // Duff request, cannot blend to nothing
        // Just return source
        return mPoints[fromIndex];

    }

    // Fast special cases
    if (t == 0.0f)
    {
        return mPoints[fromIndex];
    }
    else if(t == 1.0f)
    {
        return mPoints[fromIndex + 1];
    }

    // float interpolation
    // Form a vector of powers of t
    float t2, t3;
    t2 = t * t;
    t3 = t2 * t;
    Vector4 powers(t3, t2, t, 1);


    // Algorithm is ret = powers * mCoeffs * Matrix4(point1, point2, tangent1, tangent2)
    const Vector& point1 = mPoints[fromIndex];
    const Vector& point2 = mPoints[fromIndex+1];
    const Vector& tan1 = mTangents[fromIndex];
    const Vector& tan2 = mTangents[fromIndex+1];
    MeMatrix pt;

    pt.m[0][0] = point1.x;
    pt.m[0][1] = point1.y;
    pt.m[0][2] = point1.z;
    pt.m[0][3] = 1.0f;
    pt.m[1][0] = point2.x;
    pt.m[1][1] = point2.y;
    pt.m[1][2] = point2.z;
    pt.m[1][3] = 1.0f;
    pt.m[2][0] = tan1.x;
    pt.m[2][1] = tan1.y;
    pt.m[2][2] = tan1.z;
    pt.m[2][3] = 1.0f;
    pt.m[3][0] = tan2.x;
    pt.m[3][1] = tan2.y;
    pt.m[3][2] = tan2.z;
    pt.m[3][3] = 1.0f;

    Vector4 ret = powers * mCoeffs * pt;

    return Vector(ret.x, ret.y, ret.z);
}
//---------------------------------------------------------------------
void SimpleSpline::recalcTangents(void)
{
    // Catmull-Rom approach
    // 
    // tangent[i] = 0.5 * (point[i+1] - point[i-1])
    //
    // Assume endpoint tangents are parallel with line with neighbour

    size_t i, numPoints;
    bool isClosed;

    numPoints = mPoints.size();
    if (numPoints < 2)
    {
        // Can't do anything yet
        return;
    }

    // Closed or open?
    if (mPoints[0] == mPoints[numPoints-1])
    {
        isClosed = true;
    }
    else
    {
        isClosed = false;
    }

    mTangents.resize(numPoints);



    for(i = 0; i < numPoints; ++i)
    {
        if (i ==0)
        {
            // Special case start
            if (isClosed)
            {
                // Use numPoints-2 since numPoints-1 is the last point and == [0]
                mTangents[i] = 0.5 * (mPoints[1] - mPoints[numPoints-2]);
            }
            else
            {
                mTangents[i] = 0.5 * (mPoints[1] - mPoints[0]);
            }
        }
        else if (i == numPoints-1)
        {
            // Special case end
            if (isClosed)
            {
                // Use same tangent as already calculated for [0]
                mTangents[i] = mTangents[0];
            }
            else
            {
                mTangents[i] = 0.5 * (mPoints[i] - mPoints[i-1]);
            }
        }
        else
        {
            mTangents[i] = 0.5 * (mPoints[i+1] - mPoints[i-1]);
        }
        
    }



}
//---------------------------------------------------------------------
const Vector& SimpleSpline::getPoint(unsigned short index) const
{
    assert (index < mPoints.size() && "Point index is out of bounds!!");

    return mPoints[index];
}
//---------------------------------------------------------------------
unsigned short SimpleSpline::getNumPoints(void) const
{
    return (unsigned short)mPoints.size();
}
//---------------------------------------------------------------------
void SimpleSpline::clear(void)
{
    mPoints.clear();
    mTangents.clear();
}
//---------------------------------------------------------------------
void SimpleSpline::updatePoint(unsigned short index, const Vector& value)
{
    assert (index < mPoints.size() && "Point index is out of bounds!!");

    mPoints[index] = value;
    if (mAutoCalc)
    {
        recalcTangents();
    }
}
//---------------------------------------------------------------------
void SimpleSpline::setAutoCalculate(bool autoCalc)
{
    mAutoCalc = autoCalc;
}



