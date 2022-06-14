#pragma once

#include "SDL.h"
#include "Room.h"


class Ball
{
public:
	Ball(double radius, Room* room);

	void Reset();
	virtual void Update(double timestep_s);
	void Launch(double initial_force_x, double initial_force_y);


	void velocity(double x, double y) { v_[0] = x; v_[1] = y; }
	double radius() const { return radius_; }
	double mass() const { return mass_; }
	double coeff_of_restitution() { return coeff_of_restitution_; }

	double pos_x() const { return p_[0]; }
	double pos_y() const { return p_[1]; }

protected:
	Room* room_;
	
	double radius_;	// meter
	double mass_;	// kg
	double coeff_of_restitution_; // from 0 o 1
	double frictional_force_;

	// position
	double p_[2];	// x, y
	double predicted_p_[2];

	// velocity
	double v_[2];	// x, y
	double predicted_v_[2];
};

