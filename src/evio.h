#ifndef _EVIO_H_
#define _EVIO_H_

#ifdef __cplusplus
extern "C" {
#endif

#include <sys/types.h>

#include <glitter.h>

TODO (move to ez-io-common)
typedef __attribute__ ((nonnull (1, 2, 4), /*nothrow,*/ warn_unused_result))
int (*evio_cb_t) (
   void *restrict dest,
   void const *restrict src, size_t srcsz, size_t *restrict destsz) ;

int evio (
   fd_t in, fd_t out,
   size_t in_bufsz,
   size_t out_bufsz,
   evio_cb_t cb)
__attribute__ ((nonnull (5), nothrow, warn_unused_result)) ;

TODO (evio_alloc)

#ifdef __cplusplus
}
#endif

#endif /* _EVIO_H_ */