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

#include <modem/lte_lc.h>
#include <modem/modem_info.h>

/**
 * Contains last known tracked state from nRF Link Control library.
 */
struct anjay_zephyr_nrf_lc_info {
    enum lte_lc_lte_mode lte_mode;
    struct lte_lc_cells_info cells;
    char ip_addr[MODEM_INFO_MAX_RESPONSE_SIZE];
    struct {
        struct lte_lc_ncell neighbor_cells[CONFIG_LTE_NEIGHBOR_CELLS_MAX];
    } storage;
};

int _anjay_zephyr_initialize_nrf_lc_info_listener(void);
void _anjay_zephyr_nrf_lc_info_get(struct anjay_zephyr_nrf_lc_info *out);
bool _anjay_zephyr_nrf_lc_info_get_if_changed(
        struct anjay_zephyr_nrf_lc_info *out);
int _anjay_zephyr_nrf_lc_info_schedule_refresh_now(void);
