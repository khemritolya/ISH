#!/bin/bash
rm -f $1.out
g++ $1.cpp -o $1.out
chmod +x $1.out
