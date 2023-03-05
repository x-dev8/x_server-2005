#ifndef __PARADIGMCOMPONENT_H__
#define __PARADIGMCOMPONENT_H__

// ±‡“Î∆⁄∂œ—‘ STATIC_ASSERT( expr );
template <bool x> struct STATIC_ASSERTION_FAILURE;
template <> struct STATIC_ASSERTION_FAILURE<true> { enum { value = 1 }; };
template<int x> struct static_assert_test{};

#define STATIC_ASSERT( B ) \
    typedef static_assert_test<\
    sizeof(STATIC_ASSERTION_FAILURE< (bool)( B ) >)\
    > boost_static_assert_typedef_

#endif // __PARADIGMCOMPONENT_H__
