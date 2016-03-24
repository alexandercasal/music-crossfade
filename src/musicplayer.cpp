#include <stdexcept>
#include <string>
#include <algorithm>
#include "musicplayer.h"
#include "floatcompare.h"

// Debug Messages
#ifdef _DEBUG
#define _dmessage(m) std::cout << m
#else
#define _dmessage(m)
#endif

/*-------------------------------------------------------
* STRUCT      : TRACK
* METHOD      : Constructor
* DESCRIPTION : Initialize effects to inactive
*--------------------------------------------------------*/
MusicPlayer::Track::Track() : song()
, fadeState(TransitionState::NONE)
{
	_dmessage("Music Player Track: Constructed\n");
}

/*-------------------------------------------------------
* CLASS       : MUSICPLAYER
* METHOD      : Constructor
* DESCRIPTION : Set up empty Music Player
*--------------------------------------------------------*/
MusicPlayer::MusicPlayer() : musicPaths()
, track()
, maxVolume(100.f)
, volumeFade(true)
, fadeDuration(sf::seconds(2.f))
{
	_dmessage("Music Playr:\tConstructed.\n\t\tMax Volume: " << maxVolume << "\n");
	_dmessage("\t\tFading Active: " << volumeFade << "\n");
	_dmessage("\t\tFade Duration: " << fadeDuration.asSeconds() << " seconds.\n");
}

/*-------------------------------------------------------
* CLASS       : MUSICPLAYER
* METHOD      : Destructor
* DESCRIPTION : Clean up Music Player
*--------------------------------------------------------*/
MusicPlayer::~MusicPlayer()
{
	musicPaths.clear();

	_dmessage("Music Player: Destroyed\n");
}

/*-------------------------------------------------------
* CLASS       : MUSICPLAYER
* METHOD      : loadPaths
* DESCRIPTION : Load song paths during loading stage
*--------------------------------------------------------*/
void MusicPlayer::loadPaths()
{
	_dmessage("Music Player: Loading music paths\n");

	musicPaths.pairToPath(MusicIdentifier::TITLE_SCREEN, "snd/title.ogg");
	musicPaths.pairToPath(MusicIdentifier::GAME, "snd/gamesong.ogg");
}

/*-------------------------------------------------------
* CLASS       : MUSICPLAYER
* METHOD      : throwLoadingError (private)
* DESCRIPTION : Error message if a music file isn't available
*--------------------------------------------------------*/
void MusicPlayer::throwLoadingError(const std::string filePath) const
{
	std::string message = "Unable to find music at \'" + filePath
		+ "\'\nFile may have been deleted, modified, or moved.";
	throw std::runtime_error(message);
}

/*-------------------------------------------------------
* CLASS       : MUSICPLAYER
* METHOD      : playFirstTrack (private)
* DESCRIPTION : Determines how the first track should play and plays it
*--------------------------------------------------------*/
void MusicPlayer::playFirstTrack(const MusicIdentifier ID, const bool loop)
{
	// open song file
	if (!track[0].song.openFromFile(musicPaths.getPath(ID)))
	{
		throwLoadingError(musicPaths.getPath(ID));
	}

	track[0].song.setLoop(loop);

	if (volumeFade)
	{
		// Play track with volume fading
		track[0].fadeState = Track::TransitionState::FADE_IN;
		track[0].song.setVolume(0.f);
		track[0].song.play();
		track[1].fadeState = Track::TransitionState::FADE_OUT;
		
		_dmessage("Music Player: Playing track 0 with fading\n");
	}
	else
	{
		// Play track without volume fading
		stop();
		track[0].song.setVolume(maxVolume);
		track[0].song.play();

		_dmessage("Music Player: Playing track 0 without fading\n");
	}
}

/*-------------------------------------------------------
* CLASS       : MUSICPLAYER
* METHOD      : playSecondTrack (private)
* DESCRIPTION : Determines how the second track should play and plays it
*--------------------------------------------------------*/
void MusicPlayer::playSecondTrack(const MusicIdentifier ID, const bool loop)
{
	// open song file
	if (!track[1].song.openFromFile(musicPaths.getPath(ID)))
	{
		throwLoadingError(musicPaths.getPath(ID));
	}

	track[1].song.setLoop(loop);

	if (volumeFade)
	{
		// Play track with volume fading
		track[1].fadeState = Track::TransitionState::FADE_IN;
		track[1].song.setVolume(0.f);
		track[1].song.play();
		track[0].fadeState = Track::TransitionState::FADE_OUT;

		_dmessage("Music Player: Playing track 1 with fading\n");
	}
	else
	{
		// Play track without volume fading
		stop();
		track[1].song.setVolume(maxVolume);
		track[1].song.play();

		_dmessage("Music Player: Playing track 1 without fading\n");
	}
}


/*-------------------------------------------------------
* CLASS       : MUSICPLAYER
* METHOD      : play
* DESCRIPTION : Play a different song. Activates optional
*               crossfade if another song is currently playing.
*--------------------------------------------------------*/
void MusicPlayer::play(MusicIdentifier ID, bool loop)
{
	_dmessage("Music Player:\tPlay called\n\t\tID: " << (int)ID << "\n\t\tLoop: " << loop << "\n\t\tFade: " << volumeFade << std::endl);
	_dmessage("Music Player:\tTrack Status\n\t\tTrack 0: " << track[0].song.getStatus());
	_dmessage("\n\t\tTrack 1: " << track[1].song.getStatus() << std::endl);

	// Two songs can't play at the same time. If they are,
	// then the other must stop or crossfade.
	if (track[0].song.getStatus() == sf::Music::Stopped)
	{
		_dmessage("Music Player: Stop track 1. Play track 0\n");

		playFirstTrack(ID, loop);
	}
	else if (track[1].song.getStatus() == sf::Music::Stopped)
	{
		_dmessage("Music Player: Stop track 0. Play track 1\n");

		playSecondTrack(ID, loop);
	}
	else
	{
		_dmessage("Music Player: Both tracks active. Stopping both. Playing Track 0\n");

		// Both tracks are active. Fade out the loudest
		if (track[0].song.getVolume() < track[1].song.getVolume())
		{
			playFirstTrack(ID, loop);
		}
		else
		{
			playSecondTrack(ID, loop);
		}
	}

	_dmessage("Music Player:\tEnd Play. Track Status\n\t\tTrack 0: " << track[0].song.getStatus());
	_dmessage("\n\t\tTack 1: " << track[1].song.getStatus() << std::endl);
}

