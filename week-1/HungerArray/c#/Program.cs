using System;

namespace Sol
{
    class Program
    {
        static void Main(string[] args)
        {
            if (args.Length < 1)
            {
                Console.WriteLine("dotnet run data.csv");
                return;
            }

            App app = new();
            app.Start(args[0]);
            
        }
    }
}
