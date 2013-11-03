#include "partikls.h"

#include <cmath>
#include <SDL/SDL.h>

#include <iostream>

void Partikls::add(const Partikl& p) {
	partikls.push_back(p);
}

void Partikls::draw(SDL_Surface* display) {
	for(std::vector<Partikl>::iterator it = partikls.begin(); it != partikls.end(); ++it) { 
		it->draw(display);
	}
}

void Partikls::update() {
	for(std::vector<Partikl>::iterator it = partikls.begin(); it != partikls.end(); ++it) {
		bool stillAlive = it->update();
		if(!stillAlive)
			partikls.erase(it--);
	}

	for(std::vector<Partikl>::iterator it = partikls.begin(); it != partikls.end(); ++it) {
		if(it->mass != 0.f) {
			float ax = 0.f, ay = 0.f;
			for(std::vector<Partikl>::iterator partner_it = partikls.begin(); partner_it != partikls.end(); ++partner_it) {
				if(partner_it != it && partner_it->mass != 0.f) {
					const float dx = it->x - partner_it->x;
					const float dy = it->y - partner_it->y;

					const unsigned int rsquare = dx * dx + dy * dy;
					if(rsquare == 0)
						continue;
					const float angle = atan2(dx, dy);

					const float f = partner_it->mass * it->mass / rsquare;
					const float a = f / it->mass;

					ax -= std::sin(angle) * a;
					ay -= std::cos(angle) * a;
				}
			}

			it->vx += ax;
			it->vy += ay;
		}
	}
}

