/**
 * @file xf_ble_lp.h
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

#ifndef __XF_BLE_LP_H__
#define __XF_BLE_LP_H__

/* ==================== [Includes] ========================================== */

#include "xf_utils.h"
#include "xf_ble_config_internal.h"

#if XF_BLE_IS_ENABLE  || defined(__DOXYGEN__)

#include "xf_sys.h"
#include "xf_ble_lp_types.h"

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

/* ==================== [Global Prototypes] ================================= */

/**
 * @brief XF BLE 低功耗初始化
 * 
 * @return xf_err_t 
 */
xf_err_t xf_ble_lp_init(void);

/**
 * @brief XF BLE 低功耗反初始化
 * 
 * @return xf_err_t 
 */
xf_err_t xf_ble_lp_deinit(void);

/**
 * @brief XF BLE 低功耗功能开启
 * 
 * @return xf_err_t 
 */
xf_err_t xf_ble_lp_enable(void);

/**
 * @brief XF BLE 低功耗功能关闭
 * 
 * @return xf_err_t 
 */
xf_err_t xf_ble_lp_disable(void);

/**
 * @brief ble lp 配置
 * 
 * @param type 配置类型
 * @param value 配置值
 * @return xf_err_t 
 * 
 * @note 该函数主要用于自定义一些低功耗处理，大多情况下无需进行自定义配置，即可正常使用默认的低功耗处理。
 */
xf_err_t xf_ble_lp_config(xf_ble_lp_cfg_t type, xf_ble_lp_cfg_value_t value);

/**
 * @brief ble lp 尝试休眠
 * @param mode 可选的休眠模式
 * 
 * @return xf_ble_lp_state_t 
 */
xf_ble_lp_state_t xf_ble_lp_sleep(xf_ble_lp_mode_t mode);

/* ==================== [Macros] ============================================ */

#ifdef __cplusplus
} /* extern "C" */
#endif

/**
 * End of addtogroup group_xf_wal_ble
 * @}
 */

#endif /* XF_BLE_IS_ENABLE */

#endif /* __XF_BLE_LP_H__ */
