#define _CRT_SECURE_NO_WARNINGS


#include "ReadWAVE.h"
#include <string.h>
#include <stdio.h>

ReadWAVE::ReadWAVE(char* filename)
{
	State = LoadWAVEData(filename);
}


ReadWAVE::~ReadWAVE()
{

	delete[] waveformData;

}


int ReadWAVE::LoadWAVEData(char *fileName)
{
	FILE* fp = fopen(fileName, "rb");

	fread(&m_RiffHeader, sizeof(RiffHeader), 1, fp);
	
	if (strncmp(m_RiffHeader.riff, "RIFF",4) != 0) return NOTFOUND_RIFF;

	if (strncmp(m_RiffHeader.type, "WAVE",4) != 0) return NOTFOUND_WAVE;

	fread(&m_FormatChunk, sizeof(FormatChunk), 1, fp);

	if (strncmp(m_FormatChunk.fmt, "fmt ",4) != 0) return NOTFOUND_FMT;

	//Šg’£—L‚è‚Ìê‡‚Í‚±‚±‚Å“Ç‚Ý’¼‚·

	fread(&m_DataChunk, sizeof(DataChunk), 1, fp);

	if (strncmp(m_DataChunk.id, "data",4) != 0) return NOTFOUND_DATA;

	waveformData = new short[m_DataChunk.size];

	fread(waveformData, sizeof(short), m_DataChunk.size / sizeof(short), fp);

	fclose(fp);

	return LOAD_SUCCESS;

}


short ReadWAVE::GetWaveData(unsigned long index)
{
	if (index >= 0 && index <= m_DataChunk.size) return waveformData[index];
		
	return -1;

}
