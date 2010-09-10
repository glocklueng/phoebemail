#ifndef PLAYGRAPH_H
#define PLAYGRAPH_H

#include "decode.h"
#include "interface.h"
#include "videorender.h"
#include "FifoBuffer.h"
#include "h264videodecode.h"
#include "../depend/DllDeinterlace.h"
//#include "hisih264videodecode.h"
#include "mp4decoder.h"
#include "DhStreamParser/DhStreamParser.h"
#include "audiodecode.h"
//#include "analyse.h"
#include <time.h>
#include <vfw.h>

typedef struct _SHELTERINFO
{
	int SX;
	int SY;
	int W;
	int H;
	BYTE Y;
	BYTE U;
	BYTE V;
	BOOL bEn;
}SHELTERINFO;


typedef struct
{
	int m_decID ;
	PAVIFILE m_hAVIFile;
	PAVISTREAM m_hVideoStream;
	PAVISTREAM m_hAudioStream;
	unsigned int m_aviVideoWritePos;
	unsigned int m_aviAudioWritePos;

	bool m_foundIFrame;
	
	AVISTREAMINFO strhdr;

	XVID_ENC_PARAM enc_param;
	XVID_ENC_FRAME enc_frame;
	XVID_ENC_STATS enc_stats;

	unsigned char * m_encBuffer;
}AVICONVERTINFO;

//���ܷ���֡
typedef struct 
{
	DWORD x;
	DWORD y;
}POSITION_;

typedef struct
{
	char alerttime[100];
	char entrytime[100];
	DWORD event;
	POSITION_ position;
	DWORD width;
	DWORD height;
	DWORD direction;
	DWORD speed;
}IVALERT;

typedef struct 
{
	POSITION_ p0;
	POSITION_ p1;
	DWORD direction;
	BOOL bEnable;
}TRIP;

typedef enum
{
	ENUM_FILE_CHANGE = 0,  //�ֱ��ʷ����ı�
	ENUM_FILE_RATE,
	ENUM_FILE_ENC,
	ENUM_FILE_RATE_AND_FIX,
}FILE_CHANGE_ENUM;

#define MAX_TRIP_NUM 20
#define MAX_IVALERT_NUM 10

typedef	int (*MP4_Xvid_Encore)(void *handle, int opt, void *param1, void *param2);
//! ���������
class DhPlayGraph
{
public:
	//! ���캯��
    DhPlayGraph();

	// ��������
    virtual ~DhPlayGraph();

	//! ��ʼ��������ͼ
    int init(DecodeOption *info); 
	
	//! ��������
    int start();

	//! ��ͣ����ص�
    int pause();

	//! ֹͣ����
	int stop();

	//! �����뻺����
    int parseData(unsigned char *data, unsigned int len);

	//! ����ִ��
    int stepGo();

	//! ������ʾ֡��
    int changeRate(int rate);
	
	//���֡��
	int getRate();

	int getFileRate();
	//�õ�ָ��֡����
	BYTE* GetLocateFrameData(int* width, int* height) ;

	//! ����
	void reset(int level);
	
	//�õ��ѽ���֡��
	int GetImgCount(int* imgcount) ;

	//���ö�λ���
	void SetIfFrameUsed(BOOL IfUsed) ;

	//�Ƿ������Ƶ
	void SetDecVideo(BOOL IfDecVideo) ;
	
	//�Ƿ������Ƶ
	void SetDecAudio(BOOL IfDecAudio) ;

	time_t GetCurTimeEx() ;

	void AdjustFluency(int bufnum, int adjustrange);

	unsigned char* GetLastFrame();

	bool FixRate(int rate);
	
	void GetTimeStr(char* pBuf);

	void SetWaterMarkCallback(void *pvCallback, long userData);

	void SetPandoraWaterMarkCallback(void *pvCallback, long userData);

	void ConvToAVI(unsigned char* pAVIFileName);

	void SetAVIConvSize(long lWidth, long lHeight);
	
	void StopAVIConv();

	void RealStop();

	void SetBeginTime(DWORD timeBegin){m_BeginTime = timeBegin;}

	void NotifyRendering();

	DWORD GetHandledDataLen();
	void  SetHandledDataLen(DWORD dCurDataPos);

	inline void SetStepGoStatus(BOOL bStatus) { m_IfStepGo = bStatus ;}

	BOOL WaterMarkVerify(DH_FRAME_INFO* fFrameInfo);

	BOOL GetMediaInfo(char* pBuf, int len);

	void SetIVSCallback(void *pIVSFunc, long nUserData);

	double GetFrameBitRate(void) { return m_video_render.GetRealFrameBitRate(); }

private:
	unsigned char*  m_yuvBuf ;//�ݴ��������
	unsigned char*	m_preBuffer;
	unsigned char*  m_audioBuf;//��Ƶ����AUDIOBUFLEN
	unsigned char*	m_lastYUVBuf;

	int m_width ;//ͼ���
	int m_height ;//ͼ���

	DhAVFrame* m_item ;
	unsigned int m_encode_type ;//��������,h264��MP4��PCM
	DH_FRAME_INFO* m_frameinfo ;

	DhVideoRender   m_video_render ;//��Ƶ���ݶ�ʱ�ص�

