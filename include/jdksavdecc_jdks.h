#pragma once

/*
  Copyright (c) 2014, J.D. Koftinoff Software, Ltd.
  All rights reserved.

  Redistribution and use in source and binary forms, with or without
  modification, are permitted provided that the following conditions are met:

   1. Redistributions of source code must retain the above copyright notice,
      this list of conditions and the following disclaimer.

   2. Redistributions in binary form must reproduce the above copyright
      notice, this list of conditions and the following disclaimer in the
      documentation and/or other materials provided with the distribution.

   3. Neither the name of J.D. Koftinoff Software, Ltd. nor the names of its
      contributors may be used to endorse or promote products derived from
      this software without specific prior written permission.

  THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
  AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
  IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE
  ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT OWNER OR CONTRIBUTORS BE
  LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR
  CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF
  SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS
  INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN
  CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE)
  ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE
  POSSIBILITY OF SUCH DAMAGE.
*/

#include "jdksavdecc_world.h"
#include "jdksavdecc_util.h"
#include "jdksavdecc_pdu.h"
#include "jdksavdecc_frame.h"
#include "jdksavdecc_aem_command.h"
#include "jdksavdecc_aem_descriptor.h"

#ifdef __cplusplus
extern "C" {
#endif

/** \addtogroup jdks Publically usable definitions and types under
 * J.D. Koftinoff Software, Ltd.'s MAC-S (OUI-36) 70-B3-D5-ED-C
 */
/*@{*/

/** \addtogroup jdks_log Logging mechanism using multicast AECP AEM Unsolicited SET_CONTROL Response
 *  to the jdks notifications controller entity id (70:b3:d5:ed:cf:ff:ff:ff) with
 *  a vendor defined blob control type.
 *  Any AEM SET_CONTROL Response sent to the multicast MAC address 71:b3:d5:ed:cf:ff and controller_entity_id
 *  of 70:b3:d5:ed:cf:ff:ff:ff may be interpreted as a vendor specific blob control value (See Clause 7.3.5.2.9)
 *  if the vendor_eui64 field is 0:b3:d5:ed:c0:00:00:00 then the message is a logging message
 *  and shall be interpreted as defined:
 *
 *      Offset  0: vendor_eui64 is JDKSAVDECC_JDKS_AEM_CONTROL_LOG_TEXT ( 70:b3:d5:ed:c0:00:00:00 )
 *      Offset  8: blob_length is 8+text_length
 *      Offset 10: Doublet: source_descriptor_type
 *      Offset 12:  Doublet: source_descriptor_index
 *      Offset 14:  Doublet: log_sequence_id log message number from this source
 *      Offset 16:  Octet: log_priority { 0 = error, 1=warning, 2=info, 3..0xffff = debug/trace
 *      Offset 17:  Octet: reserved
 *      Offset 18:  Octet array: utf8_chars[0..352] with no LF
 *
 */
/*@{*/

/// Special controller entity id used for JDKS notifications - only for use with
/// controls with value_type set to CONTROL_VENDOR.

#define JDKSAVDECC_JDKS_NOTIFICATIONS_CONTROLLER_ENTITY_ID \
    { \
        { 0x70, 0xb3, 0xd5, 0xed, 0xcf, 0xff, 0xff, 0xff } \
    }

extern struct jdksavdecc_eui64 jdksavdecc_jdks_notifications_controller_entity_id;


/// Multicast MAC address 71:b3:d5:ed:cf:ff is reserved for logging via
/// unsolicited SET_CONTROL of control descriptor of control type JDKSAVDECC_JDKS_AEM_CONTROL_LOG_TEXT
#define JDKSAVDECC_JDKS_MULTICAST_LOG                                                                                          \
    {                                                                                                                          \
        { 0x71, 0xb3, 0xd5, 0xed, 0xcf, 0xff }                                                                                 \
    }

extern struct jdksavdecc_eui48 jdksavdecc_jdks_multicast_log;


#define JDKSAVDECC_JDKS_AEM_CONTROL_LOG_TEXT \
    { \
        { 0x70, 0xb3, 0xd5, 0xed, 0xc0, 0x00, 0x00, 0x00 } \
    }

extern struct jdksavdecc_eui64 jdksavdecc_jdks_aem_control_log_text;

#define JDKSAVDECC_JDKS_LOG_CONTROL_OFFSET_VENDOR_EUI64 (JDKSAVDECC_AEM_COMMAND_SET_CONTROL_RESPONSE_LEN + 0)
#define JDKSAVDECC_JDKS_LOG_CONTROL_OFFSET_BLOB_SIZE (JDKSAVDECC_AEM_COMMAND_SET_CONTROL_RESPONSE_LEN + 8)
#define JDKSAVDECC_JDKS_LOG_CONTROL_OFFSET_SOURCE_DESCRIPTOR_TYPE (JDKSAVDECC_AEM_COMMAND_SET_CONTROL_RESPONSE_LEN + 10)
#define JDKSAVDECC_JDKS_LOG_CONTROL_OFFSET_SOURCE_DESCRIPTOR_INDEX (JDKSAVDECC_AEM_COMMAND_SET_CONTROL_RESPONSE_LEN + 12)
#define JDKSAVDECC_JDKS_LOG_CONTROL_OFFSET_LOG_SEQUENCE_ID (JDKSAVDECC_AEM_COMMAND_SET_CONTROL_RESPONSE_LEN + 14)
#define JDKSAVDECC_JDKS_LOG_CONTROL_OFFSET_LOG_DETAIL (JDKSAVDECC_AEM_COMMAND_SET_CONTROL_RESPONSE_LEN + 16)
#define JDKSAVDECC_JDKS_LOG_CONTROL_OFFSET_RESERVED (JDKSAVDECC_AEM_COMMAND_SET_CONTROL_RESPONSE_LEN + 17)
#define JDKSAVDECC_JDKS_LOG_CONTROL_OFFSET_TEXT (JDKSAVDECC_AEM_COMMAND_SET_CONTROL_RESPONSE_LEN + 18)
#define JDKSAVDECC_JDKS_LOG_CONTROL_HEADER_LEN JDKSAVDECC_JDKS_LOG_CONTROL_OFFSET_TEXT
#define JDKSAVDECC_JDKS_LOG_CONTROL_MAX_TEXT_LEN (JDKSAVDECC_AEM_CONTROL_VALUE_TYPE_BLOB_MAX_SIZE - JDKSAVDECC_JDKS_LOG_CONTROL_HEADER_LEN - JDKSAVDECC_AEM_COMMAND_SET_CONTROL_RESPONSE_LEN)


struct jdksavdecc_jdks_log_control {
    struct jdksavdecc_aem_command_set_control_response cmd;
    struct jdksavdecc_eui64 vendor_eui64;
    uint16_t blob_size;
    uint16_t source_descriptor_type;
    uint16_t source_descriptor_index;
    uint16_t log_sequence_id;
    uint8_t log_detail;
    uint8_t reserved;
    uint8_t text[JDKSAVDECC_JDKS_LOG_CONTROL_MAX_TEXT_LEN+1];
};


static inline ssize_t jdksavdecc_jdks_log_control_generate(
        struct jdksavdecc_eui64 const *my_entity_id,
        uint16_t descriptor_index,
        uint16_t source_descriptor_type,
        uint16_t source_descriptor_index,
        uint16_t *aecp_sequence_id,
        uint16_t *logging_sequence_id,
        uint8_t log_detail,
        uint8_t reserved,
        const char *utf8_log_string,
        void *buf,
        ssize_t pos,
        size_t len ) {
    ssize_t text_len = (ssize_t)strlen(utf8_log_string);
    ssize_t expected_length = JDKSAVDECC_JDKS_LOG_CONTROL_HEADER_LEN + text_len;
    ssize_t r = jdksavdecc_validate_range(pos,len,expected_length);
    if( r>=0 ) {
        struct jdksavdecc_aem_command_set_control_response setctrl;
        setctrl.aem_header.aecpdu_header.header.cd = true;
        setctrl.aem_header.aecpdu_header.header.subtype = JDKSAVDECC_SUBTYPE_AECP;
        setctrl.aem_header.aecpdu_header.header.sv = false;
        setctrl.aem_header.aecpdu_header.header.version = 0;
        setctrl.aem_header.aecpdu_header.header.message_type = JDKSAVDECC_AECP_MESSAGE_TYPE_AEM_RESPONSE;
        setctrl.aem_header.aecpdu_header.header.status = JDKSAVDECC_AEM_STATUS_SUCCESS;
        setctrl.aem_header.aecpdu_header.header.control_data_length = text_len + JDKSAVDECC_JDKS_LOG_CONTROL_HEADER_LEN - JDKSAVDECC_COMMON_CONTROL_HEADER_LEN;
        setctrl.aem_header.aecpdu_header.header.target_entity_id = *my_entity_id;
        setctrl.aem_header.aecpdu_header.controller_entity_id = jdksavdecc_jdks_notifications_controller_entity_id;
        setctrl.aem_header.aecpdu_header.sequence_id = *aecp_sequence_id;
        setctrl.aem_header.command_type = JDKSAVDECC_AEM_COMMAND_SET_CONTROL | 0x8000;
        setctrl.descriptor_type = JDKSAVDECC_DESCRIPTOR_CONTROL;
        setctrl.descriptor_index = descriptor_index;
        jdksavdecc_aem_command_set_control_response_write(&setctrl, buf, pos, len);
        jdksavdecc_eui64_write( &jdksavdecc_jdks_aem_control_log_text, buf, pos+JDKSAVDECC_JDKS_LOG_CONTROL_OFFSET_VENDOR_EUI64, len );
        jdksavdecc_uint16_write( text_len + JDKSAVDECC_JDKS_LOG_CONTROL_HEADER_LEN - JDKSAVDECC_AEM_COMMAND_SET_CONTROL_RESPONSE_LEN,
                                 buf,pos + JDKSAVDECC_JDKS_LOG_CONTROL_OFFSET_BLOB_SIZE,
                                 len );
        jdksavdecc_uint16_write( source_descriptor_type,
                                 buf,pos + JDKSAVDECC_JDKS_LOG_CONTROL_OFFSET_SOURCE_DESCRIPTOR_TYPE,
                                 len );
        jdksavdecc_uint16_write( source_descriptor_index,
                                 buf,pos + JDKSAVDECC_JDKS_LOG_CONTROL_OFFSET_SOURCE_DESCRIPTOR_INDEX,
                                 len );
        jdksavdecc_uint16_write( *logging_sequence_id,
                                 buf,pos + JDKSAVDECC_JDKS_LOG_CONTROL_OFFSET_LOG_SEQUENCE_ID,
                                 len );
        jdksavdecc_uint8_write( log_detail,
                                 buf,pos + JDKSAVDECC_JDKS_LOG_CONTROL_OFFSET_LOG_DETAIL,
                                 len );
        jdksavdecc_uint8_write( reserved,
                                 buf,pos + JDKSAVDECC_JDKS_LOG_CONTROL_OFFSET_RESERVED,
                                 len );
        memcpy( ((uint8_t *)buf) + pos + JDKSAVDECC_JDKS_LOG_CONTROL_OFFSET_TEXT, utf8_log_string, text_len );
        *aecp_sequence_id = *aecp_sequence_id + 1;
        *logging_sequence_id = *logging_sequence_id + 1;
    }
    return r;
}

static inline ssize_t jdksavdecc_jdks_log_control_read(
    struct jdksavdecc_jdks_log_control *p,
    void const *buf,
    ssize_t pos,
    size_t len) {
    ssize_t r = jdksavdecc_validate_range(pos,len,JDKSAVDECC_JDKS_LOG_CONTROL_HEADER_LEN);
    if( r>=0 ) {
        jdksavdecc_eui64_read(&p->vendor_eui64, buf, JDKSAVDECC_JDKS_LOG_CONTROL_OFFSET_VENDOR_EUI64+pos, len);
        if( jdksavdecc_eui64_compare(&jdksavdecc_jdks_aem_control_log_text,&p->vendor_eui64)==0 ) {
            jdksavdecc_uint16_read(&p->blob_size, buf, JDKSAVDECC_JDKS_LOG_CONTROL_OFFSET_BLOB_SIZE+pos);
            if( p->blob_size > (JDKSAVDECC_JDKS_LOG_CONTROL_OFFSET_TEXT-JDKSAVDECC_AEM_COMMAND_SET_CONTROL_RESPONSE_LEN) &&
                p->blob_size <= JDKSAVDECC_AEM_CONTROL_VALUE_TYPE_BLOB_MAX_SIZE ) {
                uint16_t text_len =p->blob_size - (JDKSAVDECC_JDKS_LOG_CONTROL_OFFSET_TEXT-JDKSAVDECC_AEM_COMMAND_SET_CONTROL_RESPONSE_LEN);
                jdksavdecc_uint16_read(
                    &p->source_descriptor_type,
                    buf,
                    JDKSAVDECC_JDKS_LOG_CONTROL_OFFSET_SOURCE_DESCRIPTOR_TYPE+pos);

                jdksavdecc_uint16_read(
                    &p->source_descriptor_index,
                    buf,
                    JDKSAVDECC_JDKS_LOG_CONTROL_OFFSET_SOURCE_DESCRIPTOR_INDEX +pos);

                jdksavdecc_uint16_read(
                    &p->log_sequence_id,
                    buf,
                    JDKSAVDECC_JDKS_LOG_CONTROL_OFFSET_LOG_SEQUENCE_ID +pos);

                jdksavdecc_uint8_read(
                    &p->log_detail,
                    buf,
                    JDKSAVDECC_JDKS_LOG_CONTROL_OFFSET_LOG_DETAIL,
                    len );

                if( text_len < JDKSAVDECC_JDKS_LOG_CONTROL_MAX_TEXT_LEN ) {
                    r=pos+JDKSAVDECC_JDKS_LOG_CONTROL_OFFSET_TEXT;
                    memcpy( p->text, (uint8_t const *)buf+r, text_len);
                    p->text[text_len+1]='\0';
                    r+=text_len;
                } else {
                    r=-1;
                }
            } else {
                r=-1;
            }
        } else {
        r=-1;
        }
    }
    return r;
}


/*@}*/

/** \addtogroup jdks_ipv4 JDKS Vendor specific blob control type for setting/getting ethernet port IPv4 parameters
 */
/*@{*/

/// Control type for setting IPv4 parameters
///
/// vendor_eui64 is JDKSAVDECC_JDKS_AEM_CONTROL_IPV4_PARAMETERS ( 70:b3:d5:ed:c0:00:00:01 )
///
/// BLOB contains:
///     Doublet interface_descriptor_type
///     Doublet interface_descriptor_index
///     Quadlet flags:
///         bit 0 = static_enable
///         bit 1 = link_local_enable
///         bit 2 = dhcp_enable
///         bit 3 = ipv4_address_valid
///         bit 4 = ipv4_netmask_valid
///         bit 5 = ipv4_gateway_valid
///         bit 6 = ipv4_broadcast_valid
///         bit 7 = dnsserver1_valid
///         bit 8 = dnsserver2_valid
///     Quadlet ipv4_address
///     Quadlet ipv4_netmask
///     Quadlet ipv4_gateway
///     Quadlet ipv4_broadcast
///     Quadlet ipv4_dnsserver1
///     Quadlet ipv4_dnsserver2


/// Control type for setting/getting network IPV4 parameters
#define JDKSAVDECC_JDKS_AEM_CONTROL_IPV4_PARAMETERS \
    {\
        { 0x70, 0xb3, 0xd5, 0xed, 0xc0, 0x00, 0x00, 0x01 } \
    }

extern struct jdksavdecc_eui64 jdksavdecc_jdks_aem_control_ipv4_parameters;

/*@}*/

#ifdef __cplusplus
}
#endif