/*-----------------------------------------------------------------------------------
 这个就是strct loop的一个实例对象，表示的是预制事件驱动器。如果在代码中使用的是预制事
 件驱动器，那么后续的操作就都围绕着这个数据结构展开了。为了操作方便，还定义了指向该对
 象的一个全局指针。struct ev_loop称作为事件循环驱动器而将各种watcher称为事件监控器。
-----------------------------------------------------------------------------------*/


struct ev_loop *x_ev_default_loop (unsigned int flags) 
{
    if (!ev_default_loop_ptr)
    {
        #if EV_MULTIPLICITY
        struct ev_loop *loop = ev_default_loop_ptr = &default_loop_struct;
        #else
        ev_default_loop_ptr = 1;
        #endif

        loop_init (loop, flags);

        if (ev_backend (EV_A)) {
            #if EV_CHILD_ENABLE
            ev_signal_init (&childev, childcb, SIGCHLD);
            ev_set_priority (&childev, EV_MAXPRI);
            ev_signal_start (EV_A_ &childev);
            ev_unref (EV_A); /* child watcher should not keep loop alive */
            #endif
        } else {
            ev_default_loop_ptr = 0;
        }
    }

  return ev_default_loop_ptr;
}

/* initialise a loop structure, must be zero-initialised */
static void x_loop_init (struct ev_loop *loop, unsigned int flags)
{
    if (!backend)
    {
        loop->origflags = flags;

        #if EV_USE_REALTIME
        if (!have_realtime)
        {
            struct timespec ts;

            if (!clock_gettime (CLOCK_REALTIME, &ts))
                have_realtime = 1;
        }
        #endif

        #if EV_USE_MONOTONIC
        if (!have_monotonic)
        {
            struct timespec ts;

            if (!clock_gettime (CLOCK_MONOTONIC, &ts))
                have_monotonic = 1;
        }
        #endif

      /* pid check not overridable via env */
        #ifndef _WIN32
        if (flags & EVFLAG_FORKCHECK)
            curpid = getpid ();
        #endif

        if (!(flags & EVFLAG_NOENV) && !enable_secure () && getenv ("LIBEV_FLAGS"))
            flags = atoi (getenv ("LIBEV_FLAGS"));

        ev_rt_now          = ev_time ();
        mn_now             = get_clock ();
        now_floor          = mn_now;
        rtmn_diff          = ev_rt_now - mn_now;
        #if EV_FEATURE_API
        invoke_cb          = ev_invoke_pending;
        #endif

        io_blocktime       = 0.;
        timeout_blocktime  = 0.;
        backend            = 0;
        backend_fd         = -1;
        sig_pending        = 0;
        #if EV_ASYNC_ENABLE
        async_pending      = 0;
        #endif
        pipe_write_skipped = 0;
        pipe_write_wanted  = 0;
        evpipe [0]         = -1;
        evpipe [1]         = -1;
        #if EV_USE_INOTIFY
        fs_fd              = flags & EVFLAG_NOINOTIFY ? -1 : -2;
        #endif
        #if EV_USE_SIGNALFD
        sigfd              = flags & EVFLAG_SIGNALFD  ? -2 : -1;
        #endif

        if (!(flags & EVBACKEND_MASK))
            flags |= ev_recommended_backends ();

        #if EV_USE_IOCP
        if (!backend && (flags & EVBACKEND_IOCP  )) backend = iocp_init   (EV_A_ flags);
        #endif
        #if EV_USE_PORT
        if (!backend && (flags & EVBACKEND_PORT  )) backend = port_init   (EV_A_ flags);
        #endif
        #if EV_USE_KQUEUE
        if (!backend && (flags & EVBACKEND_KQUEUE)) backend = kqueue_init (EV_A_ flags);
        #endif
        #if EV_USE_EPOLL
        if (!backend && (flags & EVBACKEND_EPOLL )) backend = epoll_init  (EV_A_ flags);
        #endif
        #if EV_USE_POLL
        if (!backend && (flags & EVBACKEND_POLL  )) backend = poll_init   (EV_A_ flags);
        #endif
        #if EV_USE_SELECT
        if (!backend && (flags & EVBACKEND_SELECT)) backend = select_init (EV_A_ flags);
        #endif

        ev_prepare_init (&pending_w, pendingcb);

        #if EV_SIGNAL_ENABLE || EV_ASYNC_ENABLE
        ev_init (&pipe_w, pipecb);
        ev_set_priority (&pipe_w, EV_MAXPRI);
        #endif
    }
}


/*
http://my.oschina.net/u/917596/blog/177030


*/
