#pragma once
#ifndef MONITOR_INFO_H
#define MONITOR_INFO_H

#include <Windows.h>
#include <string>
#include <sstream>
#include <cmath>
#define TIMER_ID 1  // ��ʱ��ID
#define REFRESH_INTERVAL 2000  // ˢ�¼�������룩

BOOL CALLBACK MonitorEnumProc(HMONITOR hMonitor, HDC hdcMonitor, LPRECT lprcMonitor, LPARAM dwData);//������ȡ������Ϣ

std::wstring GetMonitorInfoText(); //��ȡ��Ļ��Ϣ

LRESULT CALLBACK WindowProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam);// ���ڴ����������źţ����ٴ���

void ShowMonitorInfoWindow();//ע�ᴰ����

class Rectangle {};//��Ļ���� //ˢ�°�ť���¶�����Ϣ
#endif // MONITOR_INFO_H
