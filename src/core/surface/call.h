/*
 *
 * Copyright 2014, Google Inc.
 * All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions are
 * met:
 *
 *     * Redistributions of source code must retain the above copyright
 * notice, this list of conditions and the following disclaimer.
 *     * Redistributions in binary form must reproduce the above
 * copyright notice, this list of conditions and the following disclaimer
 * in the documentation and/or other materials provided with the
 * distribution.
 *     * Neither the name of Google Inc. nor the names of its
 * contributors may be used to endorse or promote products derived from
 * this software without specific prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS
 * "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT
 * LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR
 * A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT
 * OWNER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL,
 * SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT
 * LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE,
 * DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY
 * THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
 * (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
 * OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 *
 */

#ifndef __GRPC_INTERNAL_SURFACE_CALL_H__
#define __GRPC_INTERNAL_SURFACE_CALL_H__

#include "src/core/channel/channel_stack.h"
#include "src/core/channel/metadata_buffer.h"
#include <grpc/grpc.h>

grpc_call *grpc_call_create(grpc_channel *channel,
                            const void *server_transport_data);

void grpc_call_internal_ref(grpc_call *call);
void grpc_call_internal_unref(grpc_call *call);

/* Helpers for grpc_client, grpc_server filters to publish received data to
   the completion queue/surface layer */
void grpc_call_recv_metadata(grpc_call_element *surface_element,
                             grpc_call_op *op);
void grpc_call_recv_message(
    grpc_call_element *surface_element, grpc_byte_buffer *message,
    void (*on_finish)(void *user_data, grpc_op_error error), void *user_data);
void grpc_call_recv_finish(grpc_call_element *surface_element,
                           int is_full_close);

void grpc_call_execute_op(grpc_call *call, grpc_call_op *op);

/* Called when it's known that the initial batch of metadata is complete on the
   client side (must not be called on the server) */
void grpc_call_client_initial_metadata_complete(
    grpc_call_element *surface_element);

void grpc_call_set_deadline(grpc_call_element *surface_element,
                            gpr_timespec deadline);

/* Given the top call_element, get the call object. */
grpc_call *grpc_call_from_top_element(grpc_call_element *surface_element);

/* Get the metadata buffer. */
grpc_metadata_buffer *grpc_call_get_metadata_buffer(grpc_call *call);

#endif  /* __GRPC_INTERNAL_SURFACE_CALL_H__ */