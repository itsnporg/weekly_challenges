using System.Threading.Tasks;

namespace ZiaulHasanHamim
{
    internal class Program
    {
        private static async Task Main(string[] args)
        {
            string fileName = "data.csv";
            if (args.Length > 0)
            {
                fileName = args[0];
            }
            var data = await CsvParser.ParseCsv(fileName);
            await JsonWriter.WriteToJsonFile(data);
        }
    }
}
