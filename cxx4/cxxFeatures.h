#ifndef CXX_FEATURES_H
#define CXX_FEATURES_H


/* Quick pre-processor macros to check which version of c++
	a compiler supports.
*/

/* C++11 */
#if __cplusplus >= 201103L
	#define HAS_CXX11
#endif

/* C++14 */
#if __cplusplus >= 201402L
	#define HAS_CXX14
#endif

/* C++17 */
#if __cplusplus >= 201703L
	#define HAS_CXX17
#endif

#endif
