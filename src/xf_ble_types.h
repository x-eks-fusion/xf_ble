/**
 * @file xf_ble_types.h
 * @author dotc (dotchan@qq.com)
 * @brief
 * @date 2024-08-06
 *
 * Copyright (c) 2024, CorAL. All rights reserved.
 *
 */


/**
 * @cond (XFAPI_USER || XFAPI_PORT || XFAPI_INTERNAL)
 * @ingroup group_xf_wal
 * @defgroup group_xf_wal_ble xf_ble
 * @brief xf_ble 是对 ble 的封装。
 * @endcond
 */

#ifndef __XF_BLE_TYPES_H__
#define __XF_BLE_TYPES_H__

/* ==================== [Includes] ========================================== */

#include "xf_utils.h"
#include "xf_ble_config_internal.h"

#if XF_BLE_IS_ENABLE  || defined(__DOXYGEN__)

/**
 * @cond (XFAPI_USER || XFAPI_PORT)
 * @addtogroup group_xf_wal_ble
 * @endcond
 * @{
 */

#ifdef __cplusplus
extern "C" {
#endif

/* ==================== [Defines] =========================================== */

/* ==================== [Typedefs] ========================================== */

/**
 * @brief BLE 地址长度
 */
#define XF_BLE_ADDR_LEN     6

/**
 * @brief BLE 地址打印格式
 */
#define XF_BLE_ADDR_PRINT_FMT  "%02X:%02X:%02X:%02X:%02X:%02X"

/**
 * @brief BLE 地址展开为参数
 *
 * @note 一般用于配合 'XF_BLE_ADDR_PRINT_FMT' 进行地址打印输出
 */
#define XF_BLE_ADDR_EXPAND_TO_ARG(addr)  (addr)[0],(addr)[1],(addr)[2],(addr)[3],(addr)[4],(addr)[5]

/**
 * @brief 蓝牙地址类型，完全遵循蓝牙标准进行定义
 *
 * @details 地址类型如下：
 * @code
 *  1、公共设备地址（类似USB VID，需申请）
 *  2、随机设备地址：设备启动后随机生成
 *      2.A、静态设备地址：在启动后地址不变，下次复位后地址可能会变（非强制要求）
 *      2.B、私有设备地址：地址会更新
 *          2.B.1、不可解析私有地址：地址定时更新
 *          2.B.2、可解析私有地址：地址加密生成
 * @endcode
 * @see 详参蓝牙核心文档 《Core_v5.4》>> Vol 6, Part B >> 1.3 DEVICE ADDRESS
 *  在线文档: https://www.bluetooth.com/specifications/specs/core54-html/
 *  离线文档: https://www.bluetooth.com/specifications/specs/core-specification-amended-5-4/
 */
typedef uint8_t xf_ble_addr_type_t;
enum _xf_ble_addr_type_t {
    XF_BLE_ADDR_TYPE_PUBLIC_DEV  = 0x00,    /*!< 公有地址 */
    XF_BLE_ADDR_TYPE_RANDOM_DEV  = 0x01,    /*!< 随机地址 */
    XF_BLE_ADDR_TYPE_RPA_PUBLIC  = 0x02,    /*!< 不可解析私有地址：地址定时更新 */
    XF_BLE_ADDR_TYPE_RPA_RANDOM  = 0x03,    /*!< 可解析私有地址：地址加密生成 */
};

/**
 * @brief BLE 地址信息
 */
typedef struct {
    uint8_t addr[XF_BLE_ADDR_LEN];     /*!< BLE 地址值 */
    xf_ble_addr_type_t type;           /*!< BLE 地址类型，见 @ref xf_ble_addr_type_t */
} xf_ble_addr_t;

/**
 * @brief BLE APP ID
 */
typedef uint8_t xf_ble_app_id_t;

/**
 * @brief 无效 BLE APP ID
 */
#define XF_BLE_APP_ID_INVALID   (0)

/**
 * @brief BLE 广播 ID
 */
typedef uint8_t xf_ble_adv_id_t;

/**
 * @brief 无效广播 ID
 */
#ifndef XF_BLE_ADV_ID_INVALID
#	define XF_BLE_ADV_ID_INVALID  (0)
#endif

/**
 * @brief BLE 连接 (链接) ID
 * 
 * @note 目前暂未规定无效 conn_id 值
 *  因为部分平台 conn_id 是 U8，部分是 U16 的
 */
typedef uint8_t xf_ble_conn_id_t;

/**
 * @brief 无效 连接 (链接) ID
 */
#ifndef XF_BLE_CONN_ID_INVALID
#	define XF_BLE_CONN_ID_INVALID  (0)
#endif

/**
 * @brief BLE 属性句柄
 */
typedef uint16_t xf_ble_attr_handle_t;

/**
 * @brief BLE 无效属性句柄
 * @note 通常用于对接服务结构添加时，判断服务、特征、特征描述符等属性的句柄是否有效
 */
#define XF_BLE_ATTR_HANDLE_INVALID  (0x0000)

/**
 * @brief BLE 属性句柄最小值
 */
#define XF_BLE_ATTR_HANDLE_MIN  (0x0001)

/**
 * @brief BLE 属性句柄最大值
 */
#define XF_BLE_ATTR_HANDLE_MAX  (0xFFFF)

/**
 * @brief BLE UUID 类型 (长度类型)
 */
typedef uint8_t xf_ble_uuid_type_t;
enum _xf_ble_uuid_type_t {
    XF_BLE_UUID_TYPE_16 = 2,        /*!< 长度 16-bit */
    XF_BLE_UUID_TYPE_32 = 4,        /*!< 长度 32-bit */
    XF_BLE_UUID_TYPE_128 = 16,      /*!< 长度 128-bit */
};

/**
 * @brief BLE UUID 信息 (多种长度类型通用)
 */
typedef struct __packed _xf_ble_uuid_info_t {
    union {
        xf_ble_uuid_type_t type;                    /*!< UUID 长度类型，见 @ref xf_ble_uuid_type_t */
        uint8_t _invalid;                           /*!< 用于固定 UUID 长度类型变量的大小为 8-bit */
    };
    union {
        uint16_t    uuid16;                         /*!< 16-bit UUID */
        uint32_t    uuid32;                         /*!< 32-bit UUID */
        uint8_t     uuid128[XF_BLE_UUID_TYPE_128];  /*!< 128-bit UUID */
    };
} xf_ble_uuid_info_t;

#define XF_BLE_UUID16_INIT(uuid16_val)      \
    {                                       \
        .type = XF_BLE_UUID_TYPE_16,        \
        .uuid16 = (uuid16_val),             \
    }

#define XF_BLE_UUID32_INIT(uuid32_val)      \
    {                                       \
        .type = XF_BLE_UUID_TYPE_32,        \
        .uuid32 = (uuid32_val),             \
    }

#define XF_BLE_UUID128_INIT(uuid128_expr)   \
    {                                       \
        .type = XF_BLE_UUID_TYPE_128,       \
        .uuid128 = { uuid128_expr },        \
    }

/**
 * @brief BLE 声明一个 16-bit UUID
 * @note 通常用于填充服务结构时填入常量 UUID
 */
#define XF_BLE_UUID16_DECLARE(uuid16) \
    ((&(xf_ble_uuid_info_t) XF_BLE_UUID16_INIT(uuid16)))

/**
 * @brief BLE 声明一个 32-bit UUID
 * @note 通常用于填充服务结构时填入常量 UUID
 */
#define XF_BLE_UUID32_DECLARE(uuid32) \
    ((&(xf_ble_uuid_info_t) XF_BLE_UUID32_INIT(uuid32)))

/**
 * @brief BLE 声明一个 128-bit UUID
 * @note 通常用于填充服务结构时填入常量 UUID
 */
#define XF_BLE_UUID128_DECLARE(uuid128...) \
    ((&(xf_ble_uuid_info_t) XF_BLE_UUID128_INIT(uuid128)))

/**
 * @brief XF BLE 事件处理结果
 */
typedef uint8_t xf_ble_evt_res_t;
enum _xf_ble_evt_res_t{
    XF_BLE_EVT_RES_HANDLED = 0,     /*!< BLE 事件已被处理 */
    XF_BLE_EVT_RES_NOT_HANDLED,     /*!< BLE 事件未被处理 */
    XF_BLE_EVT_RES_ERR,             /*!< BLE 事件处理错误 */
};

/**
 * @brief BLE 中类型可变的数据
 *
 * @note 基于 uintptr 类型，可变数据的最大大小等于 uintptr 类型的大小
 */
typedef union _xf_ble_var_uintptr_t {
    uintptr_t   _untyped;
    bool        val_bool;
    uint8_t     val_u8;
    uint16_t    val_u16;
    uint32_t    val_u32;

    uint8_t     *ptr_u8;
    uint16_t    *ptr_u16;
    uint32_t    *ptr_u32;

    uint8_t     array_u8[sizeof(uintptr_t)];
    uint16_t    array_u16[sizeof(uintptr_t) / sizeof(uint16_t)];
    uint32_t    array_u32[sizeof(uintptr_t) / sizeof(uint32_t)];
} xf_ble_var_uintptr_t;

#define XF_BLE_EVT_ALL       (UINT8_MAX)    /*!< 所有事件 */

/* ==================== [Global Prototypes] ================================= */

/* ==================== [Macros] ============================================ */

#ifdef __cplusplus
} /* extern "C" */
#endif

/**
 * End of addtogroup group_xf_wal_ble
 * @}
 */

#endif /* XF_BLE_IS_ENABLE */

#endif /* __XF_BLE_TYPES_H__ */
