#include <ev_vars.h>

struct ev_loop
{
    ev_tstamp ev_rt_now;


 ev_tstamp  now_floor; /* last time we refreshed rt_time */
 ev_tstamp  mn_now;    /* monotonic clock "now" */
 ev_tstamp  rtmn_diff; /* difference realtime - monotonic time */

/* for reverse feeding of events */
W * rfeeds;
int rfeedmax;
int rfeedcnt;

static ANPENDING *pendings [NUMPRI];
static int pendingmax [NUMPRI];
static int pendingcnt [NUMPRI];
int pendingpri; /* highest priority currently pending */
ev_prepare pending_w; /* dummy pending watcher */

ev_tstamp io_blocktime;
ev_tstamp timeout_blocktime;

    int  backend; /* loop_init() */
 int  activecnt; /* total number of active events ("refcount") */
   EV_ATOMIC_T  loop_done;  /* signal by ev_break */

   int  backend_fd; /* loop_init->epoll_init */
 ev_tstamp  backend_mintime; /* assumed typical timer resolution */
static void (*backend_modify)(EV_P_ int fd  int oev  int nev);
static void (*backend_poll)(EV_P_ ev_tstamp timeout);

    ANFD *anfds;
    int  anfdmax;

static int evpipe [2];
 ev_io  pipe_w;
 EV_ATOMIC_T  pipe_write_wanted;
 EV_ATOMIC_T  pipe_write_skipped;

#if !defined(_WIN32) || EV_GENWRAP
   pid_t  curpid; /*loop_init() */
#endif

 char  postfork;  /* true if we need to recreate kernel state after fork */

#if EV_USE_SELECT || EV_GENWRAP
 void *  vec_ri;
 void *  vec_ro;
 void *  vec_wi;
 void *  vec_wo;
#if defined(_WIN32) || EV_GENWRAP
 void *  vec_eo;
#endif
 int  vec_max;
#endif

#if EV_USE_POLL || EV_GENWRAP
 struct pollfd *  polls;
 int  pollmax;
 int  pollcnt;
 int *  pollidxs; /* maps fds into structure indices */
 int  pollidxmax;
#endif

#if EV_USE_EPOLL || EV_GENWRAP
    struct epoll_event *epoll_events;
 int  epoll_eventmax;
 int *  epoll_eperms;
 int  epoll_epermcnt;
 int  epoll_epermmax;
#endif

#if EV_USE_KQUEUE || EV_GENWRAP
 pid_t  kqueue_fd_pid;
 struct kevent *  kqueue_changes;
 int  kqueue_changemax;
 int  kqueue_changecnt;
 struct kevent *  kqueue_events;
 int  kqueue_eventmax;
#endif

#if EV_USE_PORT || EV_GENWRAP
 struct port_event *  port_events;
 int  port_eventmax;
#endif

#if EV_USE_IOCP || EV_GENWRAP
 HANDLE  iocp;
#endif

 int  *fdchanges;
 int  fdchangemax;
 int  fdchangecnt;

 ANHE *  timers;
 int  timermax;
 int  timercnt;

#if EV_PERIODIC_ENABLE || EV_GENWRAP
 ANHE *  periodics;
 int  periodicmax;
 int  periodiccnt;
#endif

#if EV_IDLE_ENABLE || EV_GENWRAP
static ev_idle **idles [NUMPRI];
static int idlemax [NUMPRI];
static int idlecnt [NUMPRI];
#endif
 int  idleall; /* total number */

 struct ev_prepare **  prepares;
 int  preparemax;
 int  preparecnt;

 struct ev_check **  checks;
 int  checkmax;
 int  checkcnt;

#if EV_FORK_ENABLE || EV_GENWRAP
 struct ev_fork **  forks;
 int  forkmax;
 int  forkcnt;
#endif

#if EV_CLEANUP_ENABLE || EV_GENWRAP
 struct ev_cleanup **  cleanups;
 int  cleanupmax;
 int  cleanupcnt;
#endif

#if EV_ASYNC_ENABLE || EV_GENWRAP
 EV_ATOMIC_T  async_pending;
 struct ev_async **  asyncs;
 int  asyncmax;
 int  asynccnt;
#endif

#if EV_USE_INOTIFY || EV_GENWRAP
 int  fs_fd;
 ev_io  fs_w;
 char  fs_2625;/* whether we are running in linux 2.6.25 or newer */
static ANFS fs_hash [EV_INOTIFY_HASHSIZE];
#endif

 EV_ATOMIC_T  sig_pending;
#if EV_USE_SIGNALFD || EV_GENWRAP
 int  sigfd;
 ev_io  sigfd_w;
 sigset_t  sigfd_set;
#endif

   unsigned int  origflags; /* loop_init() original loop flags */

#if EV_FEATURE_API || EV_GENWRAP
   unsigned int  loop_count; /* total number of loop iterations/blocks */
   unsigned int  loop_depth; /* #ev_run enters - #ev_run leaves */

 void *  userdata;
/* C++ doesn't support the ev_loop_callback typedef here. stinks. */
static void (*release_cb)(EV_P) EV_THROW;
static void (*acquire_cb)(EV_P) EV_THROW;
static ev_loop_callback invoke_cb;
#endif

};


