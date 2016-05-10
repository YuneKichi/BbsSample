using System;

namespace ClassLibrary1
{
    public class BaseClass : BaseBaseClass
    {
        public override void Function()
        {
            Console.WriteLine($"[IN] {nameof(BaseClass)}.{nameof(Function)} is called.");
            base.Function();
            Console.WriteLine($"[OUT] {nameof(BaseClass)}.{nameof(Function)} is called.");
        }
    }
}
