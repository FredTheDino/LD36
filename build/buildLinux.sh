#!/bin/bash

echo "              Cmake"
echo ""

cmake ../src

echo ""
echo "               Make"
echo ""

make

echo ""
echo "             Program"

./game/game