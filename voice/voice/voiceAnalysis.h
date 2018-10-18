#pragma once
extern "C"
{
#include "kiss_fftr.h"
}

constexpr auto N = 44100*3;

void runVoiceAnalysis(signed short* voice, size_t size, kiss_fft_cpx fftOut[N / 2 + 1]);
void kissFFT(const kiss_fft_scalar in[N], kiss_fft_cpx out[N / 2 + 1]);