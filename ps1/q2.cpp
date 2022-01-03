#include <iostream>
#include <cstdlib>
#include <ctime>

using namespace std;
 
int humanTurn(int humanTotalScore);
int computerTurn(int computerTotalScore);
int rollDice();

int main(){

	int humanTotalScore=0, computerTotalScore=0;
	bool gameover =false;

	srand(static_cast<int>(time(NULL)));


	while(!gameover){
		
		if (!gameover){
			humanTotalScore 	+= humanTurn(humanTotalScore);
			if (humanTotalScore >= 100){
				cout << "Congragulations! You win."  <<endl;
				gameover = true;
			}

		}
		
		if (!gameover){
			computerTotalScore 	+= computerTurn(computerTotalScore);
			if (computerTotalScore >= 100){
				cout << "Sorry, Computer wins."  <<endl;
				gameover = true;		
			}

		}

		
	}
	return 0;
}



int humanTurn(int humanTotalScore){
	int score = 0, roll;
	char cInput;
	bool bTurnOver = false;

	cout << "Its your turn! Enter 'r' to roll" <<endl;
	cin >> cInput;


do{
	roll = rollDice();

	cout << "You rolled " << roll  <<endl;

	if (roll==1){
		cout << "You lose your turn! " << "Enter 'c' to continue" << endl;;
		cin >> cInput;
		return 0;
	}
	else{
		score += roll;
		cout << "Your score this round is " << score  <<endl;
		cout << "If you hold, your total score will be " << humanTotalScore+score <<endl;
		cout << "Enter 'r' to roll again, Enter 'h' to hold" <<endl;
		cin >> cInput;

		if (cInput=='h'){
			bTurnOver=true;
		}

	}
}while(!bTurnOver);



return score;

}

int computerTurn(int computerTotalScore){
	int score = 0, roll;
	char cInput;
	bool bTurnOver = false;

	cout << "Its computer's turn!" <<endl;


do{
	roll = rollDice();

	cout << "Computer rolled " << roll  <<endl;

	if (roll==1){
		cout << "Computer lose its turn! " << "Enter 'c' to continue" << endl;
		cin >> cInput;
		return 0;
	}
	else{
		score += roll;
		cout << "Computer's score this round is " << score  <<endl;
		cout << "If the computer holds, its total score will be " << computerTotalScore+score <<endl;
		
		if ((score >= 20) || computerTotalScore + score > 100){
			cout << "Computer holds!" << "Enter 'c' to continue " << endl;
			cin >> cInput;
			bTurnOver=true;
		}

	}

}while(!bTurnOver);



return score;

}

int rollDice(){
	
	return (rand()%6)+1;
}