#pragma once

/* implementation of Robert Jenkins' ibaa generator.  Main difference is
that I wrote an entirely new initialization function which is much
simpler yet still excellent. */

#include "MeRTLibs.h"

class CIBAA_RandGen
{
    bool				hasBuffered16_;
    unsigned short		buffer16_;
    unsigned int		m_[256], result_[256], aa_, bb_;
    unsigned int		resultCount_;

protected:
    void ibaa()
    {
        register unsigned int a = aa_, b = bb_, x, y, i;

        for (i=0; i<256; ++i)
        {
            x = m_[i];
            a = ((a<<19)^(a>>13)) + m_[(i+128)&255];
            m_[i] = y = m_[x&255] + a + b;
            result_[i] = b = m_[(y>>8)&255] + x;
        }
        bb_ = b;
        aa_ = a;
    }
public:
    CIBAA_RandGen() { init( static_cast< int >( time( NULL ) ) ); }

    static CIBAA_RandGen& Instance()
    {
        static CIBAA_RandGen s_xRand;
        return s_xRand;
    }

    // Call rand32() to retrieve a single 32-bit random value
    unsigned long rand32()
    {
        //return (!resultCount_-- ? (ibaa(), resultCount_=255, result_[resultCount_]) : result_[resultCount_]);
        if( resultCount_ == 0)
        {
            ibaa();
            resultCount_ = 256;
        }
        return result_[--resultCount_];
    }

    unsigned short rand16()
    {

        if(hasBuffered16_)
        {
            hasBuffered16_ = false;
            return buffer16_;
        }
        else
        {
            hasBuffered16_ = true;
            unsigned long result = rand32();
            buffer16_ = (unsigned short)(result >> 16);
            return (unsigned short)result;
        }
    }

    // return a random float >= 0 and < 1
    double rand_float()
    {
        return ((double)rand32() / 4294967296.0);
    }

    void init(int seed)
    {
        hasBuffered16_ = false;

        seed |= 1;    

        for (int i=0; i<256; i++)  // initialize memory
        {
            seed = 16807*(seed%127773) - 2836*(seed/127773);
            if (seed < 0) seed += 2147483647;
            m_[i] = seed;
        }

        ibaa();      // get first set of results
        resultCount_ = 256;
    }
};

#define theRand CIBAA_RandGen::Instance()