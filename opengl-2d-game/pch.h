// Standard libraries
#include <windows.h>
#include <d3d11.h>
#include <dxgi.h>
#include <string>
#include <vector>
#include <iostream>
#include <sstream>
#include <fstream>
#include <filesystem>
#include <thread>
#include <chrono>
#include <mutex>
#include <unordered_map>
#include <algorithm>
#include <functional>
#include <map>
#include <random>


// External libraries
// GLFW
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <GLFW/glfw3native.h>

#define GLM_ENABLE_EXPERIMENTAL

// MATHS
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtx/matrix_decompose.hpp>
#include <glm/gtc/type_ptr.hpp>

#include <irKlang/ik_ESoundEngineOptions.h>
#include <irKlang/irrKlang.h>

using namespace irrklang;