#pragma once

enum class WINDCOMPATTR {
	WCA_UNDEFINED = 0,
	WCA_USEDARKMODECOLORS = 26,
	WCA_LAST = 27
};
struct WINDCOMPATTRDATA {
	WINDCOMPATTR Attrib;
	PVOID pvData;
	SIZE_T cbData;
};

typedef BOOL(WINAPI* SetWindowCompositionAttribute_t)(HWND hWnd, WINDCOMPATTRDATA*);
typedef int(WINAPI* ShowCursor_t)(BOOL bShow);
typedef BOOL(WINAPI* SetCursorPos_t)(int X, int Y);
typedef BOOL(WINAPI* SetWindowPos_t)(HWND hWnd, HWND hWndInsertAfter, int X, int Y, int cx, int cy, UINT uFlags);
typedef LRESULT(WINAPI* SendMessageA_t)(HWND hWnd, UINT Msg, WPARAM wParam, LPARAM lParam);
typedef int(WINAPI* DrawTextA_t)(HDC hdc, LPCSTR lpchText, int cchText, LPRECT lprc, UINT format);
typedef COLORREF(WINAPI* GetPixel_t)(HDC hdc, int x, int y);

extern SetWindowCompositionAttribute_t SetWindowCompositionAttribute;
extern ShowCursor_t ShowCursor_Og;
extern SetCursorPos_t SetCursorPos_Og;
extern SetWindowPos_t SetWindowPos_Og;
extern SendMessageA_t SendMessageA_Og;
extern DrawTextA_t DrawTextA_Og;
extern GetPixel_t GetPixel_Og;

namespace d2gl::win32 {

void initHooks();
void destroyHooks();

int WINAPI ShowCursor(BOOL bShow);
BOOL WINAPI SetCursorPos(int X, int Y);
BOOL WINAPI SetWindowPos(HWND hWnd, HWND hWndInsertAfter, int X, int Y, int cx, int cy, UINT uFlags);
LRESULT WINAPI SendMessageA(HWND hWnd, UINT Msg, WPARAM wParam, LPARAM lParam);
int WINAPI DrawTextA(HDC hdc, LPCSTR lpchText, int cchText, LPRECT lprc, UINT format);
COLORREF WINAPI GetPixel(HDC hdc, int x, int y);
LRESULT CALLBACK WndProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam);

void setWindow(HWND hwnd);
void setWindowRect();
void setWindowMetricts();
void setCursorLock();
void setCursorUnlock();
void windowResize();
void toggleDarkmode();

}