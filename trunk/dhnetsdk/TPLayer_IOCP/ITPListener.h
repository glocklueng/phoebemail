/*
* Copyright (c) 2008, �㽭���ܼ����ɷ����޹�˾
* All rights reserved.
*
* �ļ����ƣ�ITPListener.h
* ժ����Ҫ�������������ӿ�
*
* ȡ���汾��0.1
* ԭ���ߡ���Peng Dongfeng
* ������ڣ�2008��6��16��
* �޶���¼������
*/
//////////////////////////////////////////////////////////////////////

#ifndef _ITPLISTENER_H_
#define _ITPLISTENER_H_

class ITPListener
{
public:
	//	���յ����ݺ����������ԣ��ú����Ĵ���ʱ���Ӱ���������
	virtual int onData(int nEngineId, int nConnId, unsigned char* data, int nLen) = 0;

	//	����������(��������)������ֵ��0��æ��1������
	virtual int	onDealData(int nEngineId, int nConnId, unsigned char* buffer, int nLen) = 0;

	//	������ɻص�����������ɾ���ϲ�ķ��Ͷ���
	virtual int onSendDataAck(int nEngineId, int nConnId, int nId) = 0;

    //	����ֵΪ0��ʾ���ܴ����ӣ�����ֵΪ1��ʾ�ܾ�����
	virtual int onConnect(int nEngineId, int nConnId, char* szIp, int nPort) = 0;

	//	��Ϊ��������Żص�����ʾ�ͻ������ӶϿ�
	virtual int onClose(int nEngineId, int nConnId) = 0;

	//	��Ϊ�ͻ�����Żص�����ʾ���ӶϿ�
	virtual int onDisconnect(int nEngineId, int nConnId) = 0;

	//	��Ϊ�ͻ�����Żص�����ʾ����������
	virtual int onReconnect(int nEngineId, int nConnId) = 0;


};
#endif	//_ITPLISTENER_H_