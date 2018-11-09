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
	cyclicBuffer<SampleData, 30> samples;

	void runVoiceAnalysis(signed short* voice, size_t size);
	void kissFFT(const kiss_fft_scalar in[NFFT]);
	void displayFFT();

	VoiceAnalyzer() :samples(SampleData()) {};
};