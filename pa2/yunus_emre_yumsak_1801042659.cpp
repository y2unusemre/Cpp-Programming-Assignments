#include <iostream>
#include <cstdlib>
#include <vector>
#include <fstream>
#include <string>

using namespace std;

class pixel{				// this class is used for indivudual pixels


public:
	int r;
	int g;
	int b;
};


class ppmImage{
public:
	ppmImage();											//default constractor 
	ppmImage(int x, int y);								//constructor with given dimensions
	ppmImage(const string source_ppm_file_name); 		//constructor with a file source 
	int getColumn();
	int getRow();
	int getMax();										//getters
	int getRed(int x,int y);
	int getGreen(int x,int y);
	int getBlue(int x,int y);

	void setColumn(int newColumn);
	void setRow(int newRow);
	void setMax(int newMax);							//setters
	void setRed(int x,int y, int newRed);
	void setGreen(int x,int y, int newGreen);
	void setBlue(int x,int y, int newBlue);

	int savetoFile(const string source_ppm_file_name);							//in order to save ppm image to a file.
	int  readfromFile(const string source_ppm_file_name);						//to read ppm image from a file.
	void printDimension();														//which prints dimensions of the ppm image.
	int	 pixelInfo(int x, int y, char color);									//individual pixel information
	void changePixel(int x, int y, char color, int newVal);						//for changing a pixel





private:
	int column;
	int row;
	int MAX_VALUE;														//members
	vector<vector<pixel> > image;
	
	
};


ppmImage::ppmImage(){
	column=0;
	row=0;
	MAX_VALUE=0;
}

ppmImage::ppmImage(int x, int y){
	if (x<0 || y<0 ){
		exit(0);
	}
	column=x;
	row=y;
	MAX_VALUE=255;

	for (int i = 0; i < column; i++){
		vector<pixel> temp(y);
		for (int j = 0; j < row; j++){
			temp[j].r=MAX_VALUE;
			temp[j].g=MAX_VALUE;
			temp[j].b=MAX_VALUE;	
		}
		image.push_back(temp);
	}
}

ppmImage::ppmImage(const string source_ppm_file_name){
	
	readfromFile(source_ppm_file_name);
}

int ppmImage::getColumn(){

	return column;
}
int ppmImage::getRow(){

	return row;
}
int ppmImage::getMax(){

	return MAX_VALUE;
}

int ppmImage::getRed	(int x,int y){

	return image[x][y].r;
}
int ppmImage::getGreen	(int x,int y){

	return image[x][y].g;	
}
int ppmImage::getBlue	(int x,int y){
	
	return image[x][y].b;
}

void ppmImage::setColumn(int newColumn){
	if (newColumn>0){
		column=newColumn;
	}	
}
void ppmImage::setRow(int newRow){
	if (newRow>0){
		row=newRow;
	}
}
void ppmImage::setMax(int newMax){
	if (newMax>0){
		MAX_VALUE=newMax;
	}
}

void ppmImage::setRed(int x,int y, int newRed){
	if (newRed <= MAX_VALUE && newRed >= 0){
		image[x][y].r = newRed;
	}
}
void ppmImage::setGreen(int x,int y, int newGreen){
	if (newGreen <= MAX_VALUE && newGreen >= 0){
		image[x][y].g = newGreen;
	}
}
void ppmImage::setBlue(int x,int y, int newBlue){
	if (newBlue <= MAX_VALUE && newBlue >= 0){
		image[x][y].b = newBlue;
	}
}

int ppmImage::savetoFile(const string source_ppm_file_name){


	ofstream fout(source_ppm_file_name.c_str());
	fout << "P3" << endl;
	fout << row << " " << column << endl;
	fout << MAX_VALUE << endl;
	for (int i = 0; i < column; i++){
		for (int j = 0; j < row; j++){
			fout << getRed(i,j) << " " << getGreen(i,j) << " " << getBlue(i,j) << " ";
		}
		fout << endl;
	}
	return 1;
}

