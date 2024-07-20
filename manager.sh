#!/bin/bash

error() {
	msg="$1"
	echo -e "\e[31m$msg\e[0m"
}

commit() {
	msg="$1"
	git add .
	git commit -m "$msg"
}

#------------------------------------------------------------------------ end of Libs

EXECUTABLE="./bin/app"
SRC="./src/*.cpp"
INCLUDE="./include/"
LIB="./lib/"
FLAGS="-lportaudio -lsfml-graphics -lsfml-window -lsfml-system"

run() {
	if [ ! -f "$EXECUTABLE" ]; then
		error "Error: $EXECUTABLE not found."
		return
	fi
	$EXECUTABLE
}

clean() {
	if [ ! -f "$EXECUTABLE" ]; then
		return
	fi
	rm $EXECUTABLE
}

build() {
	g++ $SRC -o $EXECUTABLE -I$INCLUDE -L$LIB $FLAGS
}

main() {
	for callback in "$@"; do
		if declare -f "$callback" > /dev/null; then
			"$callback"
		else
			error "Error: Function '$callback' not found."
		fi
	done
}

main "$@"
