#include "music.h"

void music::play(int vol)
{
	mciSendStringA("open \"youneuoy_Data\\music\\m2tweop.mp3\" type mpegvideo alias mp3", NULL, 0, NULL);
	mciSendStringA("play mp3", NULL, 0, NULL);
	setVolume(vol);

}

void music::setVolume(int vol)
{
	string volume = "setaudio mp3 volume to ";
	volume += to_string(vol);
	mciSendStringA(volume.c_str(), nullptr, 0, nullptr);
}
