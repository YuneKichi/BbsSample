#include <Windows.h>

// エラー出力用関数群
void output_error_string_value(LPCTSTR errorString)
{
	OutputDebugString(errorString);
	MessageBox(nullptr, TEXT("API failed"), errorString, MB_OK);
}

void output_error_string(LPCTSTR functionName)
{
	TCHAR buf[128];
	wsprintf(buf, TEXT("%s Failed.\r\n"), functionName);
	output_error_string_value(buf);
}

void output_error(LPCTSTR functionName)
{
	TCHAR buf[128];
	auto error = GetLastError();
	wsprintf(buf, TEXT("%s Failed (%d).\r\n"), functionName, error);
	output_error_string_value(buf);
}

// タイマー応答関数
// 現在のカーソル位置の色を拾ってウィンドウに表示する
void on_timer(HWND hWnd, UINT_PTR nIDEvent)
{
	// 現在のカーソル位置の取得
	POINT pos;
	if (!GetCursorPos(&pos))
	{
		output_error(TEXT("GetCursorPos"));
		KillTimer(hWnd, nIDEvent);
		return;
	}

	// カーソル位置のスクリーンの色の取得
	auto hdcScreen = GetDC(nullptr);
	if (hdcScreen == nullptr)
	{
		output_error(TEXT("GetDC(nullptr)"));
		KillTimer(hWnd, nIDEvent);
		return;
	}
	auto color = GetPixel(hdcScreen, pos.x, pos.y);
	ReleaseDC(nullptr, hdcScreen);
	if (color == CLR_INVALID)
	{
		output_error_string(TEXT("GetPixel"));
		KillTimer(hWnd, nIDEvent);
		return;
	}

	// ウィンドウのクライアント領域の取得
	RECT client;
	if (!GetClientRect(hWnd, &client))
	{
		output_error(TEXT("GetClientRect"));
		KillTimer(hWnd, nIDEvent);
		return;
	}
	client.right -= client.left;
	client.left = 0;
	client.bottom -= client.top;
	client.top = 0;

	// 描画処理
	auto hdc = GetDC(hWnd);
	if (hdc == nullptr)
	{
		output_error(TEXT("GetDC(hWnd)"));
		KillTimer(hWnd, nIDEvent);
		return;
	}

	FillRect(hdc, &client, GetSysColorBrush(COLOR_WINDOW));

	auto oldFont = SelectObject(hdc, GetStockObject(ANSI_FIXED_FONT));

	TCHAR posStr[32];
	RECT posRect;
	posRect.left = 0;
	posRect.right = client.right;
	posRect.top = 0;
	posRect.bottom = client.bottom / 2;
	wsprintf(posStr, TEXT("(%d, %d)"), pos.x, pos.y);
	DrawText(hdc, posStr, -1, &posRect, DT_CENTER | DT_VCENTER | DT_NOPREFIX | DT_SINGLELINE);

	TCHAR colorStr[64];
	RECT colorRect;
	colorRect.left = 0;
	colorRect.right = client.right;
	colorRect.top = posRect.bottom;
	colorRect.bottom = client.bottom;
	wsprintf(colorStr, TEXT("#%02X%02X%02X (R: %3d, G: %3d, B: %3d)"),
		GetRValue(color), GetGValue(color), GetBValue(color),
		GetRValue(color), GetGValue(color), GetBValue(color));
	DrawText(hdc, colorStr, -1, &colorRect, DT_CENTER | DT_VCENTER | DT_NOPREFIX | DT_SINGLELINE);

	SelectObject(hdc, oldFont);
	ReleaseDC(hWnd, hdc);
}

// ウィンドウプロシージャ
LRESULT CALLBACK WindowProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
	switch (uMsg)
	{
	case WM_CREATE:
		// 最初にタイマーを作っておく
		SetTimer(hWnd, 1, 50, nullptr);
		return 0;
	case WM_TIMER:
		on_timer(hWnd, static_cast<UINT_PTR>(wParam));
		return 0;
	case WM_DESTROY:
		PostQuitMessage(0);
		return 0;
	}
	return DefWindowProc(hWnd, uMsg, wParam, lParam);
}

int CALLBACK WinMain(HINSTANCE, HINSTANCE, LPSTR, int)
{
	// ウィンドウクラスの登録
	WNDCLASS wc = { 0 };
	wc.style = CS_HREDRAW | CS_VREDRAW;
	wc.lpfnWndProc = WindowProc;
	wc.hIcon = LoadIcon(nullptr, IDI_APPLICATION);
	wc.hCursor = LoadCursor(nullptr, IDC_ARROW);
	wc.hbrBackground = reinterpret_cast<HBRUSH>(COLOR_WINDOW + 1);
	wc.lpszClassName = TEXT("A272C09C-277D-4AD0-9AC8-74ADA061BC0D");
	auto wcAtom = RegisterClass(&wc);
	if (wcAtom == 0)
	{
		output_error(TEXT("RegisterClass"));
		return 1;
	}

	// ウィンドウの作成
	auto hwnd = CreateWindow(reinterpret_cast<LPCTSTR>(wcAtom), TEXT("Color Pick"),
		WS_OVERLAPPED | WS_VISIBLE | WS_SYSMENU | WS_MINIMIZEBOX,
		CW_USEDEFAULT, CW_USEDEFAULT, 300, 100, nullptr, nullptr, nullptr, nullptr);
	if (hwnd == nullptr)
	{
		output_error(TEXT("CreateWindow"));
		return 1;
	}

	// メッセージループ
	MSG msg;
	BOOL loopResult;
	while ((loopResult = GetMessage(&msg, nullptr, 0, 0)) != 0 && loopResult != -1)
	{
		TranslateMessage(&msg);
		DispatchMessage(&msg);
	}
	if (loopResult == -1)
	{
		output_error(TEXT("GetMessage"));
		return 1;
	}
	return static_cast<int>(msg.wParam);
}
