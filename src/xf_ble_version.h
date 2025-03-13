/**
 * @file xf_ble_version.h
 * @author dotc (dotchan@qq.com)
 * @brief XF_BLE 版本号
 * @date 2025-03-13
 *
 * @Copyright (c) 2025, CorAL. All rights reserved.
 */

#ifndef __XF_BLE_VERSION_H__
#define __XF_BLE_VERSION_H__

/* ==================== [Includes] ========================================== */

#include "xf_utils.h"

#ifdef __cplusplus
extern "C" {
#endif

/* ==================== [Defines] =========================================== */

/**
 * @brief 主要版本号 (X.x.x).
 */
#define XF_BLE_VERSION_MAJOR 2

/**
 * @brief 次要版本号 (x.X.x).
 */
#define XF_BLE_VERSION_MINOR 0

/**
 * @brief 补丁版本号 (x.x.X).
 */
#define XF_BLE_VERSION_PATCH 0

/* ==================== [Typedefs] ========================================== */

/* ==================== [Global Prototypes] ================================= */

/* ==================== [Macros] ============================================ */

/**
 * @brief 当前版本号, 返回一个整数。
 * 编译时使用。比如：XF_BLE_VERSION >= XF_BLE_VERSION_VAL(1, 0, 0)
 */
#define XF_BLE_VERSION \
    XF_VERSION_VAL(XF_BLE_VERSION_MAJOR, XF_BLE_VERSION_MINOR, XF_BLE_VERSION_PATCH)

/**
 * @brief 当前版本号, 返回一个字符串。
 */
#define XF_BLE_VERSION_STR \
    "v" XSTR(XF_BLE_VERSION_MAJOR) "." XSTR(XF_BLE_VERSION_MINOR) "." XSTR(XF_BLE_VERSION_PATCH)

#ifdef __cplusplus
} /*extern "C"*/
#endif

#endif /* __XF_BLE_VERSION_H__ */
