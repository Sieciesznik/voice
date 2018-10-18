#include "voiceTools.h"

#include <iostream>
#include <fstream>

void fft() {

}

bool VoiceRecorder::onStart() {
	this->setProcessingInterval(sf::seconds(0.5));
	return true;
}

bool VoiceRecorder::onProcessSamples(const sf::Int16* samples, std::size_t sampleCount) 
{
	commandBuffer.put(samples, sampleCount);
	runVoiceAnalysis(commandBuffer.getBuffer(), commandBuffer.getSize(), fftOut);

	return true;
}

void VoiceRecorder::onStop()
{
	std::ofstream myfile;
	myfile.open("sample.txt", std::ios::out);
	
	if (myfile.is_open())
	{
		const sf::Int16* buff = commandBuffer.getBuffer();
		for (uint32_t i = 0; i < commandBuffer.getSize(); ++i) {
			myfile << buff[i] << " ";
		}

		myfile.close();
	}

	std::ofstream myfile2;
	myfile2.open("fft.txt", std::ios::out);

	if (myfile2.is_open())
	{
		for (uint32_t i = 0; i < N / 2 + 1; ++i) {
			myfile2 << fftOut[i].r << " " << fftOut[i].i << std::endl;
		}

		myfile2.close();
	}
}



sf::SoundBuffer VoiceRecorder::getBuffer() {
	if (buffer.loadFromSamples(commandBuffer.getBuffer(), commandBuffer.getSize(), 1, 44100)) {
		return buffer;
	}
	else {
		std::cerr << "voiceRecorer::getBuffer sie zjebalo";
	}
	return buffer;
}