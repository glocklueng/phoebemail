
#ifndef PARATIMER_H
#define PARATIMER_H

#ifdef __cplusplus
extern "C"
{
#endif

//��ʱ���Ļص���������
typedef void (* TimerProc_Para)(long nId,void* lpPara);

//�趨һ����ʱ��
//��ʶ��			nId
//�����			uElapse
//��ʱ���ص�������	lpfn
//��ʱ��������		lpPara
//����ֵ����1 ��Ӷ�ʱ������
long SetTimer_Para(long nId,unsigned long uElapse,TimerProc_Para lpfn,void* lpPara);

//ɾ��һ����ʱ��
//��ʶ��	nId
void KillTimer_Para(long nId);


#ifdef __cplusplus
}
#endif

#endif

