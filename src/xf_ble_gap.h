/**
 * @file xf_ble_gap.h
 * @author dotc (dotchan@qq.com)
 * @brief
 * @date 2024-08-06
 *
 * Copyright (c) 2024, CorAL. All rights reserved.
 *
 */

#ifndef __XF_BLE_GAP_H__
#define __XF_BLE_GAP_H__

/* ==================== [Includes] ========================================== */

#include "xf_utils.h"
#include "xf_ble_gap_types.h"
#include "xf_ble_sm_types.h"

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

/* ==================== [Global Prototypes] ================================= */

/**
 * @brief BLE 功能开启
 *
 * @note 包含所有 BLE 开启前的处理
 * @return xf_err_t
 *      - XF_OK                 成功
 *      - XF_FAIL               失败
 *      - (OTHER)               @ref xf_err_t
 */
xf_err_t xf_ble_enable(void);

/**
 * @brief BLE 功能关闭
 *
 * @note 包含所有 BLE 关闭前的处理
 * @return xf_err_t
 *      - XF_OK                 成功
 *      - XF_FAIL               失败
 *      - (OTHER)               @ref xf_err_t
 */
xf_err_t xf_ble_disable(void);

/**
 * @brief BLE GAP 设置本端设备地址
 *
 * @param addr BLE 地址信息，见 @ref xf_ble_addr_t
 * @return xf_err_t
 *      - XF_OK                 成功
 *      - XF_FAIL               失败
 *      - XF_ERR_NOT_SUPPORTED  不支持
 *      - (OTHER)               @ref xf_err_t
 */
xf_err_t xf_ble_gap_set_local_addr(xf_ble_addr_t *addr);

/**
 * @brief BLE GAP 获取本端设备地址
 *
 * @param[out] addr BLE 地址信息，见 @ref xf_ble_addr_t
 * @return xf_err_t
 *      - XF_OK                 成功
 *      - XF_FAIL               失败
 *      - (OTHER)               @ref xf_err_t
 */
xf_err_t xf_ble_gap_get_local_addr(xf_ble_addr_t *addr);

/**
 * @brief BLE GAP 设置本端设备的外观
 *
 * @param appearance 外观值，见 @ref xf_ble_appearance_t
 * @return xf_err_t
 *      - XF_OK                 成功
 *      - XF_FAIL               失败
 *      - (OTHER)               @ref xf_err_t
 */
xf_err_t xf_ble_gap_set_local_appearance(xf_ble_appearance_t appearance);

/**
 * @brief BLE GAP 获取本端设备的外观
 *
 * @param[out] appearance 外观值，见 @ref xf_ble_appearance_t
 * @return xf_err_t
 *      - XF_OK                 成功
 *      - XF_FAIL               失败
 *      - (OTHER)               @ref xf_err_t
 */
xf_err_t xf_ble_gap_get_local_appearance(xf_ble_appearance_t *appearance);

/**
 * @brief BLE GAP 设置本端设备名称
 *
 * @param name 设备名
 * @param len 设备名长度
 * @return xf_err_t
 *      - XF_OK                 成功
 *      - XF_FAIL               失败
 *      - (OTHER)               @ref xf_err_t
 */
xf_err_t xf_ble_gap_set_local_name(const uint8_t *name, const uint8_t len);

/**
 * @brief BLE GAP 获取本端设备名称
 *
 * @param[out] name 设备名
 * @param[out] len 设备名长度
 * @return xf_err_t
 *      - XF_OK                 成功
 *      - XF_FAIL               失败
 *      - (OTHER)               @ref xf_err_t
 */
xf_err_t xf_ble_gap_get_local_name(uint8_t *name, uint8_t *len);

/**
 * @brief BLE GAP 广播创建
 *
 * @param[out] adv_id 广播 ID
 * @param param 广播参数，见 @ref xf_ble_gap_adv_param_t
 * @param data 广播数据，见 @ref xf_ble_gap_adv_data_t
 * @return xf_err_t
 *      - XF_OK                 成功
 *      - XF_FAIL               失败
 *      - (OTHER)               @ref xf_err_t
 */
xf_err_t xf_ble_gap_create_adv(
    uint8_t *adv_id,
    const xf_ble_gap_adv_param_t *param,
    const xf_ble_gap_adv_data_t *data
);

/**
 * @brief BLE GAP 广播销毁
 *
 * @param adv_id 广播 ID，见 @ref xf_ble_adv_id_t
 * @return xf_err_t
 *      - XF_OK                 成功
 *      - XF_FAIL               失败
 *      - (OTHER)               @ref xf_err_t
 */
xf_err_t xf_ble_gap_delete_adv(xf_ble_adv_id_t adv_id);

/**
 * @brief BLE GAP 广播开启
 *
 * @param adv_id 广播 ID，见 @ref xf_ble_adv_id_t
 * @param duration 广告时长，0 表示始终开启
 * @return xf_err_t
 *      - XF_OK                 成功
 *      - XF_FAIL               失败
 *      - (OTHER)               @ref xf_err_t
 */
xf_err_t xf_ble_gap_start_adv(xf_ble_adv_id_t adv_id, uint16_t duration);

