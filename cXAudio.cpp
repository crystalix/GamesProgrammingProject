/*
=================
cXAudio.cpp
- CPP file for class definition - IMPLEMENTATION
- CPP file for the cXAUDIO class
=================
*/
#include "cXAudio.h"

/*
=================
- Data constructor initializes the cXAudio object 
- Is always called, thus ensures all cXAudio objects are in a consistent state.
=================
*/
cXAudio::cXAudio()
{
	HRESULT hResult;
	// Initialize XAudio2
	CoInitializeEx( NULL, COINIT_MULTITHREADED );
	
	// create an XAudio2 instance
    if( FAILED( hResult = XAudio2Create( &mXAudio2, 0, XAUDIO2_DEFAULT_PROCESSOR  ) ) )
    {
        OutputDebugString("Failed to init XAudio2 engine.");
        CoUninitialize();
    }
	else
    if( FAILED( hResult = mXAudio2->CreateMasteringVoice( &mMasteringVoice, XAUDIO2_DEFAULT_CHANNELS, XAUDIO2_DEFAULT_SAMPLERATE, 0, 0, NULL  ) ) )
    {
        OutputDebugString( "Failed creating mastering voice.");
        mXAudio2->Release();
        CoUninitialize();
    }

}
/*
=================
- Destructor, cleans up after the cXAudio object is deleted
=================
*/
cXAudio::~cXAudio()
{
	// Destroy the source voice instance
	if(mSourceVoice != NULL)
		mSourceVoice->DestroyVoice();
	// Destroy the voice instance
	if(mMasteringVoice != NULL)
		mMasteringVoice->DestroyVoice();

	// Release the XAudio2 instance
	if(mXAudio2 != NULL)
		mXAudio2->Release();
    CoUninitialize();
}

/*
=================
- Play sound.
=================
*/
void cXAudio::playSound(LPWSTR theFilename, bool pLoop )					// Play sound
{
	HRESULT hResult;
	CWaveFile wavFile;

	wavFile.Open( theFilename, NULL, WAVEFILE_READ );
    // Get format of wave file
    WAVEFORMATEX* pwfx = wavFile.GetFormat();

    // Calculate how many bytes and samples are in the wave
    DWORD cbWaveSize = wavFile.GetSize();

    // Read the sample data into memory
    BYTE* pbWaveData = new BYTE[ cbWaveSize ];

    wavFile.Read( pbWaveData, cbWaveSize, &cbWaveSize );

    // Submit the wave sample data using an XAUDIO2_BUFFER structure
    XAUDIO2_BUFFER buffer = {0};
    buffer.pAudioData = pbWaveData;
    buffer.Flags = XAUDIO2_END_OF_STREAM;  // tell the source voice not to expect any data after this buffer
    buffer.AudioBytes = cbWaveSize;
	if (pLoop)
	{
		buffer.LoopLength = 0;
		buffer.LoopCount = XAUDIO2_LOOP_INFINITE;
	}

    // Create the source voice
    if( FAILED( hResult = mXAudio2->CreateSourceVoice( &mSourceVoice, pwfx ) ) )
    {
        OutputDebugString("Error creating source voice\n");
        delete pbWaveData;
    }
	else
	{
		mSourceVoice->SubmitSourceBuffer(&buffer);
		mSourceVoice->Start(0, XAUDIO2_COMMIT_NOW );
	}
}