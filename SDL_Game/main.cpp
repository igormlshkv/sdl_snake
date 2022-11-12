#include <SDL.h>
#include <vector>
#include <deque>
#include <algorithm>

int main(int argc, char* argv[]) {
	SDL_Init(SDL_INIT_VIDEO);
	SDL_Window* window = SDL_CreateWindow( "snejk", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 
		800, 800, SDL_WINDOW_BORDERLESS);
	SDL_Renderer* renderer = SDL_CreateRenderer(window, -1, 0);
	SDL_Event event; 
	int dir = 0;
	int last_dir = 0;
	bool is_head = 1;

	SDL_Rect snake_head{ 400,400,40,40 };
	std::deque <SDL_Rect> snake_body;
	unsigned int snake_length = 1; 
	SDL_Rect apple{ rand() % 20 * 40, rand() % 20 * 40, 40, 40 };
	/*SDL_Surface* image = SDL_LoadBMP("");
	SDL_Texture* texture = SDL_CreateTextureFromSurface(renderer,image);*/

	while (1) {
		while (SDL_PollEvent(&event)) { 
			if (event.type == SDL_KEYDOWN) {
				switch (event.key.keysym.sym) {
				case SDLK_DOWN:
					if (last_dir != 3) {
						dir = 0;
						last_dir = 0;

					}
					break;
				case SDLK_LEFT:
					if (last_dir != 2) {
						dir = 1;
						last_dir = 1;

					}
					break;
				case SDLK_RIGHT:
					if (last_dir != 1) {
						dir = 2;
						last_dir = 2;
					}
					break;
				case SDLK_UP:
					if (last_dir != 0) {
						dir = 3;
						last_dir = 3;
					}
					break;
				}
			}
			else if (event.type == SDL_QUIT) return 0;
		}

		switch (dir) {   
		case 0:
			snake_head.y += 40;
			break;
		case 1:
			snake_head.x -= 40;
			break;
		case 2:
			snake_head.x += 40;
			break;
		case 3:
			snake_head.y -= 40;
			break;
		}

		SDL_SetRenderDrawColor(renderer, 3, 252, 115, 255);
		SDL_RenderClear(renderer);
		
		SDL_SetRenderDrawColor(renderer, 168, 50, 70, 255);
		SDL_RenderFillRect(renderer, &apple);

		if (snake_head.x == apple.x && snake_head.y == apple.y) {
			snake_length += 1;
			apple.x = rand() % 20 * 40;
			apple.y = rand() % 20 * 40;
		}
		
		std::for_each(snake_body.begin(), snake_body.end(), [&](SDL_Rect& p_snake_body) {
			if (snake_head.x == p_snake_body.x && snake_head.y == p_snake_body.y && snake_length>=5)
			{
				SDL_Delay(1000);
				snake_length = 1;
				snake_head.x = 400;
				snake_head.y = 400;
			}
		});

		if (snake_head.x <0 || snake_head.x>800 || snake_head.y < 0 || snake_head.y>800)
		{	
			SDL_Delay(1000);
			snake_length = 1;
			snake_head.x = 400;
			snake_head.y = 400;
		}
	
		snake_body.push_front(snake_head);
		while (snake_body.size() > snake_length) {
			snake_body.pop_back();
		}

		is_head = 1;
		std::for_each(snake_body.begin(), snake_body.end(), [&](auto& p_snake_body) {
			if (is_head) {
				SDL_SetRenderDrawColor(renderer, 161, 3, 252, 255);
				SDL_RenderFillRect(renderer, &p_snake_body);
				is_head = 0;

			}
			else {
				SDL_SetRenderDrawColor(renderer, 3, 127, 252, 255);
				SDL_RenderFillRect(renderer, &p_snake_body);

			}
		});

		SDL_RenderPresent(renderer);
		SDL_Delay(80);
	}
	return 0;
}