/*-------------------------------------------------------
* CLASS       : MUSICPLAYER
* METHOD      : stop
* DESCRIPTION : Stop playing the music.
*--------------------------------------------------------*/
void MusicPlayer::stop()
{
	for (int i = 0; i < 2; ++i)
	{
		assert(i == 0 || i == 1);

		if (volumeFade)
		{
			if (track[i].song.getStatus() == sf::Music::Playing)
			{
				track[i].fadeState = Track::TransitionState::FADE_OUT;
			}
			else
			{
				track[i].song.stop();
			}
		}
		else
		{
			track[i].song.stop();
		}
	}
}

/*-------------------------------------------------------
* CLASS       : MUSICPLAYER
* METHOD      : setVolume
* DESCRIPTION : Change the max volume
*--------------------------------------------------------*/
void MusicPlayer::setMaxVolume(const float volume)
{
	maxVolume = volume;

	for (int i = 0; i < 2; ++i)
	{
		assert(i == 0 || i == 1);
		
		// Change volume only if the track is currently playing
		if (track[i].song.getStatus() == sf::Music::Playing)
		{
			if (track[i].song.getVolume() > maxVolume)
			{
				// Fade out lowers volume to 0 and stops it, so just set new volume immediately.
				track[i].song.setVolume(maxVolume);
			}
			else
			{
				// Current volume is less than new max, pump it up
				if (volumeFade)
				{
					track[i].fadeState = Track::TransitionState::FADE_IN;
				}
				else
				{
					track[i].song.setVolume(maxVolume);
				}
			}
		}
	}
}

/*-------------------------------------------------------
* CLASS       : MUSICPLAYER
* METHOD      : updateFadeIn
* DESCRIPTION : Used by update to increase volume
*--------------------------------------------------------*/
void MusicPlayer::updateFadeIn(Track & track, const float significantVolume, const float fadeRate)
{
	float newVolume = track.song.getVolume();

	// Choose increment value depending if significant volume has been reached
	if (track.song.getVolume() < significantVolume)
	{
		newVolume = std::min(maxVolume, newVolume + fadeRate);
	}
	else
	{
		newVolume = std::min(maxVolume, newVolume + 1);
	}

	// Assign the new volume and stop fading if max volume is reached
	track.song.setVolume(newVolume);

	_dmessage("Music Player:\tFade in\n\t\tVolume: " << newVolume << std::endl);

	if (floatCompare(track.song.getVolume(), maxVolume))
	{
		track.fadeState = Track::TransitionState::NONE;
		_dmessage("Music Player:\tFade in\n\t\tDONE\n");
	}
}

/*-------------------------------------------------------
* CLASS       : MUSICPLAYER
* METHOD      : updateFadeOut
* DESCRIPTION : Used by update to decrease volume and stop song
*--------------------------------------------------------*/
void MusicPlayer::updateFadeOut(Track & track, const float significantVolume, const float fadeRate)
{
	float newVolume = track.song.getVolume();

	// Choose decrement value depending if significant volume has been reached
	if (track.song.getVolume() < significantVolume)
	{
		newVolume = std::max(0.f, newVolume - fadeRate);
	}
	else
	{
		newVolume = std::max(0.f, newVolume - 1);
	}

	// Assign the new volume and stop song if volume 0 is reached
	track.song.setVolume(newVolume);
	_dmessage("Music Player:\tFade out\n\t\tVolume: " << newVolume << std::endl);

	if (floatCompare(track.song.getVolume(), 0.f))
	{
		track.fadeState = Track::TransitionState::NONE;
		track.song.stop();
		_dmessage("Music Player:\tFade out\n\t\tDONE\n");
	}
}

/*-------------------------------------------------------
* CLASS       : MUSICPLAYER
* METHOD      : update
* DESCRIPTION : Apply volume fading effects each frame
*--------------------------------------------------------*/
void MusicPlayer::update(sf::Time dt)
{
	// Volume fading seemed hard to notice after a volume of about 20 when incrementing.
	// So I applied the calculated fade rate only up to a volume of 20, afterward it is
	// incremented by 1 each call.
	const float significantVolume = 20.f;
	const float time = dt.asSeconds() / fadeDuration.asSeconds();
	const float fadeRate = significantVolume * time;

	for (int i = 0; i < 2; ++i)
	{
		assert(i == 0 || i == 1);

		if (track[i].fadeState == Track::TransitionState::FADE_IN)
		{
			_dmessage("Music Player: Fading in track " << i << std::endl);

			updateFadeIn(track[i], significantVolume, fadeRate);
		}
		else if (track[i].fadeState == Track::TransitionState::FADE_OUT)
		{
			_dmessage("Music Player: Fading out track " << i << std::endl);

			updateFadeOut(track[i], significantVolume, fadeRate);
		}
	}
}