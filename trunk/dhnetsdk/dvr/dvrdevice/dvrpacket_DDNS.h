
#ifndef DVRPACKETDDNS_H
#define DVRPACKETDDNS_H

#include "../kernel/afkinc.h"

class CDvrDevice;
class CDvrSearchChannel;

//ͨ�����ֲ�ѯIP
bool sendQueryIPByName_DDNS(CDvrDevice* device, char *name, int namelen);

#endif

