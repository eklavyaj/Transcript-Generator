#include <bits/stdc++.h>
using namespace std; 


int Stoi(string s){
	stringstream t(s);
	int x=0;
	t>>x;
	return x;
}

struct course
{
    int sem;
    int L, T, P, C;
    string title;
};

//to resolve white space issue in grades.csv file
string space(string str){
	int len=str.length();
	string ans;
	if(str[len-1]==' '){
		for(int i=0; i<len-1; i++ ){
			ans+=str[i];
		}
		return ans;
	}
	return str;
}


int sumv(vector<int> v){
	return accumulate(v.begin(), v.end(),0);
}

 
int main(){

	fstream students,courses,grades;
	string line,word;

	students.open("students.csv");
	courses.open("courses.csv");
	grades.open("grades.csv");
	


	map<int,string> rollname;

	vector<int> rolls;

	int temp;
	
	vector<string> row;
	
	while(students){
		row.clear();
		getline(students,line);
		stringstream s(line); 

		while (getline(s, word, ',')) { 
 
			row.push_back(word); 
		}

		temp=Stoi(row[1]);

		rolls.push_back(temp);	

		rollname[temp]=row[0];

	}
	students.close();


	unordered_map <string, course> coursemap;
	
    while(courses)
    {
    	row.clear();
    	string id;
    	course temp1;
		getline(courses,line);
		stringstream s(line); 
		while (getline(s, word, ',')) { 
 
			row.push_back(word); 
		}
		temp1.sem=Stoi(row[0]);
		temp1.title=row[2];
		temp1.L=Stoi(row[3]);
		temp1.T=Stoi(row[4]);
		temp1.P=Stoi(row[5]);
		temp1.C=Stoi(row[6]);

		id=row[1];
	
		coursemap[id]=temp1;

	}

	courses.close();

	vector< pair <int,pair<string,string> > > grade;
	
	pair<int,pair<string,string> > temp2;
	
	while(grades){

		row.clear();
		getline(grades,line);
		stringstream s(line); 
		while (getline(s, word, ',')) { 
			
			row.push_back(word); 
		}

		temp2=make_pair(Stoi(row[0]), make_pair(space(row[1]),row[2]));
		grade.push_back(temp2);

	}


	
	for(int k=0;k<rolls.size();k++){

		int roll=rolls[k];
	
		string filename=to_string(roll)+".txt";
	
		FILE* fptr=fopen(filename.c_str(),"w");
	
		stringstream ss;

		
		ss<<"NAME: "<<rollname[roll]<<endl;
		ss<<"ROLL NUMBER: "<<roll<<endl<<endl;

		vector <long double> spi;
		vector<int> semcredits(9,0);
		vector<long double> cpi;

		int ttcredits=0;

		for(int i=1; i<=8; i++){
			
			int totalcredits=0;
			int sum=0;
			string str;
			int x;
			int score=0;
			
			vector<int > marks;
			
			ss<<"SEMESTER "<<i<<endl;

			ss<<"COURSE NUMBER   |        COURSE NAME                | C  | GRADE  "<<endl;			
			for(int j=0; j< grade.size(); j++){
		
				if(roll==grade[j].first){
		
					if(i==coursemap[grade[j].second.first].sem){
		
						str=grade[j].second.second;
		
						ss<<grade[j].second.first<<"\t\t\t"<<coursemap[grade[j].second.first].title<<"\t"<<coursemap[grade[j].second.first].C<<"   "<<grade[j].second.second<<endl;
		
						totalcredits+=coursemap[grade[j].second.first].C;
		
						if(str=="AA"){
							score=10;
						}
		
						else if(str=="AB"){
							score=9;
						}
		
						else if(str=="BB"){
							score=8;
						}
		
						else if(str=="BC"){
							score=7;
						}
		
						else if(str=="CC"){
							score=6;
						}
		
						else if(str=="CD"){
							score=5;
						}
		
						else if(str=="DD"){
							score=4;
						}
						
						
						marks.push_back(score*(coursemap[grade[j].second.first].C));

					}

				}
			}

			int sum1=sumv(marks);

			//cout<<totalcredits<<endl;

			semcredits[i]=totalcredits;

			spi.push_back((long double)sum1/totalcredits);

			long double sum2=0;

			ttcredits+=semcredits[i];

			
			for(int j=0; j<i; j++){
				
				sum2+=(long double)(spi[j]*semcredits[j+1]);
			}	

			ss<<"-----------------------------------------------------------------------"<<endl;

			cpi.push_back((long double)(sum2/ttcredits));

		}


		ss<<"        I       II        III        IV       V       VI        VII       VIII"<<endl;
	
		ss<<"SPI  ";
	
		for(int i=0; i<spi.size(); i++){
			ss<<spi[i]<<"   ";
		}
		ss<<endl;
		ss<<"CPI  ";
		for(int i=0; i<cpi.size(); i++){
			ss<<cpi[i]<<"   ";
		}
		ss<<endl;
		fprintf(fptr,ss.str().c_str());
		
		// fptr->close()
	}
}	
	
	

