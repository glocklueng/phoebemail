#include "ZKit_CommandReceiver.h"

BEGIN_ZKIT

void CommandReceiver::OnData( const char* data, size_t length )
{
	m_bytes.insert(m_bytes.end(), data, data + length);
	ExtractCommand();
}

bool CommandReceiver::IsAckReceived( uint32 sessionId ) const
{
	LOCK(m_acksMutex);
	return m_acks.empty()? false : m_acks.find(sessionId) != m_acks.end();
}

ZKit::Command CommandReceiver::ConfirmAck( uint32 sessionId )
{
	LOCK(m_acksMutex);
	Command ack = m_acks[sessionId];
	m_acks.erase(sessionId);
	return ack;
}

void CommandReceiver::ExtractCommand()
{
	Command cmd;
	if (cmd.Deserialize(m_bytes))
	{
		assert(cmd.GetSessionId() > 0);//�����߿���������дsessionId, �������
		DispatchCommand(cmd);//�յ�һ��������, ֪ͨ�۲�����.
		m_bytes.erase(m_bytes.begin(), m_bytes.begin() + cmd.GetTotalLength());
		ExtractCommand();//�ݹ����, �ٴγ�����ȡ����.
	}
}

void CommandReceiver::DispatchCommand( const Command& cmd )
{
	if (cmd.IsAck())//ack
	{
		//�����б�, ���ȴ���Ӧ��ʹ���߲�ѯ��ȷ��.
		{
			LOCK(m_acksMutex);
			m_acks[cmd.GetSessionId()] = cmd;
		}	
		OnAck(cmd);	
	}
	else
	{
		OnReq(cmd);
	}

	OnCmd(cmd);
}
END_ZKIT