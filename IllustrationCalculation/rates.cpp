#include "pch.h"
#include "rates.h"
#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>

rates::rates(string FilePath)
{
	sSCRatePath = FilePath + "SC_scale.csv";
	sCorrFactorsPath = FilePath + "corridor_factors.csv";
	sMortPath = FilePath + "vector_data.csv";
    sLoadsPath = FilePath + "loads.csv";

    LoadSurrenderCharges(sSCRatePath);
    LoadCorridorFactors(sCorrFactorsPath);
    LoadMortChages(sMortPath);
    LoadLoadCharges(sLoadsPath);
    

}
int rates::LoadSurrenderCharges(string FileName)
{
    ifstream file(FileName);  // Open the CSV file for reading
    if (!file.is_open()) {
        cerr << "Error opening file!" << endl;
        return 1;
    }

    string line;

    // Skip the header line
    getline(file, line);

    // Read the data line by line
    while (getline(file, line)) {
        stringstream ss(line);
        SurrenderCharge surrcharge;

        // Read the data for each column
        ss >> surrcharge.year;            // Read the year(integer)
        ss.ignore();                      // Skip the comma
        ss >> surrcharge.charge;          // Read the charge (double)

        // Store the surrender charge data in the vector
        surrenderCharges.push_back(surrcharge);
    }

    // Close the file
    file.close();

    return 0;
}


int rates::LoadCorridorFactors(string FileName)
{
    ifstream file(FileName);  // Open the CSV file for reading
    if (!file.is_open()) {
        cerr << "Error opening file!" << endl;
        return 1;
    }

    string line;

    // Skip the header line
    getline(file, line);

    // Read the data line by line
    while (getline(file, line)) {
        stringstream ss(line);
        CorridorFactor corrfactor;

        // Read the data for each column
        ss >> corrfactor.age;            // Read the age(integer)
        ss.ignore();                      // Skip the comma
        ss >> corrfactor.factor;          // Read the factor (double)

        // Store the surrender charge data in the vector
        corridorFactors.push_back(corrfactor);
    }

    // Close the file
    file.close();

    return 0;

}
int rates::LoadMortChages(string FileName)
{
    fstream file(FileName);  // Open the CSV file for reading
    if (!file.is_open()) {
        cerr << "Error opening file!" << endl;
        return;
    }

    string line;

    // Read the first line to get company names
    getline(file, line);
    stringstream headerStream(line);
    string column;

    // Skip the first column (Age) and read the company names
    getline(headerStream, column, ',');  // Ignore the "Age" column header
    while (getline(headerStream, column, ',')) {
        companies.push_back(column);  // Add company name to the vector
    }

    int iYear = 0; 

    // Read the remaining data
    while (getline(file, line)) {
        stringstream ss(line);
        MortalityCharge entry;  // Create an entry for year and rates

        entry.year = iYear;

        // Read the rates for each company (remaining columns)
        double rate;
        size_t companyIndex = 0;
        while (ss >> rate) {
            entry.companyRates[companies[companyIndex]] = rate;  // Store rate for the company
            companyIndex++;
            if (ss.peek() == ',')  // Skip the comma after each rate
                ss.ignore();
        }

        // Store the entry in the vector
        mortalityCharges.push_back(entry);
        iYear++;

    }

    // Close the file
    file.close();

}

int rates::LoadLoadCharges(string FileName)
{
    ifstream file(FileName);
    if (!file.is_open()) {
        cerr << "Failed to open file: " << FileName << endl;
        return false;
    }

    string line, company, type;
    int year;
    double rate;
    while (getline(file, line)) {
        stringstream ss(line);
        if (getline(ss, company, ',') && getline(ss, type, ',') && ss >> year && ss >> rate) {
            Loads[company][type][year] = rate;
        }
    }
    return true;
}

double rates::GetMortCharge(const string& company, int year) const {
    // Iterate over the mortalityCharges vector to find the entry for the given year
    for (const auto& entry : mortalityCharges) {
        if (entry.year == year) {
            // Check if the company exists in the companyRates map
            auto companyIt = entry.companyRates.find(company);
            if (companyIt != entry.companyRates.end()) {
                return companyIt->second;  // Return the rate for the given company
            }
            else {
                cerr << "Company not found for the given year!" << endl;
                return 0.0;  // Return an error value if company not found
            }
        }
    }

    cerr << "Year not found!" << endl;
    return 0.0;  // Return an error value if the year is not found
}
double rates::GetSurrenderCharge(int year) const {
    // Iterate over the surrenderCharges vector to find the entry for the given year
    for (const auto& entry : surrenderCharges) {
        if (entry.year == year) {
            return entry.charge;  // Return the surrender charge for the given year
        }
    }

    cerr << "Year not found!" << endl;
    return -1;  // Return an error value if the year is not found
}
double rates::GetCorrFactor(int age) const {
   // for ages 40 and less use the same rate     
    int useAge = max(age, 40);

    for (const auto& entry : corridorFactors) {
        if (entry.age == useAge) {
            return entry.factor;  // Return the corridor factor for the given age
        }
    }

    cerr << "Age not found!" << endl;
    return -1;  // Return an error value if the age is not found
}


double rates::getLoadRate(const string& company, const string& type, int year) const {
    auto companyIt = Loads.find(company);
    if (companyIt != Loads.end()) {
        auto typeIt = companyIt->second.find(type);
        if (typeIt != companyIt->second.end()) {
            auto yearIt = typeIt->second.find(year);
            if (yearIt != typeIt->second.end()) {
                return yearIt->second;
            }
            else {
                while (true)
                {
                    auto findyear = yearIt--;
                    if (yearIt != typeIt->second.end())
                        return yearIt->second;
                }
            }

            
        }
    }
    cerr << "Rate not found for " << company << " (" << type << ", " << year << ")." << endl;
    return 0.0; // Indicates rate not found
}





/*CompanyRates buildCompanyRates(const string& company) const {
    CompanyRates result;
    auto companyIt = rates.find(company);
    if (companyIt != rates.end()) {
        for (const auto& [year, rate] : companyIt->second.at("TypeA")) {
            result.rateTypeA.push_back(rate);
            result.years.push_back(year);
        }
        for (const auto& [year, rate] : companyIt->second.at("TypeB")) {
            result.rateTypeB.push_back(rate);
        }
        for (const auto& [year, rate] : companyIt->second.at("TypeC")) {
            result.rateTypeC.push_back(rate);
        }
    }
    else {
        cerr << "Company not found: " << company << endl;
    }
    return result;
    */