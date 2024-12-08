#include "portal_cursor.h"

int a = 0;//test value release should nor exit

BOOL CALLBACK MonitorEnumProc(HMONITOR hMonitor, HDC hdcMonitor, LPRECT lprcMonitor, LPARAM dwData) {
    MONITORINFOEX miex;
    POINT cursorPos;
    a++;
    miex.cbSize = sizeof(MONITORINFOEX);
    if (GetMonitorInfo(hMonitor, &miex)) {
        GetCursorPos(&cursorPos);
        std::wstringstream* monitorInfo = reinterpret_cast<std::wstringstream*>(dwData);
        *monitorInfo << L"Monitor: " << miex.szDevice << L"\r\n"
            << L"Mouse Position: (" << cursorPos.x << L", " << cursorPos.y << L")\r\n"
            << L"a: " << a << L"\r\n"
            << L"Monitor Area: (" << miex.rcMonitor.left << L", " << miex.rcMonitor.top << L") - "
            << L"(" << miex.rcMonitor.right << L", " << miex.rcMonitor.bottom << L")\r\n"
            << L"Work Area: (" << miex.rcWork.left << L", " << miex.rcWork.top << L") - "
            << L"(" << miex.rcWork.right << L", " << miex.rcWork.bottom << L")\r\n"
            << L"Primary: " << ((miex.dwFlags & MONITORINFOF_PRIMARY) ? L"Yes" : L"No") << L"\r\n\r\n";
    }
    return TRUE;
}

std::wstring GetMonitorInfoText() {
    std::wstringstream monitorInfo;
    monitorInfo << L"Connected Monitors Information:\n\n";
    EnumDisplayMonitors(NULL, NULL, MonitorEnumProc, reinterpret_cast<LPARAM>(&monitorInfo));
    return monitorInfo.str();
}

LRESULT CALLBACK WindowProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam) {
    static HWND hEdit;

    switch (uMsg) {
    case WM_CREATE: {
        // 创建 EDIT 控件
        hEdit = CreateWindowEx(
            0, L"EDIT", NULL,
            WS_CHILD | WS_VISIBLE | WS_VSCROLL | WS_HSCROLL | ES_MULTILINE | ES_READONLY,
            10, 10, 460, 340, hwnd, NULL, GetModuleHandle(NULL), NULL);

        // 设置定时器，每2秒触发一次
        SetTimer(hwnd, TIMER_ID, REFRESH_INTERVAL, NULL);

        // 初始化显示器信息
        std::wstring info = GetMonitorInfoText();
        SetWindowText(hEdit, info.c_str());
        return 0;
    }
    case WM_TIMER: {
        if (wParam == TIMER_ID) {
            // 定时器触发，刷新显示器信息
            std::wstring info = GetMonitorInfoText();
            SetWindowText(hEdit, info.c_str());
        }
        return 0;
    }
    case WM_DESTROY: {
        KillTimer(hwnd, TIMER_ID);  // 销毁定时器
        PostQuitMessage(0);  // 结束消息循环
        return 0;
    }
    }
    return DefWindowProc(hwnd, uMsg, wParam, lParam);
}

void ShowMonitorInfoWindow() {
    // 注册窗口类
    const wchar_t CLASS_NAME[] = L"MonitorInfoWindowClass";

    WNDCLASS wc = {};
    wc.lpfnWndProc = WindowProc;
    wc.hInstance = GetModuleHandle(NULL);
    wc.lpszClassName = CLASS_NAME;
    wc.hbrBackground = (HBRUSH)(COLOR_WINDOW + 1);  // 设置背景色
    wc.style = CS_HREDRAW | CS_VREDRAW;

    RegisterClass(&wc);

    // 创建主窗口
    HWND hwnd = CreateWindowEx(
        0, CLASS_NAME, L"Monitor Information",
        WS_OVERLAPPEDWINDOW | WS_VISIBLE,
        CW_USEDEFAULT, CW_USEDEFAULT, 500, 400,
        NULL, NULL, GetModuleHandle(NULL), NULL);

    if (!hwnd) return;

    // 显示窗口
    ShowWindow(hwnd, SW_SHOW);
    UpdateWindow(hwnd);

    // 消息循环
    MSG msg;
    while (GetMessage(&msg, NULL, 0, 0)) {
        TranslateMessage(&msg);
        DispatchMessage(&msg);
    }
}


int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nShowCmd) {
    //try make a window in order show monitors
    ShowMonitorInfoWindow();
    while (true) {
        POINT cursorPos;
        GetCursorPos(&cursorPos);

        if (cursorPos.x == 2560 && cursorPos.y < 0) {
        // 从 2561 切换到 2559
            float ratio = static_cast<float>(cursorPos.y + 1137) / 2560.0f; // 比例计算
            int newY = static_cast<int>(std::floor(ratio * 1440.0f)); // 计算新的 y 值并向下取整
            SetCursorPos(2559, newY);
        }
        //吸附功能待做：方案一：检测鼠标状态，如果是拖动，则等上一秒看是不是想要吸附在上面。方案二：设置一个区域不穿越。

        Sleep(1); // 减少 CPU 占用，避免频繁跳动
    }

    return 0;
}

