#ifndef DEFINE_H
#define DEFINE_H

#define SAMPLE_FREQ_4000	1
#define SAMPLE_FREQ_8000	2
#define SAMPLE_FREQ_11025	3
#define SAMPLE_FREQ_16000	4
#define SAMPLE_FREQ_20000	5
#define SAMPLE_FREQ_22050	6
#define SAMPLE_FREQ_32000	7
#define SAMPLE_FREQ_44100	8
#define SAMPLE_FREQ_48000	9

// ��������
enum InputType
{
	File = 0,
	Stream = 1
};

// ��������
enum EncodeType {
	Encode_None = 0,

	// ��Ƶ��������
	Encode_MPEG4,
	Encode_H264,

	// ��Ƶ��������
	Encode_PCM = 7,
	Encode_G729,
	Encode_IMA,
	Encode_PCM_MULAW,
	Encode_G721,
	Encode_PCM8_VWIS,
	Encode_MS_ADPCM
};

enum PackageType
{
	PackageInvalid = -1,// �޷�ʶ��Ĵ����ʽ
	PackageNew = 0,		// �µĴ����ʽ
	PackageNone,		// û������ͷ,ͨ��MPEG4����
	PackageHB			// �Ӻ�2�����ʽ
};

// ֡����
enum FrameType {
	InvialdFrame = 0,	// ��Ч֡
	VideoFrame,			// ��Ƶ֡
	AudioFrame,			// ��Ƶ֡
	DataFrame			// ��ʶ�������֡
};

// ��Ƶ֡����
enum VideoFrameType {
	N_Frame = 0, // 
	I_Frame,
	P_Frame
};

/************************************************************************
* ��Ƶ�������ӿ�
************************************************************************/
struct IVideoDecoder {
	// ��ʼ��
	virtual int init() = 0;
	
	// ���
    virtual int clean() = 0;	
	
	// ����
	virtual int reset() = 0;	
	
	// �ı�ͼ���С�����Բ���
    virtual int resize(int w, int h) = 0; 
	
	// ����, ����paramΪ�Զ�����Ϣ
    virtual int decode(unsigned char *buf, unsigned int buflen, int param1, int param2) = 0;
};

struct tagFrameInfo {
	unsigned char	*header;	// ����ͷ������ָ��
	unsigned char	*content;	// �������ݵ�ƫ��
	unsigned int	length;		// ���ݳ���(����ͷ��)
	unsigned int	datalen;	// ���ݳ���.	

	int type; // VIDEO, AUDIO, DATA
	int subtype; // I-FRAME, P-FRAME, etc.
	
	int encode; // MPEG4/H264, PCM, MSADPCM, etc.
	
	int rate;
	
	int width;
	int height;
	
	// ֻ��I֡���е�����
	int year;
	int month;
	int day;
	int hour;
	int minute;
	int second;
	
	// ��Ƶ���е�����
	int channels;
	int bitsPerSample;
	int samplesPerSecond;
	
	int param1;
	int param2;
};

struct IStreamParser 
{
	virtual int init() = 0;
	
	virtual void clean() = 0;
	
	// �������ݽӿ�
	/*! ����:
	0: û�еõ�һ��Frame
	N>0: �õ�N��������֡ 
	*/
	virtual int parse(unsigned char *data, int datalen) = 0;
	
	// �õ����������
	/*!
	����: ����ֵ(0x01FD, 0x01FC, 0x01FB, 0x01FA....)
	����: indexΪ������
	parm:Ϊ����
	*/
	virtual int getFrameData(int index, void **parm) = 0;
	
	// ���� ���force == true �����������ݰ���
	virtual void reset(bool force = false) = 0;
};

struct YUVDataInfo
{
	int width;		// ��
	int height;		// ��
	int rate;		// ָʾYUV��ʽ,�������������Ƿ�Ϊ���������CIF��
	int reserved;	// ����,Ŀǰ���0
};

struct IFifoBuffer
{
	virtual int init(int count, int blocksize, const char *name) = 0;
	virtual int reset() = 0;
	virtual int clear() = 0;
	virtual int write(unsigned char *data, unsigned int datalen) = 0;
	virtual int read(unsigned char *data, unsigned int &datalen) = 0;
	virtual bool readReady() = 0;
	virtual bool writeReady() = 0;
	virtual int chunkCount() = 0;
	virtual int maxCount() = 0;
	virtual int restCount() = 0;
};

#endif // DEFINE_H
