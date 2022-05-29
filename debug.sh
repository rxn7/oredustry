make -f linux.mk OUT="bin/debug/oredustry" OBJ_DIR="obj/debug/linux" GDB_FLAGS="-g"
cp ./res ./bin/debug/ -r
pushd bin/debug
gdb ./oredustry
popd
