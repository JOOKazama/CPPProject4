#include"pch.h"
#include<iostream>
#include<string>
#include<list>
#include<iterator>
#include<fstream>
#include<math.h>

using namespace std;

class Digit
{
private:

	int digit;

public:

	Digit() {};
	Digit(int digit) { this->digit=digit; }
	Digit(Digit &Digit_main) { this->digit=Digit_main.digit; }
	int get_digit() const { return digit; }
	void set_digit(const int digit) { this->digit=digit; }
	virtual void output(ostream& output) { output<<"The value is: "<<digit<<endl<<endl; }
	virtual void set_virtual(const int value)=0;
	virtual bool less_than_digit(const Digit* digit)=0;
	virtual int get_virtual() const=0;
};

class Expected_Frequency: public Digit
{
	private:

		int expected_frequency;

	public:

		Expected_Frequency() {};

		Expected_Frequency(int digit, int expected_frequency): Digit(digit) { this->expected_frequency=expected_frequency; }
		Expected_Frequency(const Expected_Frequency& expected_frequency_main) { this->expected_frequency=expected_frequency_main.expected_frequency; }
		int get_expected() const { return this->expected_frequency; }
		int get_virtual() const { return this->expected_frequency; }
		void set_expected(const int expected_frequency) { this->expected_frequency=expected_frequency; }
		void set_virtual(const int expected_frequency) { this->expected_frequency = expected_frequency; }
		void output(ostream& output) { output<<"The value is: "<<expected_frequency<<endl<<endl; }
		int operator =(Expected_Frequency const &expected_frequency_main) { this->expected_frequency=expected_frequency_main.expected_frequency; }
		bool operator ==(Expected_Frequency const &expected_frequency_main) { if (this->expected_frequency==expected_frequency_main.expected_frequency) return true; }

		bool less_than_digit(const Digit* digit)
		{
			if(expected_frequency>digit->get_virtual()) return true;
			else if(expected_frequency<digit->get_virtual()) return false;
		}

		friend istream &operator >>(istream &input, Expected_Frequency& expected_frequency_main)
		{
			input>>expected_frequency_main.expected_frequency;
			return input;
		}

		friend ostream &operator <<(ostream &output, const Expected_Frequency& expected_frequency_main)
		{
			output<<expected_frequency_main.get_expected();
			return output;
		}
};

class Observed_Frequency: public Digit
{
private:

	int observed_frequency;

public:

	Observed_Frequency() {};

	Observed_Frequency(int digit, int val):Digit(digit) { this->observed_frequency=val; }
	Observed_Frequency(const Observed_Frequency& observed_frequency_main) { observed_frequency=observed_frequency_main.observed_frequency; }
	int get_observed() const { return observed_frequency; }
	int get_virtual() const { return this->observed_frequency; }
	void set_observed(const int observed_frequency) { this->observed_frequency=observed_frequency; }
	void set_virtual(const int observed_frequency) { this->observed_frequency=observed_frequency; }
	void output(ostream& output) { output<<"The value is: "<<observed_frequency<<endl<<endl; }
	int operator =(Observed_Frequency const &observed_frequency_main) { observed_frequency=observed_frequency_main.observed_frequency; }
	bool operator ==(Observed_Frequency const &observed_frequency_main) { if(observed_frequency==observed_frequency_main.observed_frequency) return true; }

	bool less_than_digit(const Digit* digit)
	{
		if(observed_frequency>digit->get_virtual()) return true;
		else if(observed_frequency<digit->get_virtual()) return false;
	}

	friend istream &operator >>(istream &input, Observed_Frequency& observed_frequency_main)
	{
		input>>observed_frequency_main.observed_frequency;
		return input;
	}

	friend ostream &operator <<(ostream &output, const Observed_Frequency& observed_frequency_main)
	{
		output<<observed_frequency_main.get_observed();
		return output;
	}
};

class GoodnessOfFit
{
	private:

		list<Digit*>expected_frequency;
		list<Digit*>observed_frequency;
		int total_frequency_difference;
		double statistical_grade;

	public:

		GoodnessOfFit(const string& str_file_name_exp, const string& str_file_name_obs)
		{
			ifstream my_file(str_file_name_exp.c_str());
			ifstream my_file1(str_file_name_obs.c_str());
			int first_value, second_value;

			my_file.exceptions(ifstream::badbit);
			my_file1.exceptions(ifstream::badbit);

			try
			{
				if (my_file.is_open())
				{
					while(!my_file.eof())
					{
						my_file>>first_value>>second_value;
						Digit* digit=new Expected_Frequency(first_value, second_value);
						expected_frequency.push_back(digit);
					}
					my_file.close();
				}

				else
				{
					cout<<"Problem, check name or file destination!"<<endl;
					system("pause");
				}
			}

			catch(const int x) { cout<<"Exception reading file"; }

			try
			{
				if(my_file1.is_open())
				{
					while(!my_file1.eof())
					{
						my_file1>>first_value>>second_value;
						Digit* digit=new Observed_Frequency(first_value, second_value);
						observed_frequency.push_back(digit);
					}

					my_file1.close();
				}

				else
				{
					cout<<"Problem, check name or file destination!"<<endl;
					system("pause");
				}
			}

			catch(const int x) { cout<<"Exception reading file"; }

		}