/**
 * @brief BLE GAP 广播关闭
 *
 * @param adv_id 广播 ID，见 @ref xf_ble_adv_id_t
 * @return xf_err_t
 *      - XF_OK                 成功
 *      - XF_FAIL               失败
 *      - (OTHER)               @ref xf_err_t
 */
xf_err_t xf_ble_gap_stop_adv(xf_ble_adv_id_t adv_id);

/**
 * @brief BLE GAP 设置广播数据
 *
 * @param adv_id 广播 ID，活跃中的广播的 ID，见 @ref xf_ble_adv_id_t
 * @param data 广播数据，见 @ref xf_ble_gap_adv_data_t
 * @return xf_err_t
 *      - XF_OK                 成功
 *      - XF_FAIL               失败
 *      - (OTHER)               @ref xf_err_t
 */
xf_err_t xf_ble_gap_set_adv_data(
    xf_ble_adv_id_t adv_id, const xf_ble_gap_adv_data_t *data);

/**
 * @brief BLE GAP 扫描开启
 *
 * @param param 扫描参数，见 @ref xf_ble_gap_scan_param_t
 * @return xf_err_t
 *      - XF_OK                 成功
 *      - XF_FAIL               失败
 *      - (OTHER)               @ref xf_err_t
 */
xf_err_t xf_ble_gap_start_scan(const xf_ble_gap_scan_param_t *param);

/**
 * @brief BLE GAP 扫描停止
 *
 * @return xf_err_t
 *      - XF_OK                 成功
 *      - XF_FAIL               失败
 *      - (OTHER)               @ref xf_err_t
 */
xf_err_t xf_ble_gap_stop_scan(void);

/**
 * @brief BLE GAP 更新连接参数
 *
 * @param conn_id 连接 (链接) ID，见 @ref xf_ble_conn_id_t
 * @param param 更新连接参数的信息，见 @ref xf_ble_gap_conn_param_update_t
 * @return xf_err_t
 *      - XF_OK                 成功
 *      - XF_FAIL               失败
 *      - (OTHER)               @ref xf_err_t
 */
xf_err_t xf_ble_gap_update_conn_param(
    xf_ble_conn_id_t conn_id, xf_ble_gap_conn_param_update_t *param);

/**
 * @brief BLE GAP 发起连接
 *
 * @param addr 要连接的地址，见 @ref xf_ble_addr_t
 * @return xf_err_t
 *      - XF_OK                 成功
 *      - XF_FAIL               失败
 *      - (OTHER)               @ref xf_err_t
 */
xf_err_t xf_ble_gap_connect(const xf_ble_addr_t *addr);

/**
 * @brief BLE GAP 断开连接
 *
 * @param addr 要断连的地址，见 @ref xf_ble_addr_t
 * @return xf_err_t
 *      - XF_OK                 成功
 *      - XF_FAIL               失败
 *      - (OTHER)               @ref xf_err_t
 */
xf_err_t xf_ble_gap_disconnect(const xf_ble_addr_t *addr);

/**
 * @brief BLE GAP 添加配对
 *
 * @param addr 要配对的设备的地址，见 @ref xf_ble_addr_t
 * @return xf_err_t
 *      - XF_OK                 成功
 *      - XF_FAIL               失败
 *      - (OTHER)               @ref xf_err_t
 */
xf_err_t xf_ble_gap_add_pair(const xf_ble_addr_t *addr);

/**
 * @brief BLE GAP 删除配对
 *
 * @param addr 要删除配对的设备的地址，见 @ref xf_ble_addr_t
 * @return xf_err_t
 *      - XF_OK                 成功
 *      - XF_FAIL               失败
 *      - (OTHER)               @ref xf_err_t
 */
xf_err_t xf_ble_gap_del_pair(const xf_ble_addr_t *addr);

/**
 * @brief BLE GAP 删除所有配对
 *
 * @return xf_err_t
 *      - XF_OK                 成功
 *      - XF_FAIL               失败
 *      - (OTHER)               @ref xf_err_t
 */
xf_err_t xf_ble_gap_del_pair_all(void);

/**
 * @brief BLE GAP 获取已配对的设备
 *
 * @param max_num 要获取的最大数量
 * @param[out] dev_list 获取到的设备列表，见 @ref xf_ble_addr_t
 * @return xf_err_t
 *      - XF_OK                 成功
 *      - XF_FAIL               失败
 *      - (OTHER)               @ref xf_err_t
 */
xf_err_t xf_ble_gap_get_pair_list(
    uint16_t *max_num, xf_ble_addr_t *dev_list);

/**
 * @brief BLE GAP 获取已绑定的设备
 *
 * @param max_num 要获取的最大数量
 * @param[out] dev_list 获取到的设备列表，见 @ref xf_ble_addr_t
 * @return xf_err_t
 *      - XF_OK                 成功
 *      - XF_FAIL               失败
 *      - (OTHER)               @ref xf_err_t
 */
xf_err_t xf_ble_gap_get_bond_list(
    int *max_num, xf_ble_addr_t *dev_list);

