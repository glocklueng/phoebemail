// NewStreamFileOpr.h: interface for the NewStreamFileOpr class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_NEWSTREAMFILEOPR_H__FBF4EA8A_4731_4567_A145_06DEB45C24A1__INCLUDED_)
#define AFX_NEWSTREAMFILEOPR_H__FBF4EA8A_4731_4567_A145_06DEB45C24A1__INCLUDED_

#include "fileoprinterface.h"

class NewStreamFileOpr  : public IFileOperator
{
public:
	NewStreamFileOpr();
	virtual ~NewStreamFileOpr();

	int   CreateIndex(char* fileName, DWORD beginpos, std::vector<DH_INDEX_INFO*>& m_pFileIndex, 
		DWORD& m_totalFrameNum, DHTIME& begintime, DHTIME& endtime,__int64& nDataLen)  ;//������������������Ϣ����m_pFileIndex��

	__int64 GetFrameEndPos(HANDLE m_pFile, DWORD KeyFrameNum, __int64 KeyFramePos, 
		DWORD nFrame); //�õ�ָ��֡�Ľ���λ��

	void GetFileInfo(HANDLE m_pFile, DWORD& dwFrame, DH_VIDEOFILE_HDR& _video_info);
};

#endif // !defined(AFX_NEWSTREAMFILEOPR_H__FBF4EA8A_4731_4567_A145_06DEB45C24A1__INCLUDED_)
