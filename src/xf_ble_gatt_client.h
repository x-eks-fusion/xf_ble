/**
 * @file xf_ble_gatt_client.h
 * @author dotc (dotchan@qq.com)
 * @brief
 * @date 2024-08-06
 *
 * Copyright (c) 2024, CorAL. All rights reserved.
 *
 */

#ifndef __XF_BLE_GATT_CLIENT_H__
#define __XF_BLE_GATT_CLIENT_H__

/* ==================== [Includes] ========================================== */

#include "xf_utils.h"

#include "xf_ble_types.h"
#include "xf_ble_gatt_client_types.h"

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
 * @brief BLE GATTC 客户端注册
 *
 * @param[in] app_uuid 要注册的客户端 (应用) 的 UUID ，见 @ref xf_ble_uuid_info_t
 * @param[out] app_id 客户端 (应用) ID，见 @ref xf_ble_app_id_t 
 * @return xf_err_t
 *      - XF_OK                 成功
 *      - XF_FAIL               失败
 *      - (OTHER)               @ref xf_err_t
 */
xf_err_t xf_ble_gattc_app_register(
    xf_ble_uuid_info_t *app_uuid, xf_ble_app_id_t *app_id);

/**
 * @brief BLE GATTC 客户端注销
 *
 * @param app_id 客户端 ID，见 @ref xf_ble_app_id_t 
 * @return xf_err_t
 *      - XF_OK                 成功
 *      - XF_FAIL               失败
 *      - (OTHER)               @ref xf_err_t
 */
xf_err_t xf_ble_gattc_app_unregister(xf_ble_app_id_t app_id);

/**
 * @brief BLE GATTC 搜寻服务（指定 UUID 或 尝试搜寻所有服务）
 *
 * @param app_id 客户端 ID (应用 ID )，见 @ref xf_ble_app_id_t 
 * @param conn_id 连接 ID (链接 ID )，见 @ref xf_ble_conn_id_t
 * @param start_handle 服务起始句柄
 * @param end_handle 服务结束句柄
 * @param service_uuid 搜寻的服务的 UUID，见 @ref xf_ble_uuid_info_t
 *      - NULL      搜寻给定句柄范围内所有服务
 *      - (OTHER)   搜寻给定句柄范围内指定 UUID 的服务 ( 注意 UUID 需要为有效值，如不能为 0 )
 * @param [in,out] service_set_info 传入将存储服务集合信息的地址。
 *  见 @ref xf_ble_gattc_service_found_set_t ，例：
 * @code
 *  xf_ble_gattc_service_found_set_t service_set_info = {0};
 *  ......
 *  xf_ble_gattc_discover_service(s_app_id, s_conn_id, NULL, &service_set_info);
 * @endcode
 * @return xf_err_t
 *      - XF_OK                 成功
 *      - XF_FAIL               失败
 *      - (OTHER)               @ref xf_err_t
 */
xf_err_t xf_ble_gattc_discover_service(
    xf_ble_app_id_t app_id, xf_ble_conn_id_t conn_id,
    xf_ble_attr_handle_t start_handle,
    xf_ble_attr_handle_t end_handle,
    xf_ble_uuid_info_t *service_uuid,
    xf_ble_gattc_service_found_set_t *service_set_info);

/**
 * @brief BLE GATTC 搜寻特征（指定 UUID 或 尝试搜寻所有特征）
 *
 * @param app_id 客户端 ID (应用 ID)，见 @ref xf_ble_app_id_t 
 * @param conn_id 连接 ID (链接 ID )，见 @ref xf_ble_conn_id_t
 * @param start_handle 服务起始句柄
 * @param end_handle 服务结束句柄
 * @param chara_uuid 搜寻的特征的 UUID，见 @ref xf_ble_uuid_info_t
 *      - NULL      搜寻给定句柄范围内所有特征
 *      - (OTHER)   搜寻给定句柄范围内指定 UUID 的特征 ( 注意 UUID 需要为有效值，如不能为 0 )
 * @param [in,out] chara_set_info 传入将存储特征集合信息的地址。
 *  见 @ref xf_ble_gattc_chara_found_set_t ，例：
 * @code
 *  xf_ble_gattc_chara_found_set_t chara_set_info = {0};
 *  ......
 *  xf_ble_gattc_discover_chara(s_app_id, s_conn_id, svc->start_hdl, svc->end_hdl, NULL, &chara_set_info);
 * @endcode
 * @return xf_err_t
 *      - XF_OK                 成功
 *      - XF_FAIL               失败
 *      - (OTHER)               @ref xf_err_t
 */
