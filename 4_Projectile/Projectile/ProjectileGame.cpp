#include <iostream>
#include "ProjectileGame.h" 
#include "SDL_image.h"
#include "G2W.h"
#include "math.h"

extern int g_current_game_phase;
extern bool g_flag_running;
extern SDL_Renderer* g_renderer;
extern SDL_Window* g_window;
extern float g_timestep_s;



ProjectileGame::ProjectileGame()
{
	g_flag_running = true;


	// Texture
	{
		SDL_Surface* ball_surface = IMG_Load("../../Resources/ball.png");
		ball_src_rectangle_.x = 0;
		ball_src_rectangle_.y = 0;
		ball_src_rectangle_.w = ball_surface->w;
		ball_src_rectangle_.h = ball_surface->h;
		ball_texture_ = SDL_CreateTextureFromSurface(g_renderer, ball_surface);

		SDL_Surface* spot_surface = IMG_Load("../../Resources/spot.png");
		predicted_spot_rectangle_ = { 0,0,spot_surface->w, spot_surface->h };
		predicted_spot_texture_ = SDL_CreateTextureFromSurface(g_renderer, spot_surface);

		SDL_FreeSurface(ball_surface);
		SDL_FreeSurface(spot_surface);
	}


	// Initialize ball pointers
	for (int i = 0; i < MAX_BALL_NUM; i++)
	{
		balls_[i] = 0;
	}

	num_of_balls_ = 0;

	mouse_win_x_ = 0;
	mouse_win_y_ = 0;

	pre_mouse_x_ = 0;
	pre_mouse_y_ = 0;

	AddNewBall();
	//predicted_ball = new Ball(0.11f, &room_);
}



ProjectileGame::~ProjectileGame()
{
	// Delete balls
	for (int i = 0; i < MAX_BALL_NUM; i++)
	{
		if (balls_[i] != 0)
			delete balls_[i];

		balls_[i] = 0;
	}

	num_of_balls_ = 0;
	SDL_DestroyTexture(ball_texture_);
}


void
ProjectileGame::AddNewBall()
{
	if (num_of_balls_ == MAX_BALL_NUM) return;

	// Create new Ball
	Ball* ball = new Ball(0.11f, &room_);

	// Add to the list
	balls_[num_of_balls_] = ball;

	// Increase Num
	num_of_balls_++;

}


void
ProjectileGame::Update()
{

	// Update balls
	for (int i = 0; i < num_of_balls_; i++)
	{
		balls_[i]->Update(g_timestep_s);
	}


	//if ((pre_mouse_x_ != mouse_win_x_) || (pre_mouse_y_ != mouse_win_y_)) {
	//	double mouse_game_x = W2G_X(mouse_win_x_);
	//	double mouse_game_y = W2G_Y(mouse_win_y_);

	//	// Luanch
	//	// Guide Line Vector
	//	double guide_line_x = mouse_game_x - predicted_ball->pos_x();
	//	double guide_line_y = mouse_game_y - predicted_ball->pos_y();

	//	// Lauching Force
	//	double launcing_force_x = 8.0 * guide_line_x;
	//	double launcing_force_y = 8.0 * guide_line_y;

	//	// Launch
	//	predicted_ball->Launch(launcing_force_x, launcing_force_y);
	//}	
	//for (int i = 0; i < 6; i++) {
	//	predicted_ball->Update(g_timestep_s * 10);
	//	predicted_x[i] = predicted_ball->pos_x();
	//	predicted_y[i] = predicted_ball->pos_y();
	//	std::cout << i << "¹ø" << std::endl;
	//}
}

