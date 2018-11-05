#pragma once
#include <SFML/Audio.hpp>
#include "voiceAnalysis.h"

class VoiceRecorder : public sf::SoundRecorder
{
	cyclicBuffer<sf::Int16, N> commandBuffer;
	sf::SoundBuffer buffer;
	VoiceAnalyzer analyzer;


	virtual bool onStart(); // optional
	virtual bool onProcessSamples(const sf::Int16* samples, std::size_t sampleCount);
	virtual void onStop();
public:
	virtual sf::SoundBuffer getBuffer();
	VoiceRecorder() : commandBuffer(), analyzer(){};
};