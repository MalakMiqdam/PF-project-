 #ifndef FILEHANDLER_H
#define FILEHANDLER_H

#include <iostream>
#include <fstream>
#include <string>
#include <vector>

using namespace std;

vector<vector<string>> readTXT(const string& filename);
void writeTXT(const string& filename, const vector<string>& header, const vector<vector<string>>& rows);
void appendTXT(const string& filename, const vector<string>& row);
vector<string> findRow(const vector<vector<string>>& data, int colIndex, const string& value);
bool rowExists(const vector<vector<string>>& data, int colIndex, const string& value);

#endif