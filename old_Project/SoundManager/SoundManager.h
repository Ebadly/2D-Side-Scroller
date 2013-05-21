#ifndef SOUND_H
#define SOUND_H

#include "SDL/SDL_mixer.h"
#include <string>

class SoundManager {
    private:
    public:
        SoundManager();
        ~SoundManager();
        bool play_music( std::string filename );
        void stop_music();
};

#endif
