/*********************************************************************
 * PicoTCP-NG
 * Copyright (c) 2020 Daniele Lacamera <root@danielinux.net>
 *
 * This file also includes code from:
 * PicoTCP
 * Copyright (c) 2012-2017 Altran Intelligent Systems
 *
 * SPDX-License-Identifier: GPL-2.0-only OR GPL-3.0-only
 *
 * PicoTCP-NG is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 2 of the License, or
 * (at your option) version 3.
 *
 * PicoTCP-NG is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA 02110-1335, USA
 *
 *
 *********************************************************************/
#ifndef INCLUDE_PICO_DNS_SD
#define INCLUDE_PICO_DNS_SD

#include "pico_mdns.h"

typedef struct
{
    char *key;
    char *value;
} key_value_pair_t;

typedef struct
{
    key_value_pair_t **pairs;
    uint16_t count;
} kv_vector;

#define PICO_DNS_SD_KV_VECTOR_DECLARE(name) \
    kv_vector (name) = {0}

/* ****************************************************************************
 *  Maximum length of a key-value pair.
 * ****************************************************************************/
#define PICO_DNS_SD_KV_MAXLEN (0xFFFFu)

/* ****************************************************************************
 *  Just calls pico_mdns_init in it's turn to initialise the mDNS-module.
 *  See pico_mdns.h for description.
 * ****************************************************************************/
int
pico_dns_sd_init( const char *_hostname,
                  struct pico_ip4 address,
                  void (*callback)(pico_mdns_rtree *,
                                   char *,
                                   void *),
                  void *arg );

/* ****************************************************************************
 *  Register a DNS-SD service via Multicast DNS on the local network.
 *
 *  @param name     Instance Name of the service, f.e. "Printer 2nd Floor".
 *  @param type     ServiceType of the service, f.e. "_http._tcp".
 *  @param port     Port number on which the service runs.
 *  @param txt_data TXT data to create TXT record with, need kv_vector-type,
 *                  Declare such a type with PICO_DNS_SD_KV_VECTOR_DECLARE(*) &
 *                  add key-value pairs with pico_dns_sd_kv_vector_add().
 *  @param ttl      TTL
 *  @param callback Callback-function to call when the service is registered.
 *  @return
 * ****************************************************************************/
int
pico_dns_sd_register_service( const char *name,
                              const char *type,
                              uint16_t port,
                              kv_vector *txt_data,
                              uint16_t ttl,
                              void (*callback)(pico_mdns_rtree *,
                                               char *,
                                               void *),
                              void *arg);

/* ****************************************************************************
 *  Does nothing for now.
 *
 *  @param type     Type to browse for.
 *  @param callback Callback to call when something particular happens.
 *  @return When the module successfully started browsing the servicetype.
 * ****************************************************************************/
int
pico_dns_sd_browse_service( const char *type,
                            void (*callback)(pico_mdns_rtree *,
                                             char *,
                                             void *),
                            void *arg );

/* ****************************************************************************
 *  Add a key-value pair the a key-value pair vector.
 *
 *  @param vector Vector to add the pair to.
 *  @param key    Key of the pair, cannot be NULL.
 *  @param value  Value of the pair, can be NULL, empty ("") or filled ("qkejq")
 *  @return Returns 0 when the pair is added successfully, something else on
 *			failure.
 * ****************************************************************************/
int
pico_dns_sd_kv_vector_add( kv_vector *vector, char *key, char *value );


#endif /* _INCLUDE_PICO_DNS_SD */