	//������
	IDecode* m_Decoder ;
    //HisiH264VideoDecoder* m_hisih264videoDecoder ;//��˼h264������	
	H264VideoDecoder* m_h264videoDecoder ;//H264����
	Mpeg4Decoder * m_hMp4Decoder ;//MPEG����
	DhAudioDecoder* m_audioDecoder;//��Ƶ����

	//��������
	DhStreamParser* m_streamParser ;

	dec_callback m_callback;//�ص�ָ��

	int m_port ;//ͨ����
	unsigned int m_filerate ;//�ļ��е�֡��
//	unsigned int m_tmpfilerate;
	int m_userrate ;//�û��趨���ٶȼ��𣬿��һ����Ŷ�����������һ�����Ŷ�������
	int m_transMode ;
	int m_deinterlace ;
	int m_h264flag ;//0 ��264   1 ��׼264

	//���Ʊ���
	BOOL m_IfDecOnly ;//ֻ���룬��ͨ����ʱ��
	BOOL m_IfDecPause ;
	BOOL m_IfStepGo ;
	BOOL m_IfUsed ;//����֡��λʱ������ָ��֡ǰ���֡
	BOOL m_IfPauseData ;
	BOOL m_IfFindIFrame ;
	BOOL m_IfFindFirstIFrame ;
	BOOL m_IfFindAFrame;
	BOOL m_IfDecVideo ;
	BOOL m_IfDecAudio ;
	BOOL m_IfFirstFrame;
	time_t m_FirstIFrameTime ;
	time_t m_curtime ;
	time_t m_preIFrameTime;
	time_t m_BeginTime;
	int m_PframeNum ;
	DWORD m_dwFrameNum;
	BOOL  m_bFrameNumScan;

	int m_adjust_range;
	int m_adjust_bufnum;

	int m_fixrate;
	DH_FRAME_INFO m_demuxinfo;

	__int64 m_iHandledDataLen;

	// for ��Ƶ���ݵ���
	struct OSDData {
		unsigned char data[64*32];
		int en;
		int num;
		int x,y;
	} m_osdInfo,m_chnInfo;

	SHELTERINFO m_shelterinfo;
	
	int m_flagcount;

	BOOL m_bWaterMarkExist;

	watermark_callback m_wmPandoraCallback; //֡����ˮӡ��Ϣ�ص�
	long m_pandorawatermark_user;

	watermark_callback m_wmCallback; //ˮӡ��Ϣ�ص�
	WATERMARK_INFO m_Watermark_info;	//��Ҫ���ˮӡ��Ϣ�����ݽṹ
	long m_watermark_user;
	void *m_hDeinterlace;
	DEINTERLACE_PARA_S  m_struPara;  

	AVICONVERTINFO m_aviinfo;
	static MP4_Xvid_Init m_Fun_MP4_Init;
	static MP4_Xvid_Encore m_Fun_Mp4_Encore;

	IVALERT m_Ivalert[MAX_IVALERT_NUM];
	TRIP m_Trip[MAX_TRIP_NUM];

	enum{AVI_IDL, AVI_RUN, AVI_STOP};
	int  m_status;

	int m_tempLen;
	int m_bufLen;

	BOOL m_bYUV2AVIEnable;
	long m_lAVIDesWidth;
	long m_lAVIDesHeight;
	BYTE* m_pYUVResizeBuf;

	int m_ivsObjNum;
	unsigned long m_ivsSeq;
	DH_IVS_OBJ* m_IvsObjList;

	BYTE* m_pPresetPosInfo;
	long  m_lPresetPosInfoSize;

	IVS_callback m_IVSCallback; //����IVS�ص�
	long m_IVS_user;

//avi�����ı��ļ����Ʊ���
	char m_aviFileName[MAX_PATH];  //the first file name;
	unsigned int  m_fileEncChangeCount;     //�����ʽ�仯����
	unsigned int  m_fileRateChangeCount;    //֡�ʱ仯���
	unsigned int  m_fileChangeCount;        //�ֱ��ʷ����ı�

private:
	int decode(DH_FRAME_INFO* frameinfo);
	unsigned char* Deinterlace(unsigned char* data);
	int AdjustRateInter();
	int DemuxCallback(DH_FRAME_INFO* frameinfo);
	inline void swapimg(unsigned char *src, unsigned char *dst, int width, int height);
	void ConvertToAVI(unsigned char * pBuf, long nSize, DH_FRAME_INFO* frameinfo);
	void ConvertToAVIEx(unsigned char * pBuf, long nSize, DH_FRAME_INFO* pFrameInfo);
	void StopAVIConvReal();
	void StopAVIConvRealImp();           //�ڲ�����stop avi�Ľӿڣ���ζ���ļ���ʽ�����ı䣬�ļ�������Ҫ����Ӻ�׺
	int ParseIvsInfo(char* pBuf, int len);
	int ParseIVSPresetPosInfo(BYTE* pDataBuf, long lDataLen);
	int GetAviFileName( char* pAviFileName,FILE_CHANGE_ENUM nType);
	void ChangeNewAviFile(FILE_CHANGE_ENUM nType);
};

#endif /* PLAYGRAPH_H */





