		void calculated_total_frequency_difference()
		{
			list<Digit*>::iterator i;
			int sum_expected_frequency=0, sum_observed_frequency=0;

			for (i=expected_frequency.begin(); i!=expected_frequency.end(); i++) { sum_expected_frequency+=(*i)->get_virtual(); }
			for (i=observed_frequency.begin(); i!=observed_frequency.end(); i++) { sum_observed_frequency+=(*i)->get_virtual(); }

			total_frequency_difference=sum_expected_frequency-sum_observed_frequency;
			cout<<"The difference is: "<<total_frequency_difference <<endl<<endl;
		}

		bool calculate_statistical_grade()
		{
			list<Digit*>::iterator i;
			double sum=0, sum1=0, sum2=0, sum3=0, sum4=0, sum5=0;

			for(i=expected_frequency.begin(); i!=expected_frequency.end(); i++) { sum+=(*i)->get_virtual(); }
			for(i=observed_frequency.begin(); i!=observed_frequency.end(); i++) { sum1+=(*i)->get_virtual(); }

			sum2+=sum+sum1;
			sum3=sum1-sum;
			sum4=sum2*sum3;
			sum5=pow(sum4, 2);

			statistical_grade=sqrt(sum5/sum);

			if(statistical_grade<=0) return false;
			else return true;
		}

		bool check_statistical_grade()

		{
			if(statistical_grade<=0) return false;
			else
			{
				cout<<"The statistical grade is: "<<statistical_grade <<endl<<endl;
				return true;
			}
		}

		double get_statistical_grade() { return statistical_grade; }

		void set_data(int digit, int expected_frequency1, int observed_frequency1)
		{
			while(digit<=0)
			{
				cout<<"Enter a iDigit bigger than 0: ";
				cin>>digit;
			}

			while(expected_frequency1<=0)
			{
				cout<<"Enter a iExpected bigger than 0: ";
				cin>>expected_frequency1;
			}

			while(observed_frequency1<=0)
			{
				cout<<"Enter a iObserved bigger than 0: ";
				cin>>observed_frequency1;
			}

			list<Digit*>::iterator i, i1;

			for(i=expected_frequency.begin(); i!=expected_frequency.end(); i++)
			{
				for(i1=observed_frequency.begin(); i1!=observed_frequency.end(); i1++)
				{
					if((*i)->get_digit()==digit && (*i1)->get_digit()== digit)
					{
						(*i)->set_virtual(expected_frequency1);
						(*i1)->set_virtual(observed_frequency1);
					}
				}
			}
		}

		void write_to_cout()
		{
			list<Digit*>::iterator i, i1;

			cout<<"The data is: "<<endl;
			cout<<"Digit Exp Obs"<<endl;

			for(i=expected_frequency.begin(); i!=expected_frequency.end(); i++)
			{
				for(i1=observed_frequency.begin(); i1!=observed_frequency.end(); i1++)
				{ if((*i)->get_digit()==(*i1)->get_digit()) cout<<(*i)->get_digit()<<"     "<<(*i)->get_virtual()<<"   "<<(*i1)->get_virtual()<<endl; }
			}
			cout<<endl;
		}

		bool find_expected_number(int expected_number)
		{

			while(expected_number<=0)
			{
				cout<<"Enter a number bigger than 0: ";
				cin>>expected_number;
			}

			list<Digit*>::iterator i;
			cout<<"The matching result is: ";

			for(i=expected_frequency.begin(); i!=expected_frequency.end(); i++)
			{ if((*i)->get_digit()==expected_number) cout<<(*i)->get_digit()<<" "<<(*i)->get_virtual()<<endl; }
			cout<<endl;
			return expected_number;
		}

		int get_total_frequency_difference() { return total_frequency_difference; }
};

int main(void)
{
	GoodnessOfFit goodness_of_fit("goodnessExp.txt", "goodnessObs.txt");
	goodness_of_fit.write_to_cout();
	goodness_of_fit.find_expected_number(4);
	goodness_of_fit.get_total_frequency_difference();
	goodness_of_fit.calculate_statistical_grade();
	goodness_of_fit.check_statistical_grade();
	goodness_of_fit.set_data(4, 16, 15);
	goodness_of_fit.write_to_cout();
	system("pause");
}
