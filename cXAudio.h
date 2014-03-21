/*
=================
cXAudio.h
- Header file for class definition - SPECIFICATION
- Header file for the cXAudio class
=================
*/
#ifndef _CXAUDIO_H
#define _CXAUDIO_H
#include "GameConstants.h"

class cXAudio
{
private:
    IXAudio2* mXAudio2;
    IXAudio2MasteringVoice* mMasteringVoice;
	IXAudio2SourceVoice* mSourceVoice;

public:
	cXAudio();						// Default constructor
	~cXAudio();						// Default destructor
	void playSound(LPWSTR theFilename, bool pLoop );		// Play sound
};
#endif