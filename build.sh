#!/usr/bin/env bash

PLATFORM=""

build() {
	echo "Building for $PLATFORM..."
	CPUS=$(grep '^core id' /proc/cpuinfo | sort -u | wc -l)
	JOBS=$(echo "$CPUS * 1.5" | bc)
	JOBS=$(printf %.0f $JOBS)
	echo "Cores: $CPUS"
	echo "Jobs: $JOBS"
	make -f "$PLATFORM.mk" -j "$CPUS"
	cp ./res ./bin/$PLATFORM -r
}

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

time build

