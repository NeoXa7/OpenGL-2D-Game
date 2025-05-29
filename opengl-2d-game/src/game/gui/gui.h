#pragma once
#include <libs/imgui/imgui.h>
#include <libs/imgui/imgui_impl_glfw.h>
#include <libs/imgui/imgui_impl_opengl3.h>
#include <libs/imgui/imgui_impl_opengl3_loader.h>
#include <libs/imgui/imgui_internal.h>

#include <renderer/renderer.h>

class gui {
private:
	static Renderer::OpenGL* renderer;
public:
	gui();
	~gui();

	static void init(Renderer::OpenGL* target_renderer);
	static void setup_new_frames();
	static void render();
	static void shutdown();
	static void set_up_viewport_rendering(const char* name);
	static void end_viewport_rendering();

	static void text(const char* text, ImColor color = ImColor(255, 255, 255, 255));
	static bool Button(
		const char* label,
		float width, float height,
		ImColor button_text_color = ImColor(250, 250, 250, 255),
		ImColor button_color = ImColor(244, 125, 93, 255),
		ImColor button_hover_color = ImColor(244, 125, 93, 200)
	);

	template <typename T>
	static bool slider(
		const char* title,
		T* value, T v_min, T v_max,
		float width = 150.0f, float height = 10.0f, 
		ImColor slider_fill_color = ImColor(192, 255, 140, 255), 
		ImColor slider_back_color = ImColor(255, 255, 255, 120)
	) {
		ImGui::PushID(title);
		
		ImGui::TextColored(ImColor(255, 255, 255, 255), title);
		ImGui::SameLine();

		if constexpr (std::is_integral<T>::value) {
			ImGui::TextColored(ImColor(255, 255, 255, 255), "(%d)", *value);
		}
		else {
			ImGui::TextColored(ImColor(255, 255, 255, 255), "(%.1f)", *value);
		}

		ImVec2 cursor_spos = ImGui::GetCursorScreenPos();
		float circle_height = 20.0f;


		ImGui::InvisibleButton(title, ImVec2(width, height));
		bool is_item_active = ImGui::IsItemActive();
		bool is_item_clicked = ImGui::IsItemClicked();

		if (is_item_active) {
			float mouse_pos = ImGui::GetMousePos().x - cursor_spos.x;
			float t = ImClamp(mouse_pos / width, 0.0f, 1.0f);
			float float_value = v_min + (v_max - v_min) * t;

			if constexpr (std::is_integral<T>::value) {
				*value = static_cast<T>(float_value + 0.5f); // round to nearest int
			}
			else {
				*value = static_cast<T>(float_value);
			}

			*value = ImClamp(*value, v_min, v_max);
		}

		ImGui::GetWindowDrawList()->AddRectFilled(cursor_spos, ImVec2(cursor_spos.x + width, cursor_spos.y + height), slider_back_color, height * 0.3f);
		float fill_width = (*value - v_min) / (float)(v_max - v_min) * width;
		ImGui::GetWindowDrawList()->AddRectFilled(
			cursor_spos,
			ImVec2(cursor_spos.x + fill_width, cursor_spos.y + height),
			IM_COL32(
				static_cast<int>(slider_fill_color.Value.x * 255.0f),
				static_cast<int>(slider_fill_color.Value.y * 255.0f),
				static_cast<int>(slider_fill_color.Value.z * 255.0f),
				(ImGui::IsItemActive() ? 255.0f : 200.0f)
			),
			5.0f
		);

		ImGui::PopID();
		return is_item_clicked;
	}


	static bool checkbox(const char* label, bool* value);
};
