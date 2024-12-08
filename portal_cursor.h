#pragma once
#ifndef MONITOR_INFO_H
#define MONITOR_INFO_H

#include <Windows.h>
#include <string>
#include <sstream>
#include <cmath>
#define TIMER_ID 1  // 定时器ID
#define REFRESH_INTERVAL 2000  // 刷新间隔（毫秒）

// 函数声明
BOOL CALLBACK MonitorEnumProc(HMONITOR hMonitor, HDC hdcMonitor, LPRECT lprcMonitor, LPARAM dwData);
std::wstring GetMonitorInfoText();
LRESULT CALLBACK WindowProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam);
void ShowMonitorInfoWindow();

class Rectangle {};
#endif // MONITOR_INFO_H
