/*
	belle-sip - SIP (RFC3261) library.
    Copyright (C) 2010  Belledonne Communications SARL

    This program is free software: you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation, either version 3 of the License, or
    (at your option) any later version.

    This program is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.

    You should have received a copy of the GNU General Public License
    along with this program.  If not, see <http://www.gnu.org/licenses/>.
*/
#ifndef BELLE_SIP_CHANNEL_H
#define BELLE_SIP_CHANNEL_H

#ifndef WIN32
#include <sys/types.h>
#include <sys/socket.h>
#else

#endif

static const int belle_sip_network_buffer_size=65535;

typedef enum belle_sip_channel_state{
	BELLE_SIP_CHANNEL_INIT,
	BELLE_SIP_CHANNEL_RES_IN_PROGRESS,
	BELLE_SIP_CHANNEL_RES_DONE,
	BELLE_SIP_CHANNEL_CONNECTING,
	BELLE_SIP_CHANNEL_READY,
	BELLE_SIP_CHANNEL_ERROR
}belle_sip_channel_state_t;


/**
* belle_sip_channel_t is an object representing a single communication channel ( socket or file descriptor), 
* unlike the belle_sip_listening_point_t that can owns several channels for TCP or TLS (incoming server child sockets or 
* outgoing client sockets).
**/
typedef struct belle_sip_channel belle_sip_channel_t;

BELLE_SIP_DECLARE_INTERFACE_BEGIN(belle_sip_channel_listener_t)
void (*on_state_changed)(belle_sip_channel_listener_t *obj, belle_sip_channel_t *, belle_sip_channel_state_t state);
BELLE_SIP_DECLARE_INTERFACE_END

struct belle_sip_channel{
	belle_sip_source_t base;
	belle_sip_stack_t *stack;
	belle_sip_channel_state_t state;
	belle_sip_list_t *listeners;
	char *peer_name;
	int peer_port;
	unsigned long resolver_id;
	struct addrinfo *peer;
	belle_sip_message_t *msg;
};

#define BELLE_SIP_CHANNEL(obj)		BELLE_SIP_CAST(obj,belle_sip_channel_t)

belle_sip_channel_t * belle_sip_channel_new_udp(belle_sip_stack_t *stack, int sock, const char *peername, int peerport);

belle_sip_channel_t * belle_sip_channel_new_tcp(belle_sip_stack_t *stack, const char *name, int port);

void belle_sip_channel_add_listener(belle_sip_channel_t *chan, belle_sip_channel_listener_t *l);

void belle_sip_channel_remove_listener(belle_sip_channel_t *obj, belle_sip_channel_listener_t *l);

int belle_sip_channel_matches(const belle_sip_channel_t *obj, const char *peername, int peerport, struct addrinfo *addr);

int belle_sip_channel_resolve(belle_sip_channel_t *obj);

int belle_sip_channel_connect(belle_sip_channel_t *obj);

int belle_sip_channel_send(belle_sip_channel_t *obj, const void *buf, size_t buflen);

int belle_sip_channel_recv(belle_sip_channel_t *obj, void *buf, size_t buflen);

int belle_sip_channel_queue_message(belle_sip_channel_t *obj, belle_sip_message_t *msg);

int belle_sip_channel_is_reliable(const belle_sip_channel_t *obj);

const char * chain_sip_channel_get_transport_name(const belle_sip_channel_t *obj);

const struct addrinfo * belle_sip_channel_get_peer(belle_sip_channel_t *obj);


BELLE_SIP_DECLARE_CUSTOM_VPTR_BEGIN(belle_sip_channel_t,belle_sip_source_t)
	const char *transport;
	int reliable;
	int (*connect)(belle_sip_channel_t *obj, const struct sockaddr *, socklen_t socklen);
	int (*channel_send)(belle_sip_channel_t *obj, const void *buf, size_t buflen);
	int (*channel_recv)(belle_sip_channel_t *obj, void *buf, size_t buflen);
BELLE_SIP_DECLARE_CUSTOM_VPTR_END

BELLE_SIP_DECLARE_CUSTOM_VPTR_BEGIN(belle_sip_udp_channel_t,belle_sip_channel_t)
BELLE_SIP_DECLARE_CUSTOM_VPTR_END

#endif