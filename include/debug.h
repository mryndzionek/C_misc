#ifndef __DEBUG_H__
#define __DEBUG_H__

#include <stdio.h>
#include <errno.h>
#include <string.h>
#include <stdint.h>

extern uint8_t verboseOutput;

#define PRINT_PREFIX                            "app: "

#ifdef NDEBUG
#define DEBUG(M, ...)
#else
#define DEBUG(M, ...) fprintf(stderr, "DEBUG %s:%d: " M "\n", __FILE__, __LINE__, ##__VA_ARGS__)
#endif

#define CLEAN_ERRNO() (errno == 0 ? "None" : strerror(errno))

#define LOG_ERR(M, ...) fprintf(stderr, "[ERROR] (%s:%d: errno: %s) " M "\n", __FILE__, __LINE__, CLEAN_ERRNO(), ##__VA_ARGS__)

#define LOG_WARN(M, ...) fprintf(stderr, "[WARN] (%s:%d: errno: %s) " M "\n", __FILE__, __LINE__, CLEAN_ERRNO(), ##__VA_ARGS__)

#define LOG_INFO(M, ...) fprintf(stderr, "[INFO] (%s:%d) " M "\n", __FILE__, __LINE__, ##__VA_ARGS__)

#define CHECK(A, M, ...) if(!(A)) { LOG_ERR(M, ##__VA_ARGS__); errno=0; goto error; }

#define SENTINEL(M, ...)  { LOG_ERR(M, ##__VA_ARGS__); errno=0; goto error; }

#define CHECK_MEM(A) CHECK((A), "Out of memory.")

#define CHECK_DEBUG(A, M, ...) if(!(A)) { DEBUG(M, ##__VA_ARGS__); errno=0; goto error; }

#define PRINTF_STDOUT( _format, _args... )        \
do { if( verboseOutput ) fprintf( stdout, "%s"_format "%s", PRINT_PREFIX, ##_args, ".\n" ); } while( 0 )

#ifndef NDEBUG
    #define DEBUG_PRINTF( format, args... )         PRINTF_STDOUT( format, ## args )
    #define FUNC_ENTER_PRINT                        PRINTF_STDOUT( "--->Entering %s", __FUNCTION__ );
    #define FUNC_EXIT_PRINT                         PRINTF_STDOUT( "<---Exiting %s",  __FUNCTION__ );
#else
    #define DEBUG_PRINTF(...)
    #define FUNC_ENTER_PRINT
    #define FUNC_EXIT_PRINT
#endif

#endif //__DEBUG_H__
