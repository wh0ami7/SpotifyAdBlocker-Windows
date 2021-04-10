#pragma once
#include "pch.h"
#include "capi/cef_urlrequest_capi.h"
extern "C" {
    typedef cef_urlrequest_t* (*PCEF_URLREQUEST_CREATE_T)(
        cef_request_t* request,
        cef_urlrequest_client_t* client,
        cef_request_context_t* request_context);

    typedef void (*PCEF_STRING_USERFREE_UTF16_FREE_T)(cef_string_userfree_utf16_t str);
}