#ifndef _ZKit_Logger_h_
#define _ZKit_Logger_h_

#include "ZKit_Mutex.h"
#include "ZKit_Singleton.h"

BEGIN_ZKIT

//////////////////////////////////////////////////////////////////////////
enum LogLevel
{
	LogLevel_All,
	LogLevel_Debug,
	LogLevel_Info,
	LogLevel_Warn,
	LogLevel_Error,
	LogLevel_Fatal,
	LogLevel_Off
};

extern char* strLogLevel[];

class Logger : public Singleton<Logger>
{
	friend class Singleton<Logger>;
public:

	void SetLevel(LogLevel minLevel)
	{
		m_minLevel = minLevel;
	};

	LogLevel GetMinLevel() const
	{
		return m_minLevel;
	};

	void SetLogInfo(LogLevel level, char* file, int line)
	{
		m_mutex.Lock();
		m_level = level;
		m_file  = file;
		m_line  = line;
	}

	virtual void WriteLog(const char* format, ...);

private:

	Logger() : m_minLevel(LogLevel_All)
	{

	}

	LogLevel  m_minLevel;//��־���𿪹�, ��ʾ���ڴ˼������־��������¼
	ZKit::Mutex     m_mutex;

	//��ʱ��Ϣ
	char*    m_file;
	int      m_line;
	LogLevel m_level;
};

//////////////////////////////////////////////////////////////////////////
//��־��, ֧���ַ�����ʽ��, �ҳ�����־������, ������Ϣ���Զ�����, �����ļ�, �к�, ����, ʱ��
//by qguo. 2010.04.30
//////////////////////////////////////////////////////////////////////////
#define LOG_SET_LEVEL(level) Logger::instance()->SetLevel(level)
#define LOG_GET_LEVEL        Logger::instance()->GetMinLevel()
#define LOG_RELEASE          Logger::unInstance();

#define LOG_DEBUG Logger::instance()->SetLogInfo(LogLevel_Debug, __FILE__, __LINE__); Logger::instance()->WriteLog
#define LOG_INFO  Logger::instance()->SetLogInfo(LogLevel_Info,  __FILE__, __LINE__); Logger::instance()->WriteLog
#define LOG_WARN  Logger::instance()->SetLogInfo(LogLevel_Warn,  __FILE__, __LINE__); Logger::instance()->WriteLog
#define LOG_ERROR Logger::instance()->SetLogInfo(LogLevel_Error, __FILE__, __LINE__); Logger::instance()->WriteLog
#define LOG_FATAL Logger::instance()->SetLogInfo(LogLevel_Fatal, __FILE__, __LINE__); Logger::instance()->WriteLog

END_ZKIT
#endif // _ZKit_Logger_h_