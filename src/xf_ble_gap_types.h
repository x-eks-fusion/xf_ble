/**
 * @file xf_ble_gap_types.h
 * @author dotc (dotchan@qq.com)
 * @brief
 * @date 2024-08-06
 *
 * Copyright (c) 2024, CorAL. All rights reserved.
 *
 */

/**
 * @cond (XFAPI_USER || XFAPI_PORT || XFAPI_INTERNAL)
 * @ingroup group_xf_wal_ble
 * @defgroup group_xf_wal_ble_gap gap
 * @brief Generic Attribute Profile
 * @endcond
 */

#ifndef __XF_BLE_GAP_TYPES_H__
#define __XF_BLE_GAP_TYPES_H__

/* ==================== [Includes] ========================================== */

#include "xf_utils.h"
#include "xf_ble_types.h"
#include "xf_ble_base_data_types.h"

#if XF_BLE_IS_ENABLE || defined(__DOXYGEN__)

/**
 * @cond (XFAPI_USER || XFAPI_PORT)
 * @addtogroup group_xf_wal_ble_gap
 * @endcond
 * @{
 */

#ifdef __cplusplus
extern "C" {
#endif

/* ==================== [Defines] =========================================== */

/* ==================== [Typedefs] ========================================== */

/**
 * @brief BLE GAP 链接角色类型
 */
typedef enum {
    XF_BLE_GAP_LINK_ROLE_MASTER = 0,        /*!< 主机 */
    XF_BLE_GAP_LINK_ROLE_SLAVE  = 1         /*!< 从机 */
} xf_ble_gap_link_role_type_t;

/**
 * @brief BLE 广播数据单元 ( AD Structure ) 类型，完全遵循蓝牙标准进行定义
 *
 * @note  这里仅列出部分常用的类型，更多可选类型参见蓝牙官方文档
 *  《Assigned Numbers》 > 2.3 Common Data Types
 * @see https://www.bluetooth.com/specifications/assigned-numbers/
 * 
 *  《Supplement to the Bluetooth Core Specification》
 * 
 */
typedef uint8_t xf_ble_gap_adv_struct_type_t;

#define XF_BLE_ADV_STRUCT_TYPE_FLAGS                    0x01
#define XF_BLE_ADV_STRUCT_TYPE_SVC_UUID16_LIST_PART     0x02
#define XF_BLE_ADV_STRUCT_TYPE_SVC_UUID16_LIST_ALL      0x03
#define XF_BLE_ADV_STRUCT_TYPE_SVC_UUID32_LIST_PART     0x04
#define XF_BLE_ADV_STRUCT_TYPE_SVC_UUID32_LIST_ALL      0x05
#define XF_BLE_ADV_STRUCT_TYPE_SVC_UUID128_LIST_PART    0x06
#define XF_BLE_ADV_STRUCT_TYPE_SVC_UUID128_LIST_ALL     0x07
#define XF_BLE_ADV_STRUCT_TYPE_LOCAL_NAME_SHORT         0x08
#define XF_BLE_ADV_STRUCT_TYPE_LOCAL_NAME_ALL           0x09
#define XF_BLE_ADV_STRUCT_TYPE_TX_POWER_LEVEL           0x0A    // 1 bytes
#define XF_BLE_ADV_STRUCT_TYPE_CLASS_OF_DEVICE          0x0D
#define XF_BLE_ADV_STRUCT_TYPE_DEVICE_ID                0x10    // 2 bytes
#define XF_BLE_ADV_STRUCT_TYPE_APPEARANCE               0x19    // 2 bytes

/**
 * @brief BLE GAP 广播数据单元类型 (AD_TYPE) 字段的大小
 */
#define XF_BLE_GAP_ADV_STRUCT_AD_TYPE_FIELD_SIZE  1
/**
 * @brief BLE GAP 广播数据单元数据长度 (LEN) 字段的大小
 */
#define XF_BLE_GAP_ADV_STRUCT_LEN_FIELD_SIZE      1

/**
 * @brief BLE 广播数据单元数据的最大长度
 * @note 按广播数据包最大长度定义，一般是 37 字节 (地址占 6 字节，即仅 31 字节可用)
 *  BLE 5.0 是 254 字节
 * @note 该宏一般只用于对接广播数据设置时，XF 便捷方法的处理。
 */
#define XF_BLE_GAP_ADV_STRUCT_DATA_MAX_SIZE        (254)

/**
 * @brief BLE GAP 广播数据单元的数据 ( AD Data )
 *
 * @note 以下暂时仅列出部分类型的广播数据单元数据成员
 * @details 以下为蓝牙标准定义的广播数据结构及广播数据单元数据 ( AD Data ) 所在的位置
 * @code
 *  | AdvData                                                                                                   |
 *  | AD Structure 1                            | AD Structure 2                | ...... |（无效数据 000...000b）|
 *  | Length              | Data                | Length | Data                 | ......                        |
 *  | Length(type + data) | AD type | AD Data   | Length | AD type | AD Data    | ......                        |
 *                                  |    ^      |
 * @endcode
 */
typedef union _xf_ble_gap_adv_struct_data_t {
    xf_ble_var_uintptr_t adv_var;       /*!< 通用类型 (类型不定) 的广播数据单元数据 */
    uint8_t flag;                       /*!< 类型为: 0x01, type:flag */
    uint8_t *uuid_list;                 /*!< 类型为: [0x02,0x07], 服务 UUID 的列表（16/32/128位，完整/不完整列表）*/
    uint8_t *local_name;                /*!< 类型为: 0x08, type:name short; 0x09, type:name all */
    xf_ble_appearance_t appearance;     /*!< 类型为: 0x19, type:appearance，见 @ref xf_ble_appearance_t */
} xf_ble_gap_adv_struct_data_t;

/**
 * @brief BLE GAP 广播数据单元 ( AD structure ）
 *
 * @note 广播数据包与扫描响应数据包均是这个结构
 * @warning 这里的内存空间结构及成员并非严格按蓝牙标准定义的广播数据单元结构进行定义
 * @details 以下为蓝牙标准定义的广播数据结构及广播数据单元 ( AD structure ）所在的位置
 * @code
 *  | AdvData (or ScanRspData)                                                                                                  |
 *  | AD Structure 1                            | AD Structure 2                | ... |（无效数据 000...000b）   |
 *  | Length              | Data                | Length | Data                 | ......                        |
 *  | Length(type + data) | AD type | AD Data   | Length | AD type | AD Data    | ......                        |
 *  |               ^                           |
 * @endcode
 */
typedef struct {
    uint8_t is_ptr          :1;             /*!< 传入的广播单元数据是值还是指针()，
                                             * 如果是指针则 true ；否则 false */
    uint8_t ad_data_len     :7;             /*!< 注意，这并不是蓝牙标准中
                                             * 广播数据结构 AD structure 长度（ Length ），
                                             * 仅是 AD data 字段的长度（不包含 AD type 字段的长度 ）*/
    xf_ble_gap_adv_struct_type_t ad_type;   /*!< 广播数据单元的类型，见 @ref xf_ble_gap_adv_struct_type_t */
    xf_ble_gap_adv_struct_data_t ad_data;   /*!< 广播数据单元的数据，见 @ref xf_ble_gap_adv_struct_data_t */
} xf_ble_gap_adv_struct_t;

/**
 * @brief 定义一个严格遵循蓝牙标准的广播数据单元结构，单元数据 ( AD Data ) 为 U8 数组的类型
 *
 * @param type_name 指定定义的类型名
 * @param adv_data_array_size 单元数据 ( AD Data ) 数组的大小
 * @note 一般仅用于平台对接时使用，便于 XF BLE 广播数据单元结构与符号标准的广播数据结构间的转换
 */
#define XF_BLE_GAP_ADV_STRUCT_TYPE_ARRAY_U8(type_name, adv_data_array_size)   \
typedef struct {                                                \
    /* len of struct */                                         \
    uint8_t struct_data_len;                                    \
    /* AD_Type */                                               \
    xf_ble_gap_adv_struct_type_t ad_type;                       \
    /* AD_Data */                                               \
    uint8_t ad_data[adv_data_array_size];                       \
}type_name

/**
 * @brief 定义一个严格遵循蓝牙标准的广播数据单元结构，单元数据 ( AD Data ) 为固定大小数组的类型
 *
 * @param type_name 指定定义的类型名
 * @note 一般仅用于平台对接时使用，便于 XF BLE 广播数据单元结构与符号标准的广播数据结构间的转换
 * @warning 注意，此处数组大小为广播包最大大小，并不代表广播数据单元 (adv struct) 的实际有效大小
 */
#define XF_BLE_GAP_ADV_STRUCT_TYPE_ARRAY_FIXED(type_name)           \
typedef struct {                                                \
    /* len of struct */                                         \
    uint8_t struct_data_len;                                    \
    /* AD_Type */                                               \
    xf_ble_gap_adv_struct_type_t ad_type;                       \
    /* AD_Data */                                               \
    uint8_t ad_data[XF_BLE_GAP_ADV_STRUCT_DATA_MAX_SIZE];       \
}type_name

/**
 * @brief BLE GAP 广播数据 ( 包含响应数据 )
 *
 * @warning 目前 广播数据单元 与 扫描响应数据单元 并不是严格按标准的广播数据结构进行定义，
 *  而是从更方便使用的角度对标准的结构进行了微调
 */
typedef struct {
    xf_ble_gap_adv_struct_t *adv_struct_set;    /*!< 广播数据单元（ AD Structure ）的集合，
                                                 * 见 @ref xf_ble_gap_adv_struct_t */

    xf_ble_gap_adv_struct_t *scan_rsp_struct_set;
    /*!< 扫描响应数据单元（ AD Structure ）的集合，
     * 见 @ref xf_ble_gap_adv_struct_t */

} xf_ble_gap_adv_data_t;

/**
 * @brief BLE GAP 广播类型，完全遵循蓝牙标准进行定义
 *
 * @see 详参蓝牙核心文档 《Core_v5.4》>> Vol 4, Part E >> 7.8.5 LE Set Advertising Parameters command
 *  >> Command parameters >> Advertising_Type
 *  在线文档: https://www.bluetooth.com/specifications/specs/core54-html/
 *  离线文档: https://www.bluetooth.com/specifications/specs/core-specification-amended-5-4/
 */
typedef uint8_t xf_ble_gap_adv_type_t;
enum _xf_ble_gap_adv_type_t {
    XF_BLE_GAP_ADV_TYPE_CONN_SCAN_UNDIR             = 0x00, /*!< 可连接，   可扫描，    非定向 广播 (ADV_IND) (默认) */
    XF_BLE_GAP_ADV_TYPE_CONN_NONSCAN_DIR            = 0x01, /*!< 可连接，   不可扫描，  定向 广播   (ADV_DIRECT_IND) (高频) */
    XF_BLE_GAP_ADV_TYPE_NONCONN_SCAN_UNDIR          = 0x02, /*!< 不可连接， 可扫描，    非定向 广播 (ADV_SCAN_IND) */
    XF_BLE_GAP_ADV_TYPE_NONCONN_NONSCAN_UNDIR       = 0x03, /*!< 不可连接， 不可扫描，  非定向 广播 (ADV_NONCONN_IND) */
    XF_BLE_GAP_ADV_TYPE_CONN_NONSCAN_DIR_LOW_DUTY   = 0x04, /*!< 可连接，   不可扫描，  定向 广播   (ADV_DIRECT_IND) (低频) */
};

/**
 * @brief BLE GAP 广播过滤策略，完全遵循蓝牙标准进行定义
 *
 * @see 详参蓝牙核心文档 《Core_v5.4》>> Vol 4, Part E >> 7.8.5 LE Set Advertising Parameters command
 *  >> Command parameters >> Advertising_Filter_Policy
 *  在线文档: https://www.bluetooth.com/specifications/specs/core54-html/
 *  离线文档: https://www.bluetooth.com/specifications/specs/core-specification-amended-5-4/
 */
typedef uint8_t xf_ble_gap_adv_filter_policy_t;
enum _xf_ble_gap_adv_filter_policy_t {
    XF_BLE_GAP_ADV_FILTER_POLICY_ANY_SCAN_ANY_CONN      = 0x00,     /*!< 处理所有设备的扫描和连接请求 */
    XF_BLE_GAP_ADV_FILTER_POLICY_WLIST_SCAN_ANY_CONN    = 0x01,     /*!< 仅处理白名单的 扫描 请求，处理所有 连接 请求 */
    XF_BLE_GAP_ADV_FILTER_POLICY_ANY_SCAN_WLIST_CONN    = 0x02,     /*!< 处理所有 扫描 请求，仅处理白名单的 连接 请求 */
    XF_BLE_GAP_ADV_FILTER_POLICY_WLIST_SCAN_WLIST_CONN  = 0x03,     /*!< 仅处理白名单中扫描请求和连接请求 */
};

/**
 * @brief BLE GAP 广播通道，完全遵循蓝牙标准进行定义
 *
 * @see 详参蓝牙核心文档 《Core_v5.4》>> Vol 4, Part E >> 7.8.5 LE Set Advertising Parameters command
 *  >> Command parameters >> Advertising_Channel_Map
 *  在线文档: https://www.bluetooth.com/specifications/specs/core54-html/
 *  离线文档: https://www.bluetooth.com/specifications/specs/core-specification-amended-5-4/
 */
typedef uint8_t xf_ble_gap_adv_channel_t; 
enum _xf_ble_gap_adv_channel_t {
    XF_BLE_GAP_ADV_CH_37    = 0x01,         /*!< 启用 37 通道 */
    XF_BLE_GAP_ADV_CH_38    = 0x02,         /*!< 启用 38 通道 */
    XF_BLE_GAP_ADV_CH_39    = 0x04,         /*!< 启用 39 通道 */
    XF_BLE_GAP_ADV_CH_ALL   = 0x07,         /*!< 启用所有通道 */
};

/**
 * @brief BLE GAP PHY 类型
 */
typedef uint8_t xf_ble_gap_phy_type_t;
enum _xf_ble_gap_phy_type_t {
    XF_BLE_GAP_PHY_NO_PACKET    = 0x00,     /*!< 无数据包 */
    XF_BLE_GAP_PHY_1M           = 0x01,     /*!< 1M PHY */
    XF_BLE_GAP_PHY_2M           = 0x02,     /*!< 2M PHY */
    XF_BLE_GAP_PHY_CODED        = 0x03,     /*!< Coded PHY */
};

/**
 * @brief BLE GAP 广播参数
 */
typedef struct {
    uint32_t min_interval;                  /*!< 最小的广播间隔 [N * 0.625ms] */
    uint32_t max_interval;                  /*!< 最大的广播间隔 [N * 0.625ms] */
    xf_ble_gap_adv_type_t type;             /*!< 广播类型，见 @ref xf_ble_gap_adv_type_t */
    xf_ble_addr_t own_addr;                 /*!< 本端地址，见 @ref xf_ble_addr_t */
    xf_ble_addr_t peer_addr;                /*!< 对端地址，见 @ref xf_ble_addr_t */
    xf_ble_gap_adv_channel_t channel_map;   /*!< 广播通道，见 @ref xf_ble_gap_adv_channel_t */
    xf_ble_gap_adv_filter_policy_t filter_policy;  
                                            /*!< 白名单过滤策略，见 @ref xf_ble_gap_adv_filter_policy_t */
    int8_t tx_power;                        /*!< 发送功率, 单位 dBm , 范围-127~20 */
} xf_ble_gap_adv_param_t;

/**
 * @brief BLE GAP 扫描过滤策略，完全遵循蓝牙标准进行定义
 *
 * @see 详参蓝牙核心文档 《Core_v5.4》
 *  1. >> Vol 6, Part B >> 4.3.3 Scanning filter policy
 *  2. >> Vol 4, Part E >> 7.8.10 LE Set Scan Parameters command >> Command parameters >> Scanning_Filter_Policy
 *  在线文档: https://www.bluetooth.com/specifications/specs/core54-html/
 *  离线文档: https://www.bluetooth.com/specifications/specs/core-specification-amended-5-4/
 */
typedef uint8_t xf_ble_gap_scan_filter_policy_t; 
enum _xf_ble_gap_scan_filter_policy_t {
    XF_BLE_GAP_SCAN_FILTER_POLICY_ALL           = 0x00, /*!<
                                                         *  1. 处理包含本设备地址的 定向广播 (默认)
                                                         *  2. 处理所有的 非定向广播 
                                                         */
    XF_BLE_GAP_SCAN_FILTER_POLICY_WLIST         = 0x01, /*!< 
                                                         *  1. 处理包含本设备地址的 定向广播 (默认)
                                                         *  2. 只处理白名单里设备的 非定向广播 
                                                         */
    XF_BLE_GAP_SCAN_FILTER_POLICY_ALL_AND_RPA   = 0x02, /*!< 
                                                         *  1. 处理包含本设备地址的 定向广播 (默认)
                                                         *  2. 处理所有的 非定向广播
                                                         *  3. 处理地址是可解析私有地址 (RPA) 的 定向广播 
                                                         */
    XF_BLE_GAP_SCAN_FILTER_POLICY_WLIST_AND_RPA = 0x03,
                                                        /*!<
                                                         *  1. 处理包含本设备地址的 定向广播 (默认)
                                                         *  2. 只处理白名单里设备的 非定向广播
                                                         *  3. 处理地址是可解析私有地址 (RPA) 的定向广播
                                                         */
};

/**
 * @brief BLE GAP 扫描类型，完全遵循蓝牙标准进行定义
 *
 * @see 详参蓝牙核心文档 《Core_v5.4》>> Vol 4, Part E
 *  >> 7.8.10 LE Set Scan Parameters command >> Command parameters >> Scan_Type
 *  在线文档: https://www.bluetooth.com/specifications/specs/core54-html/
 *  离线文档: https://www.bluetooth.com/specifications/specs/core-specification-amended-5-4/
 */
typedef uint8_t xf_ble_gap_scan_type_t;
enum _xf_ble_gap_scan_type_t {
    XF_BLE_GAP_SCAN_TYPE_PASSIVE    = 0x0,          /*!< 被动扫描 */
    XF_BLE_GAP_SCAN_TYPE_ACTIVE     = 0x1,          /*!< 主动扫描 */
};

/**
 * @brief BLE GAP 扫描 PHY 类型
 * 
 * @see 详参蓝牙核心文档 《Core_v5.4》>> Vol 4, Part E
 *  >> 7.8.10 LE Set Scan Parameters command >> Command parameters >> Scanning_PHYs
 *  在线文档: https://www.bluetooth.com/specifications/specs/core54-html/
 *  离线文档: https://www.bluetooth.com/specifications/specs/core-specification-amended-5-4/
 */
typedef uint8_t xf_ble_gap_scan_phy_type_t;
enum _xf_ble_gap_scan_phy_type_t {
    XF_BLE_GAP_SCAN_PHY_1M           = (1 << 0),    /*!< 1M PHY */
    XF_BLE_GAP_SCAN_PHY_CODED        = (1 << 2),    /*!< Coded PHY */
};

/**
 * @brief BLE GAP 扫描参数
 */
typedef struct {
    xf_ble_gap_scan_phy_type_t phy;                 /*!< PHY类型，见 @ref xf_ble_gap_scan_phy_type_t */
    xf_ble_gap_scan_filter_policy_t filter_policy;  /*!< 扫描过滤策略，见 @ref xf_ble_gap_scan_filter_policy_t */
    xf_ble_gap_scan_type_t type;                    /*!< 扫描类型 @ref xf_ble_gap_scan_type_t */
    uint16_t interval;                              /*!< 扫描间隔，[N * 0.625 ms]，
                                                     *  范围 (看具体标准)：[0x0004, 0x4000]，[2.5 ms, 10.24 s] */
    uint16_t window;                                /*!< 扫描窗长，[N * 0.625 ms]，
                                                     *  范围 (看具体标准)：[0x0004, 0x4000]，[2.5 ms, 10.24 s] */
} xf_ble_gap_scan_param_t;

/**
 * @brief BLE GAP 扫描结果中的事件类型，扫描响应、广播数据或其他类型
 */
typedef uint8_t xf_ble_gap_scanned_adv_type_t;
enum _xf_ble_gap_scanned_adv_type_t {
    XF_BLE_GAP_SCANNED_ADV_TYPE_CONN        = 0x00, /*!< Connectable undirected advertising (ADV_IND) */
    XF_BLE_GAP_SCANNED_ADV_TYPE_CONN_DIR    = 0x01, /*!< Connectable directed advertising (ADV_DIRECT_IND) */
    XF_BLE_GAP_SCANNED_ADV_TYPE_SCAN        = 0x02, /*!< Scannable undirected advertising (ADV_SCAN_IND) */
    XF_BLE_GAP_SCANNED_ADV_TYPE_NONCONN     = 0x03, /*!< Non connectable undirected advertising (ADV_NONCONN_IND) */
    XF_BLE_GAP_SCANNED_ADV_TYPE_SCAN_RSP    = 0x04, /*!< Scan Response (SCAN_RSP) */
};

/**
 * @brief BLE GAP 连接参数更新数据结构
 */
typedef struct {
    uint16_t min_interval;      /*!< 最小连接间隔，[N * 0.625 ms]，0xFFFF：表示没有特定值，
                                 *  范围：[0x0006,0x0C80] (看具体标准) */
    uint16_t max_interval;      /*!< 最大连接间隔，[N * 0.625 ms]，0xFFFF：表示没有特定值，
                                 *  范围：[0x0006,0x0C80] (看具体标准) */
    uint16_t latency;           /*!< 从机链路的延迟（应答或响应延迟）（以连接事件数为单位)，
                                 *  范围：[0x0000,0x01F3]（看具体标准)，
                                 *  允许 Slave（从设备）在没有数据要发的情况下，
                                 *  跳过一定数目的连接事件，在这些连接事件中不必回复 Master（主设备）。 */
    uint16_t timeout;           /*!< 链接超时（将进行）断连的时间，[N * 10 ms]，0xFFFF：表示没有特定值，
                                 *  范围：[0x000A,0x0C80]（看具体标准） */
} xf_ble_gap_conn_param_update_t;

/**
 * @brief 蓝牙断连原因
 *
 * @note 其他错误码值参见：具体平台说明或参考蓝牙标准
 * @see 详参蓝牙核心文档 《Core_v5.4》>> Vol 1, Part F >> 1.3 LIST OF ERROR CODES
 *  在线文档: https://www.bluetooth.com/specifications/specs/core54-html/
 *  离线文档: https://www.bluetooth.com/specifications/specs/core-specification-amended-5-4/
 */
typedef uint8_t xf_ble_gap_disconnect_reason_t;
enum _xf_ble_gap_disconnect_reason_t {
    XF_BLE_GAP_DISCONNECT_UNKNOWN              = 0x00,    /*!< 未知原因断连 */
    XF_BLE_GAP_DISCONNECT_TIMEOUT              = 0x8,     /*!< 连接超时断连 */
    XF_BLE_GAP_DISCONNECT_ENDED_BY_REMOTE_USER = 0x13,    /*!< 远端用户断连 */
    XF_BLE_GAP_DISCONNECT_ENDED_BY_LOCAL_HOST  = 0x16,    /*!< 本端 HOST 断连 */
};

/**
 * @brief BLE 连接请求事件的参数
 */
typedef struct {
    xf_ble_conn_id_t conn_id;               /*!< 链接(连接) ID */
    xf_ble_addr_t *addr;                    /*!< 对端地址，见 @ref xf_ble_addr_t */
} xf_ble_gap_evt_param_connect_req_t;

/**
 * @brief BLE 连接事件的参数
 */
typedef struct {
    xf_ble_conn_id_t conn_id;               /*!< 链接(连接) ID */
    xf_ble_gap_link_role_type_t link_role;  /*!< 链路角色，见 @ref xf_ble_gap_link_role_type_t */
    xf_ble_addr_t *addr;                    /*!< 对端地址，见 @ref xf_ble_addr_t */
} xf_ble_gap_evt_param_connect_t;

/**
 * @brief BLE 断连事件的参数
 */
typedef struct {
    xf_ble_conn_id_t conn_id;               /*!< 链接(连接) ID */
    xf_ble_addr_t *addr;                    /*!< 对端地址，见 @ref xf_ble_addr_t */
    xf_ble_gap_disconnect_reason_t reason;  /*!< 断连原因，见 @ref xf_ble_gap_disconnect_reason_t */
} xf_ble_gap_evt_param_disconnect_t;

/**
 * @brief BLE 配对请求事件的参数
 */
typedef struct {
    xf_ble_conn_id_t conn_id;               /*!< 链接 (连接) ID */
} xf_ble_gap_evt_param_pair_req_t;

/**
 * @brief BLE 配对中 passkey disp 事件的参数
 */
typedef struct {
    xf_ble_conn_id_t conn_id;               /*!< 链接 (连接) ID */
} xf_ble_gap_evt_param_pair_passkey_disp_t;

/**
 * @brief BLE 配对中 passkey entry 事件的参数
 */
typedef struct {
    xf_ble_conn_id_t conn_id;               /*!< 链接 (连接) ID */
    uint32_t pin_code;
} xf_ble_gap_evt_param_pair_passkey_entry_t;

/**
 * @brief BLE 配对结束事件的参数
 */
typedef struct {
    xf_ble_conn_id_t conn_id;               /*!< 链接 (连接) ID */
    bool is_succ;                           /*!< 是否配对成功 */
    xf_ble_addr_t *addr;                    /*!< 对端地址， @ref xf_ble_addr_t */
    struct
    {
        void *data;
        uint8_t len;
    }ltk;                                   /*!< 平台侧配对完成分配的 ltk 的数据，
                                             * 一般用于自定义绑定处理方式或拓展绑定个数 */
} xf_ble_gap_evt_param_pair_end_t;

/**
 * @brief BLE 收到扫描结果事件的参数
 */
typedef struct {
    int rssi;                                   /*!< 扫到的设备的 RSSI 值 */
    xf_ble_addr_t *addr;                        /*!< 扫到的设备的地址，见 @ref xf_ble_addr_t */
    xf_ble_gap_scanned_adv_type_t type;         /*!< 扫到的设备广播类型，见 @ref xf_ble_gap_scanned_adv_type_t */
    uint8_t adv_data_len;                       /*!< 广播数据的长度 (指整个广播数据 AdvData ) */
    uint8_t *adv_data;                          /*!< 广播数据 (指整个广播数据 AdvData ) */
} xf_ble_gap_evt_param_scan_result_t;

/**
 * @brief BLE 连接参数更新事件的参数
 */
typedef struct {
    xf_ble_conn_id_t conn_id;                   /*!< 链接 (连接) ID */
    uint16_t interval;                          /*!< 链接间隔，单位 slot */
    uint16_t latency;                           /*!< 链接延迟，单位 slot */
    uint16_t timeout;                           /*!< 链接超时 (断连) 时间 */
} xf_ble_gap_evt_conn_param_upd_t;

/**
 * @brief BLE GAP 事件回调参数
 */
typedef union {
    xf_ble_gap_evt_param_connect_req_t conn_req;/*!< 连接请求事件的参数，
                                                 *  @ref xf_ble_gap_evt_param_connect_req_t
                                                 *  XF_BLE_GAP_EVT_CONNECT_REQ
                                                 */
    xf_ble_gap_evt_param_connect_t connect;     /*!< 连接事件的参数，
                                                 *  @ref xf_ble_gap_evt_param_connect_t
                                                 *  XF_BLE_GAP_EVT_CONNECT
                                                 */
    xf_ble_gap_evt_param_disconnect_t disconnect;
                                                /*!< 断连事件的参数，
                                                 *  @ref xf_ble_gap_evt_param_disconnect_t
                                                 *  XF_BLE_GAP_EVT_DISCONNECT
                                                 */
    xf_ble_gap_evt_param_scan_result_t scan_result; 
                                                /*!< 收到扫描结果事件的参数，
                                                 *  @ref xf_ble_gap_evt_param_scan_result_t
                                                 *  XF_BLE_GAP_EVT_SCAN_RESULT
                                                 */
    xf_ble_gap_evt_conn_param_upd_t conn_param_upd;
                                                /*!< 连接参数更新事件的参数，
                                                 *  @ref xf_ble_gap_evt_conn_param_upd_t
                                                 *  XF_BLE_GAP_EVT_CONN_PARAM_UPDATE,
                                                 */
    xf_ble_gap_evt_param_pair_req_t pair_req;   /*!< 配对请求事件的参数，
                                                 *  @ref xf_ble_gap_evt_param_pair_req_t
                                                 *  XF_BLE_GAP_EVT_PAIR_REQ,
                                                 */

    xf_ble_gap_evt_param_pair_passkey_disp_t pair_key_disp;
                                                /*!< 配对码 (passkey) 显示 (请求) 事件的参数，
                                                 *  @ref xf_ble_gap_evt_param_pair_passkey_disp_t
                                                 *  XF_BLE_GAP_EVT_PAIR_PASSKEY_REQ,
                                                 */
    xf_ble_gap_evt_param_pair_passkey_entry_t pair_key_entry;
                                                /*!< 配对码 (passkey) 输入事件的参数，
                                                 *  @ref xf_ble_gap_evt_param_pair_passkey_entry_t
                                                 *  XF_BLE_GAP_EVT_PAIR_PASSKEY_ENTRY,
                                                 */
    xf_ble_gap_evt_param_pair_end_t pair_end;   /*!< 配对结束事件的参数，
                                                 *  @ref xf_ble_gap_evt_param_pair_end_t
                                                 *  XF_BLE_GAP_EVT_PAIR_END
                                                 */
} xf_ble_gap_evt_cb_param_t;

/**
 * @brief BLE GAP 事件
 */
typedef uint8_t xf_ble_gap_evt_t;
enum _xf_ble_gap_evt_t {
    XF_BLE_GAP_EVT_CONNECT_REQ,                 /*!< 连接请求事件 */
    XF_BLE_GAP_EVT_CONNECT,                     /*!< 连接事件 */
    XF_BLE_GAP_EVT_DISCONNECT,                  /*!< 断连事件 */
    XF_BLE_GAP_EVT_SCAN_RESULT,                 /*!< 收到扫描结果事件 */
    XF_BLE_GAP_EVT_SECURITY_REQ,                /*!< (host<-slave) 收到安全请求 (Security Request) (responder) */
    XF_BLE_GAP_EVT_PAIR_REQ,                    /*!< (host->slave) 收到配对请求 (Pairing Request) (initiator) */
    XF_BLE_GAP_EVT_PAIR_JUST_WORKS,             /*!< (host->slave) 收到 just work 配对 */
    XF_BLE_GAP_EVT_PAIR_PASSKEY_REQ,            /*!< (host->slave) 收到 passkey display 配对 */
    XF_BLE_GAP_EVT_PAIR_PASSKEY_ENTRY,          /*!< (host->slave) 收到 passkey entry 配对 */
    XF_BLE_GAP_EVT_PAIR_NUM_CMP,                /*!< (host and slave？) 收到 numeric comparison 配对 */

    XF_BLE_GAP_EVT_PAIR_OOB_REQ,               
    XF_BLE_GAP_EVT_PAIR_END,                    /*!< 配对结束事件 */
    XF_BLE_GAP_EVT_CONN_PARAM_UPDATE,           /*!< 连接参数更新事件 */
    _XF_BLE_GAP_EVT_MAX,                        /*!< BLE GAP 事件枚举结束值 */
};

/**
 * @brief BLE GAP 事件回调函数原型
 *
 * @param event 事件，见 @ref xf_ble_gap_evt_t
 * @param param 事件回调参数，见 @ref xf_ble_gap_evt_cb_param_t
 * @return xf_ble_evt_res_t 事件处理结果
 *      - XF_BLE_EVT_RES_NOT_HANDLED    事件未被处理
 *      - XF_BLE_EVT_RES_HANDLED        事件已被处理
 *      - XF_BLE_EVT_RES_ERR            事件处理错误
 * 
 * @warning 返回值请应该按实际处理结果进行返回，
 *  因为部分未被处理的事件可能会在底层有的默认处理补充，
 *  所以避免出现同一事件同时被多次处理，请按实际结构返回
 */
typedef xf_ble_evt_res_t (*xf_ble_gap_evt_cb_t)(
    xf_ble_gap_evt_t event,
    xf_ble_gap_evt_cb_param_t *param);

/* ==================== [Global Prototypes] ================================= */

/* ==================== [Macros] ============================================ */

#ifdef __cplusplus
} /* extern "C" */
#endif

/**
 * End of addtogroup group_xf_wal_ble_gap
 * @}
 */

#endif /* XF_BLE_IS_ENABLE */

#endif /* __XF_BLE_GAP_TYPES_H__ */
