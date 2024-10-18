#pragma once

#include "stb_image.h"

#include "Shader.hpp"

#ifndef TEXTURE_HPP
#define TEXTURE_HPP

class Texture {
public:
	unsigned int id;

	Texture(const char* path, const long channels);
	void use(int unit);
};

#endif