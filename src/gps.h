/*
 * Copyright 2020-2025 AVSystem <avsystem@avsystem.com>
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

#include <stdatomic.h>
#include <stdbool.h>

#include <zephyr/kernel.h>

#ifdef CONFIG_ANJAY_ZEPHYR_GPS
struct anjay_zephyr_gps_data {
    bool valid;
    int64_t timestamp;
    double latitude;
    double longitude;
#    ifdef CONFIG_ANJAY_ZEPHYR_GPS_ALTITUDE
    double altitude;
#    endif // CONFIG_ANJAY_ZEPHYR_GPS_ALTITUDE
#    ifdef CONFIG_ANJAY_ZEPHYR_GPS_RADIUS
    double radius;
#    endif // CONFIG_ANJAY_ZEPHYR_GPS_RADIUS
#    ifdef CONFIG_ANJAY_ZEPHYR_GPS_VELOCITY
// TODO: implement velocity binary format as in 3GPP-TS_23.032
#        error "velocity binary format not implemented yet"
#    endif // CONFIG_ANJAY_ZEPHYR_GPS_VELOCITY
#    ifdef CONFIG_ANJAY_ZEPHYR_GPS_SPEED
    double speed;
#    endif // CONFIG_ANJAY_ZEPHYR_GPS_SPEED
};

extern struct k_mutex anjay_zephyr_gps_read_last_mtx;
extern struct anjay_zephyr_gps_data anjay_zephyr_gps_read_last;

#    ifdef CONFIG_ANJAY_ZEPHYR_GPS_NRF
extern volatile atomic_bool anjay_zephyr_gps_prio_mode;
#    endif // CONFIG_ANJAY_ZEPHYR_GPS_NRF

int _anjay_zephyr_initialize_gps(void);
int _anjay_zephyr_stop_gps(void);
#    ifdef CONFIG_ANJAY_ZEPHYR_GPS_NRF_A_GPS
uint32_t _anjay_zephyr_gps_fetch_modem_agps_request_mask(void);
void _anjay_zephyr_gps_clear_modem_agps_request_mask(void);
#    endif // CONFIG_ANJAY_ZEPHYR_GPS_NRF_A_GPS

#endif // CONFIG_ANJAY_ZEPHYR_GPS
