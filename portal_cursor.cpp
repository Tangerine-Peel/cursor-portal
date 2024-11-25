#include <Windows.h>
#include <string>
#include <sstream>
#include <cmath>
#define TIMER_ID 1  // 定时器ID
#define REFRESH_INTERVAL 2000  // 刷新间隔（毫秒）

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nShowCmd) {
    //ShowMonitorInfoWindow();
    while (true) {
        POINT cursorPos;
        GetCursorPos(&cursorPos);

        /*if (cursorPos.x == 2559) {
            // 从 2559 切换到 2561
            float ratio = static_cast<float>(cursorPos.y) / 1440.0f; // 比例计算
            int newY = static_cast<int>(std::floor(ratio * 2560.0f - 1137.0f)); // 计算新的 y 值并向下取整
            SetCursorPos(2561, newY);
        }
        else */if (cursorPos.x == 2560 && cursorPos.y < 0) {
        // 从 2561 切换到 2559
            float ratio = static_cast<float>(cursorPos.y + 1137) / 2560.0f; // 比例计算
            int newY = static_cast<int>(std::floor(ratio * 1440.0f)); // 计算新的 y 值并向下取整
            SetCursorPos(2559, newY);
        }
        //检测鼠标状态，如果是拖动，则等上一秒看是不是想要吸附在上面

        Sleep(1); // 减少 CPU 占用，避免频繁跳动
    }

    return 0;
}

