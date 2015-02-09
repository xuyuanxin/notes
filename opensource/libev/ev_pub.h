typedef struct ev_watcher
{
    int active; 
    int pending;
    int priority;
    void *data; 
    void (*cb)(struct ev_loop *loop, struct ev_watcher *w, int revents);
} ev_watcher;

typedef struct ev_watcher_list
{
    int active; 
    int pending;
    int priority;
    void *data; 
    void (*cb)(struct ev_loop *loop, struct ev_watcher_list *w, int revents);
    struct ev_watcher_list *next;
} ev_watcher_list;

union ev_any_watcher
{
  struct ev_watcher w;
  struct ev_watcher_list wl;    
  struct ev_io io;
  struct ev_timer timer;
  struct ev_periodic periodic;
  struct ev_signal signal;
  struct ev_child child;
  struct ev_stat stat;
  struct ev_idle idle;
  struct ev_prepare prepare;
  struct ev_check check;
  struct ev_fork fork;
  struct ev_cleanup cleanup;
  struct ev_embed embed;
  struct ev_async async;
};

/* 定时器watcher */
typedef struct ev_watcher_time
{
    int active; 
    int pending;
    int priority;
    void *data; 
    void (*cb)(struct ev_loop *loop, struct ev_watcher_time *w, int revents);

    ev_tstamp at;     /* 这个at就是派生类中新的自有成员 ，表示的是at时间触发 */
} ev_watcher_time;


/* 信号watcher */
typedef struct ev_signal
{
    int active; 
    int pending;
    int priority;
    void *data; 
    void (*cb)(struct ev_loop *loop, struct ev_signal *w, int revents);
    struct ev_watcher_list *next;

    int signum; /* 这个signum就是派生类中新的自有成员 ，表示的是接收到的信号，和定时器中的at类似 */
} ev_signal;


