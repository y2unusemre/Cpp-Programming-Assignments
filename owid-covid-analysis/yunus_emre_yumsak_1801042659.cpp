#include <iostream>
#include <cstdlib>
#include <vector>
#include <fstream>
#include <string>
#include <sstream>
#include <cmath>

using namespace std;



void insertSpace(string& str);
bool compDate(string first, string second);

double variation(double arr[],double sum,int size);



int main(){


	string line;
	string temp;

	string currCountry;
	string tempCountry;
	string prevCountry;

	string currDate;
	string prevDate;
	string earliestDate="2022-01-01";
	string tempDate;
	
	int total_case;
	int total_death;
	int total_test;
	int people_vacc;
	int people_vacc_full;
	int total_vacc;

	double reproArr[500];
	double curr_min_repro=100000.0;
	double curr_max_repro=0.0;
	double total_repro=0.0;

	double icuArr[500];
	double curr_min_icu=100000.0;
	double curr_max_icu=0.0;
	double total_icu=0.0;

	double hospArr[500];
	double curr_min_hosp=100000.0;
	double curr_max_hosp=0.0;
	double total_hosp=0.0;

	double weekly_icuArr[500];
	double curr_min_weekly_icu=100000.0;
	double curr_max_weekly_icu=0.0;
	double total_weekly_icu=0.0;

	double weekly_hospArr[500];
	double curr_min_weekly_hosp=100000.0;
	double curr_max_weekly_hosp=0.0;
	double total_weekly_hosp=0.0;

	double new_testArr[500];
	double curr_min_new_test=100000.0;
	double curr_max_new_test=0.0;
	double total_new_test=0.0;

	double pos_rateArr[500];
	double curr_min_pos_rate=100000.0;
	double curr_max_pos_rate=0.0;
	double total_pos_rate=0.0;

	double test_per_caseArr[500];
	double curr_min_test_per_case=100000.0;
	double curr_max_test_per_case=0.0;
	double total_test_per_case=0.0;

	long int population;
	double median_age;
	double aged_65_older;
	double aged_70_older;
	double gdp_per_capita;
	double extreme_poverty;
	double cardiovasc_death_rate;
	double diabetes_prevalence;
	double female_smokers;
	double male_smokers;
	double  handwashing_facilities;
	double hospital_beds_per_thousand;
	double life_expectancy;
	double human_development_index;


	double temp_float;
	int countryNum=0;


	int counter=0;

	string str;
	ifstream fin;
	fin.open("owid-covid-data.csv");
	
	ofstream fout;
	fout.open("output.csv");


	getline(fin,line); // ignore first line



//****************************question1****************************

	while(getline(fin,line)){					
		counter=0;
		insertSpace(line);		
		stringstream s(line);
		
		while(getline(s,temp,',')){
			
			if (temp!=currCountry && counter==0){
				countryNum++;			
			}
			if (counter==0){
				currCountry=temp;	
			}
			counter++;
		}
		
	}
	
	fout << "####Question1####" << endl;
	fout << "Number of countries:"<< countryNum <<endl<<endl;

//***************************question2************************


	ifstream fin2;
	fin2.open("owid-covid-data.csv");
	getline(fin2,line); // başlık linedan kurtulmak için

	fout << "####Question2####" << endl;

	fout <<endl<<"Country EarliestDate"<<endl;
	while(getline(fin2,line)){					
		insertSpace(line);		
		stringstream s(line);
		getline(s,temp,',');
		getline(s,temp,',');
		getline(s,temp,',');
		currCountry=temp;
		getline(s,temp,',');
		currDate=temp;
		if (currCountry != prevCountry){
			earliestDate=currDate;
			fout << currCountry << " " << earliestDate << endl;
		}
		prevCountry=currCountry;

	}
	
	fout << endl;

//*************************question3*******************

	ifstream fin3,tempFin3;
	fin3.open("owid-covid-data.csv");
	getline(fin3,line); // başlık linedan kurtulmak için
	ofstream fout3;

	fout << "####Question3####" << endl;
	fout <<endl<<"Country Cases"<<endl;

	while(getline(fin3,line)){					//
		insertSpace(line);		
		stringstream s(line);
		getline(s,temp,',');
		getline(s,temp,',');
		getline(s,temp,',');
		currCountry=temp;
		getline(s,temp,',');
		currDate=temp;
		getline(s,temp,',');	//
		if (temp==" "){
			temp="0";
		}
			total_case=stoi(temp);
		if (currCountry == prevCountry){
 			fout3.open ("temp.txt");
  			fout3 << currCountry << " " << total_case << endl;
  			fout3.close();
		}

  		if (currCountry != prevCountry){
  			tempFin3.open("temp.txt");
			getline(tempFin3,temp);
			tempFin3.close();
			fout << temp << endl;
    	}	
		prevCountry=currCountry;
		prevDate=currDate;

	}
	remove( "temp.txt" );
	fout <<endl;


//************************question4************************


	ifstream fin4,tempFin4;
	fin4.open("owid-covid-data.csv");
	getline(fin4,line); // başlık linedan kurtulmak için
	ofstream fout4;

	fout << "####Question4####" << endl;
	fout <<endl<<"Country Deaths"<<endl;



	while(getline(fin4,line)){					//dış loop iso değişti mi kontrol? bütün dosyayı okuyacak getline ile
		insertSpace(line);		
		stringstream s(line);
		getline(s,temp,',');
		getline(s,temp,',');
		getline(s,temp,',');
		currCountry=temp;
		getline(s,temp,',');
		currDate=temp;	
		getline(s,temp,',');	
		getline(s,temp,',');	
		getline(s,temp,',');	//o güne özel total case
		if (temp==" "){
			temp="0";
		}
			total_death=stoi(temp);
		if (currCountry == prevCountry){
			//	;
 			fout4.open ("temp.txt");
  			fout4 << currCountry << " " << total_death << endl;
  			fout4.close();
		}

  		if (currCountry != prevCountry){
  			tempFin4.open("temp.txt");
			getline(tempFin4,temp);
			tempFin4.close();
			fout << temp << endl;
    	}

		prevCountry=currCountry;
		prevDate=currDate;

	}
	remove( "temp.txt" );

	fout << endl;


//***********************question5**********************

	ifstream fin5,tempFin5;
	fin5.open("owid-covid-data.csv");
	getline(fin5,line); // başlık linedan kurtulmak için
	ofstream fout5;
	fout << "####Question5####" << endl;
	fout <<endl<<"Country minimum maximum average variation"<<endl;



	counter=0;
	while(getline(fin5,line)){					//dış loop iso değişti mi kontrol? bütün dosyayı okuyacak getline ile
		insertSpace(line);		
		stringstream s(line);
		getline(s,temp,',');
		getline(s,temp,',');
		getline(s,temp,',');
		currCountry=temp;
		getline(s,temp,',');
		currDate=temp;	
			//o güne özel total death sonraki looptaki ilk
		for (int i = 0; i < 12; i++){
		getline(s,temp,',');	
		}
		if (temp==" "){
			temp="0";
			continue;
 //			counter--;
		}else{
		reproArr[counter]=stof(temp);
		}
		total_repro+=reproArr[counter];
		counter++;
		
		if (reproArr[counter-1]<curr_min_repro){
			curr_min_repro=reproArr[counter-1];
		}
		if (reproArr[counter-1]>curr_max_repro){
			curr_max_repro=reproArr[counter-1];
		}

		if (currCountry == prevCountry){
 			fout5.open ("temp.txt");
  			fout5 << currCountry << " " << curr_min_repro <<" " << curr_max_repro << " " << total_repro / counter << " "
  			<< variation(reproArr,total_repro,counter) << endl;
  			fout5.close();
		}

  		if (currCountry != prevCountry){
  			tempFin5.open("temp.txt");
			getline(tempFin5,temp);
			tempFin5.close();
			fout << temp << endl;
			curr_min_repro=100000.0;
			curr_max_repro=0.0;
			total_repro=0.0;
			counter=0;
    	}

		prevCountry=currCountry;
		prevDate=currDate;

	}
	remove( "temp.txt" );
	fout << endl;


//*********************question6**********************

	ifstream fin6,tempFin6;
	fin6.open("owid-covid-data.csv");
	getline(fin6,line); // başlık linedan kurtulmak için
	ofstream fout6;
	fout << "####Question6####" << endl;
	fout <<endl<<"Country minimum maximum average variation"<<endl;

	counter=0;
	while(getline(fin6,line)){					//dış loop iso değişti mi kontrol? bütün dosyayı okuyacak getline ile
		insertSpace(line);		
		stringstream s(line);
		getline(s,temp,',');
		getline(s,temp,',');
		getline(s,temp,',');
		currCountry=temp;
		getline(s,temp,',');
		currDate=temp;	
			//o güne özel total death sonraki looptaki ilk
		for (int i = 0; i < 13; i++){
		getline(s,temp,',');	
		}
		if (temp==" "){
			temp="0";
			continue;
 //			counter--;
		}else{
		icuArr[counter]=stof(temp);
		}
		total_icu+=icuArr[counter];
		counter++;
		
		if (icuArr[counter-1]<curr_min_icu){
			curr_min_icu=icuArr[counter-1];
		}
		if (icuArr[counter-1]>curr_max_icu){
			curr_max_icu=icuArr[counter-1];
		}

		if (currCountry == prevCountry){
 			fout6.open ("temp.txt");
  			fout6 << currCountry << " " << curr_min_icu <<" " << curr_max_icu << " " << total_icu / counter << " "
  			<< variation(icuArr,total_icu,counter) << endl;
  			fout6.close();
		}

  		if (currCountry != prevCountry){
  			tempFin6.open("temp.txt");
			getline(tempFin6,temp);
			tempFin6.close();
			fout << temp << endl;
			curr_min_icu=100000.0;
			curr_max_icu=0.0;
			total_icu=0.0;
			counter=0;
    	}

		prevCountry=currCountry;
		prevDate=currDate;

	}
	remove( "temp.txt" );
	fout << endl;

//*******************question7*********************

 
	ifstream fin7,tempFin7;
	fin7.open("owid-covid-data.csv");
	getline(fin7,line); // başlık linedan kurtulmak için
	ofstream fout7;
	fout << "####Question7####" << endl;
	fout <<endl<<"Country minimum maximum average variation"<<endl;

	counter=0;
	while(getline(fin7,line)){					//dış loop iso değişti mi kontrol? bütün dosyayı okuyacak getline ile
		insertSpace(line);		
		stringstream s(line);
		getline(s,temp,',');
		getline(s,temp,',');
		getline(s,temp,',');
		currCountry=temp;
		getline(s,temp,',');
		currDate=temp;	
			//o güne özel total death sonraki looptaki ilk
		for (int i = 0; i < 16; i++){
		getline(s,temp,',');	
		}
		if (temp==" "){
			temp="0";
			continue;
 //			counter--;
		}else{
		hospArr[counter]=stof(temp);
		}
		total_hosp+=hospArr[counter];
		counter++;
		
		if (hospArr[counter-1]<curr_min_hosp){
			curr_min_hosp=hospArr[counter-1];
		}
		if (hospArr[counter-1]>curr_max_hosp){
			curr_max_hosp=hospArr[counter-1];
		}

		if (currCountry == prevCountry){
 			fout7.open ("temp.txt");
  			fout7 << currCountry << " " << curr_min_hosp <<" " << curr_max_hosp << " " << total_hosp / counter << " "
  			<< variation(hospArr,total_hosp,counter) << endl;
  			fout7.close();
		}

  		if (currCountry != prevCountry){
  			tempFin7.open("temp.txt");
			getline(tempFin7,temp);
			tempFin7.close();
			fout << temp << endl;
			curr_min_hosp=100000.0;
			curr_max_hosp=0.0;
			total_hosp=0.0;
			counter=0;
    	}

		prevCountry=currCountry;
		prevDate=currDate;

	}
	remove( "temp.txt" );

 
	fout << endl;

//*******************question8*********************

 
	ifstream fin8,tempFin8;
	fin8.open("owid-covid-data.csv");
	getline(fin8,line); // başlık linedan kurtulmak için
	ofstream fout8;
	fout << "####Question8####" << endl;
	fout <<endl<<"Country minimum maximum average variation"<<endl;


	counter=0;
	while(getline(fin8,line)){					//dış loop iso değişti mi kontrol? bütün dosyayı okuyacak getline ile
		insertSpace(line);		
		stringstream s(line);
		getline(s,temp,',');
		getline(s,temp,',');
		getline(s,temp,',');
		currCountry=temp;
		getline(s,temp,',');
		currDate=temp;	
			//o güne özel total death sonraki looptaki ilk
		for (int i = 0; i < 18; i++){
		getline(s,temp,',');	
		}
		if (temp==" "){
			temp="0";
			continue;
 //			counter--;
		}else{
		weekly_icuArr[counter]=stof(temp);
		}
		total_weekly_icu+=weekly_icuArr[counter];
		counter++;
		
		if (weekly_icuArr[counter-1]<curr_min_weekly_icu){
			curr_min_weekly_icu=weekly_icuArr[counter-1];
		}
		if (weekly_icuArr[counter-1]>curr_max_weekly_icu){
			curr_max_weekly_icu=weekly_icuArr[counter-1];
		}

		if (currCountry == prevCountry){
 			fout8.open ("temp.txt");
  			fout8 << currCountry << " " << curr_min_weekly_icu <<" " << curr_max_weekly_icu << " " << total_weekly_icu / counter << " "
  			<< variation(weekly_icuArr,total_weekly_icu,counter) << endl;
  			fout8.close();
		}

  		if (currCountry != prevCountry){
  			tempFin8.open("temp.txt");
			getline(tempFin8,temp);
			tempFin8.close();
			fout << temp << endl;
			curr_min_weekly_icu=100000.0;
			curr_max_weekly_icu=0.0;
			total_weekly_icu=0.0;
			counter=0;
    	}

		prevCountry=currCountry;
		prevDate=currDate;

	}
	remove( "temp.txt" );

	fout << endl;


//*******************question9*********************

 
	ifstream fin9,tempFin9;
	fin9.open("owid-covid-data.csv");
	getline(fin9,line); // başlık linedan kurtulmak için
	ofstream fout9;
	fout << "####Question9####" << endl;
	fout <<endl<<"Country minimum maximum average variation"<<endl;


	counter=0;
	while(getline(fin9,line)){					//dış loop iso değişti mi kontrol? bütün dosyayı okuyacak getline ile
		insertSpace(line);		
		stringstream s(line);
		getline(s,temp,',');
		getline(s,temp,',');
		getline(s,temp,',');
		currCountry=temp;
		getline(s,temp,',');
		currDate=temp;	
			//o güne özel total death sonraki looptaki ilk
		for (int i = 0; i < 20; i++){
		getline(s,temp,',');	
		}
		if (temp==" "){
			temp="0";
			continue;
 //			counter--;
		}else{
		weekly_hospArr[counter]=stof(temp);
		}
		total_weekly_hosp+=weekly_hospArr[counter];
		counter++;
		
		if (weekly_hospArr[counter-1]<curr_min_weekly_hosp){
			curr_min_weekly_hosp=weekly_hospArr[counter-1];
		}
		if (weekly_hospArr[counter-1]>curr_max_weekly_hosp){
			curr_max_weekly_hosp=weekly_hospArr[counter-1];
		}

		if (currCountry == prevCountry){
 			fout9.open ("temp.txt");
  			fout9 << currCountry << " " << curr_min_weekly_hosp <<" " << curr_max_weekly_hosp << " " << total_weekly_hosp / counter << " "
  			<< variation(weekly_hospArr,total_weekly_hosp,counter) << endl;
  			fout9.close();
		}

  		if (currCountry != prevCountry){
  			tempFin9.open("temp.txt");
			getline(tempFin9,temp);
			tempFin9.close();
			fout << temp << endl;
			curr_min_weekly_hosp=100000.0;
			curr_max_weekly_hosp=0.0;
			total_weekly_hosp=0.0;
			counter=0;
    	}

		prevCountry=currCountry;
		prevDate=currDate;

	}
	remove( "temp.txt" );
	fout << endl;
	

//*******************question10*********************

	
	ifstream fin10,tempFin10;
	fin10.open("owid-covid-data.csv");
	getline(fin10,line); // başlık linedan kurtulmak için
	ofstream fout10;
	fout << "####Question10####" << endl;
	fout <<endl<<"Country minimum maximum average variation"<<endl;
	
	counter=0;
	while(getline(fin10,line)){					//dış loop iso değişti mi kontrol? bütün dosyayı okuyacak getline ile
		insertSpace(line);		
		stringstream s(line);
		getline(s,temp,',');
		getline(s,temp,',');
		getline(s,temp,',');
		currCountry=temp;
		getline(s,temp,',');
		currDate=temp;	
			//o güne özel total death sonraki looptaki ilk
		for (int i = 0; i < 22; i++){
		getline(s,temp,',');	
		}
		if (temp==" "){
			temp="0";
			continue;
 //			counter--;
		}else{
		new_testArr[counter]=stof(temp);
		}
		total_new_test+=new_testArr[counter];
		counter++;
		
		if (new_testArr[counter-1]<curr_min_new_test){
			curr_min_new_test=new_testArr[counter-1];
		}
		if (new_testArr[counter-1]>curr_max_new_test){
			curr_max_new_test=new_testArr[counter-1];
		}

		if (currCountry == prevCountry){
 			fout10.open ("temp.txt");
  			fout10 << currCountry << " " << curr_min_new_test <<" " << curr_max_new_test << " " << total_new_test / counter << " "
  			<< variation(new_testArr,total_new_test,counter) << endl;
  			fout10.close();
		}

  		if (currCountry != prevCountry){
  			tempFin10.open("temp.txt");
			getline(tempFin10,temp);
			tempFin10.close();
			fout << temp << endl;
			curr_min_new_test=100000.0;
			curr_max_new_test=0.0;
			total_new_test=0.0;
			counter=0;
    	}

		prevCountry=currCountry;
		prevDate=currDate;

	}
	remove( "temp.txt" );

	fout << endl;

//*****************question11*******************

	ifstream fin11,tempFin11;
	fin11.open("owid-covid-data.csv");
	getline(fin11,line); // başlık linedan kurtulmak için
	ofstream fout11;
	fout << "####Question11####" << endl;
	fout <<endl<<"Country minimum maximum average variation"<<endl;



	while(getline(fin11,line)){					//dış loop iso değişti mi kontrol? bütün dosyayı okuyacak getline ile
		insertSpace(line);		
		stringstream s(line);
		getline(s,temp,',');
		getline(s,temp,',');
		getline(s,temp,',');
		currCountry=temp;
		getline(s,temp,',');
		currDate=temp;
		for (int i = 0; i < 23; i++){
		getline(s,temp,',');	
		}	//o güne özel total case
		if (temp==" "){
			temp="0";
		}
			total_test=stoi(temp);
		if (currCountry == prevCountry){
			//	;
 			fout11.open ("temp.txt");
  			fout11 << currCountry << "'s total test : " << total_test << endl;
  			fout11.close();
		}

  		if (currCountry != prevCountry){
  			tempFin11.open("temp.txt");
			getline(tempFin11,temp);
			tempFin11.close();
			fout << temp << endl;
    	}	
		prevCountry=currCountry;
		prevDate=currDate;

	}
	remove( "temp.txt" );
	fout << endl;

//*******************question12**********************

 
	ifstream fin12,tempFin12;
	fin12.open("owid-covid-data.csv");
	getline(fin12,line); // başlık linedan kurtulmak için
	ofstream fout12;
	fout << "####Question12####" << endl;
	fout <<endl<<"Country minimum maximum average variation"<<endl;

	counter=0;
	while(getline(fin12,line)){					//dış loop iso değişti mi kontrol? bütün dosyayı okuyacak getline ile
		insertSpace(line);		
		stringstream s(line);
		getline(s,temp,',');
		getline(s,temp,',');
		getline(s,temp,',');
		currCountry=temp;
		getline(s,temp,',');
		currDate=temp;	
			//o güne özel total death sonraki looptaki ilk
		for (int i = 0; i < 22; i++){
		getline(s,temp,',');	
		}
		if (temp==" "){
			temp="0";
			continue;
 //			counter--;
		}else{
		pos_rateArr[counter]=stof(temp);
		}
		total_pos_rate+=pos_rateArr[counter];
		counter++;
		
		if (pos_rateArr[counter-1]<curr_min_pos_rate){
			curr_min_pos_rate=pos_rateArr[counter-1];
		}
		if (pos_rateArr[counter-1]>curr_max_pos_rate){
			curr_max_pos_rate=pos_rateArr[counter-1];
		}

		if (currCountry == prevCountry){
 			fout12.open ("temp.txt");
  			fout12 << currCountry << " " << curr_min_pos_rate <<" " << curr_max_pos_rate << " " << total_pos_rate / counter << " "
  			<< variation(pos_rateArr,total_pos_rate,counter) << endl;
  			fout12.close();
		}

  		if (currCountry != prevCountry){
  			tempFin12.open("temp.txt");
			getline(tempFin12,temp);
			tempFin12.close();
			fout << temp << endl;
			curr_min_pos_rate=1000000.0;
			curr_max_pos_rate=0.0;
			total_pos_rate=0.0;
			counter=0;
    	}

		prevCountry=currCountry;
		prevDate=currDate;

	}
	remove( "temp.txt" );
	fout << endl;

//*******************question13**********************
 
	ifstream fin13,tempFin13;
	fin13.open("owid-covid-data.csv");
	getline(fin13,line); // başlık linedan kurtulmak için
	ofstream fout13;
	fout << "####Question13####" << endl;
	fout <<endl<<"Country minimum maximum average variation"<<endl;


	counter=0;
	while(getline(fin13,line)){					//dış loop iso değişti mi kontrol? bütün dosyayı okuyacak getline ile
		insertSpace(line);		
		stringstream s(line);
		getline(s,temp,',');
		getline(s,temp,',');
		getline(s,temp,',');
		currCountry=temp;
		getline(s,temp,',');
		currDate=temp;	
			//o güne özel total death sonraki looptaki ilk
		for (int i = 0; i < 22; i++){
		getline(s,temp,',');	
		}
		if (temp==" "){
			temp="0";
			continue;
 //			counter--;
		}else{
		test_per_caseArr[counter]=stof(temp);
		}
		total_test_per_case+=test_per_caseArr[counter];
		counter++;
		
		if (test_per_caseArr[counter-1]<curr_min_test_per_case){
			curr_min_test_per_case=test_per_caseArr[counter-1];
		}
		if (test_per_caseArr[counter-1]>curr_max_test_per_case){
			curr_max_test_per_case=test_per_caseArr[counter-1];
		}

		if (currCountry == prevCountry){
 			fout13.open ("temp.txt");
  			fout13 << currCountry << " " << curr_min_test_per_case <<" " << curr_max_test_per_case << " " << total_test_per_case / counter << " "
  			<< variation(test_per_caseArr,total_test_per_case,counter) << endl;
  			fout13.close();
		}

  		if (currCountry != prevCountry){
  			tempFin13.open("temp.txt");
			getline(tempFin13,temp);
			tempFin13.close();
			fout << temp << endl;
			curr_min_test_per_case=100.0;
			curr_max_test_per_case=0.0;
			total_test_per_case=0.0;
			counter=0;
    	}

		prevCountry=currCountry;
		prevDate=currDate;

	}
	remove( "temp.txt" );

	fout << endl;
	
//**************question14****************


	ifstream fin14,tempFin14;
	fin14.open("owid-covid-data.csv");
	getline(fin14,line); // başlık linedan kurtulmak için
	ofstream fout14;

	fout << "####Question14####" << endl;
	fout <<endl<<"Country Vaccinated at least 1 time"<<endl;


	while(getline(fin14,line)){					//dış loop iso değişti mi kontrol? bütün dosyayı okuyacak getline ile
		insertSpace(line);		
		stringstream s(line);
		getline(s,temp,',');
		getline(s,temp,',');
		getline(s,temp,',');
		currCountry=temp;
		getline(s,temp,',');
		currDate=temp;
		for (int i = 0; i < 32; i++){
		getline(s,temp,',');	
		}	//o güne özel total case
		if (temp==" "){
			temp="0";
		}
			people_vacc=stoi(temp);
		if (currCountry == prevCountry){
			//	;
 			fout14.open ("temp.txt");
  			fout14 << currCountry << " " << people_vacc << endl;
  			fout14.close();
		}

  		if (currCountry != prevCountry){
  			tempFin14.open("temp.txt");
			getline(tempFin14,temp);
			tempFin14.close();
			fout << temp << endl;
    	}	
		prevCountry=currCountry;
		prevDate=currDate;

	}
	remove( "temp.txt" );
	fout << endl;

//**************question15****************


	ifstream fin15,tempFin15;
	fin15.open("owid-covid-data.csv");
	getline(fin15,line); // başlık linedan kurtulmak için
	ofstream fout15;
	fout << "####Question15####" << endl;
	fout <<endl<<"Country Vaccinated 2 time"<<endl;


	while(getline(fin15,line)){					//dış loop iso değişti mi kontrol? bütün dosyayı okuyacak getline ile
		insertSpace(line);		
		stringstream s(line);
		getline(s,temp,',');
		getline(s,temp,',');
		getline(s,temp,',');
		currCountry=temp;
		getline(s,temp,',');
		currDate=temp;
		for (int i = 0; i < 33; i++){
		getline(s,temp,',');	
		}	//o güne özel total case
		if (temp==" "){
			temp="0";
		}
			people_vacc_full=stoi(temp);
		if (currCountry == prevCountry){
			//	;
 			fout15.open ("temp.txt");
  			fout15 << currCountry << " " << people_vacc_full << endl;
  			fout15.close();
		}

  		if (currCountry != prevCountry){
  			tempFin15.open("temp.txt");
			getline(tempFin15,temp);
			tempFin15.close();
			fout << temp << endl;
    	}	
		prevCountry=currCountry;
		prevDate=currDate;

	}
	remove( "temp.txt" );
	fout << endl;


//**************question16****************


	ifstream fin16,tempFin16;
	fin16.open("owid-covid-data.csv");
	getline(fin16,line); // başlık linedan kurtulmak için
	ofstream fout16;
	fout << "####Question16####" << endl;
	fout <<endl<<"Country Vaccinations Administered"<<endl;



	while(getline(fin16,line)){					//dış loop iso değişti mi kontrol? bütün dosyayı okuyacak getline ile
		insertSpace(line);		
		stringstream s(line);
		getline(s,temp,',');
		getline(s,temp,',');
		getline(s,temp,',');
		currCountry=temp;
		getline(s,temp,',');
		currDate=temp;
		for (int i = 0; i < 31; i++){
		getline(s,temp,',');	
		}	//o güne özel total case
		if (temp==" "){
			temp="0";
		}
			total_vacc=stoi(temp);
		if (currCountry == prevCountry){
			//	;
 			fout16.open ("temp.txt");
  			fout16 << currCountry << " " << total_vacc << endl;
  			fout16.close();
		}

  		if (currCountry != prevCountry){
  			tempFin16.open("temp.txt");
			getline(tempFin16,temp);
			tempFin16.close();
			fout << temp << endl;
    	}	
		prevCountry=currCountry;
		prevDate=currDate;

	}
	remove( "temp.txt" );
	fout << endl;



//**************question17****************


	ifstream fin17,tempFin17;
	fin17.open("owid-covid-data.csv");
	getline(fin17,line); // başlık linedan kurtulmak için
	ofstream fout17;
	fout << "####Question17####" << endl;
	fout <<endl<<"Country  population  median  age aged 65 older  aged 70 older  gdp per capita  extreme poverty  cardiovasc death rate  diabetes prevalence  female smokers  male smokers  handwashing facilities  hospital beds per thousand  life expectancy  human development index"<<endl;


	while(getline(fin17,line)){					//dış loop iso değişti mi kontrol? bütün dosyayı okuyacak getline ile
		insertSpace(line);		
		stringstream s(line);
		getline(s,temp,',');
		getline(s,temp,',');
		getline(s,temp,',');
		currCountry=temp;
		getline(s,temp,',');
		currDate=temp;
		for (int i = 0; i < 41; i++){
		getline(s,temp,',');	
		}	//o güne özel total case
		if (temp==" ")temp="0";
			population=stof(temp);
			getline(s,temp,',');
			getline(s,temp,',');
		if (temp==" ")temp="0";
			median_age=stof(temp);
			getline(s,temp,',');
		if (temp==" ")temp="0";	
			aged_65_older=stof(temp);
			getline(s,temp,',');	
		if (temp==" ")temp="0";
			aged_70_older=stof(temp);
			getline(s,temp,',');	
		if (temp==" ")temp="0";
			gdp_per_capita=stof(temp);
			getline(s,temp,',');	
		if (temp==" ")temp="0";
			extreme_poverty=stof(temp);
			getline(s,temp,',');	
		if (temp==" ")temp="0";
			cardiovasc_death_rate=stof(temp);
			getline(s,temp,',');	
		if (temp==" ")temp="0";
			diabetes_prevalence=stof(temp);
			getline(s,temp,',');	
		if (temp==" ")temp="0";
			female_smokers=stof(temp);
			getline(s,temp,',');	
		if (temp==" ")temp="0";
			male_smokers=stof(temp);
			getline(s,temp,',');	
		if (temp==" ")temp="0";
			handwashing_facilities=stof(temp);
			getline(s,temp,',');	
		if (temp==" ")temp="0";
			hospital_beds_per_thousand=stof(temp);
			getline(s,temp,',');	
		if (temp==" ")temp="0";
			life_expectancy=stof(temp);
			getline(s,temp);	
		if (temp==" ")temp="0"; 

		//human_development_index=stof(temp);
		//fout << "temp: '" << temp << "'";

		if (currCountry == prevCountry){
			//	;
 			fout17.open ("temp.txt");
  			fout17 << currCountry << " " << population << " "<<  median_age<< " " << aged_65_older<< " " << aged_70_older<< " "
  			 <<  gdp_per_capita << " "<< extreme_poverty << " "<< cardiovasc_death_rate << " "<< diabetes_prevalence << " "
  			 << female_smokers << " "<< male_smokers << " "<< handwashing_facilities << " " << hospital_beds_per_thousand << " "
  			 << life_expectancy << " "<< temp << endl;
  			fout17.close();
		}

  		if (currCountry != prevCountry){
  			tempFin17.open("temp.txt");
			getline(tempFin17,temp);
			tempFin17.close();
			fout << temp << endl;
    	}	
		prevCountry=currCountry;
		prevDate=currDate;

	}
	remove( "temp.txt" );
	fout << endl;









	return 0;
}





void insertSpace(string& str){

	for(string::size_type i = 0; i < str.size(); i++) {
    	if (str[i]==','){
    		str.insert(i," ");
//    		str.insert(i+2," ");

    		i++;
    	}
	}
}

bool compDate(string first, string second){

	if (first>second){		//we can do this because the order is yyyy-month-day thus later dates will be bigger 
		return false;
	}
	return true;

}


double variation(double arr[],double sum,int size){

	double	variationVal=0.0;
	for(int i = 0; i < size; i++)
         variationVal+= pow(arr[i] - (sum/size), 2);

    return sqrt(variationVal / size);
}