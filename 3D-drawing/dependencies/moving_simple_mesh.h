#pragma once
#include "static_simple_mesh.h"
#include "vertex.h"
#include <vector>
#include <iostream>

struct moving_simple_mesh {
  //this is a thin wrapper around the static mesh to make using animated meshes easier to code
  //a lot of the initial setup is the same - just calling .Mesh.function() -- the only difference is for the 2 functions defined below
  //interpolation between frames might be added at somepoint
  staticSimpleMesh Mesh;
  bool modulous = false; //what to do if a frame of mesh being called is greater than the number of frames available
                        //true will make the animation repeat, false will make only the last frame show once completed
  unsigned frames = 1; //number of frames of animation - 1 frame makes it act as a static mesh

  moving_simple_mesh() {};
  moving_simple_mesh(bool _modulous, unsigned _frames = 1) : modulous(_modulous), frames(_frames){}
  std::vector<std::vector<Vertex>> Meshes; // this stores all the frames of animation
                                          // it might be better to store only the differences in frames to save on memory

	inline void createVertexBuffer(VkDevice device, VkCommandPool commandPool, VkQueue graphicsQueue, VkPhysicalDevice physicalDevice){
    //this function is a work around -- as seen in the line below
    Mesh.vertices = Meshes[0]; //<- is a work around and needs to be updated
  	Mesh.createVertexBuffer(device, commandPool, graphicsQueue, physicalDevice);
  }

	inline void updateVertexBuffer(VkDevice device, unsigned frameCounter, VkCommandPool commandPool, VkQueue graphicsQueue){
    //----------------------------------------------------------------------------------------------------------
    //the function is used to make drawing the animated meshes easier
    //there is no need to manually add a check to make sure the animation frame being requested is available
    // - this function will do this check in a way that is determined by the "modulous" variable
    //---------------------------------------------------------------------------------------------------------
   if (frameCounter >= frames) {
     if (modulous) {
       frameCounter %= (frames); // this is what will force the animation to repeat once it has finished
     } else {
       frameCounter = frames - 1; // once the animation is complete, only show the last frame
                                  // "-1" becasue it is used as an array index and arrays start from 0
     }
   }
   Mesh.updateVertexBuffer(device, Meshes[frameCounter], commandPool, graphicsQueue);
  }

};
