/*
 * Copyright 2020-2025 AVSystem <avsystem@avsystem.com>
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *     http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */

#ifndef COMPAT_H
#define COMPAT_H

#include <zephyr/net/socket.h>
#include <zephyr/posix/time.h>

typedef int sockfd_t;

int zsock_poll_workaround(struct zsock_pollfd *fds, int nfds, int timeout_ms);

#ifndef pollfd
#    define pollfd zsock_pollfd
#endif // pollfd

#ifdef poll
#    undef poll
#endif // poll

#ifdef CONFIG_ANJAY_COMPAT_NET_LIMITED_POLL_WORKAROUND
#    define poll zsock_poll_workaround
#else // CONFIG_ANJAY_COMPAT_NET_LIMITED_POLL_WORKAROUND
#    define poll zsock_poll
#endif // CONFIG_ANJAY_COMPAT_NET_LIMITED_POLL_WORKAROUND

#ifndef POLLIN
#    define POLLIN ZSOCK_POLLIN
#endif // POLLIN

#endif /* COMPAT_H */
