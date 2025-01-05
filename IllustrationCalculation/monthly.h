#pragma once
#include "math.h"

class monthly
{
	int iMode;
	int iWhichMonth;
	double dPremium;
	double dAccountValue;
	double dPctOfPremiumLoad;
	double dMonthlyFee;
	double dPerUnitLoad;
	double dMonthlyInterestRate;
	double dCorridorFactor;
	double dMortalityCharge;
	double dFaceAmount;
	double dSurrenderCharge;
	double dFace;
	double dDeathBenefit;

public :
	monthly(int);
	void SetMonthForYear(int Mode, double Premium, double PctOfPremiumLoad, double MonthlyFee, double PerUnitLoad, double AnnualInterestRate, double CorridorFactor, double AnnualMortalityCharge, double SurrenderCharge);
	void MonthlyProcess(int WhichMonth);
private :
	void AddPrem();
	void ApplyMonthlyFee(void);
	void ApplyPerUnitLoad(void);
	double ApplyMortalityCharge(void);
	double ApplyInterest(void);

public :
	double GetAnnualAccountValue(void);
	double GetAnnualCashValue(void);
	double GetAnnualDeathBenefit(void);

};

