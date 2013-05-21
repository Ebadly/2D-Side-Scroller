#include "SDL/SDL_mixer.h"
#include "SoundManager.h"

SoundManager::SoundManager() {
    //Initializes the music to the default
     Mix_OpenAudio( 22050, MIX_DEFAULT_FORMAT, 2, 4096 );
}

bool SoundManager::play_music( std::string filename ) {
    //Takes a filename and plays the music.
   
    Mix_Music *music = Mix_LoadMUS( filename.c_str() );
    if( Mix_PlayMusic( music, -1 ) == -1 ) {
        return false;
    }
    return true;
}

void SoundManager::stop_music() {
    //Stop all currently playing music.
    Mix_HaltMusic();
}

SoundManager::~SoundManager() {
    //Free the music.
    Mix_CloseAudio();
}  
