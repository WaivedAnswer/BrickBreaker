//
//  MusicClip.h
//  BrickBreaker
//
//  Created by Quinn Ramsay on 2017-02-18.
//  Copyright © 2017 Quinnter. All rights reserved.
//

#ifndef MusicClip_h
#define MusicClip_h
#include "AudioClip.h"
#include "commonSDL.h"
//MusicClip encapsulates SDL Music
class MusicClip : public AudioClip
{
public:
    MusicClip();
    virtual ~MusicClip();
    //plays repeat times, if repeat = -1 then loops
    //negative volume percentages play volume at original level
    virtual void Play(int repeat, float volumePercent);
    virtual void Stop();
    virtual void SetVolume(float volumePercent);
    virtual void LoadFromFile(std::string filename);
    virtual void free();
private:
    Mix_Music* m_music;
};

#endif /* MusicClip_h */
