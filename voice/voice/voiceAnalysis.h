#pragma once
#include "cyclicbuff.cpp"

extern "C"
{
#include "kiss_fftr.h"
}
#include <cstdlib>

constexpr auto N = 44100 * 3;
constexpr auto NFFT = 4096;

class VoiceAnalyzer {
public:
	cyclicBuffer<int32_t, (NFFT / 2 + 1) * 30> frequencies;
	cyclicBuffer<long, 30> loudness;

	void runVoiceAnalysis(signed short* voice, size_t size);
	void kissFFT(const kiss_fft_scalar in[NFFT]);

	VoiceAnalyzer() :frequencies() {};
};