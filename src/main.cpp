/**
 * Platform Globals
 */
#include "summit_lib.h"

static bool running = true;

/**
 * Platform Functions
 */
bool platformCreateWindow(int width, int height, char *title);
void platformUpdateWindow();

/**
 * Windows Platform
 */
#ifdef _WIN32
#define WIN32_LEAN_AND_MEAN
#define NOMINMAX
#include <windows.h>

/**
 * Windows Globals
 */
static HWND window;

/**
 * Windows Platform Implementations
 */
LRESULT CALLBACK windowsWindowCallback(HWND window, UINT message, WPARAM wParam, LPARAM lParam)
{
    LRESULT result = 0;

    switch(message)
    {
        case WM_CLOSE:
        {
            running = false;
            break;
        }

        default:
        {
            result = DefWindowProcA(window, message, wParam,lParam);
        }
    }

    return result;
}

bool platformCreateWindow(int width, int height, char *title)
{
    HINSTANCE instance = GetModuleHandleA(0);

    WNDCLASSA windowClass = {};
    windowClass.hInstance = instance;
    windowClass.hIcon = LoadIcon(instance, IDI_APPLICATION);
    windowClass.hCursor = LoadCursor(NULL, IDC_ARROW);
    windowClass.lpszClassName = title;
    windowClass.lpfnWndProc = windowsWindowCallback;

    if (!RegisterClassA(&windowClass))
    {
        return false;
    }

    int dwStyle = WS_OVERLAPPEDWINDOW;

    window = CreateWindowExA(0, title, title, dwStyle, 100, 100, width, height, NULL, NULL, instance, NULL);

    if (window == NULL)
    {
        return false;
    }

    ShowWindow(window, SW_SHOW);

    return true;
}

void platformUpdateWindow()
{
    MSG message;

    while (PeekMessageA(&message, window, 0, 0, PM_REMOVE))
    {
        TranslateMessage(&message);
        DispatchMessageA(&message);
    }
}

#endif

int main()
{
    platformCreateWindow(1920, 1080, "Project Summit");

    while (running)
    {
        platformUpdateWindow();

        SM_TRACE("Trace");
        SM_WARNING("Warning");
        SM_ERROR("Error");
        SM_ASSERT(false, "Assertion not hit");
    }

    return 0;
}