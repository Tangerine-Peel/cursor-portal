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
#define TIMER_ID 1  // ��ʱ��ID
#define REFRESH_INTERVAL 2  // ˢ�¼�������룩

using std::vector;
using std::pair;

BOOL CALLBACK MonitorEnumProc(HMONITOR hMonitor, HDC hdcMonitor, LPRECT lprcMonitor, LPARAM dwData);//������ȡ������Ϣ

std::wstring GetMonitorInfoText(); //��ȡ��Ļ��Ϣ

LRESULT CALLBACK WindowProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam);// ���ڴ����������źţ����ٴ���

void ShowMonitorInfoWindow();//ע�ᴰ����

class Rectangle {
	private:
		std::vector <std::pair<int, int>> monitor;
	public:
		Rectangle();
		void set_monitor(std::vector <std::pair<int, int>> &monitor);
		vector <std::pair<int, int>>print_monitor();
};//��Ļ���� //ˢ�°�ť���¶�����Ϣ
#endif // MONITOR_INFO_H
