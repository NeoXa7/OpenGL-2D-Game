
#define STB_IMAGE_IMPLEMENTATION
#include <libs/stb_image.h>
#include "pch.h"

#include <renderer/renderer.h>
#include <utils/logger.h>
#include <utils/console/console.h>

#include <game/game.h>
#include <game/sprite/sprite.h>

#include <game/gui/gui.h>

// looks shit in fullscreen 

int main() {
	Renderer::OpenGL renderer("Fortnite", 800, 600);
	Game game(renderer.GetTitle());
	ISoundEngine* sound_engine = createIrrKlangDevice();

	Console::CreateConsoleWindow("Debug-Console");

	renderer.InitializeOpenGL();	
	renderer.SetupViewport();
	renderer.InitializeGLAD();
	renderer.EnableVSync(1);
	renderer.EnableAlphaChannel(1);

	game.SetRenderer(&renderer);
	game.SetSoundEngine(sound_engine);
	game.SetMenuKey(GLFW_KEY_INSERT);
	game.Initialize();

	gui::init(&renderer);

	while (renderer.IsRendererRunning()) {
		renderer.Tick();
		renderer.ProcessBasicInputs(); 
		renderer.SetupWindowStyles(Color(25, 25, 25, 255));
		renderer.UpdateFramebufferSize();

		game.ProcessInputs();
		game.Update();

		gui::setup_new_frames(); 

		gui::set_up_viewport_rendering("game");

		game.Render();

		gui::end_viewport_rendering();

		gui::render();
		renderer.SwapAndPoll();
	}

	Console::DestroyConsoleWindow();
	renderer.Shutdown();
	gui::shutdown();
	return 0;
}
