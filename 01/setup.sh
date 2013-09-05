#! /bin/bash

src="$(pwd)"
build="$src/build"

compile() {
	cd $build
	make $@
	back
}

reset() {
	rm -rf $build
	mkdir $build
	cd $build
	cmake ..
	back
}

run() {
	cd $build
	make
	back
	cd $src;
	optirun ./build/$1
	back
}