int ppmImage::readfromFile(const string source_ppm_file_name){

	char x;
	ifstream fin;
	fin.open(source_ppm_file_name.c_str());
	fin >> x;
  	//	cout << x;
	fin >> x;
 	//	cout << x;

	fin >> column;
	fin >> row;
	fin >> MAX_VALUE;

	for (int i = 0; i < column; i++){
		vector<pixel> temp(row);
		for (int j = 0; j < row; j++){
			fin >> temp[j].r;
			fin >> temp[j].g;
			fin >> temp[j].b;
		}
		image.push_back(temp);
	}	

	return 1;

}

void ppmImage::printDimension(){
	
	cout << "Column: " << column << " Row: " << row << endl; 
}

int	 ppmImage::pixelInfo(int x, int y, char color){
	if (color == 'r'){
		return getRed(x,y);
	}
	if (color == 'g'){
		return getGreen(x,y);
	}
	if (color == 'b'){
		return getBlue(x,y);
	}
}

void ppmImage::changePixel(int x, int y, char color, int newVal){
	
	if (newVal < MAX_VALUE && newVal > 0){
			
		
		if (color == 'r'){
			setRed(x,y,newVal);
		}
		if (color == 'g'){
			setGreen(x,y,newVal);
		}
		if (color == 'b'){
			setBlue(x,y,newVal);
		}
	}
}



int read_ppm(const string source_ppm_file_name, ppmImage& destination_object);
int write_ppm(const string destination_ppm_file_name, const ppmImage& source_object);
int swap_channels(ppmImage& image_object_to_be_modified, int swap_choice);
ppmImage single_color(const ppmImage& source, int color_choice);

int main(int argc, char** argv){


	ppmImage obj1;


// if choice number is 1
// read ppm_file_name using function read_ppm
// write the same data without changing anything to a file named "o1.ppm". use write_ppm
//,! function.
if (argv[1][0]=='1'){
	read_ppm(argv[2],obj1);
	write_ppm("o1.ppm",obj1);
}
	

// if choice number is 2
// read ppm_file_name using function read_ppm
// swap red and green channels
// write the updated data to a file named "o2.ppm". use write_ppm function.
if (argv[1][0]=='2'){
	read_ppm(argv[2],obj1);
	swap_channels(obj1,1);
	write_ppm("o2.ppm",obj1);
}

// if choice number is 3
// read ppm_file_name using function read_ppm
// swap red and blue channels
// write the updated data to a file named "o3.ppm". use write_ppm function.
if (argv[1][0]=='3'){
	read_ppm(argv[2],obj1);
	swap_channels(obj1,2);
	write_ppm("o3.ppm",obj1);
}

// if choice number is 4
// read ppm_file_name using function read_ppm
// swap green and blue channels. use swap_channels function
// write the updated data to a file named "o4.ppm". use write_ppm function.
if (argv[1][0]=='4'){
	read_ppm(argv[2],obj1);
	swap_channels(obj1,3);
	write_ppm("o4.ppm",obj1);
}

// if choice number is 5
// read ppm_file_name using function read_ppm
// create a new object which only contains red channel data of the file read. ue single_color
//,! function
// write the data of the new object to a file named "o5.ppm". use write_ppm function.
if (argv[1][0]=='5'){
	read_ppm(argv[2],obj1);
	ppmImage obj2 = single_color(obj1,1);
	write_ppm("o5.ppm",obj2);
//	write_ppm("o5yan.ppm",obj1);

}

// if choice number is 6
// read ppm_file_name using function read_ppm
// create a new object which only contains green channel data of the file read. ue
//,! single_color function
// write the data of the new object to a file named "o6.ppm". use write_ppm function.
if (argv[1][0]=='6'){
	read_ppm(argv[2],obj1);
	ppmImage obj2 = single_color(obj1,2);
	write_ppm("o6.ppm",obj2);
}

// if choice number is 7
// read ppm_file_name using function read_ppm
// create a new object which only contains blue channel data of the file read. ue single_color
//,! function
// write the data of the new object to a file named "o7.ppm". use write_ppm function.
if (argv[1][0]=='7'){
	read_ppm(argv[2],obj1);
	ppmImage obj2 = single_color(obj1,3);
	write_ppm("o7.ppm",obj2);
}

	return 0;
}

