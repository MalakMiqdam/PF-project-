#ifndef FILEHANDLER_H
#define FILEHANDLER_H

#include <iostream>
#include <fstream>
#include <string>
#include <vector>

using namespace std;

vector<string> readTXT(const string& filename);
void writeTXT(const string& filename, const string& header, const vector<string>& rows);
void appendTXT(const string& filename, const string& row);
vector<string> findRow(const string& filename, const string& searchValue, int colIndex);
bool rowExists(const string& filename, const string& searchValue, int colIndex);

#endif