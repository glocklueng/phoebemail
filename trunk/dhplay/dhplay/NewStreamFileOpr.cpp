// NewStreamFileOpr.cpp: implementation of the NewStreamFileOpr class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "NewStreamFileOpr.h"
#include <time.h>
//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

NewStreamFileOpr::NewStreamFileOpr()
{

}

NewStreamFileOpr::~NewStreamFileOpr()
{

}

int   NewStreamFileOpr::CreateIndex(char* filename, DWORD beginpos, std::vector<DH_INDEX_INFO*>& m_pFileIndex
	, DWORD& m_nTotalFrameNum, DHTIME& m_begintime, DHTIME& m_endtime,__int64& m_nDataLen) 
{
	DWORD len = 0;
	BYTE mData[16];   //���ڶ�ȡ��ͷ���ݽṹ
	BYTE hFrame[4] = {00,00,01,0xF1};  //����֡��ͷ��־
	HANDLE f_CreateIndex = NULL;

	f_CreateIndex = CreateFile(filename, GENERIC_READ,FILE_SHARE_READ,NULL,OPEN_EXISTING,0,NULL) ;
	
	if (f_CreateIndex == NULL || (DWORD)f_CreateIndex == 0xffffffff)
	{
		return 1 ;
	}

	__int64 temp_pCurPos ;

	temp_pCurPos = beginpos ;	

	int tmp_TotalFrameNum = 0 ;
	
 	while(true)
	{
		if (m_bCreateIndex == 0)
		{
			CloseHandle(f_CreateIndex) ;
			f_CreateIndex = NULL ;
			return 1 ;
		}

		if ((m_nDataLen - temp_pCurPos) < 16 || temp_pCurPos >= m_nDataLen)
		{
			//�ļ�����
			if (m_nDataLen - temp_pCurPos < 16)
			{
				m_nDataLen = temp_pCurPos ;
			}
L:
			if (m_pFileIndex.size() <= 0)
			{
				//�ļ���С��û��I֡
				CloseHandle(f_CreateIndex) ;
				f_CreateIndex = NULL ;
				return 1 ;
			}
			//������һ��I֡��ʱ��
			DHTIME dhtime  ;
			memcpy(&dhtime,&(m_pFileIndex[m_pFileIndex.size()-1]->time),sizeof(DHTIME)) ;
		
			//�ļ�����ʱ�䲻��ȷ�������ļ�����ʱ��Ϊ���һ��I֡��ʱ�� 
			//���� (��֡��-���I֡֡���)/֡�ʣ��Ա�׼ʱ�亯�����д���
			tm* endtime = new tm ;
			//���ڴ��������ʱ�����׼ʱ��ṹ����������Ҫ����ת��
			endtime->tm_hour = dhtime.hour - 1 ;
			endtime->tm_min  = dhtime.minute - 1 ;
			endtime->tm_sec  = dhtime.second - 1 ;
			endtime->tm_mday = dhtime.day ;
			endtime->tm_mon  = dhtime.month - 1 ;
			endtime->tm_year = dhtime.year + 100 ;
			endtime->tm_isdst= -1; ////�Զ������Ƿ�Ϊ��ʱ��, (bug: ʱ��ѡΪ�������Զ�ʹ����ʱ��ʱ��ʱ���������)
			time_t etime = mktime(endtime) ;
			int filerate = m_pFileIndex[m_pFileIndex.size()-1]->IFrameRate ;
			if (filerate <= 0)
			{
				CloseHandle(f_CreateIndex) ;
				f_CreateIndex = NULL ;
				return 1 ;
			}
			
			etime += (tmp_TotalFrameNum - m_pFileIndex[m_pFileIndex.size()-1]->IFrameNum - 1)/filerate  ;
			delete endtime ;
			endtime = localtime(&etime) ;
			if (endtime == 0) //bug: localtime����ʧ��
			{
				CloseHandle(f_CreateIndex) ;
				f_CreateIndex = NULL ;
				return 1 ;
			}
			dhtime.hour = endtime->tm_hour + 1 ;
			dhtime.minute= endtime->tm_min + 1 ;
			dhtime.second = endtime->tm_sec + 1 ;
			dhtime.day   = endtime->tm_mday ;
			dhtime.month = endtime->tm_mon + 1 ;
			dhtime.year = endtime->tm_year - 100 ;
		
			//������������ɹ������ļ���ʼʱ����Ϊ��һ��I֡��ʱ��,����ʱ��Ϊ���һI֡ʱ���һ����ֵ
			*(DWORD*)&m_begintime = *(DWORD*)&(m_pFileIndex[0]->time) ;
			*(DWORD *)&m_endtime 	= *(DWORD *)&dhtime;	

			//�ļ����� ������һ�������I֡�����ļ��ܳ�����Ϊ��I֡��λ�ã��Է�����������
			DH_INDEX_INFO* m_index = new DH_INDEX_INFO ;
			*(DWORD *)&m_index->time = *(DWORD *)&m_endtime;  				 
			m_index->IFramePos = m_nDataLen ;
			m_index->IFrameNum = tmp_TotalFrameNum  ;
			m_index->framelen  = 0 ;
			m_pFileIndex.push_back(m_index) ;
			 
			m_nTotalFrameNum = tmp_TotalFrameNum;	

			CloseHandle(f_CreateIndex) ;
			f_CreateIndex = NULL ;

			return 0 ;
		}
	
		if (myFileSeek (f_CreateIndex, temp_pCurPos, FILE_BEGIN)	== -1)
		{	
			CloseHandle(f_CreateIndex) ;
			f_CreateIndex = NULL ;
			return 1 ;
		}

		if (ReadFile(f_CreateIndex, mData, 16, &len, NULL) == FALSE)
		{
			CloseHandle(f_CreateIndex) ;
			f_CreateIndex = NULL ;
			return 1 ;
		}
		
		if (memcmp(mData, hFrame , 3))   //����ͷ
		{
			if (m_nDataLen - temp_pCurPos < 1024)//�������1K����Ч����
			{
		 		m_nDataLen = temp_pCurPos ;
				goto L ;
			}
			temp_pCurPos++;
			continue;
// 			CloseHandle(f_CreateIndex) ;
// 			f_CreateIndex = NULL ;
// 			return 1;   //���´������ʾ�ļ�������
		}
		
		if((mData[3] == 0xfd)||(mData[3] == 0xfb)) //I��		
		{
			DH_INDEX_INFO* m_index = new DH_INDEX_INFO ;
			memset(m_index, 0, sizeof(DH_INDEX_INFO));

			*(DWORD *)&m_index->time = *(DWORD *)&mData[8];   //9~12�ֽڱ�ʾʱ��
			m_index->IFramePos = temp_pCurPos;
			m_index->IFrameNum = tmp_TotalFrameNum ;			
			m_index->framelen = 16 + (*(DWORD *)&mData[12])&0x00FFFFFF;  //֡������ֽڱ�ռ��
			m_index->IFrameRate = mData[5]&0x1F ;
			
			if (m_index->framelen > 500*1024 || m_index->framelen < 5)
			{
				temp_pCurPos += 1;
				
				if (m_index != NULL)
				{
					delete m_index;
					m_index = NULL;
				}

				continue;
			}
	
			if (m_nDataLen - temp_pCurPos >= m_index->framelen)
			{
				m_pFileIndex.push_back(m_index);

				temp_pCurPos += m_index->framelen;
				tmp_TotalFrameNum++;
				continue;
			}
			else
			{
				if (m_index != NULL)
				{
					delete m_index;
					m_index = NULL;
				}
			}

			temp_pCurPos++;
		}
		else if((mData[3] == 0xfc)||(mData[3] == 0xfa))//p��/b֡
		{	
			int len = 8 + (*(DWORD *)&mData[4])&0x00FFFFFF;    //5~8�ֽڱ�ʾ���ݴ�С
			if (len > 500*1024 || len < 5)
			{
				temp_pCurPos += 1;
				continue;
			}
			
			if (m_pFileIndex.size() != 0)  // ����ļ���P֡��ʼ�������ЩP֡�Թ�����ЩP֡���ܽ��룬����Ϊ��Ч����
			{
				if(m_nDataLen - temp_pCurPos >= len)
				{
					tmp_TotalFrameNum++;
					temp_pCurPos += len;
					continue;
				}
			}

			temp_pCurPos++;
		}
		else if(mData[3] == 0xf0)//��Ƶ��
		{
			int len = 8 + *(WORD *)&mData[6];    //7~8�ֽڱ�ʾ���ݴ�С
			if (len > 500*1024 || len < 5)
			{
				temp_pCurPos += 1;
				continue;
			}
			temp_pCurPos += len;
		}
		else if(mData[3] == 0xf1)//����֡
		{
			int len  = 16 + (*(DWORD *)&mData[12])&0x00FFFFFF;
			if (len > 500*1024 || len < 5)
			{
				temp_pCurPos += 1;
				continue;
			}
			temp_pCurPos += len;
		}
		else
		{
			temp_pCurPos++;
			continue;
		}
	}
	
	CloseHandle(f_CreateIndex) ;
	f_CreateIndex = NULL ;
	return 1;
}


