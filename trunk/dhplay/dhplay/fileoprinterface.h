#ifndef _DH_FILEOPR_INTERFACE
#define _DH_FILEOPR_INTERFACE

#include <vector>
#include <time.h>
#define interface struct 

typedef struct _DHTIME								
{
	DWORD second		:6;					//	��	1-60		
	DWORD minute		:6;					//	��	1-60		
	DWORD hour			:5;					//	ʱ	1-24		
	DWORD day			:5;					//	��	1-31		
	DWORD month			:4;					//	��	1-12		
	DWORD year			:6;					//	��	2000-2063	
}DHTIME,*pDHTIME;

//��Ƶͷ�ṹ
typedef struct _DH_VIDEOFILE_HDR
{
	BYTE	  CorpInfo[8];           //��˾��Ϣ(DAHUA)
	WORD      VerMajor;              //���汾
	WORD      VerMinor;              //���汾
	DWORD     ProductType;			 //��Ʒ����
	struct{
		BYTE   ProductMajor;         //��Ʒ���汾
		BYTE   ProductMinor;         //��Ʒ���汾
		WORD   ProductPatch;         //�����汾
	}ProductVersion;                //��Ʒ�汾��Ϣ
	DWORD     AudioType;            //��Ƶ����(PCM /ADPCM)
	WORD      AudioChannel;         //��Ƶ������
	WORD      AudioBitPerSample;    //��Ƶ����λ��
	DWORD     AudioSamplesPerSec;   //��Ƶ������
	DWORD     VideoType;            //��Ƶ����(MPEG1/MPEG4/H.264)
	WORD      VideoWidth;           //��Ƶ���
	WORD      VideoHigh;            //��Ƶ�߶�
	WORD      VideoMode;            //��ʽ(NTSC / PAL)
	WORD      Framerate;            //֡��
	DHTIME    DirStartTime;		 	 //��ʼʱ��
	DHTIME    DirEndTime;			 //����ʱ��
	DWORD     StreamPos;            //ָʾ�����ݣ�����Ƶ����ʼλ��
	BYTE      Reserved[64];         //�����ռ䡣
	DWORD     ExtendID;              //��ʾ��չ�����͵����ַ���(�磺CARD��IDX��LIST)
	DWORD     ExtendSize;           //��չ���ݿ�ĳ���
}DH_VIDEOFILE_HDR;

//������Ϣ�ṹ�������Բ�ͬ�ķ�ʽ��λ
typedef struct _INDEX_INFO{
	DWORD  IFramePos;    //I��λ��ƫ��
	DWORD  framelen ;    //I֡�����ݳ��ȣ�����֡ͷ����GetNextKeyFramePos�������������
	DWORD  IFrameNum;    //I�������
	DWORD  IFrameRate ; //I֡֡�ʣ����Թ���P֡ʱ��
	DHTIME time;        //I�����ݵ�ʱ��
	
}DH_INDEX_INFO;


static __int64 myFileSeek (HANDLE hf, __int64 distance, DWORD MoveMethod)
{
   LARGE_INTEGER li;

   li.QuadPart = distance;

   li.LowPart = SetFilePointer (hf, li.LowPart, &li.HighPart, MoveMethod);

//   if (li.LowPart == INVALID_SET_FILE_POINTER && GetLastError() != NO_ERROR)
//   {
//      li.QuadPart = -1;
//   }

   return li.QuadPart;
}

static DWORD GetTimeInterVal(DHTIME dhETime, DHTIME dhSTime)
{
	tm stime, etime ;
	//���ڴ��������ʱ�����׼ʱ��ṹ����������Ҫ����ת��
	stime.tm_mday    = dhSTime.day ;
	stime.tm_mon     = dhSTime.month - 1;
	stime.tm_year    = dhSTime.year + 100 ;
	stime.tm_sec     = dhSTime.second - 1;
	stime.tm_min     = dhSTime.minute - 1;
	stime.tm_hour    = dhSTime.hour - 1  ;
	stime.tm_isdst   = -1;////�Զ������Ƿ�Ϊ��ʱ��, (bug: ʱ��ѡΪ�������Զ�ʹ����ʱ��ʱ��ʱ���������)

	etime.tm_mday    = dhETime.day ;
	etime.tm_mon     = dhETime.month - 1;
	etime.tm_year    = dhETime.year + 100;
	etime.tm_sec     = dhETime.second - 1;
	etime.tm_min     = dhETime.minute - 1;
	etime.tm_hour    = dhETime.hour - 1  ;
	etime.tm_isdst   = -1;//�Զ������Ƿ�Ϊ��ʱ��, (bug: ʱ��ѡΪ�������Զ�ʹ����ʱ��ʱ��ʱ���������)

	stime.tm_year = (stime.tm_year >= 138)? 137 : stime.tm_year;
	etime.tm_year = (etime.tm_year >= 138)? 137 : etime.tm_year;

	time_t start_time, end_time ;
	start_time = mktime(&stime) ;
	end_time   = mktime(&etime) ;

	return ((end_time - start_time) > 0) ? (end_time - start_time) : 0  ;
}

interface IFileOperator
{
	virtual  int   CreateIndex(char* fileName, DWORD beginpos,std::vector<DH_INDEX_INFO*>& m_pFileIndex, 
		DWORD& m_totalFrameNum, DHTIME& begintime, DHTIME& endtime, __int64& nDataLen) = 0 ;//������������������Ϣ����m_pFileIndex��

	virtual  __int64 GetFrameEndPos(HANDLE m_pFile, DWORD KeyFrameNum, 
		__int64 KeyFramePos, DWORD nFrame) = 0;              //�õ�ָ��֡�Ľ���λ��	

	virtual	 void   EndCreateIndex(){m_bCreateIndex = 0 ;}

	virtual void GetFileInfo(HANDLE m_pFile, DWORD& dwFrame, DH_VIDEOFILE_HDR& _video_info) = 0;

	IFileOperator(){ m_bCreateIndex = 1 ;}

	int m_bCreateIndex ;
};


#endif