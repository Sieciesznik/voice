#include "voiceAnalysis.h"
#include <iostream>


void runVoiceAnalysis(signed short* voice, size_t size, kiss_fft_cpx fftOut[N / 2 + 1]) {

	if (size == N) {
		kissFFT(voice, fftOut);
	}
	else {
		std::cerr << "runVoiceAnalysis sie zjebalo";
	}

}

void kissFFT(const kiss_fft_scalar in[N], kiss_fft_cpx out[N / 2 + 1]) {

	kiss_fftr_cfg cfg;

	if ((cfg = kiss_fftr_alloc(N, 0/*is_inverse_fft*/, NULL, NULL)) != NULL)
	{
		kiss_fftr(cfg, in, out);
		free(cfg);
	}
}