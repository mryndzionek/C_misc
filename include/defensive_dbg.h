#ifndef __DEFENSIVE_DEBUG_H__
#define __DEFENSIVE_DEBUG_H__

#include <stdio.h>

/* Crash the process */
#define __CRASH()    (*(char *)NULL)

/* Generate a textual message about the assertion */
#define __BUG_REPORT( _cond, _format, _args ... ) \
    fprintf( stderr, "%s:%d: Assertion error in function '%s' for condition '%s': " _format "\n", \
    __FILE__, __LINE__, __FUNCTION__, # _cond, ##_args ) && fflush( NULL ) != (EOF-1)

/* Check a condition, and report and crash in case the condition is false */
#define DF_ASSERT( _cond, _format, _args ... ) \
do { if(!(_cond)) { __CRASH() = __BUG_REPORT( _cond, _format, ##_args ); } } while( 0 )

#endif //__DEFENSIVE_DEBUG_H__