xf_err_t xf_ble_gattc_discover_chara(
    xf_ble_app_id_t app_id, xf_ble_conn_id_t conn_id,
    xf_ble_attr_handle_t start_handle,
    xf_ble_attr_handle_t end_handle,
    xf_ble_uuid_info_t *chara_uuid,
    xf_ble_gattc_chara_found_set_t *chara_set_info);

/**
 * @brief BLE GATTC 通过句柄发起读请求
 *
 * @param app_id 客户端 ID (应用 ID)，见 @ref xf_ble_app_id_t 
 * @param conn_id 连接 ID (链接 ID )，见 @ref xf_ble_conn_id_t
 * @param handle 句柄
 * @return xf_err_t
 *      - XF_OK                 成功
 *      - XF_FAIL               失败
 *      - (OTHER)               @ref xf_err_t
 */
xf_err_t xf_ble_gattc_request_read_by_handle(
    xf_ble_app_id_t app_id, xf_ble_conn_id_t conn_id,
    xf_ble_attr_handle_t handle);

/**
 * @brief BLE GATTC 通过 UUID 发起读请求
 *
 * @param app_id 客户端 ID (应用 ID)，见 @ref xf_ble_app_id_t 
 * @param conn_id 连接 ID (链接 ID )，见 @ref xf_ble_conn_id_t
 * @param start_handle 起始句柄
 * @param end_handle 结束句柄
 * @param uuid 指定的 UUID
 * @return xf_err_t
 *      - XF_OK                 成功
 *      - XF_FAIL               失败
 *      - (OTHER)               @ref xf_err_t
 */
xf_err_t xf_ble_gattc_request_read_by_uuid(
    xf_ble_app_id_t app_id, xf_ble_conn_id_t conn_id,
    xf_ble_attr_handle_t start_handle,
    xf_ble_attr_handle_t end_handle,
    const xf_ble_uuid_info_t *uuid);

/**
 * @brief BLE GATTC 发起写请求
 *
 * @param app_id 客户端 ID (应用 ID)，见 @ref xf_ble_app_id_t 
 * @param conn_id 连接 ID (链接 ID )，见 @ref xf_ble_conn_id_t
 * @param handle 句柄
 * @param value 要写的数据
 * @param value_len 要写的数据的长度
 * @param write_type 写请求类型，见 @ref xf_ble_gattc_write_type_t
 * @return xf_err_t
 *      - XF_OK                 成功
 *      - XF_FAIL               失败
 *      - (OTHER)               @ref xf_err_t
 */
xf_err_t xf_ble_gattc_request_write(
    xf_ble_app_id_t app_id, xf_ble_conn_id_t conn_id,
    xf_ble_attr_handle_t handle,
    uint8_t *value,
    uint16_t value_len,
    xf_ble_gattc_write_type_t write_type);

/**
 * @brief BLE GATTC 发送 MTU 协商
 *
 * @param app_id 客户端 ID (应用 ID)，见 @ref xf_ble_app_id_t 
 * @param conn_id 连接 ID (链接 ID )，见 @ref xf_ble_conn_id_t
 * @param mtu_size 协商的 MTU 大小
 * @return xf_err_t
 *      - XF_OK                 成功
 *      - XF_FAIL               失败
 *      - (OTHER)               @ref xf_err_t
 */
xf_err_t xf_ble_gattc_request_exchange_mtu(
    xf_ble_app_id_t app_id, xf_ble_conn_id_t conn_id,
    uint16_t mtu_size);

/**
 * @brief BLE GATTC 事件回调注册
 *
 * @param evt_cb 事件回调，见 @ref xf_ble_gattc_evt_cb_t
 * @param events 事件，见 @ref xf_ble_gattc_evt_t
 * @note 当前仅支持所有事件注册在同一个回调，暂不支持指定事件对应单独的回调，
 * 所以 参数 'events' 填 0 即可
 * @return xf_err_t
 *      - XF_OK                 成功
 *      - XF_FAIL               失败
 *      - (OTHER)               @ref xf_err_t
 */
xf_err_t xf_ble_gattc_event_cb_register(
    xf_ble_gattc_evt_cb_t evt_cb,
    xf_ble_gattc_evt_t events);

/* ==================== [Macros] ============================================ */

#ifdef __cplusplus
} /* extern "C" */
#endif

/**
 * End of addtogroup group_xf_wal_ble_gatt
 * @}
 */

#endif /* XF_BLE_IS_ENABLE */

#endif /* __XF_BLE_GATT_CLIENT_H__ */
