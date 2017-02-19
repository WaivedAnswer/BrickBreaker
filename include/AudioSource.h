//
//  AudioSource.h
//  BrickBreaker
//
//  Created by Quinn Ramsay on 2017-02-18.
//  Copyright © 2017 Quinnter. All rights reserved.
//

#ifndef AudioSource_h
#define AudioSource_h
#include <string>
#include "commonSDL.h"

class AudioClip;

enum AudioType
{
    CLIP_EFFECT,
    CLIP_MUSIC
};

//AudioSource is designed to be an interface between currently SDL and BrickBreaker, it encapsulates t
//the behaviour of both SDL Chunks and SDL music into one easily usable class
class AudioSource
{
public:
    AudioSource();
    ~AudioSource();
    
    //repeat times or loop endlessly if repeat = -1
    void Play(int repeat = 0, float volumePercent = 1.0);
    void Stop();
    //TODO Add Pause
    //frees current audioclip
    void free();
    
    void SetClip(AudioClip* clip);
    void LoadClipFromFile(std::string filename, AudioType type);
                 
private:
    AudioClip* m_clip;
    
};

#endif /* AudioSource_h */
