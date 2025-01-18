#pragma once
#ifndef MONITOR_INFO_H
#define MONITOR_INFO_H

#include <Windows.h>
#include <windows.h>
#include <string>
#include <sstream>
#include <cmath>
#include <vector>
#include <stdexcept>
#define TIMER_ID 1  // 定时器ID
#define REFRESH_INTERVAL 2  // 刷新间隔（毫秒）

using std::vector;
using std::pair;

BOOL CALLBACK MonitorEnumProc(HMONITOR hMonitor, HDC hdcMonitor, LPRECT lprcMonitor, LPARAM dwData);//解析获取到的信息

std::wstring GetMonitorInfoText(); //获取屏幕信息

LRESULT CALLBACK WindowProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam);// 窗口创建，处理信号，销毁窗口

void ShowMonitorInfoWindow();//注册窗口类

class Rectangle {
	private:
		std::vector <std::pair<int, int>> monitor;
	public:
		Rectangle();
		void set_monitor(std::vector <std::pair<int, int>> &monitor);
		vector <std::pair<int, int>>print_monitor();
};//屏幕对象 //刷新按钮更新对象信息
#endif // MONITOR_INFO_H
