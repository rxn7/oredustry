#/bin/sh

pushd bin/linux>/dev/null
./oredustry
if [ "$?" -ne 0 ]; then
	echo "Failed to run oredustry!"
fi
popd>/dev/null
