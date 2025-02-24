/**
 * @file xf_ble_gatt_server_types.h
 * @author dotc (dotchan@qq.com)
 * @brief
 * @version 1.0
 * @date 2024-08-06
 *
 * Copyright (c) 2024, CorAL. All rights reserved.
 *
 */

#ifndef __XF_BLE_GATT_SERVER_TYPES_H__
#define __XF_BLE_GATT_SERVER_TYPES_H__

/* ==================== [Includes] ========================================== */

#include "xf_utils.h"

#include "xf_ble_types.h"
#include "xf_ble_gap_types.h"
#include "xf_ble_gatt_common.h"

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
 * @brief 属性集合的结束标记值
 *
 * @note 一般出现在构造服务时，
 * 多个服务、特征、描述符等属性的集合的结尾部分，
 * 一般是标记属性的 UUID 项（关键项）为
 * 'XF_BLE_ATTR_SET_END_FLAG' 表示结束(主要是为了更好显示结束的位置)
 *
 * @note 由于结束标记的特殊性（NULL），用户构造时也可以
 * 对属性集合中表示结束的最后一个属性成员结构直接置 0，如：
 *      ([attr_set_type])
 *      {
 *          {...},
 *          {...},
 *          {0}
 *      }
 */
#define XF_BLE_ATTR_SET_END_FLAG                NULL

/**
 * @brief BLE GATT 属性数值（个数、索引等）
 */
typedef uint8_t xf_ble_gatt_att_num_t;

/**
 * @brief BLE GATT 特征信息中的各个属性的偏移值 (索引值)
 */
typedef xf_ble_gatt_att_num_t xf_ble_gatt_chara_att_offset_t;
enum _xf_ble_gatt_chara_att_offset_t{
    XF_BLE_GATT_CHARA_ATT_OFFSET_DECL    = 0,   /*!< 特征声明属性 (在特征结构中) 的偏移值 (索引值)  */
    XF_BLE_GATT_CHARA_ATT_OFFSET_VALUE,         /*!< 特征值属性 (在特征结构中) 的偏移值 (索引值) */
    XF_BLE_GATT_CHARA_ATT_OFFSET_DESC_START,    /*!< 描述符属性 (在特征结构中) 的起始偏移值 (索引值) */
}; 

/**
 * @brief BLE GATT 获取特征信息下描述符的索引值 (通过描述符在特征信息下的属性偏移)
 * 
 * @param offset_of_chara 描述符在特征信息下的属性偏移
 */
#define XF_BLE_GATT_CHARA_GET_DESC_INDEX(offset_of_chara)   \
    (offset_of_chara - XF_BLE_GATT_CHARA_ATT_OFFSET_DESC_START)

/**
 * @brief BLE GATTS 描述符信息
 * 
 * @note 添加服务时使用。
 * @note
 * 必须填入的参数:
 *  uuid        - 描述符 UUID
 *  perms       - 描述符的属性权限
 *  value       - 描述符的属性值
 *  value_len   - 描述符的属性值长度
 * 
 * 无需填入的参数:
 *  handle          - 描述符句柄，在服务被添加时由协议栈分配
 */
typedef struct {
    xf_ble_uuid_info_t *uuid;                   /*!< 描述符 UUID，见 @ref xf_ble_uuid_info_t */
    xf_ble_attr_handle_t handle;                /*!< 描述符句柄，在服务被添加时由协议栈分配，不可指定，见 @ref xf_ble_attr_handle_t */
    xf_ble_gatt_attr_permission_t perms;        /*!< 描述符权限，见 @ref xf_ble_gatt_attr_permission_t */
    uint8_t *value;                             /*!< 属性值 */
    uint16_t value_len;                         /*!< 属性值长度 */
} xf_ble_gatts_desc_t;

/**
 * @brief BLE GATTS 特征信息
 * 
 * @note 添加服务时使用
 * @note
 * 必须填入的参数:
 *  uuid        - 特征 UUID
 *  props       - 特征的特性
 *  perms       - 特征值的属性权限
 *  value       - 特征值
 *  value_len   - 特征值长度
 *  
 * 选填的参数:
 *  desc_set    - 描述符集合，如无，则填 NULL 或忽略
 * 
 * 无需填入的参数:
 *  handle          - 特征句柄，在服务被添加时由协议栈分配
 *  value_handle    - 特征值句柄，在服务被添加时由协议栈分配
 */
typedef struct _xf_ble_gatts_chara_t {
    xf_ble_uuid_info_t *uuid;                   /*!< 特征 UUID ，见 @ref xf_ble_uuid_info_t */
    xf_ble_attr_handle_t handle;                /*!< 特征句柄，在服务被添加时由协议栈分配，见 @ref xf_ble_attr_handle_t */
    xf_ble_gatt_chara_property_t props;         /*!< 特征的特性，见 @ref xf_ble_gatt_chara_property_t */
    xf_ble_gatt_attr_permission_t perms;        /*!< 特征值权限，见 @ref xf_ble_gatt_attr_permission_t */
    xf_ble_attr_handle_t value_handle;          /*!< 特征值句柄，在服务被添加时由协议栈分配，不可指定，见 @ref xf_ble_attr_handle_t */
    uint8_t *value;                             /*!< 特征值 */
    uint16_t value_len;                         /*!< 特征值长度 */
    xf_ble_gatts_desc_t *desc_set;              /*!< 描述符集合，如无，则填 NULL，
                                                 * 见 @ref xf_ble_gatts_desc_t */
} xf_ble_gatts_chara_t;

