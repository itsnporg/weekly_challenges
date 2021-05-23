using System;
using System.Collections.Generic;
using System.IO;
using System.Threading.Tasks;

namespace ZiaulHasanHamim
{
    public class CsvParser
    {
        public static async Task<List<Dictionary<string, string>>> ParseCsv(string fileName)
        {
            List<Dictionary<string, string>> result = new();
            StreamReader csvFileReader = new(fileName);
            string[] headers = null;
            string line;
            int lineCount = 0;
            while ((line = await csvFileReader.ReadLineAsync()) != null)
            {
                lineCount++;
                if (lineCount == 1)
                {
                    headers = line.Split(",");
                    continue;
                }
                addNewRecord(result, headers, line);
            }
            return result;
        }
        private static void addNewRecord(List<Dictionary<string, string>> result, string[] headers, string line)
        {
            string[] row = line.Split(",");
            if (row.Length != headers.Length)
            {
                throw new Exception("Wrong Formatted Csv");
            }
            Dictionary<string, string> rowWithHeader = new();
            for (int i = 0; i < row.Length; i++)
            {
                rowWithHeader[headers[i]] = row[i];
            }
            result.Add(rowWithHeader);
        }

    }
}
