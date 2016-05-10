using System;
using ClassLibrary1;

namespace ClassLibrary3
{
    public class DerivedClass1 : BaseClass
    {
        public override void Function()
        {
            Console.WriteLine($"[IN] {nameof(DerivedClass1)}.{nameof(Function)} is called.");
            base.Function();
            Console.WriteLine($"[OUT] {nameof(DerivedClass1)}.{nameof(Function)} is called.");
        }
    }
}
