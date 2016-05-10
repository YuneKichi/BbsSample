#pragma once

namespace ClassLibrary2
{
	public ref class DerivedClass2 :
		public ClassLibrary1::BaseClass
	{
	public:
		void virtual Function() override;
	};
}
