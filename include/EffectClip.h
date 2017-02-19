//
//  EffectClip.h
//  BrickBreaker
//
//  Created by Quinn Ramsay on 2017-02-18.
//  Copyright © 2017 Quinnter. All rights reserved.
//

#ifndef EffectClip_h
#define EffectClip_h
#include "AudioClip.h"
#include "commonSDL.h"

//EffectClip encapsulates SDL chunk audio (sound effects and the like)
class EffectClip : public AudioClip
{
public:
    EffectClip();
    virtual ~EffectClip();
    //plays repeat times, if repeat = -1 then loops, plays on any available channel
    //negative volume percentages play volume at original level
    virtual void Play(int repeat, float volumePercent);
    virtual void Stop();
    virtual void SetVolume(float volumePercent);
    virtual void LoadFromFile(std::string filename);
    
    virtual void free();
private:
    Mix_Chunk* m_effect;
    int m_channel;
};


#endif /* EffectClip_h */
