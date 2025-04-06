/**
 * @file xf_ble_lp_types.h
 * @author dotc (dotchan@qq.com)
 * @brief 
 * @date 2025-03-28
 * 
 * @Copyright (c) 2025, CorAL. All rights reserved.
 */

/**
 * @cond (XFAPI_USER || XFAPI_PORT || XFAPI_INTERNAL)
 * @ingroup group_xf_wal
 * @defgroup group_xf_wal_ble xf_ble
 * @brief xf_ble 是对 ble 的封装。
 * @endcond
 */

#ifndef __XF_BLE_LP_TYPES_H__
#define __XF_BLE_LP_TYPES_H__

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

typedef enum _xf_ble_lp_state_t
{
    XF_BLE_LP_STATE_WAKEUP_CONTEXT,
    XF_BLE_LP_STATE_WAKEUP_RST,
    XF_BLE_LP_STATE_ACTIVE,
} xf_ble_lp_state_t;

typedef enum _xf_ble_lp_mode_t
{
    XF_BLE_LP_MODE_SLEEP_CONTEXT    = (0x1 << XF_BLE_LP_STATE_WAKEUP_CONTEXT),
    XF_BLE_LP_MODE_SLEEP_RST        = (0x1 << XF_BLE_LP_STATE_WAKEUP_RST),
} xf_ble_lp_mode_t;

typedef enum _xf_ble_lp_ext_state_t
{
    XF_BLE_LP_EXT_STATE_IDLE,
    XF_BLE_LP_EXT_STATE_BUSY,
} xf_ble_lp_ext_state_t;

typedef enum _xf_ble_lp_cfg_t
{
    XF_BLE_LP_CFG_SLEEP_FUNC,
    XF_BLE_LP_CFG_EXT_STATE_GET,
    XF_BLE_LP_CFG_EVT_INIT_TIME_GET,
} xf_ble_lp_cfg_t;

typedef enum _xf_ble_lp_sleep_time_t
{
    XF_BLE_LP_SLEEP_TIME_US,
    XF_BLE_LP_SLEEP_TIME_TICK,
    XF_BLE_LP_SLEEP_TIME_MS,
} xf_ble_lp_sleep_time_t;

typedef void * xf_ble_lp_cfg_value_t;

union _xf_ble_lp_cfg_value_t
{
    /**
     * @brief 用户自定义的睡眠方法的实现 
     * @param sleep_duration BLE 协议栈当前预估会休眠的时间，
     *  暂未规定单位，因为各个平台可能不同，固定单位会增加转换的工作。
     * 
     * @note 默认 (不设置 sleep_func) 时，使用底层实现的方法，
     *  设置为自定义 sleep_func 时，需自行根据 sleep_duration 选择休眠策略。
     */
    xf_ble_lp_state_t (*sleep_func)(xf_ble_lp_mode_t mode, uint32_t sleep_duration);

    /**
     * @brief BLE 协议栈以外的可休眠状态获取 (如其他外设、任务当前是否允许休眠)
     * @param sleep_duration BLE 协议栈当前预估会休眠的时间，
     *  暂未规定单位，因为各个平台可能不同，固定单位会增加转换的工作。
     * 
     * @note 默认 (不设置 sleep_func) 时，使用底层实现的方法，即不关注外部休眠状态（是否允许休眠），
     *  设置为自定义 sleep_func 时，需自行根据 sleep_duration 选择休眠策略。
     */
    xf_ble_lp_ext_state_t (*ext_state_get)(void);
    void (*evt_init_time_get)(xf_ble_lp_sleep_time_t *type, uint32_t *time);  // ble 事件发起的时间 (从启动时) 的获取
    void *_ptr;
};

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

#endif /* __XF_BLE_LP_TYPES_H__ */
