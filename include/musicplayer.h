#ifndef _MUSICPLAYER_H
#define _MUSICPLAYER_H
#include <SFML/Audio/Music.hpp>
#include <SFML/System/Time.hpp>
#include <cassert>
#include <iostream>
#include "pathholder.h"
#include "musicidentifiers.h"

/*-------------------------------------------------------
* CLASS       : MUSICPLAYER
* DESCRIPTION : Plays music. Music can fade in/out and pitch
*               can be changed.
* METHODS     : MusicPlayer       - Set up empty player
*               ~MusicPlayer      - Clean up Music Player
*
*               loadPaths         - To load song paths during loading stage
*               play              - Play a different song
*               stop              - Stop playing the music
*               update            - Must be called each frame for fading effects to work
*
*               setMaxVolume      - Change the max volume
*               setFadeSpeed      - How long does a fade transition last?
*               setVolumeFading   - Activate or deactivate volume fading effects
*               getMaxVolume      - Returns the max volume music is playing
*               getFadeSpeed      - Returns the duration volume fades last
*               getVolumeFading   - Returns if volume fading is activated
*
*               throwLoadingError - Error message if a music file isn't available
*               playFirstTrack    - Determines how the first track should play and plays it
*               playSecondTrack   - Determines how the second track should play and plays it
*               updateFadeIn      - Used by update to increase volume
*               updateFadeOut     - Used by update to decrease volume and stop song
*--------------------------------------------------------*/
class MusicPlayer
{
public:
	MusicPlayer();
	~MusicPlayer();

	void loadPaths();
	void play(MusicIdentifier ID, bool loop = true);
	void stop();
	void update(sf::Time dt);

	void setMaxVolume(const float volume);
	void setFadeSpeed(const sf::Time duration);
	void setVolumeFading(bool fade);
	float getMaxVolume() const;
	sf::Time getFadeSpeed() const;
	bool getVolumeFading() const;

private:
	// Track:
	// Keeps track of a song and its fade effect status
	struct Track
	{
		enum class TransitionState
		{
			NONE,
			FADE_IN,
			FADE_OUT
		};

		Track();

		sf::Music song;
		TransitionState fadeState;
	};

	// Music Player:
	void throwLoadingError(const std::string filePath) const;
	void playFirstTrack(const MusicIdentifier ID, const bool loop);
	void playSecondTrack(const MusicIdentifier ID, const bool loop);
	void updateFadeIn(Track & track, const float significantVolume, const float fadeRate);
	void updateFadeOut(Track & track, const float significantVolume, const float fadeRate);

	PathHolder<MusicIdentifier> musicPaths;
	Track track[2];
	float maxVolume;
	bool volumeFade;
	sf::Time fadeDuration;
};

#include "musicplayer.inl"
#endif // end _MUSICPLAYER_H