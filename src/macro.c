#include <windows.h>
#include <stdio.h>

// 특정 클래스 이름을 가진 윈도우 핸들을 찾는 함수
HWND FindWindowByClass(const char* className, HWND parentHandle) {
    HWND hwnd = NULL;
    HWND tempHwnd = GetFirstChild(parentHandle);

    while (tempHwnd != NULL) {
        if (GetClassNameA(tempHwnd, className, sizeof(className))) {
            hwnd = tempHwnd;
            break;
        }
        tempHwnd = GetNextSibling(tempHwnd);
    }
    
    return hwnd;
}

// 특정 버튼을 클릭하는 함수
void ClickButton(HWND hwndButton) {
    SendMessage(hwndButton, BM_CLICK, 0, 0);
}

int autoclick() {
    const char* windowTitle = "Stand Launchpad 1.9"; // 대상 프로그램의 제목
    const char* buttonClassName = "Button"; // 버튼의 클래스 이름
    const char* buttonText = "Inject"; // 버튼 텍스트
    
    // Stand Launchpad 윈도우 찾기
    HWND hwndMain = FindWindow(NULL, windowTitle);
    if (hwndMain == NULL) {
        printf("Stand Launchpad 창을 찾을 수 없습니다.\n");
        return 1;
    }

    // Inject 버튼 찾기
    HWND hwndButton = FindWindowByClass(buttonClassName, hwndMain);
    if (hwndButton == NULL) {
        printf("Inject 버튼을 찾을 수 없습니다.\n");
        return 1;
    }

    // Inject 버튼 클릭
    ClickButton(hwndButton);
    printf("Inject 버튼을 클릭했습니다.\n");

    return 0;
}
