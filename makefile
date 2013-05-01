all:
	g++ start.cpp -o start `sdl-config --cflags --libs`
