#pragma once

struct Color {
   float x, y, z, w;

   // Default constructor
   Color() : x(0), y(0), z(0), w(0) {}

   // Constructor with float parameters
   Color(float x, float y, float z, float w) {
       this->x = x / 255.0f;
       this->y = y / 255.0f;
       this->z = z / 255.0f;
       this->w = w / 255.0f;
   }

   // Constructor with int parameters
   Color(int x, int y, int z, int w) {
       this->x = x / 255.0f;
       this->y = y / 255.0f;
       this->z = z / 255.0f;
       this->w = w / 255.0f;
   }

   glm::vec4 Value4() {
       return glm::vec4(x, y, z, w);
   }
};