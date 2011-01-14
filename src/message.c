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

#include "belle_sip_internal.h"

int belle_sip_message_is_request(belle_sip_message_t *msg){
	return 0;
}

int belle_sip_message_is_response(belle_sip_message_t *msg){
	return 0;
}

belle_sip_header_t *belle_sip_message_get_header_last(belle_sip_message_t *msg, const char *header_name){
	return NULL;
}

char *belle_sip_message_to_string(belle_sip_message_t *msg){
	return NULL;
}