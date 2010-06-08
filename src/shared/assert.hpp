#ifndef __ASSERT_HPP
#define __ASSERT_HPP

void _assert(const char* e,const char* file,int line);

#ifndef NDEBUG
#define assert(e) ((e) ? (void)0 : _assert(#e, __FILE__, __LINE__))
#else
#define assert(x) ((void)0)
#endif

#endif // __ASSERT_HPP

