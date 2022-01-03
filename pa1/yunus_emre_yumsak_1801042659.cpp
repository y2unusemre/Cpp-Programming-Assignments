#include <iostream>
#include <cstdlib>
#include <ctime>

using namespace std;


int findDigit(int x);
int generateNumber(int length);
int myPow(int base, int exp);

int main(int argc, char const **argv){



	int cInput; 
	int i,j;
	int userInput;
	int inPlace=0,nonPlace=0;
	int tries=0;
	int arr[9];
	int arrAlt[9];
	int userDigit;
	int digit;
	bool uniq=true;

	srand(static_cast<int>(time(NULL)));
	
	if ( (argv[1][1]!='r' && argv[1][1]!='u' ) || (cInput<0) ){
		cout << "E0" << endl;
		return 0;
	}else if (argv[1][1]=='u'){
		cInput = stoi(argv[2]);
	}else if (argv[1][1]=='r'){
		cInput = generateNumber(stoi(argv[2]));
	}


	digit=findDigit(cInput);						//finddigit fuction counts and returns the length
	
	for (i = digit-1; i >= 0; i--) {				//this for loop seperates the generated or given number into array
	    arr[i] = cInput % 10;
	    cInput /= 10;

	}


	for (i = 0; i < digit - 1; i++){				//this loop checks if there are any repeated numbers
  		for (j = i + 1;j < digit; j++){   	
     		if (arr[i] == arr[j]) 					//if number is not unique E0 is printed and program is executed				
  				uniq=false;
  		}
	}
	if (!uniq){
		cout << "E0"<< endl;
		return 0;
	}

	

	//	cout << "="<< arr[0]<<arr[1]<<arr[2]<<arr[3]<<arr[4]<<arr[5]<<arr[6]<<arr[7]<< endl;
		


	while(1){
	
		cin >> userInput;
		userDigit=findDigit(userInput);				//counting  users input length 	

		if (userInput < myPow(10,digit-1) ){		//this part is a little tricky i used ascii values of the entered value if user 	
			cout << "E2" << endl;					//enters meaningless stuff it has to be less than 10^digit. if so E2 error is printed	
			return 0;
		}
		
		if (userDigit!=digit){
			cout << "E1" << endl;					//if user enters less or more digits E1 message is printed
			return 0;
		}
		


		for (i = digit-1; i >= 0; i--) {
		    arrAlt[i] = userInput % 10;				//users input is seperated into array
	    	userInput /= 10;
		}

		for (i = 0; i < digit - 1; i++){		
  			for (j = i + 1;j < digit; j++){   	
     			if (arrAlt[i] == arrAlt[j]) 		//check user inpput's uniqueness	
  					uniq=false;
  			}
		}
		if (!uniq){
			cout << "E1"<<endl;						//if users input not unique E1 is printed
			return 0;
		}

		for (i = 0; i < digit ; i++){		
  			for (j = 0;j < digit ; j++){   	
     			if (arr[i] == arrAlt[j]) {			//nonPlace counts every number that exist and inPlace counts every number in correct place
  					nonPlace++;
  					if (arr[i] == arrAlt[i]){
  						inPlace++;
  					}
  				}
  			}
		}
		tries++;									//in every turn tries counts the number of user inputs
		if (inPlace==digit){
			cout << "FOUND "<< tries << endl; 
			return 0;
		}else{
		cout << inPlace << " " << nonPlace-inPlace <<endl;
		}
		inPlace=0;									//inplace and nonplace are initialled 0 again	
		nonPlace=0;
	}



	return 0;


}


int findDigit(int x){								//counts a given numbers digit

	int i;
		
	for (i = 0; i <= 9; i++){
		x= x/10;
		if (x<1){
			break;
		}
	}

	return i+1;
}


int generateNumber(int length){						//computer generates unique number

	int numbers[9];
	int finalValue = 0;
	int temp,i=1,j;
	bool check;
	numbers[0] = (rand()%9)+1;						//specially generated first number since it can not be 0 


	finalValue += myPow(10,length-1)*numbers[0];	//then this number is added in final value
	cout << finalValue<<"..."<<endl;				//for example if length is 6 and numbers[0] is 2 final value becomes 200000 at this point, 
													//such method will be done in the next steps and the finalvalue will be a unique number
	while(i != length){
		temp= rand()%10;
		//cout<<temp<< "1.denem"<<endl;
		check=true;
		for (j = 0; j < i; j++){
			if (temp == numbers[j]){				//check wheter new random integer exist if so generates again
				check=false;
			}
		}
		if (check){
			numbers[i]=temp;
			cout << numbers[i]<<" 2.denem"<<endl;					
			i++;
			finalValue += myPow(10,length-i)*numbers[i-1];			
		}

	}

	return finalValue;



}

int myPow(int base, int exp){						//this is a basic power function i did not make it detailed because there was no need to
	int x=1;
	for (int i = 0; i < exp; i++){
		x = x*base;
	}
	return x;
}