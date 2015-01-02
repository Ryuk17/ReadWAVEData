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
		char riff[4];			//"RIFF"という文字列が格納されている
		unsigned long  size;	//ファイルサイズ
		char type[4];			//"WAVE"という文字列が格納されている
	};
	RiffHeader m_RiffHeader;

	struct FormatChunk {
		char fmt[4];			//"fmt "という文字列が格納されている
		unsigned long size;		//FormatChunkヘッダーのファイルサイズ
		unsigned short format;	//データのフォーマット
		unsigned short channels;//チャンネル数
		unsigned long samplerate;//サンプリングレート(Hz)
		unsigned long bytepersec;//データ速度(Byte/sec)
		unsigned short blockalign;//ブロックサイズ(Byte/sample * チャンネル数)
		unsigned short bitswidth;//サンプルあたりのビット数(bit/sample)
	};
	FormatChunk m_FormatChunk;
	
	struct FormatChunkEx {
		FormatChunk formatChunk;
		unsigned short extended_size;//拡張部分サイズ
	};
	unsigned char* extended;	 //拡張部分
	FormatChunkEx m_FormatChunkEx;

	struct DataChunk {
		char id[4];					//"data"という文字列が格納されている(データの始まりを意味ス)
		unsigned long size;			//波形データのバイト数
	};
	short* waveformData;//
	DataChunk m_DataChunk;
#pragma pack(pop)

	int LoadWAVEData(char *fileName);
	//エラーコード記憶用
	int State;

public:
	ReadWAVE(char* fileName);
	~ReadWAVE();
	int GetState(){ return State; };
	//indexがメモリ外をさした場合-1を返す
	short GetWaveData(unsigned long index);
	FormatChunk GetFormat(){ return m_FormatChunk; };
	unsigned short GetChannels(){ return m_FormatChunk.channels; };
	unsigned long GetSamplerate(){ return m_FormatChunk.samplerate; };
	unsigned long GetDataSize(){ return m_DataChunk.size; };
	unsigned long GetSec();

};

