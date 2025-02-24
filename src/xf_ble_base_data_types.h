/**
 * @file xf_ble_base_data_types.h
 * @author dotc (dotchan@qq.com)
 * @brief
 * @date 2025-01-23
 *
 * Copyright (c) 2025, CorAL. All rights reserved.
 *
 */

/**
 * @cond (XFAPI_USER || XFAPI_PORT || XFAPI_INTERNAL)
 * @ingroup group_xf_wal_ble
 * @defgroup group_xf_wal_ble_base_data base_data
 * @brief BLW base data types
 * @endcond
 */

#ifndef __XF_BLE_BASE_DATA_TYPES_H__
#define __XF_BLE_BASE_DATA_TYPES_H__

/* ==================== [Includes] ========================================== */

#include "xf_utils.h"

#include "xf_ble_types.h"

#if XF_BLE_IS_ENABLE || defined(__DOXYGEN__)

/**
 * @cond (XFAPI_USER || XFAPI_PORT)
 * @addtogroup group_xf_wal_ble_base_data
 * @endcond
 * @{
 */

#ifdef __cplusplus
extern "C" {
#endif

/* ==================== [Defines] =========================================== */

/* ==================== [Typedefs] ========================================== */

/**
 * @brief BLE 基础数据 Flags, 完全遵循蓝牙标准进行定义
 *
 * @note 常用于设置广播数据单元的数据
 * @note  这里仅列出部分常用的类型，更多可选类型参见蓝牙官方文档
 *  《Core Specification Supplement》 >> Part A, Section 1.3
 * @see https://www.bluetooth.com/specifications/assigned-numbers/
 */
typedef uint8_t xf_ble_flags_t;
enum _xf_ble_flags_t
{
    XF_BLE_FLAGS_LE_LIMITED             = (1 << 0), /*!< LE 有限发现模式，设备在广播状态，但只有绑定过的主机设备能回连，其他设备无法扫描和连接。 */
    XF_BLE_FLAGS_LE_GENERAL             = (1 << 1), /*!< LE 通用发现模式，设备在广播状态，可被主机扫描连接。 */
    XF_BLE_FLAGS_BR_EDR_NOT_SUPPORTED   = (1 << 2), /*!< 不支持 BR, EDR */
    XF_BLE_FLAGS_LE_BR_EDR_CONTROLLER   = (1 << 3), /*!< 支持 LE, BR, EDR 同存, Controller */
};

/**
 * @brief   BLE 基础数据: 外观, 完全遵循蓝牙标准进行定义
 *
 * @note 常用于设置广播数据单元的数据
 * @note 这里仅列出部分常用的值，更多可选值参见蓝牙官方文档
 *  《Assigned Numbers》 >> 2.6 Appearance Values >> 2.6.2 Appearance Category ranges
 *  《Assigned Numbers》 >> 2.6 Appearance Values >> 2.6.3 Appearance Sub-category values
 * @see https://www.bluetooth.com/specifications/assigned-numbers/
 */
typedef uint16_t xf_ble_appearance_t;

#define XF_BLE_APPEARANCE_UNKNOWN                               0x0000
#define XF_BLE_APPEARANCE_GENERIC_PHONE                         0x0040
#define XF_BLE_APPEARANCE_GENERIC_COMPUTER                      0x0080
#define XF_BLE_APPEARANCE_GENERIC_WATCH                         0x00C0
#define XF_BLE_APPEARANCE_SPORTS_WATCH                          0x00C1
#define XF_BLE_APPEARANCE_GENERIC_CLOCK                         0x0100
#define XF_BLE_APPEARANCE_GENERIC_DISPLAY                       0x0140
#define XF_BLE_APPEARANCE_GENERIC_REMOTE                        0x0180
#define XF_BLE_APPEARANCE_GENERIC_EYEGLASSES                    0x01C0
#define XF_BLE_APPEARANCE_GENERIC_TAG                           0x0200
#define XF_BLE_APPEARANCE_GENERIC_KEYRING                       0x0240
#define XF_BLE_APPEARANCE_GENERIC_MEDIA_PLAYER                  0x0280
#define XF_BLE_APPEARANCE_GENERIC_BARCODE_SCANNER               0x02C0
#define XF_BLE_APPEARANCE_GENERIC_THERMOMETER                   0x0300
#define XF_BLE_APPEARANCE_THERMOMETER_EAR                       0x0301
#define XF_BLE_APPEARANCE_GENERIC_HEART_RATE                    0x0340
#define XF_BLE_APPEARANCE_HEART_RATE_BELT                       0x0341
#define XF_BLE_APPEARANCE_GENERIC_BLOOD_PRESSURE                0x0380
#define XF_BLE_APPEARANCE_BLOOD_PRESSURE_ARM                    0x0381
#define XF_BLE_APPEARANCE_BLOOD_PRESSURE_WRIST                  0x0382
#define XF_BLE_APPEARANCE_GENERIC_HID                           0x03C0
#define XF_BLE_APPEARANCE_HID_KEYBOARD                          0x03C1
#define XF_BLE_APPEARANCE_HID_MOUSE                             0x03C2
#define XF_BLE_APPEARANCE_HID_JOYSTICK                          0x03C3
#define XF_BLE_APPEARANCE_HID_GAMEPAD                           0x03C4
#define XF_BLE_APPEARANCE_HID_DIGITIZER_TABLET                  0x03C5
#define XF_BLE_APPEARANCE_HID_CARD_READER                       0x03C6
#define XF_BLE_APPEARANCE_HID_DIGITAL_PEN                       0x03C7
#define XF_BLE_APPEARANCE_HID_BARCODE_SCANNER                   0x03C8
#define XF_BLE_APPEARANCE_GENERIC_GLUCOSE                       0x0400
#define XF_BLE_APPEARANCE_GENERIC_WALKING                       0x0440
#define XF_BLE_APPEARANCE_WALKING_IN_SHOE                       0x0441
#define XF_BLE_APPEARANCE_WALKING_ON_SHOE                       0x0442
#define XF_BLE_APPEARANCE_WALKING_ON_HIP                        0x0443
#define XF_BLE_APPEARANCE_GENERIC_CYCLING                       0x0480
#define XF_BLE_APPEARANCE_CYCLING_COMPUTER                      0x0481
#define XF_BLE_APPEARANCE_CYCLING_SPEED                         0x0482
#define XF_BLE_APPEARANCE_CYCLING_CADENCE                       0x0483
#define XF_BLE_APPEARANCE_CYCLING_POWER                         0x0484
#define XF_BLE_APPEARANCE_CYCLING_SPEED_CADENCE                 0x0485
#define XF_BLE_APPEARANCE_GENERIC_PULSE_OXIMETER                0x0C40
#define XF_BLE_APPEARANCE_PULSE_OXIMETER_FINGERTIP              0x0C41
#define XF_BLE_APPEARANCE_PULSE_OXIMETER_WRIST                  0x0C42
#define XF_BLE_APPEARANCE_GENERIC_WEIGHT                        0x0C80
#define XF_BLE_APPEARANCE_GENERIC_PERSONAL_MOBILITY_DEVICE      0x0CC0
#define XF_BLE_APPEARANCE_POWERED_WHEELCHAIR                    0x0CC1
#define XF_BLE_APPEARANCE_MOBILITY_SCOOTER                      0x0CC2
#define XF_BLE_APPEARANCE_GENERIC_CONTINUOUS_GLUCOSE_MONITOR    0x0D00
#define XF_BLE_APPEARANCE_GENERIC_INSULIN_PUMP                  0x0D40
#define XF_BLE_APPEARANCE_INSULIN_PUMP_DURABLE_PUMP             0x0D41
#define XF_BLE_APPEARANCE_INSULIN_PUMP_PATCH_PUMP               0x0D44
#define XF_BLE_APPEARANCE_INSULIN_PEN                           0x0D48
#define XF_BLE_APPEARANCE_GENERIC_MEDICATION_DELIVERY           0x0D80
#define XF_BLE_APPEARANCE_GENERIC_OUTDOOR_SPORTS                0x1440
#define XF_BLE_APPEARANCE_OUTDOOR_SPORTS_LOCATION               0x1441
#define XF_BLE_APPEARANCE_OUTDOOR_SPORTS_LOCATION_AND_NAV       0x1442
#define XF_BLE_APPEARANCE_OUTDOOR_SPORTS_LOCATION_POD           0x1443
#define XF_BLE_APPEARANCE_OUTDOOR_SPORTS_LOCATION_POD_AND_NAV   0x1444

/**
 * @brief BLE 基础数据: 角色, 完全遵循蓝牙标准进行定义
 *
 * @note 常用于设置广播数据单元的数据
 * @note  这里仅列出部分常用的类型，更多可选类型参见蓝牙官方文档
 *  《Core Specification Supplement》 >> Part A, Section 1.17 LE ROLE
 * @see https://www.bluetooth.com/specifications/assigned-numbers/
 */
typedef uint8_t xf_ble_role_t;
enum _xf_ble_role_t
{
    XF_BLE_ROLE_PERIPHERAL              = (0x00),   /*!< 仅支持外设角色 */
    XF_BLE_ROLE_CENTRAL                 = (0x01),   /*!< 仅支持中央角色 */
    XF_BLE_ROLE_PERIPHERAL_CENTRAL      = (0x02),   /*!< 支持外设及中央角色, 外设角色优先建立连接 */
    XF_BLE_ROLE_CENTRAL_PERIPHERAL      = (0x03),   /*!< 支持外设及中央角色, 中央角色优先建立连接 */
};

/* ==================== [Global Prototypes] ================================= */

/* ==================== [Macros] ============================================ */

#ifdef __cplusplus
} /* extern "C" */
#endif

/**
 * End of addtogroup group_xf_wal_ble_base_data
 * @}
 */

#endif /* XF_BLE_IS_ENABLE */

#endif /* __XF_BLE_BASE_DATA_TYPES_H__ */
