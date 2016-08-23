#!/bin/bash

run() {
	echo "              Cmake"
	echo ""

	cmake -DCMAKE_BUILD_TYPE=Debug ../src 

	echo ""

	if [ $? -eq 0 ]; then
		echo "          Cmake succeded"
	else
		echo "         Cmake command failed"
		return
	fi

	echo ""
	echo "               Make"
	echo ""

	make

	if [ $? -eq 0 ]; then
		echo "         Make succeded"
	else
		echo "         Make command failed"
		return
	fi

	echo ""
	echo "             Program"

	./game/game
}

run
