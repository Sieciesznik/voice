#include "voiceAnalysis.h"
#include <iostream>


void runVoiceAnalysis(signed short* voice, size_t size, kiss_fft_cpx fftOut[NFFT / 2 + 1]) {
	
	//this function has responsibility to make sure that input to fft is correct
	//default size: 4096

	if (size == NFFT) {
		//signed short tempArray[NFFT];
		//memcpy(tempArray, voice, sizeof(signed short) * NFFT);
		kissFFT(voice, fftOut);
	}
	else {
		std::cerr << "runVoiceAnalysis sie zjebalo";
	}

}

void kissFFT(const kiss_fft_scalar in[NFFT], kiss_fft_cpx out[NFFT / 2 + 1]) {

	kiss_fftr_cfg cfg;

	if ((cfg = kiss_fftr_alloc(NFFT, 0/*is_inverse_fft*/, NULL, NULL)) != NULL)
	{
		kiss_fftr(cfg, in, out);
		free(cfg);
		std::cout << "FFT!\n";
	}
}