/**
 * @brief BLE GAP 设置配对特性
 * 
 * @param conn_id 连接 (链接) ID，见 @ref xf_ble_conn_id_t
 * @param type 将要设置本端配对特性类型，见 @ref xf_ble_sm_pair_feature_t
 * @param feature 将要设置本端配对特性参数值，见 @ref xf_ble_sm_pair_feature_param_t
 * @return xf_err_t
 *      - XF_OK                 成功
 *      - XF_FAIL               失败
 *      - (OTHER)               @ref xf_err_t
 */
xf_err_t xf_ble_gap_set_pair_feature(
    xf_ble_conn_id_t conn_id, xf_ble_sm_pair_feature_t type,
    xf_ble_sm_pair_feature_param_t feature);

/**
 * @brief BLE GAP 请求配对
 *
 * @param conn_id 连接 (链接) ID，见 @ref xf_ble_conn_id_t
 * @return xf_err_t
 *      - XF_OK                 成功
 *      - XF_FAIL               失败
 *      - (OTHER)               @ref xf_err_t
 */
xf_err_t xf_ble_gap_request_pair(xf_ble_conn_id_t conn_id);

/**
 * @brief BLE GAP 回应配对 (请求)
 *
 * @param conn_id 连接 (链接) ID，见 @ref xf_ble_conn_id_t
 * @return xf_err_t
 *      - XF_OK                 成功
 *      - XF_FAIL               失败
 *      - (OTHER)               @ref xf_err_t
 */
xf_err_t xf_ble_gap_respond_pair(xf_ble_conn_id_t conn_id);

/**
 * @brief BLE GAP 配对 passkey 互访鉴权
 *
 * @param conn_id 连接 (链接) ID，见 @ref xf_ble_conn_id_t
 * @param pin_code 6位十进制数的 pin 码，范围[100000,999999]
 * @return xf_err_t
 *      - XF_OK                 成功
 *      - XF_FAIL               失败
 *      - (OTHER)               @ref xf_err_t
 */
xf_err_t xf_ble_gap_pair_exchange_passkey(
    xf_ble_conn_id_t conn_id, uint32_t pin_code);

/**
 * @brief BLE 应用与一个广播进行关联
 * 
 * @param app_id app ID
 * @param adv_id 广播 ID
 * @return xf_err_t 
 */
xf_err_t xf_ble_app_attach_adv(
    xf_ble_app_id_t app_id, xf_ble_adv_id_t adv_id);

/**
 * @brief BLE 应用与一个连接 (链接) 进行关联
 * 
 * @param app_id app ID
 * @param conn_id 连接 (链接) ID
 * @return xf_err_t 
 */
xf_err_t xf_ble_app_attach_conn(
    xf_ble_app_id_t app_id, xf_ble_conn_id_t conn_id);

/**
 * @brief BLE 应用与一个广播 解除关联
 * 
 * @param app_id app ID
 * @param adv_id 广播 ID
 * @return xf_err_t 
 */
xf_err_t xf_ble_app_detach_adv(
    xf_ble_app_id_t app_id, xf_ble_adv_id_t adv_id);

/**
 * @brief BLE 应用与一个连接 (链接) 解除关联
 * 
 * @param app_id app ID
 * @param conn_id 连接 (链接) ID
 * @return xf_err_t 
 */
xf_err_t xf_ble_app_detach_conn(
    xf_ble_app_id_t app_id, xf_ble_conn_id_t conn_id);

/**
 * @brief BLE 获取应用 ID(通过广播)
 * 
 * @param app_id app ID
 * @param adv_id 连接 (链接) ID
 * @return xf_err_t 
 */
xf_err_t xf_ble_app_get_id_by_adv(
    xf_ble_app_id_t *app_id, xf_ble_adv_id_t adv_id);

/**
 * @brief BLE 获取应用 ID (通过连接 (链接))
 * 
 * @param app_id app ID
 * @param conn_id 连接 (链接) ID
 * @return xf_err_t 
 */
xf_err_t xf_ble_app_get_id_by_conn(
    xf_ble_app_id_t *app_id, xf_ble_conn_id_t conn_id);

/**
 * @brief BLE GAP 事件回调注册
 *
 * @param evt_cb 事件回调，见 @ref xf_ble_gap_evt_cb_t
 * @param events 事件，见 @ref xf_ble_gap_evt_t
 * @note 当前仅支持所有事件注册在同一个回调，暂不支持指定事件对应单独的回调，
 * 所以 参数 'events' 填 0 即可
 * @return xf_err_t
 *      - XF_OK                 成功
 *      - XF_FAIL               失败
 *      - (OTHER)               @ref xf_err_t
 */
xf_err_t xf_ble_gap_event_cb_register(
    xf_ble_gap_evt_cb_t evt_cb,
    xf_ble_gap_evt_t events);

/* ==================== [Macros] ============================================ */

#ifdef __cplusplus
} /* extern "C" */
#endif

/**
 * End of addtogroup group_xf_wal_ble_gap
 * @}
 */

#endif /* XF_BLE_IS_ENABLE */

#endif /* __XF_BLE_GAP_H__ */
