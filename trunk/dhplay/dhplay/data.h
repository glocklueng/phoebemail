  
/********************************************************************
	created:	2005/12/09
	created:	9:12:2005   15:06
	filename: 	data.h
	file base:	data
	file ext:	h
	author:		
	
	purpose:	
*********************************************************************/

#ifndef DATA_H
#define DATA_H

#include "dhplay.h"
#include "fileoprinterface.h"
#include "decode/playgraph.h"
//�ļ���ģʽ
typedef enum
{
	FM_NOOPEN = -1,//�ļ�δ��
	FM_FILE = 0,
	FM_STREAM,	
}DATA_MODE;

//��Ƶ���ͣ���ʱֻ֧��h264���ݸ�ʽ����
enum 
{
	DH_MPEG1,
	DH_MPEG4,
	DH_H264,
	DH_MPEG2,
	DH_H263,
	DH_MJPG,
};

#define MAX_FILE_LENGTH  0xffffffff	//4*1024*1024*1024

typedef struct _INDEX_INFO_EXT
{
	DHTIME StartTime ;
	DHTIME EndTime ;
	DWORD TotalFrameNum ;
	DWORD StreamPos ;
	DWORD StreamdataType ;
}INDEX_INFO_EXT ;
/*/��Ƶͷ�ṹ
typedef struct _DH_VIDEOFILE_HDR
{
	BYTE	   CorpInfo[8];           //��˾��Ϣ(DAHUA)
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
}DH_VIDEOFILE_HDR;*/

//���ļ��Ŀ������
typedef enum _FILE_OPEN_ERROR
{
	FILE_CANNOT_OPEN, //�ļ��򲻿�
	FILE_HEADER_ERROR,//�ļ�ͷ������
	FILE_INDEX_ERROR, //���ܽ�������
	FILE_NO_ERROR     //�ļ�����ȷ�����Խ�������
}FILE_OPEN_ERROR ;

class NewStreamFileOpr ;
class OldStreamOperation ;
class ShStreamFileOpr ;
class StandardStreamFirOpr ;
class DHSTDStreamFileOpr;
////////////////////////////////////////////////////////////////////
class CDHAVData
{
	//�ļ�ģʽ������صĳ�Ա����
	HANDLE m_pFile ; //�ļ�ָ�� �����ļ���Ч
	char filename[_MAX_PATH+_MAX_FNAME] ;//�ļ���
	DWORD m_nTotalFrameNum; //������������I���P��
	DWORD m_nFileTime ;//�ļ���ʱ��
	__int64  m_pCurPos;        //��ǰ��ָ��λ��
	__int64  m_nDataLen ;      //���ݳ���
	__int64  m_EndPos ;		   //֡��λʱ��ָ��֡�Ľ���λ��	

	std::vector<DH_INDEX_INFO*> m_pFileIndex ;//�ļ�������Ϣ
	DH_VIDEOFILE_HDR m_sfile_hdr ;   //�����ļ�ͷ�����Լ�¼��ʼʱ�䡢����ʱ�䡢�ļ���ʼλ��

	IFileOperator* m_fileOpr ;
	NewStreamFileOpr* m_newstreamfileopr ;
	OldStreamOperation* m_oldstreamfileopr ;
	ShStreamFileOpr* m_shstreamfileopr ;
	StandardStreamFirOpr* m_standardfileopr ;
	DHSTDStreamFileOpr* m_dhstdstreamfileopr;
	RECT      m_MDRect ;
	DWORD m_ThreShold ;
	DWORD m_MDFrameBegin ;
	DWORD m_MDFrameEnd ;
	//��ģʽ������صĳ�Ա����
	BYTE* m_pStreamBuf ;    //�ļ�������ָ��
	DWORD m_nBufLen;        //�����������С
	DWORD m_pWrite;         //������дƫ�����2*m_nBufLen
	DWORD m_pRead;          //��������ƫ�����m_nBufLen

	//�������Գ�Ա
	DATA_MODE m_nOpenMode;  //��Ƶ��ģʽ
	STREAMDATA_TYPE m_streamtype ;//�������ͣ��������;�������LB֮�ࣩ

	HANDLE m_hCreateIndex ;

public:
	int m_port;
	BOOL m_bIsIndexCreated;
//��Ҫ��Ա�����У�	
public:
	CDHAVData();
	~CDHAVData();

