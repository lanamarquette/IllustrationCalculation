#include "pch.h"
#include "monthly.h"

monthly::monthly(int Mode)
{
	iMode = Mode;
	iWhichMonth = 0;

	dPremium = 0.0;
	dAccountValue = 0.0;
	dPctOfPremiumLoad = 1.0;
	dMonthlyFee = 0.0;
	dPerUnitLoad = 0.0;
	dMonthlyInterestRate = 1.02;
	dCorridorFactor = 2.5;
	dMortalityCharge = .0001;
	dFaceAmount = 100000.0;
	dSurrenderCharge = 0;
	dFace = 100000.0;
	dDeathBenefit = 100000.0;
}

void monthly::SetMonthForYear(int Mode, double Premium, double PctOfPremiumLoad, double MonthlyFee, double PerUnitLoad, double AnnualInterestRate, double CorridorFactor, double AnnualMortalityCharge, double SurrenderCharge)
{
	iWhichMonth = 0;
	iMode = Mode;
	dPremium = Premium;
	dPctOfPremiumLoad = 1.0 - PctOfPremiumLoad;
	dMonthlyFee = MonthlyFee;
	dPerUnitLoad = PerUnitLoad / 12.0;
	dMonthlyInterestRate = (1.0 + AnnualInterestRate) * (1 / 12.0);
	dCorridorFactor = CorridorFactor;
	dMortalityCharge = AnnualMortalityCharge / 12.0;
	dSurrenderCharge = SurrenderCharge;

}

void monthly::MonthlyProcess(int WhichMonth)
{
	iWhichMonth = WhichMonth;
	AddPrem();
	ApplyPerUnitLoad();
	ApplyMonthlyFee();
	ApplyMortalityCharge();
	ApplyInterest();
}

void monthly::AddPrem()
{
	switch (iMode)
	{
	case 1:
		if (iWhichMonth == 0)
			dAccountValue += dPremium * dPctOfPremiumLoad;
			break;
	case 2:
		if (iWhichMonth == 0 || iWhichMonth == 5)
			dAccountValue += dPremium * dPctOfPremiumLoad;
		break;
	case 3:
		if (iWhichMonth == 0 || iWhichMonth == 2 || iWhichMonth == 5 || iWhichMonth == 8)
			dAccountValue += dPremium * dPctOfPremiumLoad;
		else
			dAccountValue += dPremium * dPctOfPremiumLoad;
		break;
	}

	return;
}
void monthly::ApplyMonthlyFee(void)
{
	double exp_charge = 0.0;
	dAccountValue -= dMonthlyFee;
}
void monthly::ApplyPerUnitLoad(void)
{
	double exp_charge = 0.0;

	exp_charge = dFaceAmount / 1000.0 * dPerUnitLoad;
	dAccountValue -= exp_charge;
}
double monthly::ApplyMortalityCharge(void)
{
	double MonthNAR = 0.0;
	double mort_charge = 0.0;

	dDeathBenefit = max(dFace, dAccountValue * dCorridorFactor);
	MonthNAR = max(dDeathBenefit - dAccountValue, 0.0);
	mort_charge = MonthNAR * dMortalityCharge;
	dAccountValue -= mort_charge;
}
double monthly::ApplyInterest(void)
{
	dAccountValue *= dMonthlyInterestRate;
}
double monthly::GetAnnualAccountValue(void)
{
	return max(dAccountValue, 0.0);

}
double monthly::GetAnnualCashValue(void)
{
	return max(dAccountValue - max((dSurrenderCharge * dFaceAmount / 1000.0), 0.0), 0.0);
}
double monthly::GetAnnualDeathBenefit(void)
{
	dDeathBenefit = max(dFace, dAccountValue * dCorridorFactor);
	return dDeathBenefit;
}



