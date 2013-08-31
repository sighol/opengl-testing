#! /bin/bash

src="$(pwd)"
build="$src/build"

compile() {
	cd $build
	make $@
	back
}

reset() {
	cd $build
	rm -rf *
	cmake ..
	back
}

run() {
	cd $build
	make
	back
	optirun ./build/$1
}