/**
 * @brief BLE GATTS 服务信息
 * 
 * @note 添加服务时使用
 * @note 
 * 必须填入的参数:
 *  uuid        - 服务 UUID
 *  type        - 服务类型。表明本服务是首要服务，还是被包含在其他服务的次级服务
 *  chara_set   - 特征结构的集合。每个特征结构下包含特征 (特征声明 + 特征值)信息，可能还有描述符信息
 *  att_cnt     - 服务的属性的总数
 *      服务的属性的总数 = 包含 (引用) 服务的声明的数量 (include_cnt) + 本地服务 (即非包含的服务) 的属性数量。
 *      本地服务 (即非包含的服务) 的属性数量 = 1个服务声明属性 + 特征的数量*2 (特征声明属性 和 特征值声明属性) + 描述符声明的数量
 * 
 * 选填的参数:
 *  include_set     - 包含 (引用) 服务 (include service) 的集合，如无，则填 NULL 或忽略
 *  include_cnt     - 包含 (引用) 服务的数量。注意，如果设置了 包含服务集合时，此包含服务数量为必填项；如无，则填 0 或忽略
 *  att_local_map   - 服务的本地属性映射表，通常用于在收到读写请求事件时，查找属性在服务中的位置
 *                      仅包含: 本地属性下的特征声明属性、特征值声明声明、描述符声明属性
 *                      不包含: 服务声明属性、包含 (引用) 服务声明属性 
 *                    可通过静态定义的方式生成，然后填入 (建议)
 *                    当然也可使用动态方式生成，然后填入，可以调用接口 `xf_ble_gatts_svc_get_att_local_map` ，
 *                      但此方式会需要一定处理时间及内存空间
 * 
 *  handle      - 服务句柄，通常在服务被添加时由协议栈分配；
 *                  也可指定（即服务起始句柄），在添加服务前设置为指定的句柄即可。
 *                  但需要注意的是，指定句柄时可能会影响其他不指定服务句柄 (起始句柄) 的服务属性的句柄分配
 */
typedef struct _xf_ble_gatts_service_t xf_ble_gatts_service_t;
typedef struct _xf_ble_gatts_service_t {
    xf_ble_uuid_info_t *uuid;                   /*!< 服务 UUID ，见 @ref xf_ble_uuid_info_t */
    xf_ble_gatts_service_t  **include_set;      /*!< 包含 (引用) 服务 (include service) 集合信息，见 @ref xf_ble_gatts_service_t */
    xf_ble_attr_handle_t handle;                /*!< 服务句柄，见 @ref xf_ble_attr_handle_t 
                                                 *  通常在服务被添加时由协议栈分配；
                                                 *  也可指定（即服务起始句柄），在添加服务前设置为指定的句柄即可，
                                                 *  但需要注意的是，指定句柄时可能会影响其他不指定服务句柄 (起始句柄) 的服务属性的句柄分配 */
    xf_ble_gatt_service_type_t type;            /*!< 服务类型，见 @ref xf_ble_gatt_service_type_t */
    xf_ble_gatts_chara_t *chara_set;            /*!< 特征集合 ，见 @ref xf_ble_gatts_chara_t */
    uint8_t include_cnt;                        /*!< 包含 (引用) 服务的数量 */
    xf_ble_gatt_att_num_t att_cnt;              /*!< 服务的属性总数，见 @ref xf_ble_gatt_att_num_t */
    xf_ble_gatt_att_num_t *att_local_map;       /*!< 服务的本地 (部分的) 属性的映射表，包含哪些属性详见本结构体的总注释 */
} xf_ble_gatts_service_t;

/**
 * @brief BLE GATTS MTU 协商事件的参数
 */
typedef struct {
    xf_ble_app_id_t app_id;                     /*!< 服务端 (应用) ID */
    xf_ble_conn_id_t conn_id;                   /*!< 链接 (连接) ID */
    uint16_t mtu_size;                          /*!< MTU 大小 */
} xf_ble_gatts_evt_param_exchange_mtu_t;

/**
 * @brief BLE GATTS 接收到读请求事件的参数
 */
typedef struct { 
    xf_ble_app_id_t app_id;                     /*!< 服务端 (应用) ID */
    xf_ble_conn_id_t conn_id;                   /*!< 链接 (连接) ID */
    uint32_t trans_id;                          /*!< 传输 ID */
    xf_ble_attr_handle_t handle;                /*!< 属性句柄 */
    uint16_t offset;                            /*!< 值偏移 (如果值过长) */
    bool need_rsp;                              /*!< 是否需要响应 (回应) */
    bool need_author;                           /*!< 是否需要授权 */
    bool is_long;                               /*!< 值是否过长 */
} xf_ble_gatts_evt_param_read_req_t;