__int64 NewStreamFileOpr::GetFrameEndPos(HANDLE m_pFile, DWORD KeyFrameNum, __int64 KeyFramePos, 
		DWORD nFrame)  //�õ�ָ��֡�Ľ���λ��
{
	BYTE mData[16];
	BYTE hFrame[4] = {0X00, 0X00, 0X01,0xF1 };//����֡֡ͷ
	DWORD len = 0 ;

	DWORD FrameNum		= KeyFrameNum ;
	__int64 temp_pos		= KeyFramePos ;
	__int64 m_nDataLen	  = GetFileSize(m_pFile,NULL) ;
	
	while(true)
	{
		if (temp_pos >= m_nDataLen)
		{
			return -1 ;
		}

		if (myFileSeek (m_pFile, temp_pos, FILE_BEGIN)	== -1)
		{
			return -1 ;
		}

		if (ReadFile(m_pFile, mData, 16, &len, NULL) == FALSE)
		{
			return -1 ;
		}

		if (len < 16)
		{
			return -1 ;
		}
		
		if(memcmp(mData, hFrame , 3))   //����ͷ
		{
			temp_pos += 1;
			continue;
		}

		if((mData[3] == 0xfd)||(mData[3] == 0xfb))//I��
		{
			if (FrameNum == nFrame)
			{
				temp_pos += 16 + (*(DWORD *)&mData[12])&0x00FFFFFF;
				return temp_pos;
			}
			temp_pos += 16 + (*(DWORD *)&mData[12])&0x00FFFFFF;    //13~16�ֽڱ�ʾ���ݴ�С
			FrameNum ++;
			//��������֡
			if (myFileSeek (m_pFile, temp_pos, FILE_BEGIN)	== -1)
			{
				return -1 ;
			}
			
			if (ReadFile(m_pFile, mData, 16, &len, NULL) == FALSE)
			{
				return -1 ;
			}

			if (len < 16)
			{
				return -1 ;
			}
			
			if (memcmp(mData, hFrame,4) == 0)
			{
				temp_pos += 16 + (*(DWORD *)&mData[12])&0x00FFFFFF ;
			}
			
		}
		else if((mData[3] == 0xfc)||(mData[3] == 0xfa))//p��
		{
			if (FrameNum == nFrame)
			{
				temp_pos += 8 + (*(DWORD *)&mData[4])&0x00FFFFFF;
				return temp_pos;
			}
			temp_pos += 8 + (*(DWORD *)&mData[4])&0x00FFFFFF;    //5~8�ֽڱ�ʾ���ݴ�С
			FrameNum ++;
		}
		else if(mData[3] == 0xf0)//��Ƶ��
		{
			temp_pos += 8 + *(WORD *)&mData[6];    //7~8�ֽڱ�ʾ���ݴ�С
		}
		else
		{
			temp_pos += 1;
		}
	}
	return -1 ;
}

