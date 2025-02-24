/**
 * @file xf_ble_gatt_server.h
 * @author dotc (dotchan@qq.com)
 * @brief
 * @date 2024-08-06
 *
 * Copyright (c) 2024, CorAL. All rights reserved.
 *
 */

#ifndef __XF_BLE_GATT_SERVER_H__
#define __XF_BLE_GATT_SERVER_H__

/* ==================== [Includes] ========================================== */

#include "xf_utils.h"

#include "xf_ble_types.h"
#include "xf_ble_gatt_server_types.h"

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

/* ==================== [Global Prototypes] ================================= */

/**
 * @brief BLE GATTS 服务端注册
 *
 * @param[in] app_uuid 要注册的服务端 (应用) 的 UUID ，见 @ref xf_ble_uuid_info_t
 * @param[out] app_id 服务端 (应用) ID，见 @ref xf_ble_app_id_t
 * @return xf_err_t
 *      - XF_OK                 成功
 *      - XF_FAIL               失败
 *      - (OTHER)               @ref xf_err_t
 */
xf_err_t xf_ble_gatts_app_register(
    xf_ble_uuid_info_t *app_uuid, xf_ble_app_id_t *app_id);

/**
 * @brief BLE GATTS 服务端注销
 *
 * @param app_id 服务端 (应用) ID，见 @ref xf_ble_app_id_t
 * @return xf_err_t
 *      - XF_OK                 成功
 *      - XF_FAIL               失败
 *      - (OTHER)               @ref xf_err_t
 */
xf_err_t xf_ble_gatts_app_unregister(xf_ble_app_id_t app_id);

/* TODO 支持多服务添加到一个 profile  */

/**
 * @brief BLE GATTS 向服务端 (应用) 添加服务
 *
 * @param app_id 服务端 (应用) ID，见 @ref xf_ble_app_id_t
 * @param service 要添加的服务信息，见 @ref xf_ble_gatts_service_t
 * @return xf_err_t
 *      - XF_OK                 成功
 *      - XF_FAIL               失败
 *      - (OTHER)               @ref xf_err_t
 * 
 */
xf_err_t xf_ble_gatts_add_service(
    xf_ble_app_id_t app_id, xf_ble_gatts_service_t *service);

/**
 * @brief BLE GATTS 动态获取服务属性的总数
 * 
 * @param service 服务结构，见 @ref xf_ble_gatts_service_t
 * @return xf_err_t 
 * 
 * @note 获取到的结果将会填至服务信息中的 att_cnt 中，注意，这将覆盖 att_local_map 的值
 * @note 此方法为动态方法，即作用在运行时，会需要一定处理时间及内存空间，
 *  建议使用静态方法 (如自行编译前统计) 获取到属性总数，直接填至服务信息的 att_cnt 参数中
 */
xf_err_t xf_ble_gatts_svc_get_att_cnt(xf_ble_gatts_service_t *service);

/**
 * @brief BLE GATTS 动态获取服务本地 (部分的) 属性的映射表 (句柄偏移值与特征集合的索引值的映射)
 * 
 * @param service 服务结构，见 @ref xf_ble_gatts_service_t
 * @return xf_err_t 
 * 
 * @note 本地 (部分的) 属性的映射表，
 *  不包含服务声明以及包含 (引用) 服务声明的属性，
 *  仅包含本地属性中的特征声明、特征值声明、描述符声明的属性
 * @note 获取到的结果将会填至服务信息中的 att_local_map 中，注意，这将覆盖 att_local_map 的值
 * @note 此方法为动态方法，即在运行时生成，会需要一定处理时间及内存空间，
 *  建议使用静态方法生成映射表 (如自行编译前定义映射表)，直接填至服务信息的 att_local_map 参数中
 */
xf_err_t xf_ble_gatts_svc_get_att_local_map(xf_ble_gatts_service_t *service);

/**
 * @brief BLE GATTS 动态获取服务本地 (部分的) 属性的映射表 (句柄偏移值与特征集合的索引值的映射)
 * 
 * @param p_svc 服务结构，见 @ref xf_ble_gatts_service_t
 * 
 * @note 本地 (部分的) 属性的数量，
 *  不包含服务声明以及包含 (引用) 服务声明的属性，
 *  仅包含本地属性中的特征声明、特征值声明、描述符声明的属性
 * @note 获取到的结果将会填至服务信息中的 att_local_map 中，注意，这将覆盖 att_local_map 的值
 * @note 此方法为动态方法，即在运行时生成，会需要一定处理时间及内存空间，
 *  建议使用静态方法生成映射表 (如自行编译前定义映射表)，直接填至服务信息的 att_local_map 参数中
 */
#define XF_BLE_GATTS_SVC_GET_ATT_LOCAL_MAP_CNT(p_svc) \
    ((p_svc)->att_cnt - 1 - (p_svc)->include_cnt)


/**
 * @brief BLE GATTS 获取属性在服务结构中的位置 (通过句柄)
 * 
 * @param service 服务结构，见 @ref xf_ble_gatts_service_t
 * @param handle 查找的属性相关的句柄，见 @ref xf_ble_attr_handle_t
 * @param[out] chara_index 获取到的属性所在特征结构(在的服务结构中)的索引值，
 *  见 @ref xf_ble_gatt_att_num_t
 * @param[out] offset 获取到的属性在特征结构的中的偏移值 (索引值)。偏移值对应的属性类型，
 *  见 @ref xf_ble_gatt_chara_att_offset_t
 * @return xf_err_t 
 */
