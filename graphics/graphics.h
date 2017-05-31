#ifndef GRAPHICS_H
#define GRAPHICS_H

#include <SDL2/SDL.h>
#include "../segment.h"
#include "../settings.h"

class Graphics {

	// Width and heigh of the window in px
	static const int WIDTH, HEIGHT;

	SDL_Window *window;
	SDL_Renderer *renderer;

	bool init_sdl();
	// Render segment square at pixel coordinates
	void render_square(int x, int y, int type);

public:
	Graphics();
	void clear_screen();
	void present_renderer(void);
	void render_segments(segment head, segment *tail, int num_segments);
	void render_apple(segment apple);
	int get_width();
	int get_height();
	~Graphics();
};

#endif