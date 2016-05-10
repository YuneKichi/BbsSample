using System;
using System.Reflection.Emit;
using ClassLibrary1;

namespace ClassLibrary3
{
    public class DerivedClass2 : BaseClass
    {
        private static readonly Action<BaseBaseClass> _callFunction;

        static DerivedClass2()
        {
            var dm = new DynamicMethod("", typeof(void), new[] { typeof(BaseBaseClass) }, typeof(DerivedClass2));
            var il = dm.GetILGenerator();

            il.Emit(OpCodes.Ldarg_0);
            il.Emit(OpCodes.Call, typeof(BaseBaseClass).GetMethod("Function"));
            il.Emit(OpCodes.Ret);

            _callFunction = (Action<BaseBaseClass>)dm.CreateDelegate(typeof(Action<BaseBaseClass>));
        }

        public override void Function()
        {
            Console.WriteLine($"[IN] {nameof(DerivedClass2)}.{nameof(Function)} is called.");
            _callFunction?.Invoke(this);
            Console.WriteLine($"[OUT] {nameof(DerivedClass2)}.{nameof(Function)} is called.");
        }
    }
}
