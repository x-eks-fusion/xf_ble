/**
 * @file xf_ble_config_internal.h
 * @author dotc (dotchan@qq.com)
 * @brief 此处列出了 XF_BLE 的可配置项。
 *  移植时请定义对应的外部配置文件 (xf_ble_config.h)，以影响此处的配置。
 * @date 2025-02-24
 *
 * @Copyright (c) 2025, CorAL. All rights reserved.
 */

#ifndef __XF_BLE_CONFIG_INTERNAL_H__
#define __XF_BLE_CONFIG_INTERNAL_H__

/* ==================== [Includes] ========================================== */

#include "xf_ble_config.h"

#ifdef __cplusplus
extern "C" {
#endif

/* ==================== [Defines] =========================================== */

#if (!defined(XF_BLE_ENABLE) || (XF_BLE_ENABLE) || defined(__DOXYGEN__))
#define XF_BLE_IS_ENABLE        (1)
#else
#define XF_BLE_IS_ENABLE        (0)
#endif

/* ==================== [Typedefs] ========================================== */

/* ==================== [Global Prototypes] ================================= */

/* ==================== [Macros] ============================================ */

#ifdef __cplusplus
} /* extern "C" */
#endif

#endif // __XF_BLE_CONFIG_INTERNAL_H__
