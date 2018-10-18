#pragma once
#include <SFML/Audio.hpp>
#include "voiceAnalysis.h"

template <class T, uint32_t size>
class cyclicBuffer {
	T buffer[size];
	T orderedArray[size];
	int32_t pivot;
public:
	cyclicBuffer(T value = 0) : pivot(-1) {
		for (uint32_t i = 0; i < size; ++i) {
			buffer[i] = value;
		}
	};

	void put(T value) {
		if (++pivot < size) {
			buffer[pivot] = value;
		}
		else
			buffer[pivot = 0] = value;
	}

	void put(const T* array, std::size_t arraySize) {
		if (pivot + arraySize <= size) {
			memcpy(&buffer[pivot], array, sizeof(T) * arraySize);
			pivot += arraySize;
		}
		else {
			memcpy(&buffer[pivot], array, sizeof(T) * (size - pivot));
			memcpy(&buffer, &array[size - pivot], sizeof(T) * (arraySize - (size - pivot)));
			pivot = arraySize - (size - pivot);
		}
	}

	T get(int32_t index) {
		if (index >= size) return NULL;
		return buffer[index];
	}

	T* getBuffer() {
		memcpy(&orderedArray, &buffer[pivot], sizeof(T) * (size - pivot));
		memcpy(&orderedArray[size - pivot], buffer, sizeof(T) * pivot);
		return orderedArray;
	}

	size_t getSize() {
		return size;
	}
};

void fft();

class VoiceRecorder : public sf::SoundRecorder
{
	cyclicBuffer<sf::Int16, N> commandBuffer;
	sf::SoundBuffer buffer;
	kiss_fft_cpx fftOut[N / 2 + 1];

	virtual bool onStart(); // optional
	virtual bool onProcessSamples(const sf::Int16* samples, std::size_t sampleCount);
	virtual void onStop();
public:
	virtual sf::SoundBuffer getBuffer();
	VoiceRecorder(){};
};