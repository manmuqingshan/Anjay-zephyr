/*
 * Copyright 2020-2023 AVSystem <avsystem@avsystem.com>
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

#pragma once

#include <stddef.h>

#include <zephyr/net/sntp.h>

#ifdef CONFIG_ANJAY_ZEPHYR_FOTA
#    include <zephyr/dfu/mcuboot.h>
#endif // CONFIG_ANJAY_ZEPHYR_FOTA

struct anjay_zephyr_device_id {
    // 96 bits as hex + NULL-byte
    char value[25];
};

int _anjay_zephyr_get_device_id(struct anjay_zephyr_device_id *out_id);

#ifdef CONFIG_ANJAY_ZEPHYR_FOTA
int _anjay_zephyr_get_fw_version_image_0(char *out_buf, size_t buf_size);
int _anjay_zephyr_get_fw_version_image_1(char *out_buf, size_t buf_size);
#endif // CONFIG_ANJAY_ZEPHYR_FOTA

#define SYNCHRONIZED(Mtx)                                          \
    for (int _synchronized_exit = k_mutex_lock(&(Mtx), K_FOREVER); \
         !_synchronized_exit;                                      \
         _synchronized_exit = -1, k_mutex_unlock(&(Mtx)))

#if defined(CONFIG_NRF_MODEM_LIB) && defined(CONFIG_MODEM_KEY_MGMT)
int _anjay_zephyr_tls_session_cache_purge(void);
#endif // defined(CONFIG_NRF_MODEM_LIB) && defined(CONFIG_MODEM_KEY_MGMT)

#ifdef CONFIG_NET_IPV6
int _anjay_zephyr_sntp_simple_ipv6(const char *server,
                                   uint32_t timeout,
                                   struct sntp_time *time);
#endif // CONFIG_NET_IPV6
