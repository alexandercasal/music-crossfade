# music-crossfade
A basic music player that might be used in a game. It supports two music tracks, allowing the capability of crossfading between the two songs.
I made this while going through the book SFML Game Development by Jan Haller, Henrik Vogelius Hansson, and Artur Moreira.

I ran into an issue where I couldn't recognize the crossfade after a volume of about 20 (it was too subtle after that point).
The crossfade works by fading at a calculated interval until the significant volume (20) is reached, then it linearly in/decreases to 100 or 0 from that point.

Dependencies: SFML (www.sfml-dev.org)
