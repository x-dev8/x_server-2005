//---------------------------------------------------------------------------
inline NiColor::NiColor(float fR, float fG, float fB)
{
    r = fR;
    g = fG;
    b = fB;
}
//---------------------------------------------------------------------------
inline NiColor& NiColor::operator= (float fScalar)
{
    r = fScalar;
    g = fScalar;
    b = fScalar;
    return *this;
}
//---------------------------------------------------------------------------
inline bool NiColor::operator== (const NiColor& c) const
{
    return (r == c.r && g == c.g && b == c.b);
}
//---------------------------------------------------------------------------
inline bool NiColor::operator!= (const NiColor& c) const
{
    return !(*this == c);
}
//---------------------------------------------------------------------------
inline NiColor NiColor::operator+ (const NiColor& c) const
{
    NiColor result = *this;
    result.r += c.r;
    result.g += c.g;
    result.b += c.b;
    return result;
}
//---------------------------------------------------------------------------
inline NiColor NiColor::operator- (const NiColor& c) const
{
    NiColor result = *this;
    result.r -= c.r;
    result.g -= c.g;
    result.b -= c.b;
    return result;
}
//---------------------------------------------------------------------------
inline NiColor NiColor::operator* (float fScalar) const
{
    NiColor result = *this;
    result.r *= fScalar;
    result.g *= fScalar;
    result.b *= fScalar;
    return result;
}
//---------------------------------------------------------------------------
inline NiColor NiColor::operator* (const NiColor &c) const
{
    NiColor result = *this;
    result.r *= c.r;
    result.g *= c.g;
    result.b *= c.b;
    return result;
}
//---------------------------------------------------------------------------
inline NiColor NiColor::operator/ (float fScalar) const
{
    NiColor result = *this;
    result.r /= fScalar;
    result.g /= fScalar;
    result.b /= fScalar;
    return result;
}
//---------------------------------------------------------------------------
inline NiColor NiColor::operator/ (const NiColor &c) const
{
    NiColor result = *this;
    result.r /= c.r;
    result.g /= c.g;
    result.b /= c.b;
    return result;
}
//---------------------------------------------------------------------------
inline NiColor NiColor::operator- () const
{
    return NiColor(-r,-g,-b);
}
//---------------------------------------------------------------------------
inline NiColor operator* (float fScalar, const NiColor& c)
{
    return c*fScalar;
}
//---------------------------------------------------------------------------
inline NiColor& NiColor::operator+= (const NiColor& c)
{
    r += c.r;
    g += c.g;
    b += c.b;
    return *this;
}
//---------------------------------------------------------------------------
inline NiColor& NiColor::operator-= (const NiColor& c)
{
    r -= c.r;
    g -= c.g;
    b -= c.b;
    return *this;
}
//---------------------------------------------------------------------------
inline NiColor& NiColor::operator*= (float fScalar)
{
    r *= fScalar;
    g *= fScalar;
    b *= fScalar;
    return *this;
}
//---------------------------------------------------------------------------
inline NiColor& NiColor::operator*= (const NiColor &c)
{
    r *= c.r;
    g *= c.g;
    b *= c.b;
    return *this;
}
//---------------------------------------------------------------------------
inline NiColor& NiColor::operator/= (float fScalar)
{
    r /= fScalar;
    g /= fScalar;
    b /= fScalar;
    return *this;
}
//---------------------------------------------------------------------------
inline NiColor& NiColor::operator/= (const NiColor &c)
{
    r /= c.r;
    g /= c.g;
    b /= c.b;
    return *this;
}
//---------------------------------------------------------------------------
inline void NiColor::Clamp()
{
    // Clamp to [0,1]^3.  Assumes that (r,g,b) >= (0,0,0).  This is a
    // reasonable assumption since colors are only added or multiplied in
    // the lighting system.  Note that clamping can cause significant
    // changes in the final color.
    if ( r > 1.0f )
        r = 1.0f;
    if ( g > 1.0f )
        g = 1.0f;
    if ( b > 1.0f )
        b = 1.0f;
}
//---------------------------------------------------------------------------
inline void NiColor::Scale()
{
    // Scale down by maximum component (preserves the final color).
    float fMax = r;
    if ( g > fMax )
        fMax = g;
    if ( b > fMax )
        fMax = b;

    if ( fMax > 1.0f )
    {
        float fInvMax = 1.0f/fMax;
        r *= fInvMax;
        g *= fInvMax;
        b *= fInvMax;
    }
}
//---------------------------------------------------------------------------
//---------------------------------------------------------------------------
inline NiColorA::NiColorA(float fR, float fG, float fB, float fA)
{
    r = fR;
    g = fG;
    b = fB;
    a = fA;
}
//---------------------------------------------------------------------------
inline NiColorA& NiColorA::operator= (float fScalar)
{
    r = fScalar;
    g = fScalar;
    b = fScalar;
    a = fScalar;
    return *this;
}
//---------------------------------------------------------------------------
inline bool NiColorA::operator== (const NiColorA& c) const
{
    return (r == c.r && g == c.g && b == c.b && a == c.a);
}
//---------------------------------------------------------------------------
inline bool NiColorA::operator!= (const NiColorA& c) const
{
    return !(*this == c);
}
//---------------------------------------------------------------------------
inline NiColorA NiColorA::operator+ (const NiColorA& c) const
{
    NiColorA result = *this;
    result.r += c.r;
    result.g += c.g;
    result.b += c.b;
    result.a += c.a;
    return result;
}
//---------------------------------------------------------------------------
inline NiColorA NiColorA::operator- (const NiColorA& c) const
{
    NiColorA result = *this;
    result.r -= c.r;
    result.g -= c.g;
    result.b -= c.b;
    result.a -= c.a;
    return result;
}
//---------------------------------------------------------------------------
inline NiColorA NiColorA::operator* (float fScalar) const
{
    NiColorA result = *this;
    result.r *= fScalar;
    result.g *= fScalar;
    result.b *= fScalar;
    result.a *= fScalar;
    return result;
}
//---------------------------------------------------------------------------
inline NiColorA NiColorA::operator* (const NiColorA &c) const
{
    NiColorA result = *this;
    result.r *= c.r;
    result.g *= c.g;
    result.b *= c.b;
    result.a *= c.a;
    return result;
}
//---------------------------------------------------------------------------
inline NiColorA NiColorA::operator/ (float fScalar) const
{
    NiColorA result = *this;
    result.r /= fScalar;
    result.g /= fScalar;
    result.b /= fScalar;
    result.a /= fScalar;
    return result;
}
//---------------------------------------------------------------------------
inline NiColorA NiColorA::operator/ (const NiColorA &c) const
{
    NiColorA result = *this;
    result.r /= c.r;
    result.g /= c.g;
    result.b /= c.b;
    result.a /= c.a;
    return result;
}
//---------------------------------------------------------------------------
inline NiColorA NiColorA::operator- () const
{
    return NiColorA(-r,-g,-b,-a);
}
//---------------------------------------------------------------------------
inline NiColorA operator* (float fScalar, const NiColorA& c)
{
    return c*fScalar;
}
//---------------------------------------------------------------------------
inline NiColorA& NiColorA::operator+= (const NiColorA& c)
{
    r += c.r;
    g += c.g;
    b += c.b;
    a += c.a;
    return *this;
}
//---------------------------------------------------------------------------
inline NiColorA& NiColorA::operator-= (const NiColorA& c)
{
    r -= c.r;
    g -= c.g;
    b -= c.b;
    a -= c.a;
    return *this;
}
//---------------------------------------------------------------------------
inline NiColorA& NiColorA::operator*= (float fScalar)
{
    r *= fScalar;
    g *= fScalar;
    b *= fScalar;
    a *= fScalar;
    return *this;
}
//---------------------------------------------------------------------------
inline NiColorA& NiColorA::operator*= (const NiColorA &c)
{
    r *= c.r;
    g *= c.g;
    b *= c.b;
    a *= c.a;
    return *this;
}
//---------------------------------------------------------------------------
inline NiColorA& NiColorA::operator/= (float fScalar)
{
    r /= fScalar;
    g /= fScalar;
    b /= fScalar;
    a /= fScalar;
    return *this;
}
//---------------------------------------------------------------------------
inline NiColorA& NiColorA::operator/= (const NiColorA &c)
{
    r /= c.r;
    g /= c.g;
    b /= c.b;
    a /= c.a;
    return *this;
}
//---------------------------------------------------------------------------
inline void NiColorA::Clamp()
{
    // Clamp to [0,1]^4.  Assumes that (r,g,b,a) >= (0,0,0).  This is a
    // reasonable assumption since colors are only added or multiplied in
    // the lighting system.  Note that clamping can cause significant
    // changes in the final color.
    if ( r > 1.0f )
        r = 1.0f;
    if ( g > 1.0f )
        g = 1.0f;
    if ( b > 1.0f )
        b = 1.0f;
    if ( a > 1.0f )
        a = 1.0f;
}
//---------------------------------------------------------------------------
inline void NiColorA::Scale()
{
    // Scale down by maximum component (preserves the final color).
    float fMax = r;
    if ( g > fMax )
        fMax = g;
    if ( b > fMax )
        fMax = b;

    if ( fMax > 1.0f )
    {
        float fInvMax = 1.0f/fMax;
        r *= fInvMax;
        g *= fInvMax;
        b *= fInvMax;
    }

    if ( a > 1.0f )
        a = 1.0f;
}

