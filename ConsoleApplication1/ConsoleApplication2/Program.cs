using System;
using ClassLibrary3;

namespace ConsoleApplication2
{
    class Program
    {
        static void Main()
        {
            Console.WriteLine(typeof(Program).Namespace);
            Console.WriteLine();

            Console.WriteLine(nameof(DerivedClass1));
            var dc1 = new DerivedClass1();
            dc1.Function();
            Console.WriteLine();

            Console.WriteLine(nameof(DerivedClass2));
            var dc2 = new DerivedClass2();
            dc2.Function();
            Console.WriteLine();

            if (System.Diagnostics.Debugger.IsAttached)
            {
                Console.ReadLine();
            }
        }
    }
}
