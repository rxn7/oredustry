# NOTE: This is only for WSL

#!/usr/bin/env bash
pushd bin/windows > /dev/null 2>&1
output=$(./oredustry.exe)
popd > /dev/null 2>&1
echo $output
