
//
//  MusicClip.cpp
//  BrickBreaker
//
//  Created by Quinn Ramsay on 2017-02-18.
//  Copyright © 2017 Quinnter. All rights reserved.
//

#include "MusicClip.h"
#include "commonSDL.h"

MusicClip::MusicClip()
{
    m_music = nullptr;
}

MusicClip::~MusicClip()
{
    free();
}

void MusicClip::Play(int repeat, float volumePercent)
{
    if(m_music == nullptr)
    {
        return;
    }
    Mix_PlayMusic(m_music, repeat);
    if(volumePercent >= 0.0 && volumePercent <= 1.0)
    {
        Mix_VolumeMusic(volumePercent*MIX_MAX_VOLUME);
    }
    else if(volumePercent > 1.0)
    {
        Mix_VolumeMusic(MIX_MAX_VOLUME);
    }
    else
    {
        //don't need to change volume.
    }
}

void MusicClip::Stop()
{
    Mix_HaltMusic();
}

void MusicClip::SetVolume(float volumePercent)
{
    if(m_music == nullptr)
    {
        return;
    }
    if(volumePercent >= 0.0 && volumePercent <= 1.0)
    {
        Mix_VolumeMusic(volumePercent*MIX_MAX_VOLUME);
    }
    else if(volumePercent > 1.0)
    {
        Mix_VolumeMusic(MIX_MAX_VOLUME);
    }
    else
    {
        //don't need to change volume.
    }
}

void MusicClip::LoadFromFile(std::string filename)
{
    free();
    m_music = Mix_LoadMUS("assets/Tetris.mp3");
    if(m_music == nullptr)
    {
        printf( "Failed to load music! SDL_mixer Error: %s\n", Mix_GetError() );
    }
}

void MusicClip::free()
{
    if(m_music != nullptr)
    {
        Mix_FreeMusic(m_music);
        m_music = nullptr;
    }
}
