#pragma once


#define NOTFOUND_RIFF (-2)
#define NOTFOUND_WAVE (-3)
#define NOTFOUND_FMT  (-4)
#define NOTFOUND_DATA  (-5)
#define LOAD_SUCCESS	(0)

class ReadWAVE
{
#pragma pack(push,1)
	struct RiffHeader {
		char riff[4];			//"RIFF"�Ƃ��������񂪊i�[����Ă���
		unsigned long  size;	//�t�@�C���T�C�Y
		char type[4];			//"WAVE"�Ƃ��������񂪊i�[����Ă���
	};
	RiffHeader m_RiffHeader;

	struct FormatChunk {
		char fmt[4];			//"fmt "�Ƃ��������񂪊i�[����Ă���
		unsigned long size;		//FormatChunk�w�b�_�[�̃t�@�C���T�C�Y
		unsigned short format;	//�f�[�^�̃t�H�[�}�b�g
		unsigned short channels;//�`�����l����
		unsigned long samplerate;//�T���v�����O���[�g(Hz)
		unsigned long bytepersec;//�f�[�^���x(Byte/sec)
		unsigned short blockalign;//�u���b�N�T�C�Y(Byte/sample * �`�����l����)
		unsigned short bitswidth;//�T���v��������̃r�b�g��(bit/sample)
	};
	FormatChunk m_FormatChunk;
	
	struct FormatChunkEx {
		FormatChunk formatChunk;
		unsigned short extended_size;//�g�������T�C�Y
	};
	unsigned char* extended;	 //�g������
	FormatChunkEx m_FormatChunkEx;

	struct DataChunk {
		char id[4];					//"data"�Ƃ��������񂪊i�[����Ă���(�f�[�^�̎n�܂���Ӗ��X)
		unsigned long size;			//�g�`�f�[�^�̃o�C�g��
	};
	short* waveformData;//
	DataChunk m_DataChunk;
#pragma pack(pop)

	int LoadWAVEData(char *fileName);
	//�G���[�R�[�h�L���p
	int State;

public:
	ReadWAVE(char* fileName);
	~ReadWAVE();
	int GetState(){ return State; };
	//index���������O���������ꍇ-1��Ԃ�
	short GetWaveData(unsigned long index);
	FormatChunk GetFormat(){ return m_FormatChunk; };
	unsigned short GetChannels(){ return m_FormatChunk.channels; };
	unsigned long GetSamplerate(){ return m_FormatChunk.samplerate; };
	unsigned long GetDataSize(){ return m_DataChunk.size; };
	unsigned long GetSec();

};

