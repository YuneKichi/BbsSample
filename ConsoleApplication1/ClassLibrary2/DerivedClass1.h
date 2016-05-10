#pragma once

namespace ClassLibrary2
{
	public ref class DerivedClass1 :
		public ClassLibrary1::BaseClass
	{
	public:
		void virtual Function(void) override;
	};
}
