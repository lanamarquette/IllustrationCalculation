#include "pch.h"
#include "DataFrame.h"

// Add a row of data
void DataFrame::addRow(const vector<variant<int, double>>& row) {
    if (row.size() != columnLabels.size()) {
        throw runtime_error("Row size doesn't match number of columns!");
    }
    data.push_back(row);
}

// Display the dataframe
void DataFrame::display() const {
    // Print column labels
    for (const auto& label : columnLabels) {
        cout << setw(12) << label;
    }
    cout << endl;

    // Print data rows
    for (const auto& row : data) {
        for (const auto& cell : row) {
            visit([](auto&& value) { cout << setw(12) << value; }, cell);
        }
        cout << endl;
    }
}

// Serialize to a Java-compatible format
string DataFrame::toJavaCompatibleString() const {
    string result;

    // Add column labels
    for (const auto& label : columnLabels) {
        result += label + ",";
    }
    result.pop_back(); // Remove trailing comma
    result += "\n";

    // Add data rows
    for (const auto& row : data) {
        for (const auto& cell : row) {
            result += visit([](auto&& value) { return to_string(value); }, cell) + ",";
        }
        result.pop_back(); // Remove trailing comma
        result += "\n";
    }
    return result;
}