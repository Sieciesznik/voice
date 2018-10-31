#pragma once
extern "C"
{
#include "kiss_fftr.h"
}

constexpr auto N = 44100*3;
constexpr auto NFFT = 4096;

void runVoiceAnalysis(signed short* voice, size_t size, kiss_fft_cpx fftOut[NFFT / 2 + 1]);
void kissFFT(const kiss_fft_scalar in[NFFT], kiss_fft_cpx out[NFFT / 2 + 1]);