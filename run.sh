#/bin/sh

[ -f "./bin/oredustry" ] || make

pushd bin
./oredustry
popd
