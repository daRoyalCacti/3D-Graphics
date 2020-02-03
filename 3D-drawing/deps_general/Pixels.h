#pragma once
#include <string>
#include <stdexcept>
#include <iostream>

struct pixels {
	//having this as a struct is quite unnecessary but the code has been built on the fact that it is so it is very hard to change
	uint8_t* pixels;
	int texWidth, texHeight;//, texChannels;

	/*inline void read_file(std::string file) {
		pixels = stbi_load(file.c_str(), &texWidth, &texHeight, &texChannels, STBI_rgb_alpha);

		//std::cout << texWidth << " " << texHeight << " " << texChannels << std::endl;

		if (!pixels) {
			throw std::runtime_error("failed to load texture image!");
		}
	}*/
};
