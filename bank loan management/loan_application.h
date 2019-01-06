#include <iostream>
#include "SortedArrayList.h"
#include <vector>
#include <fstream>
#include <string>
#include <algorithm>
using namespace std;

class loan_application
{
public:
	string applicant_full_name;
	int years_of_relevant_education;
	int years_of_relevant_experience;
	int loan_amount;
	int *estimated_yearly_profits;
	int priority;
	string decision_date;

	loan_application();
	loan_application (string applicant_full_name, int years_of_relevant_education, int years_of_relevant_experience, int loan_amount, int priority);
	loan_application (const loan_application &data);
	
	loan_application& operator= (const loan_application &data);
	bool operator< (const loan_application &data) const;
	bool operator== (const loan_application &data) const;
	bool operator> (const loan_application &data) const;
	bool operator>= (const loan_application &data) const;
	bool operator<= (const loan_application &data) const;
	bool operator!= (const loan_application &data) const;
	friend ostream& operator<< (ostream &out, const loan_application &data);
};
