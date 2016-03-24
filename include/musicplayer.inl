/*-------------------------------------------------------
* CLASS       : MUSICPLAYER
* METHOD      : setFadeSpeed
* DESCRIPTION : How long does a fade transition last?
*--------------------------------------------------------*/
inline void MusicPlayer::setFadeSpeed(const sf::Time duration)
{
	fadeDuration = duration;
}

/*-------------------------------------------------------
* CLASS       : MUSICPLAYER
* METHOD      : setVolumeFading
* DESCRIPTION : Activate or deactivate volume fading effects
*--------------------------------------------------------*/
inline void MusicPlayer::setVolumeFading(bool fade)
{
	volumeFade = fade;
}

/*-------------------------------------------------------
* CLASS       : MUSICPLAYER
* METHOD      : getMaxVolume
* DESCRIPTION : Returns the max volume music is playing
*--------------------------------------------------------*/
inline float MusicPlayer::getMaxVolume() const
{
	return maxVolume;
}

/*-------------------------------------------------------
* CLASS       : MUSICPLAYER
* METHOD      : getFadeSpeed
* DESCRIPTION : Returns the duration volume fades last
*--------------------------------------------------------*/
inline sf::Time MusicPlayer::getFadeSpeed() const
{
	return fadeDuration;
}

/*-------------------------------------------------------
* CLASS       : MUSICPLAYER
* METHOD      : getVolumeFading
* DESCRIPTION : Returns if volume fading is activated
*--------------------------------------------------------*/
inline bool MusicPlayer::getVolumeFading() const
{
	return volumeFade;
}