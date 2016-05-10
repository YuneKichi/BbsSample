#include "stdafx.h"
#include "DerivedClass1.h"

using namespace System;

void ClassLibrary2::DerivedClass1::Function()
{
	Console::WriteLine(L"[IN] DerivedClass1::Function is called.");
	__super::Function();
	Console::WriteLine(L"[OUT] DerivedClass1::Function is called.");
}
