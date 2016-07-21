#pragma once

#include "ofMain.h"
#include "ofxOsc.h"

// perhaps move to json file...
#define HOST "localhost"
#define PORT 8888

class PdSampler{
  public:
		ofxOscSender sender;
    PdSampler();
    void setSong(int _player, int _song);
    void setGain(int _player, float _gain, int _time);
    void cueTrack(int _player, float _cuePoint);
    void setBikeSpeed(float _bikeSpeed);
    void setBikeSteering(float _bikeSteering);


};
