#pragma once

#include "cyclicbuff.cpp"

extern "C"
{
#include "kiss_fftr.h"
}
#include <cstdlib>

struct SampleData {

	kiss_fft_cpx freqs[NFFT / 2 + 1];
	long loudness;
};

class VoiceAnalyzer {
public:
	long averageLoudness;
	long averageSize;

	cyclicBuffer<SampleData, 30> samples;
	cyclicBuffer<bool, 30> isCommand;
	cyclicBuffer<long, 60> ambientNoise;

	void runVoiceAnalysis(signed short* voice, size_t size);
	void kissFFT(const kiss_fft_scalar in[NFFT]);
	void updateAverageL();
	

	VoiceAnalyzer() :samples(SampleData()), isCommand(false), ambientNoise(100) {};
};