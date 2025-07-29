/*      
 *      "Marcy's Nice Libs" v1.0.0
 *
 *      A friendly network library. Easy and simple!
 *
 *      To use:
 *	    #define MNL_NET_IMPL
 *	before including the header file, like so
 *	
 *	#include ...
 *	#define MNL_NET_IMPL
 *	#include "mnl_net.h"
 */

#ifndef MNL_NET_H
#define MNL_NET_H

#define MNL_NET_VERSION 1

#define MNL_NET_BACKLOG 16

// Creates listening socket. Takes hostname and port
// Returns file descriptor of socket, or -1 on error
int mnl_net_listen(const char *host, const char *port);

// Accepts new connection. Takes server file descriptor
// Returns file descriptor of socket, or -1 on error
int mnl_net_accept(int fd);

#endif // MNL_NET_H

#ifdef MNL_NET_IMPL

#include <arpa/inet.h>
#include <fcntl.h>
#include <netdb.h>
#include <netinet/in.h>
#include <netinet/tcp.h>
#include <stdio.h>
#include <string.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <sys/un.h>
#include <unistd.h>

static int mnl_net_set_nonblock(int fd)
{
	int flags, res;

	flags = fcntl(fd, F_GETFL, 0);
	if (flags == -1) {
		perror("nf_set_nonblock fcntl F_GETFL");
		return -1;
	}
	res = fcntl(fd, F_SETFL, flags | O_NONBLOCK);
	if (res == -1) {
		perror("nf_set_nonblock fcntl F_SETFL");
		return -1;
	}

	return 0;
}

static int mnl_net_bind(const char *host, const char *port)
{
	struct addrinfo hints, *res, *rp;
	int sfd;
	int yes = 1;
	
	memset(&hints, 0, sizeof(hints));
	hints.ai_family = AF_INET;
	hints.ai_socktype = SOCK_STREAM;
	hints.ai_flags = AI_PASSIVE;

	if (getaddrinfo(host, port, &hints, &res) != 0) {
		perror("nf_bind_conn() getaddrinfo");
		return -1;
	}

	for (rp = res; rp; rp = rp->ai_next) {
		if ((sfd = socket(rp->ai_family, rp->ai_socktype, rp->ai_protocol)) == -1) {
			perror("nf_bind_conn socket");
			continue;
		}
		if (setsockopt(sfd, SOL_SOCKET, SO_REUSEADDR, &yes, sizeof(int)) == -1) {
			perror("nf_bind_conn setsockopt");
			return -1;
		}
		if ((bind(sfd, rp->ai_addr, rp->ai_addrlen)) == -1) {
			close(sfd);
			perror("nf_bind_conn bind");
			continue;
		}

		break;
	}

	freeaddrinfo(res);
	
	if (!rp) {
		fprintf(stderr, "nf_bind_conn failed to bind\n");
		return -1;
	}

	return sfd;
}

static void *mnl_net_getinaddr(struct sockaddr *sa)
{
	if (sa->sa_family == AF_INET)
		return &(((struct sockaddr_in *)sa)->sin_addr);

	return &(((struct sockaddr_in6 *)sa)->sin6_addr);
}


int mnl_net_listen(const char *host, const char *port)
{
	int fd;

	if ((fd = mnl_net_bind(host, port)) == -1)
		return -1;
	if ((mnl_net_set_nonblock(fd)) == -1) {
		return -1;
	}
	if ((listen(fd, MNL_NET_BACKLOG)) == -1) {
		perror("nf_listen_conn listen");
		return -1;
	}

	return fd;
}

int mnl_net_accept(int fd)
{
	int clientfd;
	struct sockaddr_storage client_addr;
	socklen_t addrlen = sizeof(client_addr);
	char ipbuf[INET_ADDRSTRLEN + 1];

	if ((clientfd = accept(fd, (struct sockaddr *)&client_addr, &addrlen)) < 0) {
		perror("nf_accept_conn accept");
		return -1;
	}
	
	if ((mnl_net_set_nonblock(clientfd)) == -1) {
		close(clientfd);
		return -1;
	}

	if (inet_ntop(client_addr.ss_family, 
				mnl_net_getinaddr((struct sockaddr *)&client_addr),
				ipbuf, sizeof(ipbuf)) == NULL) {
		close(clientfd);
		return -1;
	}

	return clientfd;
}

#endif // MNL_NET_IMPL
