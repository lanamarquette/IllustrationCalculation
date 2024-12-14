#pragma once

#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>
#include <map>


using namespace std;

#define ENDOWMENT_SIZE 121

#define NO_OF_LOAD_TYPES 3
#define PER_UNIT_LOAD 0
#define MONTHLY_FEE 1
#define PERCENT_OF_PREMIUM 2

using RateData = std::map<std::string, std::map<std::string, std::map<int, double>>>;
class rates
{
	string sSCRatePath;
	string sLoadsPath;
	string sCorrFactorsPath;
	string sMortPath;

	struct SurrenderCharge {
		int year;
		double charge;
	};
	struct CorridorFactor {
		int age;
		double factor;

	};
	struct MortalityCharge {
		int year;
		map<string, double> companyRates;
	};


	RateData Loads;

	vector<string> companies;  // List of company names

	vector<SurrenderCharge> surrenderCharges;
	vector<CorridorFactor> corridorFactors;
	vector<MortalityCharge> mortalityCharges;

	

	double LoadCharges[NO_OF_LOAD_TYPES][ENDOWMENT_SIZE];
	
public:
	rates(string FilePath);
	double getLoadRate(const string& company, const string& type, int year) const;
	double GetMortCharge(const string& company, int year) const;
	double GetSurrenderCharge(int) const;
	double GetCorrFactor(int) const;

private:

	int LoadSurrenderCharges(string);
	int LoadCorridorFactors(string);
	int LoadMortChages(string);
	int LoadLoadCharges(string);

};

