#ifndef LOAN_APPLICATION_H
#define LOAN_APPLICATION_H

#include <iostream>

using namespace std;

class loan_application{
public:
	loan_application(){}

	loan_application(string applicant_full_name, 
			 int years_of_relevant_education,
			 int years_of_relevant_experience,
			 int loan_amount,
			 int* estimated_yearly_profits,
			 int num_years):applicant_full_name_(applicant_full_name),
                         years_of_relevant_education_(years_of_relevant_education),
                         years_of_relevant_experience_(years_of_relevant_experience), 
                         loan_amount_(loan_amount),
                         estimated_yearly_profits_(estimated_yearly_profits), 
			 num_years_(num_years),
			 priority_(priority()), 
			 decision_(""){};

	bool valid() const {return ((years_of_relevant_education_ + years_of_relevant_experience_) >= 10);}

	int get_loan_amount(){ return loan_amount_;}
	
	void set_decision(string decision){ decision_ = decision; }

	bool operator<(const loan_application& rhs) const {return (priority_ < rhs.priority_);}
	bool operator>(const loan_application& rhs) const {return !(((*this)==rhs) || ((*this)<rhs));}
	bool operator==(const loan_application& rhs) const {return (applicant_full_name_==rhs.applicant_full_name_);}
	bool operator<=(const loan_application& rhs) const {return !((*this)>rhs);}
	bool operator>=(const loan_application& rhs) const {return !((*this)<rhs);}
	bool operator!=(const loan_application& rhs) const {return !((*this)==rhs);}

	friend ostream & operator<<(ostream & out, const loan_application& rhs);

protected:
	float priority() const;
private:
	string applicant_full_name_;
        int years_of_relevant_education_;
        int years_of_relevant_experience_; 
        int loan_amount_;
        int* estimated_yearly_profits_;
	int num_years_;
	float priority_;
	string decision_;
};

#endif
