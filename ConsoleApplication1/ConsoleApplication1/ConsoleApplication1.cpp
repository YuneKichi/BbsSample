// ConsoleApplication1.cpp : メイン プロジェクト ファイルです。

#include "stdafx.h"

using namespace System;
using namespace System::Collections::Generic;
using namespace System::Runtime::InteropServices;

delegate bool WndEnumProc(HWND, LPARAM);

#pragma comment(lib, "user32")

ref class TestClass
{
private:
	List<IntPtr>^ handles_;

	bool EnumWindowProc(HWND, LPARAM);
public:
	TestClass();

	void GetWindowHandles();

	void ShowWindowHandles();
};

TestClass::TestClass() : handles_(gcnew List<IntPtr>()) { }

bool TestClass::EnumWindowProc(HWND hWnd, LPARAM lParam)
{
	handles_->Add((IntPtr)hWnd);
	return true;
}

void TestClass::GetWindowHandles()
{
	handles_->Clear();
	auto ptr = gcnew WndEnumProc(this, &TestClass::EnumWindowProc);
	auto gch = GCHandle::Alloc(ptr);
	auto enumProc = (WNDENUMPROC)Marshal::GetFunctionPointerForDelegate(ptr).ToPointer();

	EnumWindows(enumProc, 0);

	gch.Free();
}


void TestClass::ShowWindowHandles()
{
	for each (auto ptr in handles_)
	{
		Console::WriteLine(ptr);
	}
}

int main(array<System::String ^> ^args)
{
	auto tc = gcnew TestClass();
	tc->GetWindowHandles();
	tc->ShowWindowHandles();
	return 0;
}
