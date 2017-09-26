#if HAVE_CONFIG_H
#include <config.h>
#endif

#define _POSIX_C_SOURCE 200112L
#define __STDC_VERSION__ 200112L

#include <glitter.h>

	#pragma GCC diagnostic push
	#pragma GCC diagnostic ignored "-Wpadded"
	#pragma GCC diagnostic ignored "-Wnested-externs"
	#pragma GCC diagnostic ignored "-Wmissing-prototypes"
#include <ev.h>
	#pragma GCC diagnostic pop

#include <restart.h>
#include <evio.h>

	#pragma GCC diagnostic push
	#pragma GCC diagnostic ignored "-Wpadded"
typedef struct {
   ev_io io;
   fd_t fd;
   void *restrict data;
   size_t datasz;
   size_t rd;
   void *restrict watcher;
} rd_watcher_t;
	#pragma GCC diagnostic pop

	#pragma GCC diagnostic push
	#pragma GCC diagnostic ignored "-Wpadded"
typedef struct {
   ev_io io;
   fd_t fd;
   void *restrict data;
   size_t datasz;
} wr_watcher_t;
	#pragma GCC diagnostic pop

TODO (ev_rw_cb_common ())

__attribute__ ((nonnull (1), nothrow))
static void ev_read_cb (EV_P_ ev_io *restrict _w, int revents) {
   rd_watcher_t *restrict w = (rd_watcher_t *restrict) _w;
   ssize_t rd;
   TODO (check revents)
   rd = r_read (w->fd, w->data, w->datasz);
   if (rd == 0) {
      TODO (stop ev loop)
      return;
   }
   error_check (rd == -1) {
      TODO (stop ev loop)
      return;
   }
   w->watcher->rd = (size_t) rd;
   error_check (w->cb (w->data, w->rd) != 0) {
      TODO (stop ev loop)
      return;
   }
   TODO (start wr watcher)
}
__attribute__ ((nonnull (1), nothrow))
static void ev_write_cb (EV_P_ ev_io *restrict _w, int revents) {
   wr_watcher_t *restrict w = (wr_watcher_t *restrict) _w;
   ssize_t wr;
   TODO (check revents)
   wr = r_write (w->fd, w->data, w->datasz);
   error_check (wr != w->datasz) {
      TODO (stop ev loop)
      return;
   }
   error_check (w->cb (w->data, w->rd) != 0) {
      TODO (stop ev loop)
      return;
   }
   TODO (stop wr watcher)
}

typedef struct {
   io_t *restrict io;
   fd_t in;
   fd_t out;
} thread_cb_t;

__attribute__ ((nonnull (1), nothrow, warn_unused_result))
static void *rd_thread_cb (void *restrict _arg) {
   thread_cb_t *restrict arg = (thread_cb_t *restrict) _arg;

   struct ev_loop *restrict loop = EV_DEFAULT;

   rd_watcher_t rd_watcher;

   rd_watcher.in  = arg->io->in;

   rd_watcher.fd = arg->in;
   ev_io_init (&(rd_watcher.io), ev_read_cb, rd_watcher.fd, EV_READ);
   ev_io_start (loop, (ev_io *) &rd_watcher);

   ev_run (loop, 0);
   return NULL;
}
__attribute__ ((nonnull (1), nothrow, warn_unused_result))
static void *wr_thread_cb (void *restrict _arg) {
   thread_cb_t *restrict arg = (thread_cb_t *restrict) _arg;

   struct ev_loop *restrict loop = ev_loop_new (EVFLAG_AUTO);

   wr_watcher_t wr_watcher;

   wr_watcher.out = arg->io->out;

   wr_watcher.fd = arg->out;

   ev_io_init (&(wr_watcher.io), ev_write_cb, wr_watcher.fd, EV_WRITE);
   ev_io_start (loop, (ev_io *) &wr_watcher);

   ev_run (loop, 0);
   return NULL;
}

__attribute__ ((nonnull (1, 2), nothrow, warn_unused_result))
static int worker_thread_cb_cb (
   buffer_t *restrict buf_out,
   buffer_t const *restrict buf_in,
   void *restrict _arg) {
   threv_cb_t *restrict arg = (threv_cb_t *restrict) _arg;

   TODO (init buf_out->n to out_bufsz below)
   error_check ((*arg) (buf_out->buf, buf_in->buf,
      buf_in->n, &(buf_out->n)) != 0)
      return -1;
   return 0;
}

typedef struct {
   io_t *restrict io;
   threv_cb_t cb;
} worker_cb_t;

__attribute__ ((nonnull (1), nothrow, warn_unused_result))
static void *worker_thread_cb (void *restrict _arg) {
   worker_cb_t *restrict arg = (worker_cb_t *restrict) _arg;
   error_check (worker_io (arg->io, worker_thread_cb_cb, &(arg->cb)) != 0) return NULL;
   return NULL;
}

__attribute__ ((nonnull (7), nothrow, warn_unused_result))
int evio (
   fd_t in, fd_t out,
   size_t in_bufsz,
   size_t out_bufsz,
   evio_cb_t cb) {
   thread_cb_t thread_cb;
   worker_cb_t worker_cb;
   io_t dest/*, src*/;
   pthread_t rd_thread;
   pthread_t wr_thread;
   pthread_t worker_thread;
   buffer_t *restrict buf_in;
   buffer_t *restrict buf_out;

   thread_cb.io = &dest;
   thread_cb.in  = in;
   thread_cb.out = out;
   worker_cb.io = &dest;
   worker_cb.cb = cb;

   error_check (alloc_io (&dest, /*&src,*/
      in_bufsz, in_nbuf, out_bufsz, out_nbuf) != 0) return -1;

   error_check (pthread_create (&rd_thread, NULL, rd_thread_cb, &thread_cb) != 0) {
	#pragma GCC diagnostic push
	#pragma GCC diagnostic ignored "-Wunused-result"
      (void) free_io (&dest);
	#pragma GCC diagnostic pop
      return -2;
   }
   error_check (pthread_create (&wr_thread, NULL, wr_thread_cb, &thread_cb) != 0) {
	#pragma GCC diagnostic push
	#pragma GCC diagnostic ignored "-Wunused-result"
      (void) free_io (&dest);
	#pragma GCC diagnostic pop
      return -3;
   }
   error_check (pthread_create (&worker_thread, NULL, worker_thread_cb, /*&src*/ &worker_cb) != 0) {
	#pragma GCC diagnostic push
	#pragma GCC diagnostic ignored "-Wunused-result"
      (void) free_io (&dest);
	#pragma GCC diagnostic pop
      return -4;
   }

   error_check (pthread_join (rd_thread, NULL) != 0) {
	#pragma GCC diagnostic push
	#pragma GCC diagnostic ignored "-Wunused-result"
      (void) free_io (&dest);
	#pragma GCC diagnostic pop
      return -5;
   }
   error_check (pthread_join (wr_thread, NULL) != 0) {
	#pragma GCC diagnostic push
	#pragma GCC diagnostic ignored "-Wunused-result"
      (void) free_io (&dest);
	#pragma GCC diagnostic pop
      return -6;
   }
   error_check (pthread_join (worker_thread, NULL) != 0) {
	#pragma GCC diagnostic push
	#pragma GCC diagnostic ignored "-Wunused-result"
      (void) free_io (&dest);
	#pragma GCC diagnostic pop
      return -7;
   }

   error_check (free_io (&dest/*, &src*/) != 0) return -8;

   return 0;
}
