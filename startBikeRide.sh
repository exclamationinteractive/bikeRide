#/bin/bash
qjackctl --preset bikeRide --start &
pdextended -jack pdOSCsampler/OSC_sampler_patch.pd &
./bin/bikeRide &
