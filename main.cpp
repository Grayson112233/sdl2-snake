// Grayson Pike, 2017

#include <stdlib.h>
#include <time.h>
#include "graphics/graphics.h"
#include "input/inputs.h"
#include "segment.h"
#include "settings.h"

Inputs inputs;
Graphics graphics;

// Array to hold tail
segment tail[GRID_SIZE * GRID_SIZE];
int num_segments;

segment head;
segment apple;

// Direction of the head
// 0 to 3 (clockwise from upwards)
// Initially moving to the right
int dir;

void init_game() {

	num_segments = 0;
	head.x = 10;
	head.y = 10;
	apple.x = 0;
	apple.y = 0;
	dir = 1;

}

void handle_inputs() {

	if(inputs.is_key_down(KEY_MOVE_UP) && dir != 2) {
		dir = 0;
	}

	if(inputs.is_key_down(KEY_MOVE_DOWN) && dir != 0) {
		dir = 2;
	}

	if(inputs.is_key_down(KEY_MOVE_LEFT) && dir != 3) {
		dir = 3;
	}

	if(inputs.is_key_down(KEY_MOVE_RIGHT) && dir != 1) {
		dir = 1;
	}

}

int main() {

	// Initialize random seed
	srand(time(NULL));

	bool loop = true;

	init_game();

	while(loop) {

		inputs.update();
		loop = !inputs.get_quit();

		graphics.clear_screen();
		graphics.render_apple(apple);
		graphics.render_segments(head, tail, num_segments);
		graphics.present_renderer();

	}

}