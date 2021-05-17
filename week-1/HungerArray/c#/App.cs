using System.IO;
using System.Collections.Generic;
using System;
using System.Text;
using System.Text.RegularExpressions;

namespace Sol
{
    class App
    {
        public void Start(string file_name)
        {
            var data = ParseCsv(file_name);
            WriteJson(data);
        }

        private List<Dictionary<string, string>> ParseCsv(string file_name)
        {
            using (StreamReader csv = new(file_name))
            {
                string[] titles = GetTitles(csv);
                return GetData(titles, csv);
            }
        }

        private List<Dictionary<string, string>> GetData(string[] titles, StreamReader csv)
        {
            List<Dictionary<string, string>> ret = new();

            string line;
            while ((line = csv.ReadLine()) != null)
            {
                var data = line.Split(',');
                Dictionary<string, string> dict = new();

                for (int i = 0; i < titles.Length; ++i)
                {
                    dict[titles[i]] = data[i];
                }
                ret.Add(dict);
            }

            return ret;
        }

        private string[] GetTitles(StreamReader csv) => csv.ReadLine().Split(',');

        private void WriteJson(List<Dictionary<string, string>> data)
        {
            using (StreamWriter json = new("data.json"))
            {
                string jsonStr = ToJsonString(data);
                json.Write(jsonStr);
            }
        }

        private string ToJsonString(List<Dictionary<string, string>> data)
        {
            Regex reg = new(@"-?(?:0|[1-9]\d*)(?:\.\d*)?(?:[eE][+-]?\d+)?", RegexOptions.Compiled);

            StringBuilder sw = new();
            sw.AppendLine("[");
            
            foreach(var dict in data)
            {
                sw.AppendLine("\t{");

                foreach (var elem in dict)
                {
                    if (reg.IsMatch(elem.Value))
                        sw.AppendLine($"\t\t\"{elem.Key}\" : {elem.Value},");
                    else
                        sw.AppendLine($"\t\t\"{elem.Key}\" : \"{elem.Value}\",");
                }
                sw.Remove(sw.Length - 3, 3);

                sw.AppendLine();

                if(dict == data[^1])
                    sw.AppendLine("\t}");
                else
                    sw.AppendLine("\t},");
            }

            sw.AppendLine("]");

            return sw.ToString();
        }
    }
}