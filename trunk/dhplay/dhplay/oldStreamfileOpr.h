#ifndef OLD_STREAM_FILE_OPERATION_H
#define OLD_STREAM_FILE_OPERATION_H

#include "fileoprinterface.h"

class OldStreamOperation : public IFileOperator
{
public:
	OldStreamOperation();
	virtual ~OldStreamOperation();

	int CreateIndex(char* fileName, DWORD beginpos, std::vector<DH_INDEX_INFO*>& m_pFileIndex, 
		DWORD& m_totalFrameNum, DHTIME& begintime, DHTIME& endtime,__int64& nDataLen)  ;//������������������Ϣ����m_pFileIndex��

	__int64 GetFrameEndPos(HANDLE m_pFile, DWORD KeyFrameNum, __int64 KeyFramePos, 
		DWORD nFrame); //�õ�ָ��֡�Ľ���λ��

	void GetFileInfo(HANDLE m_pFile, DWORD& dwFrame, DH_VIDEOFILE_HDR& _video_info);

} ;

#endif //OLD_STREAM_FILE_OPERATION_H