#pragma once

#include "Core.h"

class DxMenu
{
public:
	static DxMenu& Get();

	void Initialize(HWND hwnd);

	void Render();

	void CleanUp();

private:
	DxMenu();
};