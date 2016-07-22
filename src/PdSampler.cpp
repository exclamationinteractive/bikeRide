#include "PdSampler.h"

//--------------------------------------------------------------
PdSampler::PdSampler(){
	sender.setup(HOST, PORT);
}

void PdSampler::setSong(int _player, int _song){
  ofxOscMessage m;
  m.setAddress("/sampler/load");
  m.addIntArg(_player);
  m.addIntArg(_song);
  sender.sendMessage(m, false);
}

void PdSampler::setGain(int _player, float _gain, int _time){
  ofxOscMessage m;
  m.setAddress("/sampler/gain");
  m.addIntArg(_player);
  m.addFloatArg(_gain);
  m.addIntArg(_time);
  sender.sendMessage(m, false);
}

void PdSampler::cueTrack(int _player, float _cuePoint){
  ofxOscMessage m;
  m.setAddress("/sampler/cue");
  m.addIntArg(_player);
  m.addFloatArg(_cuePoint);
  sender.sendMessage(m, false);
}

void PdSampler::setBikeSpeed(float _bikeSpeed){
  ofxOscMessage m;
  m.setAddress("/bike/speed");
  m.addFloatArg(_bikeSpeed);
  sender.sendMessage(m, false);
}

void PdSampler::setBikeSteering(float _bikeSteering){
  ofxOscMessage m;
  m.setAddress("/bike/steering");
  m.addFloatArg(_bikeSteering);
  sender.sendMessage(m, false);
}
