/*
 * Copyright (C) the libgit2 contributors. All rights reserved.
 *
 * This file is part of libgit2, distributed under the GNU GPL v2 with
 * a Linking Exception. For full terms see the included COPYING file.
 */
#ifndef INCLUDE_sys_git_stream_h__
#define INCLUDE_sys_git_stream_h__

#include "git2/common.h"
#include "git2/types.h"
#include "git2/proxy.h"

GIT_BEGIN_DECL

#define GIT_STREAM_VERSION 1

/**
 * Every stream must have this struct as its first element, so the
 * API can talk to it. You'd define your stream as
 *
 *     struct my_stream {
 *             git_stream parent;
 *             ...
 *     }
 *
 * and fill the functions
 */
typedef struct git_stream {
	int version;

	int encrypted;
	int proxy_support;
	int GIT_CALLBACK(connect)(struct git_stream *);
	int GIT_CALLBACK(certificate)(git_cert **, struct git_stream *);
	int GIT_CALLBACK(set_proxy)(struct git_stream *, const git_proxy_options *proxy_opts);
	ssize_t GIT_CALLBACK(read)(struct git_stream *, void *, size_t);
	ssize_t GIT_CALLBACK(write)(struct git_stream *, const char *, size_t, int);
	int GIT_CALLBACK(close)(struct git_stream *);
	void GIT_CALLBACK(free)(struct git_stream *);
} git_stream;

#ifndef GIT_DEPRECATE_HARD

/**
 * @deprecated Provide a git_stream_registration to git_stream_register
 * @see git_stream_registration
 */
typedef int GIT_CALLBACK(git_stream_cb)(git_stream **out, const char *host, const char *port);

/**
 * Register a TLS stream constructor for the library to use.  This stream
 * will not support HTTP CONNECT proxies.  This internally calls
 * `git_stream_register` and is preserved for backward compatibility.
 *
 * This function is deprecated, but there is no plan to remove this
 * function at this time.
 *
 * @deprecated Provide a git_stream_registration to git_stream_register
 * @see git_stream_register
 */
GIT_EXTERN(int) git_stream_register_tls(git_stream_cb ctor);

/**@}*/

#endif

GIT_END_DECL

#endif
