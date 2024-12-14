#include "pch.h"
#include "yearly.h"
#include <string>

yearly::yearly(int Age, double Premium, string FilePath)
{
    sSCRatePath = FilePath + "SC_scale.csv";
    sLoadsPath = FilePath + "loads.csv";
    sCorrFactorsPath = FilePath + "corridor_factors.csv";
    sMortPath = FilePath + "vector_data.csv";
    RateInfo = new rates(FilePath);


    iYear = 0;
    iAttainedAge = Age;
    dPremium = Premium;

    dMortalityCharge = 0.0;
    dCorridorFactor = 2.5;
    dInterestRate = .05;
    dPctOfPremiumLoad = 0.0;
    dSurrenderCharge = 0.0;
    dPctOfPremiumLoad = 0.0;
    dMonthlyFee = 0.0;
    dPerUnitLoad = 0.0;
    sCompany = "Protective";  // Default to Protective
}
void yearly::SetCompany(string Company)
{
    sCompany = Company;
}


void yearly::SetupYearValues(int Year, double InterestRate, double Premium)
{
    iYear = Year;
    dPremium = Premium;
    dInterestRate = InterestRate;
    dCorridorFactor = RateInfo->GetCorrFactor(iAttainedAge);
    dSurrenderCharge = RateInfo->GetSurrenderCharge(iYear);
    dMonthlyFee = RateInfo->getLoadRate(sCompany, "monthly_fee", iYear);
    dPerUnitLoad = RateInfo->getLoadRate(sCompany, "per_unit_load", iYear);
    dPerUnitLoad = RateInfo->getLoadRate(sCompany, "percent_of_premium", iYear);
    dMortalityCharge = RateInfo->GetMortCharge(sCompany, iYear);
    iAttainedAge++;
}

double yearly::GetPremium(void)
{
    return dPremium;
}

double yearly::GetInterestRate(void)
{
    return dInterestRate;
}

double yearly::GetCorridorFactor(void)
{
    return dCorridorFactor;
}

double yearly::GetSurrenderCharge(void)
{
    return dSurrenderCharge;
}
double yearly::GetMonthlyFee(void)
{
    return dMonthlyFee;
}
double yearly::GetPerUnitLoad(void)
{
    return dPerUnitLoad;
}
double yearly::GetPctOfPremiumLoad(void)
{
    return dPctOfPremiumLoad;
}
double yearly::GetMortalityCharge(void)
{
    return dMortalityCharge;
}