	///////////�ļ������ӿ�/////////////
	FILE_OPEN_ERROR Open(LONG nPort, LPSTR strName);              //���ļ�
	BOOL     ReOpen() ;                                 //���´��ļ�����ʱֻ�������ļ���ʼλ�õĴ���
	int		     Close();                                   //�ر��ļ�
	int          CreateIndex();                             //�����ļ�����,����������ͬ
	BOOL     GetIndexInfo(BYTE *pBuffer, DWORD *pSize); //��ȡ������Ϣ
	BOOL     SetIndexInfo(BYTE *pBuffer, DWORD nSize);  //����������Ϣ	
	float       GetPos();                                   //��õ�ǰλ��
	BOOL     SetPos(float fRelativePos) ;                //�����ļ�λ��
	BOOL	GetDataPos(float fRelativePos, DWORD *pCurDataPos); //���ݲ��Űٷ�λ, ��ȡ��ǰ����ָ��λ��
	BOOL	GetRelativePos(DWORD dCurDataPos, float *pfRelativePos); //�����ļ�����ָ��λ�ã���ȡ���Űٷ�λ
	DWORD GetTotalFrames();                           //���������	
	BOOL     GetKeyFramePos(DWORD nValue, DWORD nType, PFRAME_POS pFramePos, int* KeyFrameRate = NULL);//�õ�ǰһ���ؼ�֡��I֡���������Ϣ
	BOOL     GetNextKeyFramePos(DWORD nValue, DWORD nType, PFRAME_POS pFramePos);//�õ���һ���ؼ�֡��I֡���������Ϣ
	int          GetPlayedTime(DWORD frameNum, bool ByFrameNum = true) ;          //��������ţ��õ����ŵ�ʱ��	
	DWORD GetFileTotalTime();                      //��ȡ�ļ��ܵ�ʱ�䳤��
	BOOL     IsIndexCreated() ;                       //�ļ��Ƿ�������           
	BOOL     ResetIndex() ;                           //���������Ϣ
	BOOL     SetMDRange(DWORD nValueBegin, DWORD nValueEnd, DWORD nType, RECT* MDRect) ;
	BOOL     SetMDThreShold(DWORD ThreShold) ;
	DWORD GetMDPosition(DWORD direction, DWORD nFrame, DWORD* MDValue) ;
	//���ڶ�λ����,�Ӹ�����֡��ſ�ʼ���š�������ʵ�ֵģ�����SetCurrentFrameNum���ļ�
	//ָ��m_pCurPos��Ϊ��֡ǰһ��I֡�ĵ�λ�ã���GetFrameEndPos�õ���֡�Ľ���λ�ã�
	//��SetEndPos��endPos��Ϊ��֡�Ľ���λ�ã�����ReadOneFrame��ȡm_pCurPos��endPos֮�������
	DWORD SetCurrentFrameNum(DWORD nFrameNum);       //�������������λ��	
	BOOL     SetEndPos(DWORD endPos) ;                  //����ReadOneFrame�Ľ���λ��
	int          ReadOneFrame(BYTE *pBuf) ;				 //��ȡҪ��λ��֡ǰһI֡����֡������
	__int64 GetFrameEndPos(DWORD nFrame);              //�õ�ָ��֡�Ľ���λ�ã�����������ͬ
	BOOL     ChangePos(DWORD newpos){m_pCurPos = newpos ;return TRUE ;} ;
	//////////�������ӿ�///////
	BOOL     OpenStream(BYTE *pBuf, DWORD dwSize, DWORD dwPoolSize);   //�����ӿ�
	BOOL      InputData(PBYTE pBuf,DWORD nSize);   //����������
	BOOL     CloseStream();         //�ر���
	DWORD GetBuffSize();         //�õ������С
	DWORD GetBufferRemain();     //��ȡʣ�໺���С
	BOOL     ResetRemainData();     //���ʣ������

	/////////ͨ�ýӿ�//////////
	int          Read(BYTE *pBuf, DWORD dwSize);           //��ȡ����
	DATA_MODE GetDataOpenMode(){return m_nOpenMode;}
	STREAMDATA_TYPE GetStreamDataType(){return m_streamtype ;}

	BOOL GetMediaInfo(char* pBuf, int len);
	/////////
protected:

};
#endif