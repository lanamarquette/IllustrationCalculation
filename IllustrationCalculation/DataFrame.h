#pragma once

#include <stdio.h>
#include <iostream>
#include <vector>
#include <string>
#include <variant> // For mixed types
#include <iomanip> // For formatting
using namespace std;

class DataFrame
{
private:
    vector<string> columnLabels; // Column labels
    vector<vector<variant<int, double>>> data; // Table data with mixed types

public:
    // Constructor to initialize column labels
    DataFrame(const vector<string>& labels) : columnLabels(labels) {}

    // Add a row of data
    void addRow(const vector<variant<int, double>>& row);

    // Display the dataframe
    void display() const;

    // Serialize to a Java-compatible format
    string toJavaCompatibleString() const;


};

