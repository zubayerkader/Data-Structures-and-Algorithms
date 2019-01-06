#include "loan_application.h"
using namespace std;

SortedArrayList<loan_application> active_applications_list(5000);
SortedArrayList<loan_application> approved_applications_list(5000);
ArrayList<loan_application> denied_applications_list(5000);

int activeobjs=0;
int deniedobjs =0;
int approvedobjs = 0;
int budget=0;

void Tokenize(string line, vector<string> & tokens, string delimiters = "\t ")
{
	string token = "";
	string OneCharString = " ";
    for (int i=0; i<line.size(); i++)
    {
		if (find(delimiters.begin(), delimiters.end(), line[i])!=delimiters.end()) // line[i] is one of the delimiter characters
		{
			if (token.size()>0)
				tokens.push_back(token);
			token = "";
		}
		else
		{
			OneCharString[0] = line[i];
			token +=OneCharString;
		}
	}
	if (token != "")
		tokens.push_back(token);
}

void save_application(const vector<string>& tokens)
{
	string name = tokens[1];
	int education = atoi(tokens[2].c_str());
	int experience = atoi(tokens[3].c_str());
 	int loan_amount = atoi(tokens[4].c_str());
	int priority=0;
	
	int a = 0;
	for (int i =5; i < tokens.size(); i++) 	
	{ 	
		priority = priority + (atoi(tokens[i].c_str())/(a+1));
		a++;
	}
	
	loan_application x(name, education, experience, loan_amount, priority);
	active_applications_list.add(x);
	activeobjs++;
}

void make_decision(const vector<string> &tokens)
{
	budget = budget + atoi(tokens[4].c_str());
	string date = tokens[1]+" "+tokens[2]+" "+tokens[3];
	
	for (int i=0; i<active_applications_list.count(); )
	{
		if (active_applications_list[i].years_of_relevant_education + active_applications_list[i].years_of_relevant_experience < 10)
		{
			denied_applications_list[deniedobjs]=active_applications_list[i];
			active_applications_list.removeFirst(active_applications_list[i]);
			activeobjs--;
			denied_applications_list[deniedobjs].decision_date = date;
			deniedobjs++;
			continue;
		}
		if ((active_applications_list[i].years_of_relevant_education + active_applications_list[i].years_of_relevant_experience >= 10) && (active_applications_list[i].loan_amount <= budget))
		{
			approved_applications_list[approvedobjs]=active_applications_list[i];
			budget = budget - approved_applications_list[approvedobjs].loan_amount;
			active_applications_list.removeFirst(active_applications_list[i]);

			

			activeobjs--;
			approved_applications_list[approvedobjs].decision_date = date;
			approvedobjs++;
			continue;
		}
		i++;
	}
}

void print(SortedArrayList<loan_application> &active_applications_list, ArrayList<loan_application> &denied_applications_list, SortedArrayList<loan_application> &approved_applications_list)
{
	cout << "active_applications\t";
	for (int i=0; i<activeobjs; i++)
	{
		cout << "(" << active_applications_list[i].applicant_full_name << "," << active_applications_list[i].loan_amount << ")\t";
	}
	cout << endl;

	cout << "approved_applications\t";
	for (int i=0; i<approvedobjs; i++)
	{
		cout << "(" << approved_applications_list[i].applicant_full_name << "," << approved_applications_list[i].loan_amount << "," << approved_applications_list[i].decision_date  << ")\t";
	}
	cout << endl;

	cout << "denied_applications\t";
	for (int i=0; i<deniedobjs; i++)
	{
		cout << "(" << denied_applications_list[i].applicant_full_name << "," << denied_applications_list[i].loan_amount << "," << denied_applications_list[i].decision_date << ")\t";
	}
	cout << endl;
}

void fileInput(const char* fname)
{
	ifstream inf;
	inf.open(fname);

	string line;
	while (getline(inf, line).good()){
		vector<string> tokens;
		Tokenize(line, tokens, "\t ");
		if (tokens.size()==0)
			continue;
		
		if (tokens[0]=="save_application")
			save_application(tokens);
		
		else if (tokens[0]=="make_decisions")
			make_decision (tokens);
			
			
		else if (tokens[0]=="print")
			print(active_applications_list, denied_applications_list, approved_applications_list);
	}

	inf.close();
}

int main(int argc, char** argv)
{
	if (argc != 2)
	{
		std::cout << "usage: executable.o commands.txt\n";
		return 1;
	}

	fileInput(argv[1]);
	return 0;
}



