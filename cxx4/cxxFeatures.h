#ifndef CXX_FEATURES_H
#define CXX_FEATURES_H


/* Quick pre-processor macros to check which version of c++
	a compiler supports. Adapted from Boost.Config
    https://github.com/boostorg/config
*/

/* Extract GCC version */
#define GCC_VERSION (__GNUC__ * 10000 + __GNUC_MINOR__ * 100 + __GNUC_PATCHLEVEL__)

/* C++11 */
#if defined(__GXX_EXPERIMENTAL_CXX0X__) || (__cplusplus >= 201103L)
	#define HAS_CXX11
#endif

#if (GCC_VERSION < 40600) || !defined(HAS_CXX11)
    #define NO_CXX11_DEFAULTED_MOVES
    #define NO_CXX11_NOEXCEPT
    #define NO_CXX11_NULLPTR
    #define NO_CXX11_RANGE_BASED_FOR
#endif


#endif
