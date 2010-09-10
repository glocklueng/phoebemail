
#include "dvrsearchchannel_DDNS.h"
#include "dvrpacket_DDNS.h"
#include "../def.h"


CDvrSearchChannel_DDNS::CDvrSearchChannel_DDNS(CDvrDevice *pDvrDevice, int nMainCommand, void *pParam)
	: CDvrSearchChannel(pDvrDevice, nMainCommand, pParam)
{

}

CDvrSearchChannel_DDNS::~CDvrSearchChannel_DDNS()
{
}

/*
 * ժҪ����������
 */
int CDvrSearchChannel_DDNS::OnRespond(unsigned char *pBuf, int nLen)
{
	int nRet = -1;
    if (m_search_channel_parm.base.func != NULL)
    {
        int nSearchType = GetSearchType();

        // ���ֲ�ѯIP
        if (nSearchType == AFK_CHANNEL_SEARCH_DDNSIP_BYNAME)
        {
			if (pBuf[12] == 0) // OK
			{
				nRet = m_search_channel_parm.base.func(this, pBuf + HEADER_SIZE, nLen - HEADER_SIZE, 0, m_search_channel_parm.base.udata);						
			}
			else  // ERROR
			{
			}

        }

        // ���кŲ�ѯIP
// 		else if (nSearchType == 191 && m_search_channel_parm.base.func != NULL)
// 		{
// 
// 		}
	}

	CDvrChannel::OnRespond(pBuf, nLen);

	return nRet;
}



