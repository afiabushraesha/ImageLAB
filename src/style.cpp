#include "include/style.hpp"

#include "../vendor/include/imgui/imgui.h"
#include <iostream>

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

    std::cout << hexToNormalizedRgb(0xeee0b7ff).x << " " << hexToNormalizedRgb(0xeee0b7ff).y << " " << hexToNormalizedRgb(0xeee0b7ff).z <<  " " << hexToNormalizedRgb(0xeee0b7ff).w << std::endl;

    style.Colors[ImGuiCol_Text]                 = hexToNormalizedRgb(0x4f3829ff);
    style.Colors[ImGuiCol_TextDisabled]         = hexToNormalizedRgb(0x7c6f64ff);
    style.Colors[ImGuiCol_WindowBg]             = hexToNormalizedRgb(0xf3eac7ff);
    style.Colors[ImGuiCol_PopupBg]              = hexToNormalizedRgb(0xeee0b7ff);
    style.Colors[ImGuiCol_Border]               = hexToNormalizedRgb(0xebdbb2ff);
    style.Colors[ImGuiCol_BorderShadow]         = hexToNormalizedRgb(0xc54735ff);
    style.Colors[ImGuiCol_FrameBg]              = hexToNormalizedRgb(0xf2e5bcff);
    style.Colors[ImGuiCol_FrameBgHovered]       = hexToNormalizedRgb(0xeee0b7ff);
    style.Colors[ImGuiCol_FrameBgActive]        = hexToNormalizedRgb(0xf2e5bcff);
    style.Colors[ImGuiCol_TitleBg]              = hexToNormalizedRgb(0xebdbb2ff);
    style.Colors[ImGuiCol_TitleBgCollapsed]     = hexToNormalizedRgb(0xeee0b7ff);
    style.Colors[ImGuiCol_TitleBgActive]        = hexToNormalizedRgb(0xeee0b7ff);
    style.Colors[ImGuiCol_MenuBarBg]            = hexToNormalizedRgb(0xeee0b7ff);
    style.Colors[ImGuiCol_ScrollbarBg]          = hexToNormalizedRgb(0xf2e5bcff);
    style.Colors[ImGuiCol_ScrollbarGrab]        = hexToNormalizedRgb(0xebdbb2ff);
    style.Colors[ImGuiCol_ScrollbarGrabHovered] = hexToNormalizedRgb(0xeee0b7ff);
    style.Colors[ImGuiCol_ScrollbarGrabActive]  = hexToNormalizedRgb(0xeee0b7ff);
    style.Colors[ImGuiCol_CheckMark]            = hexToNormalizedRgb(0x4c7a5dff);
    style.Colors[ImGuiCol_SliderGrab]           = hexToNormalizedRgb(0xebdbb2ff);
    style.Colors[ImGuiCol_SliderGrabActive]     = hexToNormalizedRgb(0xebdbb2ff);
    style.Colors[ImGuiCol_Button]               = hexToNormalizedRgb(0xe4edc8ff);
    style.Colors[ImGuiCol_ButtonHovered]        = hexToNormalizedRgb(0xdde5c2ff);
    style.Colors[ImGuiCol_ButtonActive]         = hexToNormalizedRgb(0x6f8352ff);
    style.Colors[ImGuiCol_Header]               = hexToNormalizedRgb(0xe4edc8ff);
    style.Colors[ImGuiCol_HeaderHovered]        = hexToNormalizedRgb(0xdde5c2ff);
    style.Colors[ImGuiCol_HeaderActive]         = hexToNormalizedRgb(0x6f8352ff);
    style.Colors[ImGuiCol_ResizeGrip]           = hexToNormalizedRgb(0xdde5c2ff);
    style.Colors[ImGuiCol_ResizeGripHovered]    = hexToNormalizedRgb(0x6f8352ff);
    style.Colors[ImGuiCol_ResizeGripActive]     = hexToNormalizedRgb(0x4c7a5dff);
    style.Colors[ImGuiCol_PlotLines]            = hexToNormalizedRgb(0x45707aff);
    style.Colors[ImGuiCol_PlotLinesHovered]     = hexToNormalizedRgb(0x6c782eff);
    style.Colors[ImGuiCol_PlotHistogram]        = hexToNormalizedRgb(0x45707aff);
    style.Colors[ImGuiCol_PlotHistogramHovered] = hexToNormalizedRgb(0x6c782eff);
    style.Colors[ImGuiCol_TextSelectedBg]       = hexToNormalizedRgb(0xd9e1ccff);
}
