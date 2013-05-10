#ifndef SOUND_H
#define SOUND_H

#include "SDL_mixer.h"
#include <string>

class Sound {
    private:
    public:
        Sound();
        ~Sound();
        bool play_music( std::string filename );
        void stop_music();
};

#endif
