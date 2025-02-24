/**
 * @file xf_ble_gatt_common.h
 * @author dotc (dotchan@qq.com)
 * @brief
 * @version 1.0
 * @date 2024-08-06
 *
 * Copyright (c) 2024, CorAL. All rights reserved.
 *
 */

/**
 * @cond (XFAPI_USER || XFAPI_PORT)
 * @ingroup group_xf_wal_ble
 * @defgroup group_xf_wal_ble_gatt gatt
 * @brief Generic Attribute Profile
 * @endcond
 */

#ifndef __XF_BLE_GATT_COMMON_H__
#define __XF_BLE_GATT_COMMON_H__

/* ==================== [Includes] ========================================== */

#include "xf_utils.h"

#include "xf_ble_types.h"
#include "xf_ble_gap_types.h"

#if XF_BLE_IS_ENABLE || defined(__DOXYGEN__)

/**
 * @cond (XFAPI_USER || XFAPI_PORT)
 * @addtogroup group_xf_wal_ble_gatt
 * @endcond
 * @{
 */

#ifdef __cplusplus
extern "C" {
#endif

/* ==================== [Defines] =========================================== */

/* ==================== [Typedefs] ========================================== */

/**
 * @brief BLE GATT 属性权限
 */
typedef uint8_t xf_ble_gatt_attr_permission_t;
enum _xf_ble_gatt_attr_permission_t {
    XF_BLE_GATT_ATTR_PERM_READ          = 0x01,     /*!< 可读 */
    XF_BLE_GATT_ATTR_PERM_WRITE         = 0x02,     /*!< 可写 */
    XF_BLE_GATT_ATTR_PERM_ENCRYPT       = 0x04,     /*!< 需要加密 */
    XF_BLE_GATT_ATTR_PERM_AUTHEN        = 0x08,     /*!< 需要认证 */
    XF_BLE_GATT_ATTR_PERM_AUTHOR        = 0x10,     /*!< 需要授权 */
};

/**
 * @brief BLE 特征的特性 (property)
 * @note
 *  @code
 *  1. 此处并不是严格按蓝牙标准进行定义 ———— 1 字节 8 个特征的基本特性类型，
 *  而是 多字节 8 个基本特性类型 + 拓展特性类型的类型定义。
 *  2. 拓展类型从 基于蓝牙标准 1 字节基本特性类型的最高位( 0x80 ) 开始替换续接为拓展特性类型。
 *  3. 拓展类型名字都带上 EXT （暂定），以便开发者查阅、对比官方描述
 *  @endcode
 * 
 * @see 详参蓝牙核心文档 《Core_v5.4》>> Vol 3, Part G 
 *  >> 3 SERVICE INTEROPERABILITY REQUIREMENTS >> 3.3 CHARACTERISTIC DEFINITION 
 *  >> 3.3.1.1 Characteristic Properties
 *  在线文档: https://www.bluetooth.com/specifications/specs/core54-html/
 *  离线文档: https://www.bluetooth.com/specifications/specs/core-specification-amended-5-4/
 */
typedef uint16_t xf_ble_gatt_chara_property_t;
enum _xf_ble_gatt_chara_property_t {
    XF_BLE_GATT_CHARA_PROP_BROADCAST            = 0x01,     /*!< 广播特征值：允许对该特征值进行广播
                                                             *  如果设置了该特性，则需要存在 服务端特征配置描述符 (SCCD) 对特征进行补充描述 */
    XF_BLE_GATT_CHARA_PROP_READ                 = 0x02,     /*!< 读特征值：允许读取特征值 */
    XF_BLE_GATT_CHARA_PROP_WRITE_NO_RSP         = 0x04,     /*!< 写特征值且无需响应：允许写入特征值 (没有响应) */
    XF_BLE_GATT_CHARA_PROP_WRITE                = 0x08,     /*!< 写特征值且需要响应：允许写入特征值 (有响应) */
    XF_BLE_GATT_CHARA_PROP_NOTIFY               = 0x10,     /*!< 通知特征值：允许向客户端进行特征值通知 (无需确认)。
                                                             *  如果设置了该特性，则需要存在 客户端特征配置描述符 (CCCD) 对特征进行补充描述 */
    XF_BLE_GATT_CHARA_PROP_INDICATE             = 0x20,     /*!< 指示特征值：允许向客户端进行特征值指示 (需要确认)。
                                                             *  如果设置了该特性，则需要存在 客户端特征配置描述符 (CCCD) 对特征进行补充描述 */
    XF_BLE_GATT_CHARA_PROP_SIGNED_WRITE         = 0x40,     /*!< 签名写特征值：允许对特征值进行签名写操作 */

    XF_BLE_GATT_CHARA_PROP_EXTENSION            = 0x80,     /*!< 拓展类型起始。
                                                             *  如果设置了该特性，则需要存在 特征拓展特性描述符 (CEPD) 对特征进行补充描述 */

    /* 以下为 特征的拓展特性类型  */
    XF_BLE_GATT_CHARA_PROP_EXT_RELIABLE_WRITE   = 0x0080,
    XF_BLE_GATT_CHARA_PROP_EXT_AUX_WRITE        = 0x0100,
    XF_BLE_GATT_CHARA_PROP_EXT_READ_ENCRYPT     = 0x0200,
    XF_BLE_GATT_CHARA_PROP_EXT_READ_AUTHEN      = 0x0400,
    XF_BLE_GATT_CHARA_PROP_EXT_READ_AUTHOR      = 0x0800,
    XF_BLE_GATT_CHARA_PROP_EXT_WRITE_ENCRYPT    = 0x1000,
    XF_BLE_GATT_CHARA_PROP_EXT_WRITE_AUTHEN     = 0x2000,
    XF_BLE_GATT_CHARA_PROP_EXT_WRITE_AUTHOR     = 0x4000,
};

/**
 * @brief BLE GATT 服务类型
 */
typedef uint8_t xf_ble_gatt_service_type_t;
enum _xf_ble_gatt_service_type_t {
    XF_BLE_GATT_SERVICE_TYPE_PRIMARY    = 0,    /*!< 首要服务 */
    XF_BLE_GATT_SERVICE_TYPE_SECONDARY  = 1,    /*!< 次级服务或次要服务 */
};

/**
 * @brief BLE ATT 错误码
 * 
 * @see 
 *  BLE 属性 (ATT) 错误码: 详参蓝牙核心文档 《Core_v5.4》>> Vol 3, Part F
 *  >> 3 PROTOCOL REQUIREMENTS >> 3.4 ATTRIBUTE PROTOCOL PDUS
 *  >> 3.4.1.1 ATT_ERROR_RSP >> Table 3.4: Error codes
 * 
 *  BLE 属性 (ATT) PDU 方法对应有效的错误码: 详参蓝牙核心文档 《Core_v5.4》>> Vol 3, Part F
 *  >> 3 PROTOCOL REQUIREMENTS >> 3.4 ATTRIBUTE PROTOCOL PDUS
 *  >> 3.4.9 Attribute PDU response summary >> Table 3.44: Attribute request and response summary
 * 
 *  在线文档: https://www.bluetooth.com/specifications/specs/core54-html/
 *  离线文档: https://www.bluetooth.com/specifications/specs/core-specification-amended-5-4/
 */
typedef uint8_t xf_ble_attr_err_t;
enum _xf_ble_attr_err_t {
    XF_BLE_ATTR_ERR_SUCCESS                             = 0x00, /*!< 执行成功 */
    XF_BLE_ATTR_ERR_INVALID_HANDLE                      = 0x01, /*!< 无效句柄 */
    XF_BLE_ATTR_ERR_READ_NOT_PERMITTED                  = 0x02, /*!< 无读权限 */
    XF_BLE_ATTR_ERR_WRITE_NOT_PERMITTED                 = 0x03, /*!< 无写权限 */
    XF_BLE_ATTR_ERR_INVALID_PDU                         = 0x04, /*!< 无效 PDU */
    XF_BLE_ATTR_ERR_INSUFFICIENT_AUTHEN                 = 0x05, /*!< 未认证 */
    XF_BLE_ATTR_ERR_REQUEST_NOT_SUPPORTED               = 0x06, /*!< 不支持客户端的请求 */
    XF_BLE_ATTR_ERR_INVALID_OFFSET                      = 0x07, /*!< 无效偏移的读写 */
    XF_BLE_ATTR_ERR_INSUFFICIENT_AUTHOR                 = 0x08, /*!< 未授权 */
    XF_BLE_ATTR_ERR_PREPARE_QUEUE_FULL                  = 0x09, /*!< 排队的 prepare writes 太多，队列已满 */
    XF_BLE_ATTR_ERR_ATTRIBUTE_NOT_FOUND                 = 0x0A, /*!< 排队的 prepare writes 太多，队列已满 */
    XF_BLE_ATTR_ERR_ATTRIBUTE_NOT_LONG                  = 0x0B, /*!< 该属性不是长属性, 不能使用 ATT_READ_BLOB_REQ PDU */
    XF_BLE_ATTR_ERR_INSUFFICIENT_ENCRYPT_KEY_SIZE       = 0x0C, /*!< 用于加密此连接的加密密钥大小不足 */
    XF_BLE_ATTR_ERR_INVALID_ATTRIBUTE_VALUE_LENGTH      = 0x0D, /*!< 用于加密此连接的加密密钥大小不足 */
    XF_BLE_ATTR_ERR_UNLIKELY_ERROR                      = 0x0E, /*!< 不可能的错误 */
    XF_BLE_ATTR_ERR_INSUFFICIENT_ENCRYPT                = 0x0F, /*!< 加密不足 */
    XF_BLE_ATTR_ERR_UNSUPPORTED_GROUP_TYPE              = 0x10, /*!< 不支持的 grouping attribute */
    XF_BLE_ATTR_ERR_INSUFFICIENT_RESOURCES              = 0x11, /*!< 资源不足错误码 */
    XF_BLE_ATTR_ERR_DATABASE_OUT_OF_SYNC                = 0x12, /*!< 服务端与客户端未同步数据库 */
    XF_BLE_ATTR_ERR_VALUE_NOT_ALLOWED                   = 0x13, /*!< 非法的参数值 */

    /* 0x80 – 0x9F ：由更高层规范定义的应用程序错误代码。 */
    XF_BLE_ATTR_ERR_APP_ERROR_START                     = 0x80,
    XF_BLE_ATTR_ERR_APP_ERROR_END                       = 0x9F,

    /* 0xE0 – 0xFF ：通用配置文件和服务错误代码 */
    XF_BLE_ATTR_ERR_COMMON_PROFILE_AND_SERVICE_START    = 0xE0,
    XF_BLE_ATTR_ERR_COMMON_PROFILE_AND_SERVICE_END      = 0xFF,
};

/* ==================== [Global Prototypes] ================================= */

/* ==================== [Macros] ============================================ */

#ifdef __cplusplus
} /* extern "C" */
#endif

/**
 * End of addtogroup group_xf_wal_ble_gatt
 * @}
 */

#endif /* XF_BLE_IS_ENABLE */

#endif /* __XF_BLE_GATT_COMMON_H__ */
