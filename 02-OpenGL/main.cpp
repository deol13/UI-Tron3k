//--------------------------------------------------------------------------------------
// BTH - Stefan Petersson 2014.
//--------------------------------------------------------------------------------------
#include <windows.h>

#include <gl/glew.h>
#include <gl/GL.h>

#pragma comment(lib, "opengl32.lib")
#pragma comment(lib, "glew32.lib")

#include "Render.h"
#include "Vertex.h"
#include "TestClass.h"

HWND InitWindow(HINSTANCE hInstance);
LRESULT CALLBACK WndProc(HWND, UINT, WPARAM, LPARAM);
HGLRC CreateOpenGLContext(HWND wndHandle);

void testData();

#define BUFFER_OFFSET(i) ((char *)nullptr + (i))

Render* render;

/*****************Test**********************/
TestClass tester[5];
Vertex objOne[4];
Vertex objTwo[4];
Vertex objThree[4];
Vertex objFour[4];
Vertex objFive[4];

int idTexList[5] = { 0, 2, 0, 1, 1 };
/*******************************************/

void SetViewport()
{
	glViewport(0, 0, 640, 480);
}

int WINAPI wWinMain( HINSTANCE hInstance, HINSTANCE hPrevInstance, LPWSTR lpCmdLine, int nCmdShow )
{
	_CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);

	MSG msg = { 0 };
	HWND wndHandle = InitWindow(hInstance); //1. Skapa f�nster
	
	if (wndHandle)
	{
		HDC hDC = GetDC(wndHandle);
		HGLRC hRC = CreateOpenGLContext(wndHandle); //2. Skapa och koppla OpenGL context

		glewInit(); //3. Initiera The OpenGL Extension Wrangler Library (GLEW)

		SetViewport(); //4. S�tt viewport

		/************Test to see if the program works***********/
		//testData();
		
		render = new Render();
		render->init(tester);
		render->newBuffers(5, idTexList);
		/*******************************************************/


		ShowWindow(wndHandle, nCmdShow);

		while (WM_QUIT != msg.message)
		{
			if (PeekMessage(&msg, nullptr, 0, 0, PM_REMOVE))
			{
				if (msg.message == MK_LBUTTON)
				{
					POINT newMpos;
					GetCursorPos(&newMpos);
					render->mouseClick(newMpos.x, newMpos.y);
				}
				else
				{
					POINT newMpos;
					GetCursorPos(&newMpos);
					render->mouseHoverCheck(newMpos.x, newMpos.y);
				}
				TranslateMessage(&msg);
				DispatchMessage(&msg);
			}
			else
			{
				glClearColor(0, 0, 0, 1);
				glClear(GL_COLOR_BUFFER_BIT);

				render->uiRenderPass();

				SwapBuffers(hDC); //10. V�xla front- och back-buffer
			}
		}

		delete render;
		wglMakeCurrent(NULL, NULL);
		ReleaseDC(wndHandle, hDC);
		wglDeleteContext(hRC);
		DestroyWindow(wndHandle);
	}

	return (int) msg.wParam;
}

HWND InitWindow(HINSTANCE hInstance)
{
	WNDCLASSEX wcex = { 0 };
	wcex.cbSize = sizeof(WNDCLASSEX); 
	wcex.style          = CS_HREDRAW | CS_VREDRAW;
	wcex.lpfnWndProc    = WndProc;
	wcex.hInstance      = hInstance;
	wcex.lpszClassName = L"BTH_GL_DEMO";
	if( !RegisterClassEx(&wcex) )
		return false;

	RECT rc = { 0, 0, 640, 480 };
	AdjustWindowRect( &rc, WS_OVERLAPPEDWINDOW, FALSE );
	
	HWND handle = CreateWindow(
		L"BTH_GL_DEMO",
		L"BTH OpenGL Demo",
		WS_OVERLAPPEDWINDOW,
		CW_USEDEFAULT,
		CW_USEDEFAULT,
		rc.right - rc.left,
		rc.bottom - rc.top,
		nullptr,
		nullptr,
		hInstance,
		nullptr);

	return handle;
}

LRESULT CALLBACK WndProc( HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam )
{
	switch (message) 
	{
	case WM_DESTROY:
		PostQuitMessage(0);
		break;		
	}

	return DefWindowProc(hWnd, message, wParam, lParam);
}

