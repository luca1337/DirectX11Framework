#pragma once

struct IDXGIAdapter1;

class Adapter
{
public:
	Adapter();

	IDXGIAdapter1* GetDXHandle();

private:
	IDXGIAdapter1* adapter;
};