#ifndef FILEHANDLER_H
#define FILEHANDLER_H

#include <iostream>
#include <fstream>
#include <string>
#include <vector>

using namespace std;

vector<vector<string>> readTXT(const string& filename);
void writeTXT(const string& filename, const vector<string>& header, const vector<vector<string>>& data);
void appendTXT(const string& filename, const vector<string>& row);
vector<string> findRow(const string& filename, const string& key, int colIndex);
bool rowExists(const string& filename, const string& value, int colIndex);

#endif