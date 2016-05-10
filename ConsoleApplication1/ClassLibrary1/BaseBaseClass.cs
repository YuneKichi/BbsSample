using System;

namespace ClassLibrary1
{
    public class BaseBaseClass
    {
        public virtual void Function ()
        {
            Console.WriteLine($"[IN] {nameof(BaseBaseClass)}.{nameof(Function)} is called.");
            Console.WriteLine($"[OUT] {nameof(BaseBaseClass)}.{nameof(Function)} is called.");
        }
    }
}
