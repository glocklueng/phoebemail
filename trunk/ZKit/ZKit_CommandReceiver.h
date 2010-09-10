#ifndef _ZKit_CommandReceiver_h_
#define _ZKit_CommandReceiver_h_

#include "ZKit_Command.h"

BEGIN_ZKIT
//�������������, ������ȡ����
//��Ҫ��������������Ӧ�ü̳д���, ��ѡ���Եĸ������鷽��.
class CommandReceiver
{
public:
	//�ж�ĳ�������Ƿ��Ѿ��յ�Ӧ��
	bool IsAckReceived( uint32 sessionId ) const;

	Command ConfirmAck( uint32 sessionId );

protected:
	//�������ݵ����
	void OnData(const char* data, size_t length);

private:
	void ExtractCommand();

	void DispatchCommand(const Command& cmd);

	//�������า�ǵĹ��Ӻ���.
	virtual void OnCmd(const Command& cmd)
	{	

	}

	virtual void OnReq(const Command& cmd)
	{	

	}

	virtual void OnAck(const Command& cmd)
	{

	}

private:
	std::vector<char> m_bytes;//���ڴ洢����Ļ���.
	mutable std::map<uint32, Command> m_acks;//�յ���Ӧ��.
	ZKit::Mutex m_acksMutex;
};

END_ZKIT
#endif // _ZKit_CommandReceiver_h_
