using System.Collections.Generic;
using System.IO;
using System.Text;
using System.Threading.Tasks;

namespace ZiaulHasanHamim
{
    public class JsonWriter
    {
        public static async Task WriteToJsonFile(List<Dictionary<string, string>> data, string fileName = "result.json")
        {
            StringBuilder jsonData = new();
            jsonData.Append("[");
            int i = 0;
            foreach (var row in data)
            {
                jsonData.Append(addNewJsonObject(row));
                i++;
                if (i != data.Count)
                {
                    jsonData.Append(", ");
                }
            }
            jsonData.Append("]");
            await File.WriteAllTextAsync(fileName, jsonData.ToString());
        }

        private static void addNewJsonField(StringBuilder jsonObject, KeyValuePair<string, string> keyValue)
        {
            jsonObject.Append($"\"{keyValue.Key}\": ");
            if (double.TryParse(keyValue.Value, out var numberValue))
            {
                jsonObject.Append(numberValue);
            }
            else
            {
                jsonObject.Append($"\"{keyValue.Value}\"");
            }
        }

        private static string addNewJsonObject(Dictionary<string, string> row)
        {
            StringBuilder jsonObject = new();
            jsonObject.Append("{");
            int j = 0;
            foreach (var keyValue in row)
            {
                addNewJsonField(jsonObject, keyValue);
                j++;
                if (j != row.Count)
                {
                    jsonObject.Append(", ");
                }
            }
            jsonObject.Append("}");
            return jsonObject.ToString();
        }
    }
}