// returns 1 if the operation is successful. otherwise, returns 0.
// reads ppm data from file named as source_ppm_file_name. stores data in destination_object,! which is already created outside of the function.
int read_ppm(const string source_ppm_file_name, ppmImage& destination_object){

		 if (destination_object.readfromFile(source_ppm_file_name)){
		 	return 1;	
		 }else
		 	return 0;
}


// returns 1 if the operation is successful. otherwise, returns 0.
// writes ppm data from source_object to the file named destination_ppm_file_name.
int write_ppm(const string destination_ppm_file_name, const ppmImage& source_object){

	ppmImage temp;
	temp=source_object;
	if (temp.savetoFile(destination_ppm_file_name)){
			return 1;
	}else
		return 0;


}


// this function swaps the color values of every pixel in a given ppm image.
// this function does not create a new object but modifies the given one.
// if swap_choice is 1: swaps red and green
// if swap_choice is 2: swaps red and blue
// if swap_choice is 3: swaps green and blue
// if swap_choice is not 1, 2 or 3: no swaps (this does not mean that the operation is not,! successful. the function should return 1 in this case if everything is normal)
// returns 1 if the operation is successful. otherwise, returns 0.
int swap_channels(ppmImage& image_object_to_be_modified, int swap_choice){

	int temp;
	int i,j;
	int row=image_object_to_be_modified.getRow();
	int column =image_object_to_be_modified.getColumn();

	if (swap_choice==1){
		for (i = 0; i < row; i++){
			for (j = 0; j < column; j++){
				temp = image_object_to_be_modified.getRed(i,j);
				image_object_to_be_modified.setRed(i,j,image_object_to_be_modified.getGreen(i,j));	
				image_object_to_be_modified.setGreen(i,j,temp);
			}
		}
		return 1;
	}
	if (swap_choice==2){
		for (i = 0; i < row; i++){
			for (j = 0; j < column; j++){
				temp = image_object_to_be_modified.getBlue(i,j);
				image_object_to_be_modified.setBlue(i,j,image_object_to_be_modified.getRed(i,j));
				image_object_to_be_modified.setRed(i,j,temp);
			}
		}
		return 1;
	}
	if (swap_choice==3){
		for (i = 0; i < row; i++){
			for (j = 0; j < column; j++){
				temp = image_object_to_be_modified.getGreen(i,j);
				image_object_to_be_modified.setGreen(i,j,image_object_to_be_modified.getBlue(i,j));
				image_object_to_be_modified.setBlue(i,j,temp);
			}
		}
		return 1;	
	}

	return 1;
	

}

	// creates and returns a copy of a new ppmImage object which stores only one color at each
	//pixel. This simply takes the source and copies only one color information and stores it in
	//a new object. The other color channels are simply going to be zeros.

	//if color_choice is 1: red channel is preserved
	//if color_choice is 2: green channel is preserved
	//if color_choice is 3: blue channel is preserved
ppmImage single_color(const ppmImage& source, int color_choice){
	ppmImage oneColor;
	ppmImage temp;
	temp=source;
	oneColor=source;

	oneColor.setColumn(temp.getColumn());
	oneColor.setRow(temp.getRow());
	oneColor.setMax(temp.getMax());

	if (color_choice==1){
		for (int i = 0; i < temp.getColumn(); i++){
			for (int j = 0; j < temp.getRow(); j++){
				oneColor.setRed(i,j,temp.getRed(i,j));
				oneColor.setGreen(i,j,0);
				oneColor.setBlue(i,j,0);

			}
		}

	}
	if (color_choice==2){
		for (int i = 0; i < temp.getColumn(); i++){
			for (int j = 0; j < temp.getRow(); j++){
				oneColor.setRed(i,j,0);
				oneColor.setGreen(i,j,temp.getGreen(i,j));
				oneColor.setBlue(i,j,0);
			}
		}
	}
	if (color_choice==3){
		for (int i = 0; i < temp.getColumn(); i++){
			for (int j = 0; j < temp.getRow(); j++){
				oneColor.setRed(i,j,0);
				oneColor.setGreen(i,j,0);
				oneColor.setBlue(i,j,temp.getBlue(i,j));
			}
		}
	}


 //	write_ppm("ahahaha.ppm",oneColor);
	return oneColor;


}