HGLRC CreateOpenGLContext(HWND wndHandle)
{
	//get handle to a device context (DC) for the client area
	//of a specified window or for the entire screen
	HDC hDC = GetDC(wndHandle);

	//details: http://msdn.microsoft.com/en-us/library/windows/desktop/dd318286(v=vs.85).aspx
	static  PIXELFORMATDESCRIPTOR pixelFormatDesc =
	{
		sizeof(PIXELFORMATDESCRIPTOR),    // size of this pfd  
		1,                                // version number  
		PFD_DRAW_TO_WINDOW |              // support window  
		PFD_SUPPORT_OPENGL |              // support OpenGL  
		PFD_DOUBLEBUFFER |                // double buffered
		PFD_DEPTH_DONTCARE,               // disable depth buffer <-- added by Stefan
		PFD_TYPE_RGBA,                    // RGBA type  
		32,                               // 32-bit color depth  
		0, 0, 0, 0, 0, 0,                 // color bits ignored  
		0,                                // no alpha buffer  
		0,                                // shift bit ignored  
		0,                                // no accumulation buffer  
		0, 0, 0, 0,                       // accum bits ignored  
		0,                                // 0-bits for depth buffer <-- modified by Stefan      
		0,                                // no stencil buffer  
		0,                                // no auxiliary buffer  
		PFD_MAIN_PLANE,                   // main layer  
		0,                                // reserved  
		0, 0, 0                           // layer masks ignored  
	};

	//attempt to match an appropriate pixel format supported by a
	//device context to a given pixel format specification.
	int pixelFormat = ChoosePixelFormat(hDC, &pixelFormatDesc);

	//set the pixel format of the specified device context
	//to the format specified by the iPixelFormat index.
	SetPixelFormat(hDC, pixelFormat, &pixelFormatDesc);

	//create a new OpenGL rendering context, which is suitable for drawing
	//on the device referenced by hdc. The rendering context has the same
	//pixel format as the device context.
	HGLRC hRC = wglCreateContext(hDC);
	
	//makes a specified OpenGL rendering context the calling thread's current
	//rendering context. All subsequent OpenGL calls made by the thread are
	//drawn on the device identified by hdc. 
	wglMakeCurrent(hDC, hRC);

	return hRC;
}


//void testData()
//{
//	objOne[0] = Vertex(-1.0f, 1.0f, 0.0f, 0.0f, 1.0f);
//	objOne[1] = Vertex(-1.0f, 0.75f, 0.0f, 0.0f, 0.0f);
//	objOne[2] = Vertex(-0.75f, 1.0f, 0.0f , 1.0f, 1.0f);
//	objOne[3] = Vertex(-0.75f, 0.75f, 0.0f, 1.0f, 0.0f);
//
//	objTwo[0] = Vertex(-0.125f, 0.125f, 0.0f, 0.0f, 1.0f);
//	objTwo[1] = Vertex(-0.125f, -0.125f, 0.0f, 0.0f, 0.0f);
//	objTwo[2] = Vertex(0.125f, 0.125f, 0.0f, 1.0f, 1.0f);
//	objTwo[3] = Vertex(0.125f, -0.125f, 0.0f, 1.0f, 0.0f);
//
//	objThree[0] = Vertex(0.75f, -0.75f, 0.0f, 0.0f, 1.0f);
//	objThree[1] = Vertex(0.75f, -1.0f, 0.0f, 0.0f, 0.0f);
//	objThree[2] = Vertex(1.0f, -0.75f, 0.0f, 1.0f, 1.0f);
//	objThree[3] = Vertex(1.0f, -1.0f, 0.0f, 1.0f, 0.0f);
//
//	objFour[0] = Vertex(0.75f, 1.0f, 0.0f, 0.0f, 1.0f);
//	objFour[1] = Vertex(0.75f, 0.75f, 0.0f, 0.0f, 0.0f);
//	objFour[2] = Vertex(1.0f, 1.0f, 0.0f, 1.0f, 1.0f);
//	objFour[3] = Vertex(1.0f, 0.75f, 0.0f, 1.0f, 0.0f);
//
//	objFive[0] = Vertex(-1.0f, -0.75f, 0.0f, 0.0f, 1.0f);
//	objFive[1] = Vertex(-1.0f, -1.0f, 0.0f, 0.0f, 0.0f);
//	objFive[2] = Vertex(-0.75f, -0.75f, 0.0f, 1.0f, 1.0f);
//	objFive[3] = Vertex(-0.75f, -1.0f, 0.0f, 1.0f, 0.0f);
//	
//	tester[0].init(objOne);
//	tester[1].init(objTwo);
//	tester[2].init(objThree);
//	tester[3].init(objFour);
//	tester[4].init(objFive);
//}