//
//  AudioClip.hpp
//  BrickBreaker
//
//  Created by Quinn Ramsay on 2017-02-18.
//  Copyright © 2017 Quinnter. All rights reserved.
//

#ifndef AudioClip_h
#define AudioClip_h
#include <string>
//TODO maybe switch to PImpl
//encapsulates both SDL sound effects and music in common interface
class AudioClip
{
public:
    AudioClip() {};
    virtual ~AudioClip() {};
    //negative volume percentages play volume at original level
    virtual void Play(int repeat, float volumePercent) = 0;
    virtual void Stop() = 0;
    virtual void SetVolume(float volumePercent) = 0;
    virtual void LoadFromFile(std::string filename) = 0;
    virtual void free() = 0;
private:
};

#endif /* AudioClip_h */
