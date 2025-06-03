#include "Commandlet.h"
#include "StringUtils.h"

constexpr int LINE_HEIGHT = 18;
constexpr int LINE_MARGIN_V = 15;
constexpr int LINE_MARGIN_H = 20;

Commandlet::Commandlet(HINSTANCE hInstance) : assistant()
{
    hBrush = CreateSolidBrush(RGB(30, 30, 30));

    WCHAR szWindowClass[] = L"CommandletWnd";

    WNDCLASS wc = {};
	wc.lpfnWndProc = StaticWndHandle;
	wc.hInstance = hInstance;
	wc.lpszClassName = szWindowClass;
    wc.hbrBackground = hBrush;
    RegisterClass(&wc);

    int screenWidth = GetSystemMetrics(SM_CXSCREEN);
    int screenHeight = GetSystemMetrics(SM_CYSCREEN);
    int width = screenWidth / 3;
    int height = LINE_HEIGHT + LINE_MARGIN_V * 2;

    hWnd = CreateWindowExW(
        WS_EX_TOOLWINDOW,
        szWindowClass,
        L"CmdAssist",
        WS_POPUP,
        screenWidth / 3, screenHeight / 4, width, height,
        nullptr, nullptr, hInstance, nullptr
    );
    DWM_WINDOW_CORNER_PREFERENCE Corners = DWMWCP_ROUND;
    DwmSetWindowAttribute(hWnd, DWMWA_WINDOW_CORNER_PREFERENCE, &Corners, sizeof(DWM_WINDOW_CORNER_PREFERENCE));
    SetWindowLongPtr(hWnd, GWLP_USERDATA, (LONG_PTR)this);

    isVisible = false;
}

Commandlet::~Commandlet()
{

}

void Commandlet::Toggle()
{
    if (isVisible)
    {
        ShowWindow(hWnd, SW_HIDE);
        isVisible = false;
    }
    else
    {
        ShowWindow(hWnd, SW_SHOW);
        SetWindowPos(hWnd, HWND_TOPMOST, 0, 0, 0, 0, SWP_NOMOVE | SWP_NOSIZE | SWP_SHOWWINDOW);
        UpdateWindow(hWnd);
        SetForegroundWindow(hWnd);
        SetActiveWindow(hWnd);
        SetFocus(hWnd);
        isVisible = true;
    }
}

bool Commandlet::WndHandle(UINT message, WPARAM wParam, LPARAM lParam)
{
    switch (message)
    {
        case WM_CREATE:
        {
            CreateCaret(hWnd, NULL, 2, 16);
            ShowCaret(hWnd);
            return true;
        }
        case WM_ACTIVATE:
        {
            if (LOWORD(wParam) == WA_INACTIVE)
            {
                ShowWindow(hWnd, SW_HIDE);
                isVisible = false;
                return true;
            }
        }
        case WM_PAINT:
        {
            PAINTSTRUCT ps;
            HDC hdc = BeginPaint(hWnd, &ps);

            SetTextColor(hdc, RGB(255, 255, 255));
            SetBkMode(hdc, TRANSPARENT);

            TextOutA(hdc, LINE_MARGIN_H, LINE_MARGIN_V, text.c_str(), text.size());

            SIZE size;
            GetTextExtentPoint32A(hdc, text.c_str(), caretPos, &size);
            SetCaretPos(LINE_MARGIN_H + size.cx, LINE_MARGIN_V);

            EndPaint(hWnd, &ps);
            return true;
        }
        case WM_CHAR:
        {
            if (wParam >= 32 && wParam <= 126) { // Printable chars
                text.insert(caretPos, 1, (wchar_t)wParam);
                caretPos++;
            }
            else
            {
                break;
            }
            Repaint();
            return true;
        } 
        case WM_KEYDOWN:
        {
            switch (wParam)
            {
                case VK_LEFT:
                {
                    if (Ctrl()) 
                    {
                        caretPos = MoveToPreviousWord(text, caretPos);
                    }
                    else
                    {
                        if (caretPos > 0)
                        {
                            caretPos--;
                        }
                    }
                    Repaint();
                    return true;
                }
				case VK_RIGHT:
				{
                    if (Ctrl())
                    {
						caretPos = MoveToNextWord(text, caretPos);
                    }
                    else
                    {
                        if (caretPos < text.size())
                        {
                            caretPos++;
                        }
                    }
                    Repaint();
                    return true;
				}
                case VK_RETURN:
                {
                    text = assistant.Execute(text);
                    caretPos = text.length();
                    Repaint();
                    return true;
                }
                case VK_BACK:
                {
                    if (Ctrl())
                    {
                        DeleteWordBackward(text, caretPos);
                    }
                    else
                    {
                        if (caretPos > 0) {
                            text.erase(caretPos - 1, 1);
                            caretPos--;
                        }
                    }
                    Repaint();
                    return true;
                }
                case VK_DELETE:
                {
                    if (Ctrl())
                    {
                        DeleteWordForward(text, caretPos);
                    }
                    else
                    {
                        if (caretPos < text.length())
                        {
                            text.erase(caretPos, 1);
                        }
                    }
                    Repaint();
                    return true;
                }
                case VK_ESCAPE:
                {
                    ShowWindow(hWnd, SW_HIDE);
                    text.clear();
                    caretPos = 0;
                    Repaint();
                    isVisible = false;
                    return true;
                }
            }
        }
        case WM_SETFOCUS:
        {
            CreateCaret(hWnd, NULL, 2, 16);
            ShowCaret(hWnd);
            Repaint();
            return true;
        }
        case WM_KILLFOCUS:
        {
            HideCaret(hWnd);
            DestroyCaret();
            Repaint();
            return true;
        }
    }
    return false;
}

bool Commandlet::Ctrl()
{
    return (GetKeyState(VK_CONTROL) & 0x8000) != 0;
}

void Commandlet::Repaint()
{
    InvalidateRect(hWnd, nullptr, true);
}

LRESULT Commandlet::StaticWndHandle(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
    if (Commandlet* pThis = reinterpret_cast<Commandlet*>(GetWindowLongPtr(hWnd, GWLP_USERDATA))) {
        if (pThis->WndHandle(message, wParam, lParam)) {
            return 1;
        }
    }
    return DefWindowProc(hWnd, message, wParam, lParam);
}
