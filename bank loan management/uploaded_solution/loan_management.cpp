#include "ArrayList.h"
#include "ListInterface.h"
#include "SortedArrayList.h"
#include "loan_application.h"
#include <vector>
#include <iostream>
#include <fstream>
#include <algorithm>

using namespace std;

const int max_applications_num = 1000;

ArrayList<loan_application> approved(max_applications_num), denied(max_applications_num);
SortedArrayList<loan_application> active(max_applications_num);

void Tokenize(string line, vector<string> & tokens, string delimiters = "\t "){
string token = "";
        string OneCharString = " ";
        for (int i=0; i<line.size(); i++)
                if (find(delimiters.begin(), delimiters.end(), line[i])!=delimiters.end()) // line[i] is one of the delimiter characters
       		{
			if (token != "")
                        	tokens.push_back(token);
                        token = "";
                }
                else
                {
                        OneCharString[0] = line[i];
                        token +=OneCharString;
                }

        if (token != "")
                tokens.push_back(token);
}

void SaveApplication(const vector<string>& tokens){

	string applicant_full_name = tokens[1];
        int years_of_relevant_education = atoi(tokens[2].c_str()) ;
        int years_of_relevant_experience = atoi(tokens[3].c_str()) ;
        int loan_amount = atoi(tokens[4].c_str()) ;
	int num_years = tokens.size() -5;
        int* estimated_yearly_profits = new int[num_years];
        for (int i=5; i< tokens.size(); i++)
		estimated_yearly_profits[i-5] = atoi(tokens[i].c_str());
	
	active.add(loan_application(applicant_full_name,
                         years_of_relevant_education,
                         years_of_relevant_experience,
                         loan_amount,
                         estimated_yearly_profits,
                         num_years));
}

void MakeDecisions(string decision, int budget){
	int n = active.count();
	int i=n-1;
	while (i >=0){
		
		loan_application & current = active[i];	
		if (current.valid()){
			if (current.get_loan_amount() <= budget){
				budget -= current.get_loan_amount();
				current.set_decision(decision);
                        	approved.add(current);
                        	active.removeFirst(current);
			}
		}
		else{
			current.set_decision(decision);
			denied.add(current);
			active.removeFirst(current);
		}
		i--;
	}
}

void ExecuteCommands(const char* fname){
	ifstream inf;
	inf.open(fname);

	string line;
	while (getline(inf, line).good()){
		vector<string> tokens;
		Tokenize(line, tokens, "\t");
		if (tokens.size()==0)
			continue;
		if (tokens[0]=="save_application")
			SaveApplication(tokens);			
		else if (tokens[0]=="make_decisions")
			MakeDecisions(tokens[1], atoi(tokens[2].c_str()));
		else{ //print
			cout << "active_applications \t";
			active.print();
			cout << "approved_applications \t";
			approved.print();
			cout << "denied_applications \t";
			denied.print();
		}
	}

	inf.close();
}

int main(int argc, char** argv){
	if (argc != 2){
		cout << "usage: executable.o command.txt\n";
		return 1;
	}

	ExecuteCommands(argv[1]);
	return 0;
}

