// StandardStreamFirOpr.cpp: implementation of the StandardStreamFirOpr class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "StandardStreamFirOpr.h"

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

StandardStreamFirOpr::StandardStreamFirOpr()
{

}

StandardStreamFirOpr::~StandardStreamFirOpr()
{

}

int   StandardStreamFirOpr::CreateIndex(char* filename, DWORD beginpos, 
									std::vector<DH_INDEX_INFO*>& m_pFileIndex, 
									DWORD& m_nTotalFrameNum, DHTIME& m_begintime, 
									DHTIME& m_endtime,
									__int64& nDataLen) //������������������Ϣ����m_pFileIndex��
{
	return 1;
}


__int64 StandardStreamFirOpr::GetFrameEndPos(HANDLE m_pFile, DWORD KeyFrameNum, 
											 __int64 KeyFramePos, DWORD nFrame)  //�õ�ָ��֡�Ľ���λ��
{
	return -1 ;
}

void StandardStreamFirOpr::GetFileInfo(HANDLE m_pFile, DWORD& dwFrame, DH_VIDEOFILE_HDR& _video_info)
{

}