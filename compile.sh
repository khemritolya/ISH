#!/bin/bash
sudo rm -f $1.out
g++ $1.cpp -o $1.out
sudo chmod +x $1.out
