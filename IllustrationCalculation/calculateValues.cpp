#include "pch.h"
#include <string>
#include <vector>
#include <map>
#include "monthly.h"
#include "yearly.h"
#include "DataFrame.h"
#include <math.h>
#define EXPORTING_DLL 
#include "IllustrationCalculation.h"

using namespace std;

double roundToTwoDecimals(double);
DataFrame CalculateValues(double dPremium, double dFace, double dInterestRate, int iAge, string sWhichCompany);

int Calculate(double dPremium, double dFace, double dInterestRate, int iAge, const char * cWhichCompany)
{
    string sWhichCompany = cWhichCompany;
    DataFrame ReturnDF = CalculateValues(dPremium, dFace, dInterestRate, iAge, sWhichCompany);
    return 1;
}

DataFrame CalculateValues(double dPremium, double dFace, double dInterestRate, int iAge, string sWhichCompany)
{
    int i = 0;
    int y = 0;
    int iDuration = 100 - iAge;

    dInterestRate /= 100.0;

    // Phase 2 input variable
    int iMode = 1;

    // This should come from Brain
    string sFilePath = "C:/Users/lanam/source/repos/IllustrationCalculation/IllustrationCalculation/rates/";
    
    DataFrame df({ "Age", "Accum Value", "Cash Value", "Death Benefit" });
    
    
    // Read the CSV file for company options - add later - read ages from here
    string CompanyFilePath = sFilePath + "company.csv";
        //df = pd.DataFrame(columns = ['Age', 'Accum Value', 'Cash Value', 'Death Benefit'])

    // Create a month loop
    monthly MonthlyLoop(iMode);

    // Create a year loop
    yearly YearlyLoop(iAge, dPremium, sFilePath);




    // Protective	annual charges from illustration per dollar	select	40
    // Corebridge	annual charges from illustration per dollar	select	40
    // Symetra	annual charges from illustration per dollar	select	40
    // Lincoln	annual charges from illustration per dollar	select	45
    // F & G	annual charges from illustration per dollar	select	45
    // Principal	annual charges from illustration per dollar	select	45
    // Nationwide	from monthly cost of insurance rate report	select	45

    YearlyLoop.SetCompany(sWhichCompany);
    //Yearly loop
    while (y < iDuration)
    {

        YearlyLoop.SetupYearValues(y, dInterestRate, dPremium);
        MonthlyLoop.SetMonthForYear(iMode, YearlyLoop.GetPremium(), YearlyLoop.GetPctOfPremiumLoad(), YearlyLoop.GetMonthlyFee(), YearlyLoop.GetPerUnitLoad(),
            YearlyLoop.GetInterestRate(), YearlyLoop.GetCorridorFactor(), YearlyLoop.GetMortalityCharge(), YearlyLoop.GetSurrenderCharge());


        while (i < 12)
        {
            MonthlyLoop.MonthlyProcess(i);
            i++;
        }

        df.addRow({ iAge + y, roundToTwoDecimals(MonthlyLoop.GetAnnualAccountValue()), roundToTwoDecimals(MonthlyLoop.GetAnnualCashValue()), roundToTwoDecimals(MonthlyLoop.GetAnnualDeathBenefit()) });

        y++;
        i = 0;
    }

    return df;
}
    double roundToTwoDecimals(double value) {
        return std::round(value * 100.0) / 100.0;
    }
