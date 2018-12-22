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
		ambientNoise.put(newAvg);
		updateAverageL();
		isCommand.put(newAvg > (averageLoudness * 1.2));

		bool* commands = isCommand.getBuffer();

		for (int i = isCommand.getSize() - 1; i >= 0; --i) {
			if (commands[i])
				std::cout << "\xdb";
			else
				std::cout << " ";
		}
		std::cout << averageLoudness << "      \r";
	}
	else {
		std::cerr << "runVoiceAnalysis sie zjebalo " << size << std::endl;
	}


}

void VoiceAnalyzer::kissFFT(const kiss_fft_scalar in[NFFT]) {

	kiss_fftr_cfg cfg;

	if ((cfg = kiss_fftr_alloc(NFFT, 0/*is_inverse_fft*/, NULL, NULL)) != NULL)
	{
		kiss_fftr(cfg, in, samples.getNext()->freqs); //getNext() returns pointer to next bucket
		free(cfg);
		
		/*
		for (uint32_t i = 0; i < NFFT / 2 + 1; ++i) {
			outr[i] = out[i].r * out[i].r + out[i].i * out[i].i;
		}*/

		samples.put();	//blank put() sets pivot in correct place

	}
}

void VoiceAnalyzer::updateAverageL() {

	averageLoudness = 0;
	long* ambient = ambientNoise.getBuffer();
	for (uint32_t i = 0; i < ambientNoise.getSize(); ++i) {
		averageLoudness += ambient[i];
	}
	averageLoudness /= ambientNoise.getSize();

	//averageLoudness = (averageLoudness * averageSize + newValue) / (averageSize + 1);
	//++averageSize;
}