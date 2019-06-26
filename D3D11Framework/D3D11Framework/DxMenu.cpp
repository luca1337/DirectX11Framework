#include "DxMenu.h"

#include "Device.h"
#include "Engine.h"

#include "imgui/imgui.h"
#include "imgui/imgui_impl_dx11.h"
#include "imgui/imgui_impl_win32.h"

DxMenu::DxMenu()
{

}

DxMenu & DxMenu::Get()
{
	// TODO: inserire l'istruzione return qui

	static DxMenu* dx_menu = nullptr;

	if (!dx_menu)
	{
		dx_menu = new DxMenu();
	}

	return *dx_menu;
}

void DxMenu::Initialize(HWND hwnd)
{
	IMGUI_CHECKVERSION();
	ImGui::CreateContext();
	ImGuiIO io = ImGui::GetIO(); (void)io;

	ImGui::StyleColorsDark();

	ImGui_ImplWin32_Init(hwnd);
	ImGui_ImplDX11_Init(Engine::Singleton().GetDxDevice()->GetDXHandle(), Engine::Singleton().GetDxDevice()->GetDXContext());

}

void DxMenu::Render()
{
	ImGui_ImplDX11_NewFrame();
	ImGui_ImplWin32_NewFrame();
	ImGui::NewFrame();


	ImGui_ImplDX11_RenderDrawData(ImGui::GetDrawData());
}

void DxMenu::CleanUp()
{
	ImGui_ImplDX11_Shutdown();
	ImGui_ImplWin32_Shutdown();
	ImGui::DestroyContext();
}
