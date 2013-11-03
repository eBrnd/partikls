#include "partikls.h"

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
		bool stillAlive = it->update(partikls);
		if(!stillAlive)
			partikls.erase(it--);
	}

}

