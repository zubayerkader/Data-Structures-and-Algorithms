#include "loan_application.h"
#include <iostream>

using namespace std;

ostream & operator<<(ostream & out, const loan_application& rhs){
	if (rhs.decision_=="")	
		out << "(" << rhs.applicant_full_name_<< "," << rhs.loan_amount_ << ")";
	else
		out << "(" << rhs.applicant_full_name_<< "," << rhs.loan_amount_ << "," << rhs.decision_ << ")";
	return out;
}


float loan_application::priority() const {
	float pr=0;
        for (int i=0; i<num_years_; i++)
        	pr += (1/(float)(i+1)) * estimated_yearly_profits_[i];
        return pr;
}
