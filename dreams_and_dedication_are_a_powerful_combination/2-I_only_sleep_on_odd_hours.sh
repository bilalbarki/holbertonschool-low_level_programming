#!/bin/bash
if (( $1 % 2 == 0 ))
then
    echo "Heh?"
elif (( $1 % 2 == 1 ))
then
    echo "Sleep time!"
fi
