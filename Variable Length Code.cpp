//https://www.codeabbey.com/index/task_view/variable-length-code
//

#include <iostream>
#include <sstream>
#include <vector>
#include <string>
#include <algorithm>
#include <map>
#include <chrono>
#include <cmath>

#include "Console.h"
#include "CodeAbbey.h"
#include "LS_library.h"
#define VERSION "1.0"

using namespace std;

using std::chrono::high_resolution_clock;
using std::chrono::duration_cast;
using std::chrono::duration;
using std::chrono::milliseconds;

map<string, string> CodingMap();
vector<int> VL_Code(string str, map<string, string> codeMap);
std::vector<std::string> IntToHex(std::vector<int>& ints);
std::string StringToUpper(std::string str);


int main() {
	auto t1 = high_resolution_clock::now();
	cout << "VLC v" << VERSION << "!\n\n";
	string path = "Test.txt";
	//string path = "Try.txt";
	vector<string> raw_data = loadData(path);
	string problem = raw_data[0];
	cout << "problem: " << problem << endl;

	map<string, string> code = CodingMap();
	vector<int> intCodes = VL_Code(problem, code);
	vector<string> hexCodes = IntToHex(intCodes);

	cout << "\nSolution: " << joinVector(hexCodes, " ") << endl;;

	/***********************/
	auto t2 = high_resolution_clock::now();
	auto ms_int = duration_cast<milliseconds>(t2 - t1);
	cout << "Execution time: " << ms_int.count() << " ms" << endl;
}

map<string, string> CodingMap() {
	map<string, string> code;
	code[" "] = "11";
	code["t"] = "1001";
	code["n"] = "10000";
	code["s"] = "0101";
	code["r"] = "01000";
	code["d"] = "00101";
	code["!"] = "001000";
	code["c"] = "000101";
	code["m"] = "000011";
	code["g"] = "0000100";
	code["b"] = "0000010";
	code["v"] = "00000001";
	code["k"] = "0000000001";
	code["q"] = "000000000001";
	code["e"] = "101";
	code["o"] = "10001";
	code["a"] = "011";
	code["i"] = "01001";
	code["h"] = "0011";
	code["l"] = "001001";
	code["u"] = "00011";
	code["f"] = "000100";
	code["p"] = "0000101";
	code["w"] = "0000011";
	code["y"] = "0000001";
	code["j"] = "000000001";
	code["x"] = "00000000001";
	code["z"] = "000000000000";

	return code;
}

vector<int> VL_Code(string str, map<string, string> codeMap) {
	vector<int> codes;
	string binary = "";
	for (int i = 0; i < str.size(); i++) {
		string chr = str.substr(i, 1);
		binary += codeMap[chr];
	}
	int parity = binary.size() % 8;
	if (parity > 0) {
		for (; parity < 8; parity++) {
			binary += "0";
		}
	}

	for (int i = 0; i < binary.size(); i += 8) {
		string byte = binary.substr(i, 8);
		codes.push_back(stoi(byte, nullptr, 2));
	}
	return codes;
}

std::vector<std::string> IntToHex(std::vector<int>& ints) {
	std::vector<std::string> hexs;

	for (auto& i : ints) {
		std::ostringstream ss;
		ss.width(2);
		ss.fill('0');
		ss << std::hex << i;
		std::string result = ss.str();
		hexs.push_back(StringToUpper(result));
	}

	return hexs;
}

std::string StringToUpper(std::string str) {
	string strUp = "";
	for (auto& c : str) {
		strUp += std::toupper(c);
	}
	return strUp;
}