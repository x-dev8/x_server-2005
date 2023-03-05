#pragma once
#include <exception>
#include <sstream>

#ifndef STD_ThrowException
#define STD_ThrowException( error )                                 \
    std::stringstream __strTemp__;                                  \
    __strTemp__ << __FILE__ << "(" << __LINE__ << "): " << error;   \
    throw std::exception( __strTemp__.str().c_str() );
#endif

//
//  static assert.
//
#ifndef BOOST_STATIC_ASSERT
namespace boost{

    // HP aCC cannot deal with missing names for template value parameters
    template <bool x> struct STATIC_ASSERTION_FAILURE;

    template <> struct STATIC_ASSERTION_FAILURE<true> { enum { value = 1 }; };

    // HP aCC cannot deal with missing names for template value parameters
    template<int x> struct static_assert_test{};

}

#define BOOST_STATIC_ASSERT( B ) \
    typedef ::boost::static_assert_test<\
    sizeof(::boost::STATIC_ASSERTION_FAILURE< (bool)( B ) >)\
    > boost_static_assert_typedef_

#endif

//
//  release function.
//
template< typename T >
void SafeDelete( T& v )
{
    if ( v )
    {
        delete v;
        v = NULL;
    }
}

template< typename T >
void SafeDeleteArray( T& v )
{
    if ( v )
    {
        delete[] v;
        v = NULL;
    }
}

template< typename T >
void SafeRelease( T& v )
{
    if ( v )
    {
        v->Release();
        v = NULL;
    }
}
