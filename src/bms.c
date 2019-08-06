#include "bms.h"
#include "uart.h"
#include "error_code.h"
#include "gm_stdlib.h"
#include "command.h"
#include "log_service.h"


#define BMS_MSG_MAX_LEN 1024

GM_ERRCODE bms_uart_receive_data(char* p_cmd, u16 cmd_len, char* p_rsp, void * pmsg)
{	
	char buf[BMS_MSG_MAX_LEN] = { 0 };
	U16 index = 0;

	if ((2*cmd_len + 1) >= BMS_MSG_MAX_LEN)
	{
		return;
	}
	
	for (index = 0; index < cmd_len; ++index)
	{
		GM_snprintf(buf + 2*index, BMS_MSG_MAX_LEN - 2*index, "%02X", p_cmd[index]);
	}
	
	uart_write(GM_UART_DEBUG, (U8*)buf, GM_strlen(buf));
	uart_write(GM_UART_DEBUG, "\n", 1);

	return GM_SUCCESS;
}


GM_ERRCODE bms_msg_receive(char *p_cmd, u16 cmd_len)
{
	if (NULL == p_cmd)
	{
		return GM_PARAM_ERROR;
	}

	if ((p_cmd[0] != 0x3A || (p_cmd[1] != 0x16) || (p_cmd[cmd_len-2] != 0x0D) || (p_cmd[cmd_len-1] != 0x0A)))
	{
		return GM_PARAM_ERROR;
	}

	uart_write(GM_UART_DEBUG,"\n[SEND]:", sizeof("\n[SEND]:")-1);
	bms_uart_receive_data(p_cmd,cmd_len,NULL,NULL);
	
	uart_write(GM_UART_BMS,p_cmd, cmd_len);

	return GM_SUCCESS;
}



GM_ERRCODE bms_cmd_write(char *cmd, u8 len)
{
	u8 bms_buff[50];
	u8 idx = 0;
	u8 index = 0;
	u16 check_sum = 0;

	//LOG(INFO, "bms_cmd_write cmd = %02X", cmd);
	if (NULL == cmd)
	{
		return GM_PARAM_ERROR;
	}
	GM_memset(bms_buff, 0x00, sizeof(bms_buff));
	bms_buff[idx++] = 0x3A;
	bms_buff[idx++] = 0x16;
	bms_buff[idx++] = cmd[0];
	if (len > 1)
	{
		bms_buff[idx++] = len - 1;
		for(index=1; index<len; index++)
		{
			bms_buff[idx++] = cmd[index];
		}
	}
	else
	{
		bms_buff[idx++] = 0x01;
		bms_buff[idx++] = 0x0B;
	}
	
	
	for (index=1; index<idx; index++)
	{
		check_sum += bms_buff[index];
	}
	bms_buff[idx++] = check_sum & 0xFF;
	bms_buff[idx++] = (check_sum >> 8) & 0xFF;
	bms_buff[idx++] = 0x0D;
	bms_buff[idx++] = 0x0A;

	uart_write(GM_UART_DEBUG,"\n[SEND]:", sizeof("\n[SEND]:")-1);
	bms_uart_receive_data(bms_buff,idx,NULL,NULL);
	
	uart_write(GM_UART_BMS,bms_buff, idx);

	return GM_SUCCESS;
}



GM_ERRCODE bms_create(void)
{
    uart_open_port(GM_UART_BMS, BAUD_RATE_LOW, 0);
    
    return GM_SUCCESS;
}


GM_ERRCODE bms_destroy(void)
{
    uart_close_port(GM_UART_BMS);
    
    return GM_SUCCESS;
}