void
ProjectileGame::Render()
{
	SDL_SetRenderDrawColor(g_renderer, 255, 255, 255, 255);
	SDL_RenderClear(g_renderer); // clear the renderer to the draw color


	// Draw room_
	{
		SDL_SetRenderDrawColor(g_renderer, 0, 0, 0, 255);

		// Left Wall
		SDL_RenderDrawLine(g_renderer, G2W_X(room_.left_wall_x()),
			G2W_Y(0),
			G2W_X(room_.left_wall_x()),
			G2W_Y(room_.height()));


		// Right Wall
		SDL_RenderDrawLine(g_renderer, G2W_X(room_.right_wall_x()),
			G2W_Y(0),
			G2W_X(room_.right_wall_x()),
			G2W_Y(room_.height()));

		// Top Wall
		SDL_RenderDrawLine(g_renderer, G2W_X(room_.left_wall_x()),
			G2W_Y(room_.height()),
			G2W_X(room_.right_wall_x()),
			G2W_Y(room_.height()));

		// Bottom Wall
		SDL_RenderDrawLine(g_renderer, G2W_X(room_.left_wall_x()),
			G2W_Y(0),
			G2W_X(room_.right_wall_x()),
			G2W_Y(0));

		// Fence
		SDL_RenderDrawLine(g_renderer, G2W_X(room_.vertiacal_fence_pos_x()),
			G2W_Y(0),
			G2W_X(room_.vertiacal_fence_pos_x()),
			G2W_Y(room_.ground_height() + room_.vertiacal_fence_height()));
	}


	// Draw Balls
	for (int i = 0; i < num_of_balls_; i++)
	{
		Ball* ball = balls_[i];

		int ball_win_x = G2W_X(balls_[i]->pos_x());
		int ball_win_y = G2W_Y(balls_[i]->pos_y());

		double win_radius = G2W_Scale * balls_[i]->radius();

		SDL_Rect dest_rect;
		dest_rect.w = (int)(2 * win_radius);
		dest_rect.h = (int)(2 * win_radius);
		dest_rect.x = (int)(ball_win_x - win_radius);
		dest_rect.y = (int)(ball_win_y - win_radius);
		SDL_RenderCopy(g_renderer, ball_texture_, &ball_src_rectangle_, &dest_rect);
	}

	/*for (int i = 0; i < 6; i++) {
		int predicted_spot_x = G2W_X(predicted_x[i]);
		int predicted_spot_y = G2W_X(predicted_y[i]);
		double predicted_radius = G2W_Scale * predicted_ball->radius();
		SDL_Rect predicted_rect;
		predicted_rect.w = predicted_spot_rectangle_.w;
		predicted_rect.h = predicted_spot_rectangle_.h;
		predicted_rect.x = (int)(predicted_spot_x - predicted_radius);
		predicted_rect.y = (int)(predicted_spot_y - predicted_radius);
		SDL_RenderCopy(g_renderer, predicted_spot_texture_, &predicted_spot_rectangle_, &predicted_rect);
	}*/


	// Draw the Guide Line 
	if (num_of_balls_ > 0)
	{
		SDL_SetRenderDrawColor(g_renderer, 255, 0, 0, 100);
		SDL_RenderDrawLine(g_renderer, G2W_X(balls_[num_of_balls_ - 1]->pos_x()),
			G2W_Y(balls_[num_of_balls_ - 1]->pos_y()),
			mouse_win_x_,
			mouse_win_y_);
	}


	SDL_RenderPresent(g_renderer); // draw to the screen
}



void
ProjectileGame::HandleEvents()
{
	SDL_Event event;
	if (SDL_PollEvent(&event))
	{
		switch (event.type)
		{
		case SDL_QUIT:
			g_flag_running = false;
			break;

		case SDL_MOUSEBUTTONDOWN:

			// If the mouse left button is pressed. 
			if (event.button.button == SDL_BUTTON_LEFT)
			{
				// Get the cursor's x position.
				mouse_win_x_ = event.button.x;
				mouse_win_y_ = event.button.y;

				double mouse_game_x = W2G_X(mouse_win_x_);
				double mouse_game_y = W2G_Y(mouse_win_y_);


				// Luanch
				if (num_of_balls_ > 0)
				{
					Ball* ball = balls_[num_of_balls_ - 1];

					// Guide Line Vector
					double guide_line_x = mouse_game_x - ball->pos_x();
					double guide_line_y = mouse_game_y - ball->pos_y();

					// Lauching Force
					double launcing_force_x = 8.0 * guide_line_x;
					double launcing_force_y = 8.0 * guide_line_y;

					// Launch
					ball->Launch(launcing_force_x, launcing_force_y);


					// Add a new ball for the next
					AddNewBall();
				}
			}


		case SDL_MOUSEMOTION:
		{
			// Get the cursor's x position.
			mouse_win_x_ = event.button.x;
			mouse_win_y_ = event.button.y;
		}
		break;

		case SDL_KEYDOWN: {
			if (event.key.keysym.sym == SDLK_2) {
				big2small();
			}
			else if (event.key.keysym.sym == SDLK_1) {
				small2big();
			}
		}

		default:
			break;
		}
	}
}
