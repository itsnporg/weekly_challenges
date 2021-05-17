#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>

std::vector<std::string> parseLine(std::string s){
    std::vector<std::string> result;
    std::stringstream linestrm(s);
    std::string tmp;
    while(std::getline(linestrm, tmp, ',')){
        result.push_back(tmp);
    }
    return result;
}

bool is_number(const std::string& s){
    std::string::const_iterator it = s.begin();
    while (it != s.end() && std::isdigit(*it)) ++it;
    return !s.empty() && it == s.end();
}

int main(){
                
    std::ifstream file("data.csv");
    std::string line;

    std::getline(file, line, '\n');
    std::vector<std::string> columns;
    columns = parseLine(line);
    std::vector<std::vector<std::string>> rows;
    while(std::getline(file, line, '\n')){
        rows.push_back(parseLine(line));
    }
    file.close();
    std::stringstream json;

    size_t cnt = 0;
    json << "[\n";
    for(auto r: rows){
        unsigned int i =0;
        json << "{\n";
        for(auto c : r){
            json << "\t\"" << columns[i] << "\"" << ":";
            if (!is_number(c) || c.empty()) {
                json << "\"";
            }
            json << c;
            if (!is_number(c) || c.empty()) {
                json << "\"";
            }
            if(i<c.size()){
                json << ",";
            }
            json << "\n";
            i++;
        }
        json << "}";
        cnt++;
        if(cnt!=rows.size()){
            json << ",";
        }
        json << "\n";
    }
    json << "]";

    std::ofstream out("result.json");
    out << json.rdbuf();
    out.close();
    return 0;
}
