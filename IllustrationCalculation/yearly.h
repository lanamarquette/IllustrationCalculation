#pragma once
#include <stdio.h>
#include <string>
#include "rates.h"

using namespace std;

class yearly
{

    
    string sSCRatePath;
    string sLoadsPath;
    string sCorrFactorsPath;
    string sMortPath;

    rates *RateInfo;



    int iYear;
    int iAttainedAge;
    double dPremium;

    double dMortalityCharge;
    double dCorridorFactor;
    double dInterestRate = .05;
    double dPctOfPremiumLoad = 0.0;
    double dSurrenderCharge = 0.0;
    double dPctOfPremiumLoad = 0.0;
    double dMonthlyFee = 0.0;
    double dPerUnitLoad = 0.0;
    string sCompany;

public :
    yearly(int Age, double Premium, string FilePath);
    void SetCompany(string Company);
    void SetupYearValues(int Year, double InterestRate, double Premium);
    double GetPremium(void);
    double GetInterestRate(void);
    double GetCorridorFactor(void);
    double GetSurrenderCharge(void);
    double GetMonthlyFee(void);
    double GetPerUnitLoad(void);
    double GetPctOfPremiumLoad(void);
    double GetMortalityCharge(void);


};

