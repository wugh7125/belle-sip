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
#ifndef BELLE_SIP_H
#define BELLE_SIP_H

#include <stdlib.h>

#ifdef __cplusplus
#define BELLE_SIP_BEGIN_DECLS		extern "C"{
#define BELLE_SIP_END_DECLS		}
#else
#define BELLE_SIP_BEGIN_DECLS
#define BELLE_SIP_END_DECLS
#endif

#define BELLE_SIP_TYPE_ID(_type) _type##_id

typedef enum belle_sip_type_id{
	belle_sip_type_id_first=1,
	BELLE_SIP_TYPE_ID(belle_sip_stack_t),
	BELLE_SIP_TYPE_ID(belle_sip_listening_point_t),
	BELLE_SIP_TYPE_ID(belle_sip_datagram_listening_point_t),
	BELLE_SIP_TYPE_ID(belle_sip_udp_listening_point_t),
	BELLE_SIP_TYPE_ID(belle_sip_channel_t),
	BELLE_SIP_TYPE_ID(belle_sip_udp_channel_t),
	BELLE_SIP_TYPE_ID(belle_sip_provider_t),
	BELLE_SIP_TYPE_ID(belle_sip_main_loop_t),
	BELLE_SIP_TYPE_ID(belle_sip_source_t),
	BELLE_SIP_TYPE_ID(belle_sip_transaction_t),
	BELLE_SIP_TYPE_ID(belle_sip_server_transaction_t),
	BELLE_SIP_TYPE_ID(belle_sip_client_transaction_t),
	BELLE_SIP_TYPE_ID(belle_sip_dialog_t),
	BELLE_SIP_TYPE_ID(belle_sip_header_address_t),
	BELLE_SIP_TYPE_ID(belle_sip_header_contact_t),
	BELLE_SIP_TYPE_ID(belle_sip_header_from_t),
	BELLE_SIP_TYPE_ID(belle_sip_header_to_t),
	BELLE_SIP_TYPE_ID(belle_sip_header_via_t),
	BELLE_SIP_TYPE_ID(belle_sip_uri_t),
	BELLE_SIP_TYPE_ID(belle_sip_message_t),
	BELLE_SIP_TYPE_ID(belle_sip_request_t),
	BELLE_SIP_TYPE_ID(belle_sip_response_t),
	BELLE_SIP_TYPE_ID(belle_sip_object_t),
	BELLE_SIP_TYPE_ID(belle_sip_parameters_t),
	BELLE_SIP_TYPE_ID(belle_sip_header_callid_t),
	BELLE_SIP_TYPE_ID(belle_sip_header_cseq_t),
	BELLE_SIP_TYPE_ID(belle_sip_header_content_type_t),
	BELLE_SIP_TYPE_ID(belle_sip_sender_task_t),
	belle_sip_type_id_end
}belle_sip_type_id_t;


/**
 * belle_sip_object_t is the base object.
 * It is the base class for all belle sip non trivial objects.
 * It owns a reference count which allows to trigger the destruction of the object when the last
 * user of it calls belle_sip_object_unref().
**/

typedef struct _belle_sip_object belle_sip_object_t;

BELLE_SIP_BEGIN_DECLS

int belle_sip_object_is_unowed(const belle_sip_object_t *obj);

/**
 * Increments reference counter, which prevents the object from being destroyed.
 * If the object is initially unowed, this acquires the first reference.
**/
belle_sip_object_t * belle_sip_object_ref(void *obj);

/**
 * Decrements the reference counter. When it drops to zero, the object is destroyed.
**/
void belle_sip_object_unref(void *obj);

/**
 * Destroy the object: this function is intended for unowed object, that is objects
 * that were created with a 0 reference count.
**/
void belle_sip_object_destroy(void *obj);

void *belle_sip_object_cast(belle_sip_object_t *obj, belle_sip_type_id_t id, const char *castname, const char *file, int fileno);

BELLE_SIP_END_DECLS

#define BELLE_SIP_CAST(obj,_type) 		((_type*)belle_sip_object_cast((belle_sip_object_t *)(obj), _type##_id, #_type, __FILE__, __LINE__))
#define BELLE_SIP_OBJECT(obj) BELLE_SIP_CAST(obj,belle_sip_object_t)



typedef struct belle_sip_listening_point belle_sip_listening_point_t;
typedef struct belle_sip_stack belle_sip_stack_t;
typedef struct belle_sip_provider belle_sip_provider_t;
typedef struct belle_sip_listener belle_sip_listener_t;
typedef struct belle_sip_dialog belle_sip_dialog_t;

#include "belle-sip/list.h"
#include "belle-sip/mainloop.h"
#include "belle-sip/uri.h"
#include "belle-sip/headers.h"
#include "belle-sip/parameters.h"
#include "belle-sip/message.h"
#include "belle-sip/transaction.h"
#include "belle-sip/dialog.h"
#include "belle-sip/sipstack.h"
#include "belle-sip/listeningpoint.h"
#include "belle-sip/provider.h"
#include "belle-sip/listener.h"

#undef TRUE
#define TRUE 1


#undef FALSE
#define FALSE 0

#endif