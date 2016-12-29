#include <iostream>
#include <windows.h>
//---
#include "header\SDL2\SDL.h"


int xpy(int x, int y);

bool quit = false;

LRESULT CALLBACK WinProc(HWND window, UINT message, WPARAM wParam, LPARAM lParam);
void Render_ClearScreen(SDL_Renderer* renderer);

//MAIN
int CALLBACK WinMain(
  HINSTANCE hInstance,
  HINSTANCE hPrevInstance,
  LPSTR     lpCmdLine,
  int       nCmdShow
)
{
	WNDCLASSEX windowclass = {};
	windowclass.cbSize = sizeof(WNDCLASSEX);
	windowclass.style = CS_HREDRAW | CS_VREDRAW;
	windowclass.lpfnWndProc = WinProc;
	windowclass.hInstance = hInstance;
	windowclass.lpszClassName = "winClass";

	RegisterClassEx(&windowclass);

	int window_width = 640;
	int window_height = 480;
	int monitor_width = GetSystemMetrics(SM_CXSCREEN);
	int monitor_height = GetSystemMetrics(SM_CYSCREEN);
	HWND window = CreateWindowEx(
		WS_EX_ACCEPTFILES,
		windowclass.lpszClassName,
		"Sentience",
		WS_OVERLAPPEDWINDOW,
		(monitor_width / 2) - (window_width / 2),
		(monitor_height / 2) - (window_height / 2),
		window_width, window_height,
		NULL, NULL,
		hInstance,
		NULL
		);

	if(SDL_Init(SDL_INIT_EVERYTHING) < 0)
	{
		MessageBox(window, "Could not initialize SDL", "Failure!", MB_OK | MB_ICONWARNING);
	}
	else
	{
		SDL_Window* sdl_window = SDL_CreateWindowFrom(window);
		if(sdl_window == 0)
		{
			MessageBox(window, "Could not create SDL window!", "Failure!", MB_OK | MB_ICONWARNING);
		}
		else
		{
			//MessageBox(window, "Created SDL window!", "Success!", MB_OK);

			SDL_Renderer * g_renderer = SDL_CreateRenderer(sdl_window, -1, SDL_RENDERER_ACCELERATED);
			if(g_renderer == 0)
			{
				MessageBox(window, "Could not create renderer!", "Failure!", MB_OK | MB_ICONWARNING);
			}
			else
			{
				//MessageBox(window, "Created renderer!", "Success!", MB_OK);
				Render_ClearScreen(g_renderer);
				SDL_RenderPresent(g_renderer);
				ShowWindow(window, SW_SHOW);
				
				while(!quit)
				{
					MSG message;
					PeekMessage(&message, window, 0, 0, PM_REMOVE);
					TranslateMessage(&message);
					DispatchMessage(&message);

					//render stuff
					Render_ClearScreen(g_renderer);

					SDL_RenderPresent(g_renderer);
				}
			}
		}
	}

	return 0;
}
//--

//Window Process
LRESULT CALLBACK WinProc(
	HWND window,
	UINT message,
	WPARAM wParam,
	LPARAM lParam
	)
{
	LRESULT result;
	switch(message)
	{
		case(WM_DESTROY):
		{
			quit = true;
			break;
		}
		default:
		{
			result = DefWindowProc(window, message, wParam, lParam);
		}
	}

	return result;
}
//--


int xpy(int x, int y)
{
	return (x * y) / 100;
}

void Render_ClearScreen(SDL_Renderer* renderer)
{
	SDL_SetRenderDrawColor(renderer, 0, 0, 0, 0);

	SDL_RenderClear(renderer);
}