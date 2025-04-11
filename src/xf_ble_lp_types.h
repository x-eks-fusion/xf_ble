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

/**
 * @brief XF BLE 低功耗状态
 */
typedef enum _xf_ble_lp_state_t
{
    XF_BLE_LP_STATE_WAKEUP_CONTEXT,     /*!< 唤醒后在上下文中恢复 (执行) */       
    XF_BLE_LP_STATE_WAKEUP_RST,         /*!< 唤醒后复位 */
    XF_BLE_LP_STATE_ACTIVE,             /*!< 活跃状态 (未休眠) */
} xf_ble_lp_state_t;

/**
 * @brief XF BLE 低功耗模式
 */
typedef enum _xf_ble_lp_mode_t
{
    XF_BLE_LP_MODE_SLEEP_CONTEXT    = (0x1 << XF_BLE_LP_STATE_WAKEUP_CONTEXT),      /*!< 唤醒后将会在上下文中恢复的休眠模式 */
    XF_BLE_LP_MODE_SLEEP_RST        = (0x1 << XF_BLE_LP_STATE_WAKEUP_RST),          /*!< 唤醒后将会复位的休眠模式 */
} xf_ble_lp_mode_t;

/**
 * @brief XF BLE 低功耗配置
 */
typedef enum _xf_ble_lp_cfg_t
{
    XF_BLE_LP_CFG_SLEEP_FUNC,       /*!< 自定义的休眠方法 */
} xf_ble_lp_cfg_t;

typedef void * xf_ble_lp_cfg_value_t;

union _xf_ble_lp_cfg_value_t
{
    /**
     * @brief 用户自定义的睡眠方法的实现
     * @param base_us 休眠时间的单位，以 us 为基准。
     * @param sleep_duration BLE 协议栈当前预估会休眠的时间，时间单位为 base_us 。
     * 
     * @note 默认 (不设置 sleep_func) 时，使用底层实现的方法，
     *  设置为自定义 sleep_func 时，需自行根据 mode、base_us、 sleep_duration 选择休眠策略。
     */
    xf_ble_lp_state_t (*sleep_func)(xf_ble_lp_mode_t mode, float base_us, uint32_t sleep_duration);
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