xf_err_t xf_ble_gatts_svc_att_get_pos_by_handle(
    const xf_ble_gatts_service_t *service,
    xf_ble_attr_handle_t handle,
    xf_ble_gatt_att_num_t *chara_index,
    xf_ble_gatt_chara_att_offset_t *offset);

/**
 * @brief BLE GATTS 服务开启
 *
 * @param app_id 服务端 (应用) ID，见 @ref xf_ble_app_id_t
 * @param handle 指定的服务句柄
 * @return xf_err_t
 *      - XF_OK                 成功
 *      - XF_FAIL               失败
 *      - (OTHER)               @ref xf_err_t
 */
xf_err_t xf_ble_gatts_start_service(
    xf_ble_app_id_t app_id, 
    xf_ble_attr_handle_t handle);
/**
 * @brief BLE GATTS 服务停止
 *
 * @param app_id 服务端 (应用) ID，见 @ref xf_ble_app_id_t
 * @param handle 指定的服务句柄
 * @return xf_err_t
 *      - XF_OK                 成功
 *      - XF_FAIL               失败
 *      - (OTHER)               @ref xf_err_t
 */
xf_err_t xf_ble_gatts_stop_service(
    xf_ble_app_id_t app_id, 
    xf_ble_attr_handle_t handle);

/**
 * @brief BLE GATTS 删除所有服务
 *
 * @param app_id 服务端 (应用) ID，见 @ref xf_ble_app_id_t
 * @return xf_err_t
 *      - XF_OK                 成功
 *      - XF_FAIL               失败
 *      - (OTHER)               @ref xf_err_t
 */
xf_err_t xf_ble_gatts_del_services_all(xf_ble_app_id_t app_id);

/**
 * @brief BLE GATTS 发送通知
 *
 * @param app_id 服务端 (应用) ID，见 @ref xf_ble_app_id_t
 * @param conn_id 连接 ID (链接 ID )，见 @ref xf_ble_conn_id_t
 * @param param 发送的通知的信息，见 @ref xf_ble_gatts_ntf_t
 * @return xf_err_t
 *      - XF_OK                 成功
 *      - XF_FAIL               失败
 *      - (OTHER)               @ref xf_err_t
 */
xf_err_t xf_ble_gatts_send_notification(
    xf_ble_app_id_t app_id, xf_ble_conn_id_t conn_id,
    xf_ble_gatts_ntf_t *param);

/**
 * @brief BLE GATTS 发送指示
 *
 * @param app_id 服务端 (应用) ID，见 @ref xf_ble_app_id_t
 * @param conn_id 连接 ID (链接 ID )，见 @ref xf_ble_conn_id_t
 * @param param 发送的指示的信息，见 @ref xf_ble_gatts_ind_t
 * @return xf_err_t
 *      - XF_OK                 成功
 *      - XF_FAIL               失败
 *      - (OTHER)               @ref xf_err_t
 */
xf_err_t xf_ble_gatts_send_indication(
    xf_ble_app_id_t app_id, xf_ble_conn_id_t conn_id,
    xf_ble_gatts_ind_t *param);

/**
 * @brief BLE GATTS 发送 读 (请求的) 响应
 *
 * @param app_id 服务端 (应用) ID，见 @ref xf_ble_app_id_t
 * @param conn_id 连接 ID (链接 ID )，见 @ref xf_ble_conn_id_t
 * @param param 发送的响应的信息，见 @ref xf_ble_gatts_response_t
 * @return xf_err_t
 */
xf_err_t xf_ble_gatts_send_read_rsp(
    xf_ble_app_id_t app_id, xf_ble_conn_id_t conn_id,
    xf_ble_gatts_response_t *param);

/**
 * @brief BLE GATTS 发送 写 (请求的) 响应
 *
 * @param app_id 服务端 (应用) ID，见 @ref xf_ble_app_id_t
 * @param conn_id 连接 ID (链接 ID )，见 @ref xf_ble_conn_id_t
 * @param param 发送的响应的信息，见 @ref xf_ble_gatts_response_t
 * @return xf_err_t
 */
xf_err_t xf_ble_gatts_send_write_rsp(
    xf_ble_app_id_t app_id, xf_ble_conn_id_t conn_id,
    xf_ble_gatts_response_t *param);

/**
 * @brief BLE GATTS 事件回调注册
 *
 * @param evt_cb 事件回调，见 @ref xf_ble_gatts_evt_cb_t
 * @param events 事件，见 @ref xf_ble_gatts_evt_t
 * @note 当前仅支持所有事件注册在同一个回调，暂不支持指定事件对应单独的回调，
 * 所以 参数 'events' 填 0 即可
 * @return xf_err_t
 *      - XF_OK                 成功
 *      - XF_FAIL               失败
 *      - (OTHER)               @ref xf_err_t
 */
xf_err_t xf_ble_gatts_event_cb_register(
    xf_ble_gatts_evt_cb_t evt_cb,
    xf_ble_gatts_evt_t events);

/* ==================== [Macros] ============================================ */

#ifdef __cplusplus
} /* extern "C" */
#endif

/**
 * End of addtogroup group_xf_wal_ble_gatt
 * @}
 */

#endif /* XF_BLE_IS_ENABLE */

#endif /* __XF_BLE_GATT_SERVER_H__ */
