#include "voiceAnalysis.h"
#include <iostream>

void VoiceAnalyzer::runVoiceAnalysis(signed short* voice, size_t size) {

	//this function has responsibility to make sure that input to fft is correct
	//default size: 4096

	if (true/*size <= NFFT*/) {

		kissFFT(voice);

		//measurement of current loudness
		long acc = 0;
		for (uint32_t i = 0; i < size; ++i) {
			acc += voice[i] > 0 ? voice[i] : -voice[i];
		}

		long newAvg = acc / size;

		samples.getLast()->loudness = newAvg;
		updateAverageL(newAvg);
		isCommand.put(newAvg > (averageLoudness));

		for (int i = 29; i > 0; --i) {
			if (*isCommand.show(i))
				std::cout << "\xdb";
			else
				std::cout << " ";
		}
		std::cout << averageLoudness << "\r";
	}
	else {
		std::cerr << "runVoiceAnalysis sie zjebalo " << size << std::endl;
	}


}

void VoiceAnalyzer::kissFFT(const kiss_fft_scalar in[NFFT]) {

	kiss_fftr_cfg cfg;

	if ((cfg = kiss_fftr_alloc(NFFT, 0/*is_inverse_fft*/, NULL, NULL)) != NULL)
	{
		kiss_fftr(cfg, in, samples.getNext()->freqs);
		free(cfg);
/*
		for (uint32_t i = 0; i < NFFT / 2 + 1; ++i) {
			outr[i] = out[i].r * out[i].r + out[i].i * out[i].i;
		}*/
		samples.put();

		//std::cout << "FFT!\n";
	}
}

void VoiceAnalyzer::updateAverageL(long newValue) {

	averageLoudness = (averageLoudness * averageSize + newValue) / (averageSize + 1);
	++averageSize;
}