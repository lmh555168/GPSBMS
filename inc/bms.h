/**
 * Copyright @ Goome Technologies Co., Ltd. 2009-2019. All rights reserved.
 * File name:        bms.h
 * Author:           李耀轩     
 * Version:          1.0
 * Date:             2019-07-22
 * Description:      
 * Others:      
 * Function List:    
    1. 创建bms模块
    2. 销毁bms模块
    3. bms模块定时处理入口
 * History: 
    1. Date:         2019-07-22
       Author:       李耀轩
       Modification: 创建初始版本
    2. Date: 		 
	   Author:		 
	   Modification: 

 */
 
#ifndef __BMS_H_
#define __BMS_H_
#include "error_code.h"
#include "gm_type.h"



/**
 * Function:   创建bms模块
 * Description:创建bms模块
 * Input:	   无
 * Output:	   无
 * Return:	   GM_SUCCESS——成功；其它错误码——失败
 * Others:	   使用前必须调用,否则调用其它接口返回失败错误码
 */
GM_ERRCODE bms_create(void);

/**
 * Function:   销毁bms模块
 * Description:销毁bms模块
 * Input:	   无
 * Output:	   无
 * Return:	   GM_SUCCESS——成功；其它错误码——失败
 * Others:	   
 */
GM_ERRCODE bms_destroy(void);

/**
 * Function:   bms模块定时处理入口
 * Description:bms模块定时处理入口
 * Input:	   无
 * Output:	   无
 * Return:	   GM_SUCCESS——成功；其它错误码——失败
 * Others:	   1秒钟调用1次
 */
GM_ERRCODE bms_timer_proc(void);


GM_ERRCODE bms_cmd_write(char *cmd, u8 len);

GM_ERRCODE bms_msg_receive(char* p_cmd, u16 cmd_len);

GM_ERRCODE bms_uart_receive_data(char* p_cmd, u16 cmd_len, char* p_rsp, void * pmsg);


#endif /*__BMS_H_*/


