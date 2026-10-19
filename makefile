all:
	g++ -o term -Isrc \
		src/Entry.cpp src/Terminal.cpp \
		src/dir/Directory.cpp src/dir/RootDirectory.cpp \
		src/file/MultilineFile.cpp src/file/SinglelineFile.cpp \
		src/functions.cpp src/main.cpp