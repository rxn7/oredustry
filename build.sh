#!/usr/bin/env bash

PLATFORMS=("linux" "windows")

if [ "$#" -eq 1 ]; then
	PLATFORM=$1
else 
	printf "Available platforms: "
	for i in ${!PLATFORMS[@]}; do
		if [ "$(($i+1))" -ne ${#PLATFORMS[@]} ]; then
			printf "%s, " ${PLATFORMS[$i]}
		else
			echo ${PLATFORMS[$i]}
		fi

	done

	printf "\n"

	read -p "Platform: " PLATFORM
fi

make -f "$PLATFORM.mk"
cp ./res ./bin/$PLATFORM -r
