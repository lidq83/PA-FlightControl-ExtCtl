#!/bin/bash

#8M
sudo rm -rf /data/mnt/x/*
sudo umount /data/mnt/x
sudo mkfs -q /dev/ram0 8192
sudo mount /dev/ram0 /data/mnt/x
sudo chown -R lidq.lidq /data/mnt/x

df -h