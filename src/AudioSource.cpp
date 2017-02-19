//
//  AudioSource.cpp
//  BrickBreaker
//
//  Created by Quinn Ramsay on 2017-02-18.
//  Copyright © 2017 Quinnter. All rights reserved.
//
#include "AudioSource.h"
#include "commonSDL.h"
#include "AudioClip.h"
#include "EffectClip.h"
#include "MusicClip.h"
AudioSource::AudioSource()
{
    m_clip = nullptr;
}

AudioSource::~AudioSource()
{
    free();
}

void AudioSource::Play(int repeat, float volumePercent)
{
    if(m_clip == nullptr)
    {
        return;
    }
    m_clip->Play(repeat, volumePercent);
}

void AudioSource::Stop()
{
    if(m_clip == nullptr)
    {
        return;
    }
    m_clip->Stop();
}

void AudioSource::free()
{
    if(m_clip != nullptr)
    {
        delete m_clip;
        m_clip = nullptr;
    }
}

void AudioSource::SetClip(AudioClip* clip)
{
    m_clip = clip;
}

void AudioSource::LoadClipFromFile(std::string filename, AudioType type)
{
    free();
    switch(type)
    {
        case CLIP_MUSIC:
            m_clip = new MusicClip();
            break;
        case CLIP_EFFECT:
            m_clip = new EffectClip();
            break;
        default:
            break;
    }
    
    if (m_clip != nullptr)
    {
        m_clip->LoadFromFile(filename);
    }
}
