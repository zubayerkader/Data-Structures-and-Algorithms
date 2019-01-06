#include "loan_application.h"
using namespace std;

loan_application:: loan_application() {}

loan_application::loan_application (string applicant_full_name, int years_of_relevant_education, int years_of_relevant_experience, int loan_amount, int priority)
{
	this->applicant_full_name = applicant_full_name;
	this->years_of_relevant_education = years_of_relevant_education;
	this->years_of_relevant_experience = years_of_relevant_experience;
	this->loan_amount = loan_amount;
	this->priority = priority;
}

loan_application::loan_application (const loan_application &data)
{
	this->applicant_full_name = data.applicant_full_name;
	this->years_of_relevant_education = data.years_of_relevant_education;
	this->years_of_relevant_experience = data.years_of_relevant_experience;
	this->loan_amount = data.loan_amount;
	this->priority = data.priority;
}

loan_application& loan_application::operator= (const loan_application &data)
{
	if (this == &data)
		return *this;
	else
	{
		this->applicant_full_name = data.applicant_full_name;
		this->years_of_relevant_education = data.years_of_relevant_education;
		this->years_of_relevant_experience = data.years_of_relevant_experience;
		this->loan_amount = data.loan_amount;
		this->priority = data.priority;
	}
}

bool loan_application::operator< (const loan_application &data) const
{
	if (this->priority > data.priority)
		return true;
	else
		return false;
}

bool loan_application::operator== (const loan_application &data) const
{
	if (this->priority == data.priority)
		return true;
	else
		return false;
}

bool loan_application::operator> (const loan_application &data) const
{
	if (this->priority < data.priority)
		return true;
	else
		return false;
}

bool loan_application::operator>= (const loan_application &data) const
{
	if (this->priority <= data.priority)
		return true;
	else
		return false;
}

bool loan_application::operator<= (const loan_application &data) const
{
	if (this->priority >= data.priority)
		return true;
	else
		return false;
}

bool loan_application::operator!= (const loan_application &data) const
{
	if (this->priority != data.priority)
		return true;
	else
		return false;
}

ostream& operator<< (ostream &out, const loan_application &data)
{
	out << data.applicant_full_name << endl;
	out << data.years_of_relevant_education << endl;
	out << data.years_of_relevant_experience << endl;
	out << data.loan_amount << endl;
	return out;
}
