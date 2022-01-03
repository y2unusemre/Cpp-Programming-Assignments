#include <iostream>
#include <cstdlib>
#include <time.h>

using namespace std;

const int NUM_DUELS = 10000;

void Aaron_shoots(bool aaron, bool& bob, bool& charlie);
void Bob_shoots(bool& aaron, bool bob, bool& charlie);
void Charlie_shoots(bool& aaron, bool& bob, bool charlie);


int main(){
	
	bool aaron_Alive, bob_Alive, charlie_Alive;
	int aaronWins = 0;
	int bobWins = 0;
	int charlieWins = 0;
	int i;
	

	srand (time(NULL));

	for (i = 0; i < NUM_DUELS; i++){

		aaron_Alive=true;
		bob_Alive=true;
		charlie_Alive=true;

		do{
			Aaron_shoots	(aaron_Alive,bob_Alive,charlie_Alive);
			Bob_shoots		(aaron_Alive,bob_Alive,charlie_Alive);
			Charlie_shoots	(aaron_Alive,bob_Alive,charlie_Alive);			
		} while((aaron_Alive && bob_Alive) 
			|| 	(aaron_Alive && charlie_Alive)	
			||	(bob_Alive && charlie_Alive));  


		if (aaron_Alive)				
			aaronWins++;
		else if (bob_Alive)
			bobWins++;
		else if (charlie_Alive)
			charlieWins++;
		else {					// I added this 'else' to make sure it counts 10000 duels otherwise it would be around 8000 for a reason i did not understand
			i--;
		}

	}


	cout << "Aaron won " << aaronWins << "/10000 duels or " << 
		(static_cast<double>(aaronWins)/NUM_DUELS)*100 << " %" << endl;
	cout << "Bob won " << bobWins << "/10000 duels or " << 
		(static_cast<double>(bobWins)/NUM_DUELS)*100 << " %" << endl;
	cout << "Charlie won " << charlieWins << "/10000 duels or " << 
		(static_cast<double>(charlieWins)/NUM_DUELS)*100 << " %" << endl;

	return 0;
}


void Aaron_shoots(bool aaron, bool& bob, bool& charlie){
	int shot;
	if (aaron==false)
		return;

	shot = rand() % 3;

	if (shot==0){
		if (charlie){
			charlie=false;
		}else if (bob){
			bob=false;
		}
	}
	return;

}

void Bob_shoots(bool& aaron, bool bob, bool& charlie){
	int shot;
	if (aaron==false)
		return;

	shot = rand() % 2;

	if (shot==0){
		if (charlie){
			charlie=false;
		}else if (aaron){
			aaron=false;
		}
	}
	return;




}
void Charlie_shoots(bool& aaron, bool& bob, bool charlie){

	if (charlie==false)
		return;

	if (bob){
		bob=false;
	}else if (aaron){
		aaron=false;
	}
	return;
}
