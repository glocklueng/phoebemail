//////////////////////////////////////////////////////////////////////
#if !defined _SHSTREAMFILEOPERATION_H
#define _SHSTREAMFILEOPERATION_H

#include "fileoprinterface.h"

class ShStreamFileOpr  : public IFileOperator
{
public:
	ShStreamFileOpr();
	virtual ~ShStreamFileOpr();

	int   CreateIndex(char* fileName, DWORD beginpos, std::vector<DH_INDEX_INFO*>& m_pFileIndex, 
		DWORD& m_totalFrameNum, DHTIME& begintime, DHTIME& endtime,__int64& nDataLen)  ;//������������������Ϣ����m_pFileIndex��

	__int64 GetFrameEndPos(HANDLE m_pFile, DWORD KeyFrameNum, __int64 KeyFramePos, 
		DWORD nFrame); //�õ�ָ��֡�Ľ���λ��

	void GetFileInfo(HANDLE m_pFile, DWORD& dwFrame, DH_VIDEOFILE_HDR& _video_info);
};

#endif 