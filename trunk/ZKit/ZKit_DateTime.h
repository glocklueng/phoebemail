#ifndef _ZKit_DateTime_h_
#define _ZKit_DateTime_h_

#include "ZKit_Config.h"

BEGIN_ZKIT

class DateTime
{
public:    
	DateTime(time_t seconds);
	DateTime(int year,int month,int day);
	DateTime(int year,int month,int day,int hour,int minute,int second);

	DateTime(std::string strDateTime);
	DateTime(std::string strDateTime, std::string format);

	static DateTime Parse(std::string strDateTime);//yyyy/MM/dd HH:mm:ss

	static DateTime Parse(std::string strDateTime,std::string format);

	static DateTime GetNow(); //���ص�ǰ�����Ǽ�

public:
	void AddSeconds(const int seconds); //��ָ���������ӵ���ʵ����ֵ�ϡ�
	void AddMinutes(const int minutes);//��ָ���ķ������ӵ���ʵ����ֵ�ϡ� 
	void AddHours(const int hours);//��ָ����Сʱ���ӵ���ʵ����ֵ�ϡ� 
	void AddDays(const int days); //��ָ���������ӵ���ʵ����ֵ�ϡ� 
	void AddWeeks(const int weeks);//��ָ���������ӵ�Щʵ�ϵ�ֵ�ϡ�
	void AddMonths(const int Months);//��ָ�����·����ӵ���ʵ����ֵ�ϡ�  
	void AddYears(const int years); //��ָ����������ӵ���ʵ����ֵ�ϡ�  
	
public:
	static int Compare(const DateTime *value1,const DateTime *value2);
	int CompareTo(const DateTime *value) const;    

	bool Equals(const DateTime* dateTime) const;
	static bool Equals(const DateTime *value1,const DateTime *value2);
 
	std::string ToString() const;
	std::string ToString(const std::string format) const;//format = "%Y-%m-%d %H:%M:%S" %Y=�� %m=�� %d=�� %H=ʱ %M=�� %S=��
	std::string ToShortDateString() const;//����ǰ DateTime �����ֵת��Ϊ���Ч�Ķ������ַ�����ʾ��ʽ�� 

public:        
	int GetYear() const;//��ȡ��ʵ������ʾ���ڵ���ݲ��֡�
	int GetMonth() const;//��ȡ��ʵ������ʾ���ڵ���ݲ��֡�
	int GetDay() const;// ��ȡ��ʵ������ʾ������Ϊ�����еĵڼ��졣
	int GetHour() const;//��ȡ��ʵ������ʾ���ڵ�Сʱ���֡� 
	int GetMinute() const;//��ȡ��ʵ������ʾ���ڵķ��Ӳ���
	int GetSecond() const;//��ȡ��ʵ������ʾ���ڵ��벿�֡� 
	int DayOfWeek() const; //��ȡ��ʵ������ʾ�����������ڼ���
	int DayOfYear() const;//��¼������һ������ĵڼ���,��1��1����,0-365

	static int DaysInMonth(const int year,const int months);//����ָ��������е�������
public:
	bool operator == (DateTime &dateTime);
	bool operator > (DateTime &dateTime);
	bool operator < (DateTime &DateTime);
	bool operator >= (DateTime &DateTime);
	bool operator <= (DateTime &DateTime);
	bool operator != (DateTime &DateTime);

private:
	void Init(time_t seconds);

	void Init(int year,int month,int day,int hour,int minute,int second);

	void Init(std::string strDateTime, std::string format);

	time_t seconds;//��1970�������
	tm date;
};
END_ZKIT

#endif // _ZKit_DateTime_h_
