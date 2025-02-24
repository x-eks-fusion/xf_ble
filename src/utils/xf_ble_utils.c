/**
 * @file xf_ble_utils.c
 * @author dotc (dotchan@qq.com)
 * @brief 主要为 BLE 辅助的一些方法，可简化处理。
 * @date 2024-12-06
 *
 * Copyright (c) 2024, CorAL. All rights reserved.
 *
 */

/* ==================== [Includes] ========================================== */

#include "xf_utils.h"
#include "xf_ble_gatt_server.h"

/* ==================== [Defines] =========================================== */

#define TAG "xf_ble_utils"

/* ==================== [Typedefs] ========================================== */

/* ==================== [Static Prototypes] ================================= */

/* ==================== [Static Variables] ================================== */

/* ==================== [Macros] ============================================ */

/* ==================== [Global Functions] ================================== */

xf_err_t xf_ble_gatts_svc_get_att_cnt(xf_ble_gatts_service_t *service)
{
    XF_ASSERT(service != NULL, XF_ERR_INVALID_ARG,
        TAG, "service == NULL");

    xf_ble_gatts_chara_t *chara_set = service->chara_set;
    XF_ASSERT(chara_set != NULL, XF_ERR_INVALID_ARG,
        TAG, "chara_set == NULL");

    xf_ble_gatt_att_num_t local_att_cnt = 0;
    uint8_t num_chara = 0;
    while (chara_set[num_chara].uuid != XF_BLE_ATTR_SET_END_FLAG) 
    {
        local_att_cnt += 2;  // 特征声明 + 特征值声明

        xf_ble_gatts_desc_t *desc_set = chara_set[num_chara].desc_set;
        if (desc_set == NULL) {
            ++num_chara;
            continue;
        }
        uint8_t num_desc = 0;
        while (desc_set[num_desc].uuid != XF_BLE_ATTR_SET_END_FLAG) {
            ++num_desc;
            ++local_att_cnt;
        }
        ++num_chara;
    }
    // 服务本地属性声明 (服务声明 + 本地属性的数量) + 引用服务声明的数量
    service->att_cnt = 1 + local_att_cnt + service->include_cnt;  
    return XF_OK;
}

xf_err_t xf_ble_gatts_svc_get_att_local_map(xf_ble_gatts_service_t *service)
{
    XF_ASSERT(service != NULL, XF_ERR_INVALID_ARG, TAG, "service == NULL");
    XF_ASSERT(service->att_cnt > (service->include_cnt + 1), XF_ERR_INVALID_ARG, 
        TAG, "att_cnt(%d) <= (include_cnt(%d) + 1)", service->att_cnt, (service->include_cnt + 1));

    /* 获取服务本地的属性数量: 服务属性总数 - 包含 (引用) 服务声明的数量 - 服务声明属性  */
    xf_ble_gatt_att_num_t local_att_cnt = service->att_cnt - service->include_cnt - 1;

    service->att_local_map = xf_malloc(local_att_cnt * sizeof(xf_ble_gatt_att_num_t));
    XF_CHECK(service->att_local_map == NULL, XF_ERR_NO_MEM, TAG, "malloc att_local_map failed!");
    xf_memset(service->att_local_map, 0, local_att_cnt * sizeof(xf_ble_gatt_att_num_t));
    
    xf_ble_gatts_chara_t *chara_set = service->chara_set;
    XF_ASSERT(chara_set != NULL, XF_ERR_INVALID_ARG, TAG, "chara_set == NULL");
    
    uint8_t num_att = 0;
    uint8_t num_chara = 0;
    while (chara_set[num_chara].uuid != XF_BLE_ATTR_SET_END_FLAG) 
    {   
        
        service->att_local_map[num_att] = num_chara; // 特征声明
        XF_ASSERT(num_att < local_att_cnt, XF_ERR_INVALID_ARG,
            TAG, "num_att(%d) >= local_att_cnt(%d)", num_att, local_att_cnt);

        ++num_att;

        service->att_local_map[num_att] = num_chara; // 特征值声明
        XF_ASSERT(num_att < local_att_cnt, XF_ERR_INVALID_ARG,
            TAG, "num_att(%d) >= local_att_cnt(%d)", num_att, local_att_cnt);

        ++num_att;

        xf_ble_gatts_desc_t *desc_set = chara_set[num_chara].desc_set;
        if (desc_set == NULL) {
            ++num_chara;
            continue;
        }
        uint8_t num_desc = 0;
        while (desc_set[num_desc].uuid != XF_BLE_ATTR_SET_END_FLAG) {
            service->att_local_map[num_att] = num_chara; // 描述符声明
            XF_ASSERT(num_att < local_att_cnt, XF_ERR_INVALID_ARG,
                TAG, "num_att(%d) >= local_att_cnt(%d)", num_att, local_att_cnt);
            ++num_att;
            ++num_desc;
        }
        ++num_chara;
    }
    return XF_OK;
}

xf_err_t xf_ble_gatts_svc_att_get_pos_by_handle(
    const xf_ble_gatts_service_t *service,
    xf_ble_attr_handle_t handle,
    xf_ble_gatt_att_num_t *chara_index,
    xf_ble_gatt_chara_att_offset_t *offset)
{
    XF_ASSERT(service != NULL, XF_ERR_INVALID_ARG, TAG, "service == NULL");
    XF_ASSERT(chara_index != NULL, XF_ERR_INVALID_ARG,
        TAG, "chara_index == NULL");
    XF_ASSERT(offset != NULL, XF_ERR_INVALID_ARG,
        TAG, "offset == NULL");

    /* 获取指定属性在服务本地属性中的偏移:
        指定句柄 - ( 服务起始句柄 + 1个服务声明属性 + N 个包含 (引用) 服务声明属性)  */
    uint8_t offset_of_local_svc = handle - (service->handle + 1 + service->include_cnt);
    *chara_index = service->att_local_map[offset_of_local_svc];
    *offset = handle - service->chara_set[*chara_index].handle;

    return XF_OK;
}
/* ==================== [Static Functions] ================================== */
