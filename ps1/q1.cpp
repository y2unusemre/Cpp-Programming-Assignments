#include <iostream>

using namespace std;

int main(int argc, char const *argv[]){
	
int check;

	for (int i = 3; i < 100; i++){
		check=1;
		for (int j = 2; j < i-1; j++){
			if (i%j==0){
				check=0;
			}
		}
		if (check==1){
			cout << i << endl;
		}
	}




	return 0;
}