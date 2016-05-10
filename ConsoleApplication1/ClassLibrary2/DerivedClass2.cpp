#include "stdafx.h"
#include "DerivedClass2.h"

using namespace System;

void ClassLibrary2::DerivedClass2::Function()
{
	Console::WriteLine(L"[IN] DerivedClass2::Function is called.");
	ClassLibrary1::BaseBaseClass::Function();
	Console::WriteLine(L"[OUT] DerivedClass2::Function is called.");
}
