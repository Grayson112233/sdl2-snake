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

void place_apple() {

	apple.x = rand() % GRID_SIZE;
	apple.y = rand() % GRID_SIZE;

}

void init_game() {

	num_segments = 0;
	head.x = GRID_SIZE/2;
	head.y = GRID_SIZE/2;
	place_apple();
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

void step() {

	// Move tail
	int next_x = head.x;
	int next_y = head.y;
	for(int i = 0; i < num_segments; i++) {
		int temp_x = tail[i].x;
		int temp_y = tail[i].y;
		tail[i].x = next_x;
		tail[i].y = next_y;
		next_x = temp_x;
		next_y = temp_y;
	}
	
	// Move in direction
	if(dir == 0) { head.y -= 1; }
	else if(dir == 1) { head.x += 1; }
	else if(dir == 2) { head.y += 1; }
	else if(dir == 3) { head.x -= 1; }

	if(head.x < 0 || head.x > GRID_SIZE - 1 || head.y < 0 || head.y > GRID_SIZE - 1) {
		num_segments = 0;
		head.x = GRID_SIZE/2;
		head.y = GRID_SIZE/2;
	}

	// Check for tail collision
	for(int i = 0; i < num_segments; i++) {
		if(head.x == tail[i].x && head.y == tail[i].y) {
			num_segments = 0;
			head.x = GRID_SIZE/2;
			head.y = GRID_SIZE/2;
			break;
		}
	}

	// Check for apple
	if(head.x == apple.x && head.y == apple.y) {

		// Insert new tail segment
		if(num_segments == 0) {
			tail[0].x = head.x;
			tail[0].y = head.y;
			num_segments = 1;
		} else {
			tail[num_segments].x = tail[num_segments-1].x;
			tail[num_segments].y = tail[num_segments-1].y;
			num_segments ++;
		}

		place_apple();
	}

}

int main() {

	// Initialize random seed
	srand(time(NULL));

	bool loop = true;
	int last_step_time = SDL_GetTicks();

	init_game();

	while(loop) {

		inputs.update();
		loop = !inputs.get_quit();

		handle_inputs();

		int current_time = SDL_GetTicks();
		if(current_time - last_step_time >= DELAY) {
			step();
			last_step_time = current_time;
		}

		graphics.clear_screen();
		graphics.render_apple(apple);
		graphics.render_segments(head, tail, num_segments);
		graphics.present_renderer();

	}

}