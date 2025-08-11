/*
 *
 *      "Marcy's Nice Libs" v1.0.0
 *
 *      A friendly network library. Easy and simple!
 *
 */

#ifndef NL_NET_H
#define NL_NET_H

#define NL_NET_VERSION 1

#define NL_NET_BACKLOG 16

// Creates listening socket. Takes hostname and port
// Returns file descriptor of socket, or -1 on error
int nl_net_listen(const char *host, const char *port);

// Accepts new connection. Takes server file descriptor
// Returns file descriptor of socket, or -1 on error
int nl_net_accept(int fd);

#endif // NL_NET_H
