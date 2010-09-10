#ifndef _ZKit_CnpDefs_h_
#define _ZKit_CnpDefs_h_

#include "ZKit_Config.h"
BEGIN_ZKIT

//////////////////////////////////////////////////////////////////////////

//0    1   |2    3   |4    5   |6    7    8    9   |10   11   12   13  |14   15   ........ 31
//----|----|----|----|----|----|----|----|----|----|----|----|----|----|----|----|........|----|
//0x55|0xAA| cmdType | cmdId   |    argsLength     |   sessionId       | 0    0   ........  0
//----|----|----|----|----|----|----|----|----|----|----|----|----|----|----|----|........|----|

//Э������ͷ�ĳ���
#define CMD_LEN_HEADER 32

//�����־λ, 0x55AA, Ϊ�����ֽ�������, �����������ֽڱ�ʾ
#define CMD_FLAG_BYTE0 0x55
#define CMD_FLAG_BYTE1 0xAA

//�����и��ֶεĳ���
#define CMD_LEN_FLAG 2
#define CMD_LEN_TYPE 2
#define CMD_LEN_ID   2
#define CMD_LEN_ARGSLEN   4
#define CMD_LEN_SESSIONID 4
#define CMD_LEN_RESERVED 18

//�����и��ֶε���ʼ����
#define CMD_IDX_FLAG 0
#define CMD_IDX_TYPE 2
#define CMD_IDX_ID   4
#define CMD_IDX_ARGSLEN    6
#define CMD_IDX_SESSIONID 10
#define CMD_IDX_RESERVED  14

//|0    1   |2    3    4    5   |6    .... n-1    
//|----|----|----|----|----|----|----|....|----|
//|  type   |       length      | value...     | 
//|----|----|----|----|----|----|----|....|----|
//                              |0   |....|length-1
#define TLV_LEN_TYPE   2
#define TLV_LEN_LENGTH 4

#define TLV_IDX_TYPE   0
#define TLV_IDX_LENGTH 2
#define TLV_IDX_VALUE  6

//////////////////////////////////////////////////////////////////////////
//Ӧ��ID��ʼֵ
#define CMD_ACK_BASE 0x8000
//����������ID���ɶ�Ӧ��Ӧ��ID
#define BUILD_ACK(cmd) (cmd | CMD_ACK_BASE)
//�ж�һ������ID�Ƿ���Ӧ��
#define IS_ACK(cmd) (cmd >= CMD_ACK_BASE)

END_ZKIT
#endif // _ZKit_CnpDefs_h_