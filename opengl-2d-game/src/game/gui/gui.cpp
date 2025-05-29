#include <pch.h>
#include "gui.h"


Renderer::OpenGL* gui::renderer;

gui::gui() {}
gui::~gui() {}

void gui::init(Renderer::OpenGL* target_renderer) {
    renderer = target_renderer;
    IMGUI_CHECKVERSION();
    ImGui::CreateContext();
    ImGuiIO& io = ImGui::GetIO();
    ImGui::StyleColorsDark();
    ImGui_ImplGlfw_InitForOpenGL(renderer->GetWindowContext(), true);
    ImGui_ImplOpenGL3_Init("#version 330");
	io.Fonts->AddFontFromFileTTF("assets/fonts/fat.ttf", 15.0f);
	io.Fonts->Build();
}

void gui::setup_new_frames() {
    ImGui_ImplOpenGL3_NewFrame();
    ImGui_ImplGlfw_NewFrame();
    ImGui::NewFrame();
}

void gui::render() {
    ImGui::Render();
    ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
}

void gui::shutdown() {
    ImGui_ImplOpenGL3_Shutdown();
    ImGui_ImplGlfw_Shutdown();
    ImGui::DestroyContext();
}

void gui::set_up_viewport_rendering(const char* name) {
	ImGui::GetStyle().Colors[ImGuiCol_WindowBg].w = 0.0f;

	ImGui::SetNextWindowSize(ImVec2(renderer->GetWidth(), renderer->GetHeight()));
	ImGui::SetNextWindowPos(ImVec2(0, 0));

	ImGui::Begin(name, nullptr,
		ImGuiWindowFlags_NoTitleBar |
		ImGuiWindowFlags_NoResize |
		ImGuiWindowFlags_NoMove |
		ImGuiWindowFlags_NoCollapse |
		ImGuiWindowFlags_NoScrollbar |
		ImGuiWindowFlags_NoScrollWithMouse |
		ImGuiWindowFlags_NoBringToFrontOnFocus |
		ImGuiWindowFlags_NoNavFocus |
		ImGuiWindowFlags_NoDecoration
	);
}

void gui::end_viewport_rendering() {
	ImGui::End();
}

void gui::text(const char* text, ImColor color) {
	ImGui::TextColored(color, text);
}

bool gui::Button(const char* label, float width, float height, ImColor button_text_color, ImColor button_color, ImColor button_hover_color) {
	static std::unordered_map<ImGuiID, float> hoverAnimMap;

	std::string fullLabel(label);
	std::string visibleLabel = fullLabel.substr(0, fullLabel.find("##"));

	ImGui::PushID(label);

	ImVec2 cursor = ImGui::GetCursorScreenPos();
	ImGui::InvisibleButton(label, ImVec2(width, height));

	bool hovered = ImGui::IsItemHovered();
	bool clicked = ImGui::IsItemClicked();
	ImGuiID id = ImGui::GetID(label);

	float& anim = hoverAnimMap[id];
	float speed = 6.0f * ImGui::GetIO().DeltaTime;
	anim = ImClamp(anim + (hovered ? speed : -speed), 0.0f, 1.0f);

	ImVec4 base = ImLerp(button_color.Value, button_hover_color.Value, anim);
	ImColor bg = ImColor(base);

	ImDrawList* DrawList = ImGui::GetBackgroundDrawList(); 
	DrawList->AddRectFilled(cursor, ImVec2(cursor.x + width, cursor.y + height), bg, 6.0f);

	// Draw centered label text
	ImVec2 textSize = ImGui::CalcTextSize(visibleLabel.c_str());
	ImVec2 textPos = ImVec2(
		cursor.x + (width - textSize.x) * 0.5f,
		cursor.y + (height - textSize.y) * 0.5f
	);
	DrawList->AddText(textPos, button_text_color, visibleLabel.c_str());

	ImGui::PopID();
	return clicked;
}

bool gui::checkbox(const char* label, bool* value)
{
	return ImGui::Checkbox(label, value);
}
