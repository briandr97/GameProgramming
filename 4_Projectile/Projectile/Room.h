#pragma once

#include "SDL.h"



class Room 
{
public:
	Room();

	double width() const { return width_; }
	double height() const { return height_; }
	double left_wall_x() const { return -1*width_/2.; }
	double right_wall_x() const { return width_ / 2.; }
	double ground_height() const { return 0; }
	double gravitational_acc_y() const { return gravitational_acc_y_; }

	// Fence
	double vertiacal_fence_pos_x() const { return vertical_fence_pos_x_; }
	double vertiacal_fence_height() const { return vertical_fence_height_; }
	

protected:
	
	double width_;
	double height_;


	// Fence
	double vertical_fence_pos_x_;
	double vertical_fence_height_;

	double gravitational_acc_y_;
	
};

