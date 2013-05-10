#include "SDL/SDL_mixer.h"
#include "Sound.h"

Sound::Sound() {
    //Initializes the music to the default
     Mix_OpenAudio( 22050, MIX_DEFAULT_FORMAT, 2, 4096 );
}

bool Sound::play_music( std::string filename ) {
    //Takes a filename and plays the music.

    //TODO: FIGURE OUT HOW TO NOT HARDCODE THE FILE NAME

    Mix_Music *music = Mix_LoadMUS( "../beat.wav" );
    if( Mix_PlayMusic( music, -1 ) == -1 ) {
        return false;
    }
    return true;
}

void Sound::stop_music() {
    //Stop all currently playing music.
    Mix_HaltMusic();
}

Sound::~Sound() {
    //Free the music.
    Mix_CloseAudio();
}  
