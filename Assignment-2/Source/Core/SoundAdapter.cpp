
#include "SoundAdapter.h"
#ifdef _WIN32
#include <SDL.h>
#include <SDL_mixer.h>
#endif
#ifdef __linux__
#include <SDL/SDL.h>
#include <SDL/SDL_mixer.h>
#endif
#include <cstdlib>
#include <iostream>
 
//-------------------------------------------------------------------------------------
SoundAdapter::SoundAdapter(void)
{
	bool success = true;
	muted = false;
	mutedM = false;
	mutedS = false;
	// Make sure the sounds are initialized to null or your check is useless! (garbage data can be read as !NULL).
	for (int i = 0; i < NUM_SOUNDS; i++) {
		gameSounds[0] = NULL;
	}

	/* Initialize all SDL subsystems */
	if( SDL_Init( SDL_INIT_EVERYTHING ) == -1 ) {
		printf( "SDL not initialized! SDL Error: %s\n", Mix_GetError() );
		success = false;
	}

 	/* Initialize SDL_mixer */
	if( Mix_OpenAudio( 44100, MIX_DEFAULT_FORMAT, 2, 2048 ) < 0 ) {
		printf( "SDL_mixer not initialized! SDL_mixer Error: %s\n", Mix_GetError() );
		success = false;
	}

	/* Load music & sound effects */

#ifdef __linux__
	music = Mix_LoadMUS( "../Assets/halo_theme.wav" ); 
	gameSounds[PADDLE_BOUNCE] = Mix_LoadWAV("../Assets/ball.wav");
	gameSounds[WALL_BOUNCE] = Mix_LoadWAV("../Assets/wall.wav");
#endif
#ifdef _WIN32
	music = Mix_LoadMUS( "../Game-Tech-12/Assignment-2/Assets/halo_theme.wav" ); 
	gameSounds[PADDLE_BOUNCE] = Mix_LoadWAV("../../../Game-Tech-12/Assignment-2/Assets/ball.wav");
	gameSounds[WALL_BOUNCE] = Mix_LoadWAV("../../../Game-Tech-12/Assignment-2/Assets/wall.wav");
#endif
	/*for ( int i = 0 ; i < NUM_SOUNDS ; i++ ) {
		if( gameSounds[i] == NULL ) {
			printf( "Failed to load clickTest sound effect! SDL_mixer Error: %s\n", Mix_GetError() );
			success = false;
		}
	}*/

}
//-------------------------------------------------------------------------------------
SoundAdapter::~SoundAdapter(void) {
}
 
void SoundAdapter::startMusic(void) {
	Mix_PlayMusic( music, -1 );
}
/* Play a sound based on the soundID. (Sound IDs are identified in the header) */
void SoundAdapter::playSound(int soundID) {
	if ( gameSounds[soundID] != NULL && !mutedS ) {
		Mix_PlayChannel( -1, gameSounds[soundID], 0 );
	}
}

void SoundAdapter::mute(void) {
	muted = !muted;
	mutedM = muted;
	mutedS = muted;

	if ( mutedM != mutedS ) {
		muted = mutedM = mutedS = true;
	}

	muteMusic(mutedM);
}

void SoundAdapter::muteMusic(bool mute) {
	 if ( mute ) {
	 	Mix_PauseMusic();
	 } 
	 else { 
	 	Mix_ResumeMusic();
	 }
}
void SoundAdapter::muteSounds(bool mute) {
	mutedS = mute;
}

/* Free resources */
void SoundAdapter::destroy(void) {
	 //Free the music 
	Mix_FreeMusic( music );

	/* Free Sounds */
	for ( int i = 0 ; i < NUM_SOUNDS ; i++ ) {
		if ( gameSounds[i] != NULL )
			Mix_FreeChunk( gameSounds[i] );
		gameSounds[i] = NULL;
	}
	//Quit SDL subsystems
	Mix_Quit();
	SDL_Quit();
}