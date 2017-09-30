#if HAVE_CONFIG_H
#include <config.h>
#endif

#define _POSIX_C_SOURCE 200112L
#define __STDC_VERSION__ 200112L

#include <stdlib.h>

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
   void *restrict watcher;
   evio_cb_t cb;
} rd_watcher_t;
	#pragma GCC diagnostic pop

	#pragma GCC diagnostic push
	#pragma GCC diagnostic ignored "-Wpadded"
typedef struct {
   ev_io io;
   fd_t fd;
   void *restrict data;
   size_t datasz;
   rd_watcher_t *restrict watcher;
   /*evio_cb_t cb;*/
} wr_watcher_t;
	#pragma GCC diagnostic pop

TODO (ev_rw_cb_common ())

static void ev_write_cb (EV_P_ ev_io *restrict _w, int revents)
__attribute__ ((nonnull (1), nothrow)) ;

__attribute__ ((nonnull (1), nothrow))
static void ev_read_cb (EV_P_ ev_io *restrict _w, int revents) {
	#pragma GCC diagnostic push
	#pragma GCC diagnostic ignored "-Wstrict-aliasing"
   rd_watcher_t *restrict w = (rd_watcher_t *restrict) _w;
	#pragma GCC diagnostic pop
   wr_watcher_t *restrict watcher = (wr_watcher_t *restrict) (w->watcher);
   ssize_t rd;
   TODO (check revents)
   rd = r_read (w->fd, w->data, w->datasz);
   if (rd == 0) {
      ev_io_stop (EV_A_ _w);
      ev_break (EV_A_ EVBREAK_ALL);
      return;
   }
   error_check (rd == -1) {
      ev_io_stop (EV_A_ _w);
      ev_break (EV_A_ EVBREAK_ALL);
      return;
   }
   error_check (w->cb (watcher->data, w->data,
      (size_t) rd, &(watcher->datasz)) != 0) {
      ev_io_stop (EV_A_ _w);
      ev_break (EV_A_ EVBREAK_ALL);
      return;
   }

   ev_io_init (&(watcher->io), ev_write_cb, watcher->fd, EV_WRITE);
   ev_io_start (loop, (ev_io *restrict) watcher);

   ev_io_stop (EV_A_ _w);
}
__attribute__ ((nonnull (1), nothrow))
static void ev_write_cb (EV_P_ ev_io *restrict _w, int revents) {
   wr_watcher_t *restrict w = (wr_watcher_t *restrict) _w;
   rd_watcher_t *restrict watcher = (rd_watcher_t *restrict) (w->watcher);
   ssize_t wr;
   TODO (check revents)
   wr = r_write (w->fd, w->data, w->datasz);
   error_check (wr == -1) {
      ev_io_stop (EV_A_ _w);
      ev_break (EV_A_ EVBREAK_ALL);
      return;
   }
   error_check ((size_t) wr != w->datasz) {
      ev_io_stop (EV_A_ _w);
      ev_break (EV_A_ EVBREAK_ALL);
      return;
   }
   /*error_check (w->cb (w->data, w->rd) != 0) {
      TODO (stop ev loop)
      return;
   }*/
   ev_io_init (&(watcher->io), ev_read_cb, watcher->fd, EV_READ);
   ev_io_start (loop, (ev_io *restrict) watcher);

   ev_io_stop (EV_A_ _w);
}

__attribute__ ((nonnull (5), nothrow, warn_unused_result))
int evio (
   fd_t in, fd_t out,
   size_t in_bufsz,
   size_t out_bufsz,
   evio_cb_t cb) {
   rd_watcher_t rd;
   wr_watcher_t wr;
   char *restrict in_buf;
   char *restrict out_buf;

   struct ev_loop *restrict loop = EV_DEFAULT;

   in_buf = malloc (in_bufsz + 1);
   error_check (in_buf == NULL) return -1;
   out_buf = malloc (out_bufsz);
   error_check (out_buf == NULL) {
      free (in_buf);
      return -2;
   }

   rd.fd = in;
   wr.fd = out;
   rd.data = in_buf;
   wr.data = out_buf;
   rd.datasz = in_bufsz;
   wr.datasz = out_bufsz;
   rd.cb = cb;
   /*wr.cb = cb;*/
   rd.watcher = &wr;
   wr.watcher = &rd;

   ev_io_init (&(rd.io), ev_read_cb, rd.fd, EV_READ);
   ev_io_start (loop, (ev_io *restrict) &rd);

   ev_run (loop, 0);
   ev_loop_destroy (loop);

   free (in_buf);
   free (out_buf);
   return 0;
}
