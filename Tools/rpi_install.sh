#!/bin/bash
rm -vf ./build/rpi/lib/*
rm -vf ./build/rpi/pa3extctl
find ./build/ -name '*.so' | xargs -i cp -rvf {} ./build/rpi/lib/
cp ./build/pa3extctl ./build/rpi/

scp -r ./build/rpi pi@192.168.43.9:work/


