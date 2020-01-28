#pragma once
#include <stb_image.h>
#include <string>
#include <stdexcept>

struct pixels {
	//having this as a struct is quite unnecessary but the code has been built on the fact that it is so it is very hard to change
	stbi_uc* pixels;
	int texWidth, texHeight, texChannels;

	inline void read_file(std::string file) {
		pixels = stbi_load(file.c_str(), &texWidth, &texHeight, &texChannels, STBI_rgb_alpha);

		if (!pixels) {
			throw std::runtime_error("failed to load texture image!");
		}
	}
};
