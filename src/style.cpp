#include "include/style.hpp"

#include "../vendor/include/imgui/imgui.h"

static ImVec4 hexToNormalizedRgb(unsigned int hex) {
    return ImVec4(
        ((hex >> 24) & 0xff) / 255.0f,
        ((hex >> 16) & 0xff) / 255.0f,
        ((hex >> 8 ) & 0xff) / 255.0f,
        ((hex      ) & 0xff) / 255.0f
    );
}

void app::styleApply() {
    ImGuiStyle &style = ImGui::GetStyle();

    style.WindowRounding = 0.0f;
    style.FrameRounding = 0.0f;
    style.ScrollbarRounding = 0.0f;
    style.TabRounding = 0.0f;
    style.GrabRounding = 0.0f;
    style.ChildRounding = 0.0f;
    style.PopupRounding = 0.0f;

    style.Colors[ImGuiCol_Text] =                       hexToNormalizedRgb(0xcdd6f4ff);
    style.Colors[ImGuiCol_TextDisabled] =               hexToNormalizedRgb(0xbac2deff);
    style.Colors[ImGuiCol_WindowBg] =                   hexToNormalizedRgb(0x181825ff);
    style.Colors[ImGuiCol_ChildBg] =                    hexToNormalizedRgb(0x181825ff);
    style.Colors[ImGuiCol_PopupBg] =                    hexToNormalizedRgb(0x181825ff);
    style.Colors[ImGuiCol_Border] =                     hexToNormalizedRgb(0x313244ff);
    style.Colors[ImGuiCol_BorderShadow] =               hexToNormalizedRgb(0x181825ff);
    style.Colors[ImGuiCol_FrameBg] =                    hexToNormalizedRgb(0x1e1e2eff);
    style.Colors[ImGuiCol_FrameBgHovered] =             hexToNormalizedRgb(0x313244ff);
    style.Colors[ImGuiCol_FrameBgActive] =              hexToNormalizedRgb(0x313244ff);
    style.Colors[ImGuiCol_TitleBg] =                    hexToNormalizedRgb(0x1e1e2eff);
    style.Colors[ImGuiCol_TitleBgActive] =              hexToNormalizedRgb(0x313244ff);
    style.Colors[ImGuiCol_TitleBgCollapsed] =           hexToNormalizedRgb(0x1e1e2eff);
    style.Colors[ImGuiCol_MenuBarBg] =                  hexToNormalizedRgb(0x181825ff);
    style.Colors[ImGuiCol_ScrollbarBg] =                hexToNormalizedRgb(0x181825ff);
    style.Colors[ImGuiCol_ScrollbarGrab] =              hexToNormalizedRgb(0x1e1e2eff);
    style.Colors[ImGuiCol_ScrollbarGrabHovered] =       hexToNormalizedRgb(0x313244ff);
    style.Colors[ImGuiCol_ScrollbarGrabActive] =        hexToNormalizedRgb(0x6c7086ff);
    style.Colors[ImGuiCol_CheckMark] =                  hexToNormalizedRgb(0x89dcebff);
    style.Colors[ImGuiCol_SliderGrab] =                 hexToNormalizedRgb(0xa6adc8ff);
    style.Colors[ImGuiCol_SliderGrabActive] =           hexToNormalizedRgb(0x6c7086ff);
    style.Colors[ImGuiCol_Button] =                     hexToNormalizedRgb(0x1e1e2eff);
    style.Colors[ImGuiCol_ButtonHovered] =              hexToNormalizedRgb(0x313244ff);
    style.Colors[ImGuiCol_ButtonActive] =               hexToNormalizedRgb(0x6c7086ff);
    style.Colors[ImGuiCol_Header] =                     hexToNormalizedRgb(0x181825ff);
    style.Colors[ImGuiCol_HeaderHovered] =              hexToNormalizedRgb(0x313244ff);
    style.Colors[ImGuiCol_HeaderActive] =               hexToNormalizedRgb(0x6c7086ff);
    style.Colors[ImGuiCol_Separator] =                  hexToNormalizedRgb(0x1e1e2eff);
    style.Colors[ImGuiCol_SeparatorHovered] =           hexToNormalizedRgb(0x1e1e2eff);
    style.Colors[ImGuiCol_SeparatorActive] =            hexToNormalizedRgb(0x1e1e2eff);
    style.Colors[ImGuiCol_ResizeGrip] =                 hexToNormalizedRgb(0x1e1e2eff);
    style.Colors[ImGuiCol_ResizeGripHovered] =          hexToNormalizedRgb(0x89dcebff);
    style.Colors[ImGuiCol_ResizeGripActive] =           hexToNormalizedRgb(0x94e2d5ff);
    style.Colors[ImGuiCol_Tab] =                        hexToNormalizedRgb(0x1e1e2eff);
    style.Colors[ImGuiCol_TabHovered] =                 hexToNormalizedRgb(0x313244ff);
    style.Colors[ImGuiCol_TabSelected] =                hexToNormalizedRgb(0x89dcebff);
    style.Colors[ImGuiCol_TabSelectedOverline] =        hexToNormalizedRgb(0x313244ff);
    style.Colors[ImGuiCol_TabDimmed] =                  hexToNormalizedRgb(0x181825ff);
    style.Colors[ImGuiCol_TabDimmedSelected] =          hexToNormalizedRgb(0x1e1e2eff);
    style.Colors[ImGuiCol_TabDimmedSelectedOverline] =  hexToNormalizedRgb(0x313244ff);
    style.Colors[ImGuiCol_PlotLines] =                  hexToNormalizedRgb(0xbac2deff);
    style.Colors[ImGuiCol_PlotLinesHovered] =           hexToNormalizedRgb(0x89dcebff);
    style.Colors[ImGuiCol_PlotHistogram] =              hexToNormalizedRgb(0xbac2deff);
    style.Colors[ImGuiCol_PlotHistogramHovered] =       hexToNormalizedRgb(0x89dcebff);
    style.Colors[ImGuiCol_TableHeaderBg] =              hexToNormalizedRgb(0x181825ff);
    style.Colors[ImGuiCol_TableBorderStrong] =          hexToNormalizedRgb(0x313244ff);
    style.Colors[ImGuiCol_TableBorderLight] =           hexToNormalizedRgb(0x1e1e2eff);
    style.Colors[ImGuiCol_TableRowBg] =                 hexToNormalizedRgb(0x89dcebff);
    style.Colors[ImGuiCol_TableRowBgAlt] =              hexToNormalizedRgb(0x94e2d5ff);
    style.Colors[ImGuiCol_TextLink] =                   hexToNormalizedRgb(0x89dcebff);
    style.Colors[ImGuiCol_TextSelectedBg] =             hexToNormalizedRgb(0x94e2d5ff);
    style.Colors[ImGuiCol_DragDropTarget] =             hexToNormalizedRgb(0x89dcebff);
    style.Colors[ImGuiCol_NavCursor] =                  hexToNormalizedRgb(0x1e1e2eff);
    style.Colors[ImGuiCol_NavWindowingHighlight] =      hexToNormalizedRgb(0x313244ff);
    style.Colors[ImGuiCol_NavWindowingDimBg] =          hexToNormalizedRgb(0x1e1e2eff);
    style.Colors[ImGuiCol_ModalWindowDimBg] =           hexToNormalizedRgb(0x1e1e2eff);
}