/**
 * @brief BLE GATTS 接收到写请求事件的参数
 */
typedef struct {
    xf_ble_app_id_t app_id;                     /*!< 服务端 (应用) ID */
    xf_ble_conn_id_t conn_id;                   /*!< 链接 (连接) ID */
    uint32_t trans_id;                          /*!< 传输 ID */
    xf_ble_attr_handle_t handle;                /*!< 属性句柄 */
    uint16_t offset;                            /*!< 值偏移 (如果值过长) */
    bool need_rsp;                              /*!< 是否需要响应 (回应) */
    bool need_author;                           /*!< 是否需要授权 */
    bool is_prep;                               /*!< 是否是 prepare write 操作 */
    uint16_t value_len;                         /*!< 属性值长度 */
    uint8_t *value;                             /*!< 属性值 */
} xf_ble_gatts_evt_param_write_req_t;

/**
 * @brief BLE GATTS 发送通知或指示的信息
 */
typedef struct {
    xf_ble_attr_handle_t handle;                /*!< 属性句柄，见 @ref xf_ble_attr_handle_t */
    uint16_t value_len;                         /*!< 通知/指示的值长度 */
    uint8_t *value;                             /*!< 发送的通知/指示的值 */
} xf_ble_gatts_ntf_t, xf_ble_gatts_ind_t;

/**
 * @brief BLE GATTS 响应 (回应) 信息
 * 
 * @note 此处 trans_id 与 handle 不一定都是有效值，有效情况看平台侧对接情况，
 *  因为响应是发生读写请求时，所以只有将事件参数中的 trans_id 和 handle 传入即可，
 *  一般不需要关注他们的有效性
 */
typedef struct {
    xf_ble_attr_handle_t handle;        /*!< 属性句柄，见 @ref xf_ble_attr_handle_t */
    uint32_t trans_id;                  /*!< 传输 ID */
    xf_ble_attr_err_t err;              /*!< 错误码，见 @ref xf_ble_attr_err_t */
    uint16_t offset;                    /*!< 属性值的偏移 */
    uint16_t value_len;                 /*!< 响应的值长度 */
    uint8_t *value;                     /*!< 响应的值 */
} xf_ble_gatts_response_t;

/**
 * @brief GATT 服务端事件回调参数
 */
typedef union {
    xf_ble_gatts_evt_param_exchange_mtu_t mtu;  /*!< MTU 协商事件的参数，
                                                 *  @ref xf_ble_gatts_evt_param_exchange_mtu_t
                                                 *  XF_BLE_GATTS_EVT_EXCHANGE_MTU,
                                                 */
    xf_ble_gatts_evt_param_read_req_t read_req;
    /*!< 接收到读请求事件的参数，
     *  @ref xf_ble_gatts_evt_param_read_req_t
     *  XF_BLE_GATTS_EVT_READ_REQ
     */
    xf_ble_gatts_evt_param_write_req_t write_req;
    /*!< 接收到写请求事件的参数，
     *  @ref xf_ble_gatts_evt_param_write_req_t
     *  XF_BLE_GATTS_EVT_WRITE_REQ
     */
} xf_ble_gatts_evt_cb_param_t;

/**
 * @brief BLE GATTS 事件
 */
typedef uint8_t xf_ble_gatts_evt_t;

enum _xf_ble_gatts_evt_t {                       
    XF_BLE_GATTS_EVT_EXCHANGE_MTU,              /*!< MTU 协商事件 */
    XF_BLE_GATTS_EVT_READ_REQ,                  /*!< 接收到读请求事件 */
    XF_BLE_GATTS_EVT_WRITE_REQ,                 /*!< 接收到写请求事件 */
    _XF_BLE_GATTS_EVT_MAX,                      /*!< BLE GATTS 事件枚举结束值 */
};

/**
 * @brief BLE GATTS 事件回调函数原型
 *
 * @param event 事件，见 @ref xf_ble_gatts_evt_t
 * @param param 事件回调参数，见 @ref xf_ble_gatts_evt_cb_param_t
 * @return xf_ble_evt_res_t 事件处理结果
 *      - XF_BLE_EVT_RES_NOT_HANDLED    事件未被处理
 *      - XF_BLE_EVT_RES_HANDLED        事件已被处理
 *      - XF_BLE_EVT_RES_ERR            事件处理错误
 * 
 * @warning 返回值请应该按实际处理结果进行返回，
 *  因为部分未被处理的事件可能会在底层有的默认处理补充，
 *  所以避免出现同一事件同时被多次处理，请按实际结构返回
 */
typedef xf_ble_evt_res_t (*xf_ble_gatts_evt_cb_t)(
    xf_ble_gatts_evt_t event,
    xf_ble_gatts_evt_cb_param_t *param);

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

#endif /* __XF_BLE_GATT_SERVER_TYPES_H__ */
