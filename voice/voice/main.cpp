#include <iostream>
#include "voiceTools.h"
#include <SFML/Audio.hpp>

using namespace std;


int main() {

	if (!sf::SoundBufferRecorder::isAvailable())
	{
		// error: audio capture is not available on this system
		cerr << "paaanie, zjebales pan!";
	}

	VoiceRecorder recorder;
	
	// start the capture
	cout << "Nagranie 1: wcisnij przycisk" << endl;
	getchar();
	recorder.start();
	//cout << "zatrzymaj i odtworz: wcisnij przycisk" << endl;
	//getchar();
	
/*

	// retrieve the buffer that contains the captured audio data
	const sf::SoundBuffer& buffer = recorder.getBuffer();
	
	sf::Sound sound;
	sound.setBuffer(buffer);
	sound.play();
	*/
	cout << "zamknij";
	getchar();
	recorder.stop();
	return 0;
}