void NewStreamFileOpr::GetFileInfo(HANDLE m_pFile, DWORD& dwFrame, DH_VIDEOFILE_HDR& _video_info)
{
	static const int BUFLEN = 4116;
	static const int HEADERLEN = 20;
	static const BYTE I_Frame[4] = {0x00,0x00,0x01,0xFD} ;
	static const BYTE B_Frame[4] = {0x00,0x00,0x01,0xFB} ;
	static const BYTE A_Frame[4] = {0x00,0x00,0x01,0xF0} ;

	unsigned int Audio_Samples[] = {4000, 8000, 11025, 16000, 20000, 22050, 32000, 44100, 48000};

	BYTE buf[BUFLEN] ;
	int rate = 25;
	BYTE *pos ;	
	DWORD len;

	__int64 m_pCurPos = 0;
	__int64 m_nDataLen = GetFileSize(m_pFile, NULL) ;

	bool bVideoFlag = true;
	bool bAudioFlag = true;
	
	while (bVideoFlag || bAudioFlag)
	{
		if (m_pCurPos > m_nDataLen - BUFLEN || (m_pCurPos >= 4194304))
		{
			if (!bVideoFlag)
			{
				dwFrame = 0;
				break;
			}
			
			break;
		}

		myFileSeek (m_pFile, m_pCurPos, FILE_BEGIN) ;
		ReadFile(m_pFile, buf, BUFLEN, &len, NULL) ;

		pos = buf;
			
		while ( (pos = (BYTE *)memchr(pos, 0, BUFLEN-HEADERLEN - (pos - buf))) != NULL)   //���ҵ���һ���ַ�
		{
			//������
			if (bVideoFlag && (memcmp(pos, I_Frame, 4) == 0 || memcmp(pos, B_Frame,4) == 0))
			{
				bVideoFlag = false;
				*(DWORD*)(&(_video_info.DirStartTime)) = *(DWORD *)(pos+8);   //9~12�ֽڱ�ʾʱ��

				if (memcmp(pos, I_Frame, 4) == 0)
				{
					_video_info.VideoType = 4;
				}
				else if (memcmp(pos, B_Frame,4) == 0)
				{
					_video_info.VideoType = 1;
				}

				_video_info.Framerate   = *(pos+5) & 0x1F;
				_video_info.VideoWidth	= *(pos+6)*8;
				_video_info.VideoHigh	= *(pos+7)*8;
				
				pos++;
			}
			else if (bAudioFlag && (memcmp(pos, A_Frame, 4) == 0))
			{	
				bAudioFlag = false;
				_video_info.AudioChannel = 1;
				
				_video_info.AudioType = *(pos+4);
				if (_video_info.AudioType == 10)
				{
					_video_info.AudioType = 22; //G711
				}
				
				_video_info.AudioSamplesPerSec = Audio_Samples[1];
				if ((*(pos+5) >= 1) && (*(pos+5) <= 9))
				{
					_video_info.AudioSamplesPerSec = Audio_Samples[*(pos+5) - 1];
				}
				
				if (_video_info.AudioType == 7 /*PCM8*/
					|| _video_info.AudioType == 30 /*DH_ENCODE_AUDIO_TALK*/)
				{
					_video_info.AudioBitPerSample = 8;
				}
				else
				{
					_video_info.AudioBitPerSample = 16;
				}
				
				pos++;
			}
			else 
			{
				pos++;
				if (BUFLEN-HEADERLEN <= (pos - buf) )
				{
					break;
				}
			}
		}

		m_pCurPos += (BUFLEN - HEADERLEN);
	}

	bVideoFlag = true;
	m_pCurPos = m_nDataLen-BUFLEN-1;

	while(bVideoFlag)
	{
		if (m_pCurPos < BUFLEN || (m_nDataLen-m_pCurPos) >= 2097152)
		{
			memset(&(_video_info.DirStartTime), 0, sizeof(DHTIME));
			return;
		}

		myFileSeek (m_pFile, m_pCurPos, FILE_BEGIN) ;
		ReadFile(m_pFile, buf, BUFLEN, &len, NULL) ;

		pos = buf ;
			
		while ( (pos = (BYTE *)memchr(pos, 0, BUFLEN-HEADERLEN - (pos - buf))) != NULL)   //���ҵ���һ���ַ�
		{
			if (memcmp(pos, I_Frame, 4) == 0 || memcmp(pos, B_Frame,4) == 0)
			{
				bVideoFlag = false;
				*(DWORD*)(&(_video_info.DirEndTime)) = *(DWORD *)(pos+8);   //9~12�ֽڱ�ʾʱ��
				rate = pos[5];
//			int second = endtime->second + 1;
				int second = _video_info.DirEndTime.second;
				_video_info.DirEndTime.second = (second > 60) ? 60 : second;
				dwFrame = GetTimeInterVal(_video_info.DirEndTime, _video_info.DirStartTime) * rate;
				break ;
			}
			else 
			{
				pos++;
				if (BUFLEN-HEADERLEN <= (pos - buf) )
				{
					break;
				}
			}
		}

		m_pCurPos -= (BUFLEN - HEADERLEN);
	}
}