//
//  EffectClip.cpp
//  BrickBreaker
//
//  Created by Quinn Ramsay on 2017-02-18.
//  Copyright © 2017 Quinnter. All rights reserved.
//
#include "EffectClip.h"
#include "commonSDL.h"
EffectClip::EffectClip()
{
    m_effect = nullptr;
    m_channel = 0;
}

EffectClip::~EffectClip()
{
    free();
}

void EffectClip::Play(int repeat, float volumePercent)
{
    if(m_effect == nullptr)
    {
        return;
    }
    m_channel = Mix_PlayChannel(-1, m_effect, repeat);
    if(volumePercent >= 0.0 && volumePercent <= 1.0)
    {
        Mix_Volume(m_channel, volumePercent*MIX_MAX_VOLUME);
    }
    else if(volumePercent > 1.0)
    {
        Mix_Volume(m_channel, MIX_MAX_VOLUME);
    }
    else
    {
        //don't need to change volume.
    }
}

void EffectClip::Stop()
{
    Mix_HaltChannel(m_channel);
}

void EffectClip::SetVolume(float volumePercent)
{
    if(m_effect == nullptr)
    {
        return;
    }
    if(volumePercent >= 0.0 && volumePercent <= 1.0)
    {
        Mix_VolumeChunk(m_effect, volumePercent*MIX_MAX_VOLUME);
    }
    else if(volumePercent > 1.0)
    {
        Mix_VolumeChunk(m_effect, MIX_MAX_VOLUME);
    }
    else
    {
        //don't need to change volume.
    }

}

void EffectClip::LoadFromFile(std::string filename)
{
    free();
    m_effect = Mix_LoadWAV(filename.c_str());
    if(m_effect == nullptr)
    {
        printf( "Failed to load effect! SDL_mixer Error: %s\n", Mix_GetError() );
    }
}

void EffectClip::free()
{
    if(m_effect != nullptr)
    {
        Mix_FreeChunk(m_effect);
        m_effect = nullptr;
    }
}
