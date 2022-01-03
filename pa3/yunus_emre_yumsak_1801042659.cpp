#include <iostream>
#include <cstdlib>
#include <vector>
#include <fstream>
#include <string>

using namespace std;

//const int MAX_VALUE = 255;

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


		ppmImage operator+ (ppmImage &obj) {										// operator+ overloading creates an empty obj with first arguments dimensions
			ppmImage res(getColumn(),getRow());		

			if (column != obj.getColumn() || row != obj.getRow()){					//if dimensions are not same returns empty image
				return res;
			}
		
			res.setMax(getMax());


			for (int i = 0; i < getColumn(); i++){
				for (int j = 0; j < getRow(); j++){									// setting the pixells of result
				 	res.setRed	(i,j, getRed(i,j) 	+ obj.getRed(i,j)	);
				 	res.setGreen(i,j, getGreen(i,j) + obj.getGreen(i,j)	);
				 	res.setBlue	(i,j, getBlue(i,j) 	+ obj.getBlue(i,j)	);        		
				}
			}

			return res;
	    }

		ppmImage operator- (ppmImage &obj) {
			ppmImage res(getColumn(),getRow());
			
			if (column != obj.getColumn() || row != obj.getRow()){
				return res;
			}

			res.setMax(getMax());


			for (int i = 0; i < getColumn(); i++){
				for (int j = 0; j < getRow(); j++){
				 	res.setRed	(i,j, getRed(i,j) 	- obj.getRed(i,j)	);
				 	res.setGreen(i,j, getGreen(i,j) - obj.getGreen(i,j)	);
				 	res.setBlue	(i,j, getBlue(i,j) 	- obj.getBlue(i,j)	);        		
				}
			}

			return res;
	    }

		friend ostream &operator<< (ostream &out, ppmImage &obj);

		int& operator()(int x, int y, int color_choice){
			if (color_choice==1){
			    return this->image[x][y].r;									//returns a reference of the chosen color of a chosen pixel
			}
			if (color_choice==2){
			    return this->image[x][y].g;
			}
			if (color_choice==3){
			    return this->image[x][y].b;
			}
		}

	private:
		int column;
		int row;
		int MAX_VALUE;														//members
		vector<vector<pixel> > image;
};

ostream &operator<< (ostream &out, ppmImage &obj){

	out << "P3" << endl;
	out << obj.getRow() << " " << obj.getColumn() << endl;
	out << obj.getMax() << endl;
	for (int i = 0; i < obj.getColumn(); i++){
		for (int j = 0; j < obj.getRow(); j++){
			out << obj.getRed(i,j) << " " << obj.getGreen(i,j) << " " << obj.getBlue(i,j) << " ";
		}
		out << endl;
	}
    return out;
}


ppmImage::ppmImage(){			//default constructor
	column=0;
	row=0;
	MAX_VALUE=0;
}

ppmImage::ppmImage(int x, int y){ 
	if (x<0 || y<0 ){			//checking validity
		exit(0);
	}
	column=x;
	row=y;
	MAX_VALUE=255;

	for (int i = 0; i < column; i++){
		vector<pixel> temp(y);
		for (int j = 0; j < row; j++){
			temp[j].r=MAX_VALUE;				//setting all pixels to white
			temp[j].g=MAX_VALUE;
			temp[j].b=MAX_VALUE;	
		}
		image.push_back(temp);
	}
}

ppmImage::ppmImage(const string source_ppm_file_name){	//file reading constructor 
	
	readfromFile(source_ppm_file_name);
}
//getters
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
//setters
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
	if (newRed < 0){								//setters check if value is higher than max or lower than 0 
		image[x][y].r = 0;
	}
	if (newRed > MAX_VALUE)
	{
		image[x][y].r = MAX_VALUE;
	}
}
void ppmImage::setGreen(int x,int y, int newGreen){
	if (newGreen <= MAX_VALUE && newGreen >= 0){
		image[x][y].g = newGreen;
	}
	if (newGreen < 0){
		image[x][y].g = 0;
	}
	if (newGreen > MAX_VALUE){
		image[x][y].g = MAX_VALUE;
	}
}
void ppmImage::setBlue(int x,int y, int newBlue){
	if (newBlue <= MAX_VALUE && newBlue >= 0){
		image[x][y].b = newBlue;
	}
	if (newBlue < 0){
		image[x][y].b = 0;
	}
	if (newBlue > MAX_VALUE){
		image[x][y].b = MAX_VALUE;
	}
}

int ppmImage::savetoFile(const string source_ppm_file_name){


	ofstream fout(source_ppm_file_name.c_str());
	fout << "P3" << endl;
	fout << row << " " << column << endl;
	fout << MAX_VALUE << endl;
	for (int i = 0; i < column; i++){							//written pixel by pixel
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
	fin >> x;												//avoiding P and 3 chars
	fin >> x;

	fin >> column;
	fin >> row;
	fin >> MAX_VALUE;

	for (int i = 0; i < column; i++){						//read pixel by pixel
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

int	 ppmImage::pixelInfo(int x, int y, char color){ 		//returns individual pixel info
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

void ppmImage::changePixel(int x, int y, char color, int newVal){ //changes a chosen pixel's chosen channel
	
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

// returns 1 if the operation is successful. otherwise, returns 0.
// reads images from filename_image1 and filename_image2. Adds them and saves the resulting image to filename_image3
int test_addition(const string filename_image1, const string filename_image2, const string filename_image3);

// returns 1 if the operation is successful. otherwise, returns 0.
// reads images from filename_image1 and filename_image2. Subtracts filename_image2 from filename_image1 saves the resulting image to filename_image3
int test_subtraction(const string filename_image1, const string filename_image2, const string filename_image3);

// returns 1 if the operation is successful. otherwise, returns 0.
// reads images from filename_image1 and prints it to stdout
int test_print(const string filename_image1);


int main(int argc, char** argv){


	ppmImage obj1,denObj;


	if (argv[2]==NULL || argv[3]==NULL){
		return 0;
	}

// if choice number is 1
// check the existance of the optional arguments. If they are not given, exit
if (argv[1][0]=='1'){
	if (argv[4]==NULL){
		return 0;
	}
	test_addition(argv[2],argv[3],argv[4]);
}
	
// if choice number is 2
// check the existance of the optional arguments. If they are not given, exit
if (argv[1][0]=='2'){
	if (argv[4]==NULL){
		return 0;
	}
	test_subtraction(argv[2],argv[3],argv[4]);
}

if (argv[1][0]=='3'){
	read_ppm(argv[2],obj1);
	swap_channels(obj1,2);
	write_ppm(argv[3],obj1);
}

// if choice number is 4
// read ppm_file_name1 using function read_ppm
// swap green and blue channels. use swap_channels function
// write the updated data to a file named "ppm_file_name2". use write_ppm function.
if (argv[1][0]=='4'){
	read_ppm(argv[2],obj1);
	swap_channels(obj1,3);
	write_ppm(argv[3],obj1);
}

// if choice number is 5
// read ppm_file_name1 using function read_ppm
// create a new object which only contains red channel data of the file read. use single_color function
// write the data of the new object to a file named "ppm_file_name2". use write_ppm function.
if (argv[1][0]=='5'){
	read_ppm(argv[2],obj1);
	ppmImage obj2 = single_color(obj1,1);
	write_ppm(argv[3],obj2);

}

// if choice number is 6
// read ppm_file_name1 using function read_ppm
// create a new object which only contains green channel data of the file read. use single_color function
// write the data of the new object to a file named "ppm_file_name2". use write_ppm function.
if (argv[1][0]=='6'){
	read_ppm(argv[2],obj1);
	ppmImage obj2 = single_color(obj1,2);
	write_ppm(argv[3],obj2);
}

// if choice number is 7
// read ppm_file_name1 using function read_ppm
// create a new object which only contains blue channel data of the file read. ue single_color function
// write the data of the new object to a file named "ppm_file_name2". use write_ppm function.
if (argv[1][0]=='7'){
	read_ppm(argv[2],obj1);
	ppmImage obj2 = single_color(obj1,3);
	write_ppm(argv[3],obj2);
}

	return 0;
}

// returns 1 if the operation is successful. otherwise, returns 0.
// reads ppm data from file named as source_ppm_file_name. stores data in destination_object, which is already created outside of the function.
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
				temp=image_object_to_be_modified(i,j,1); 								//altered by using function call operator
				image_object_to_be_modified(i,j,1)=image_object_to_be_modified(i,j,2);
				image_object_to_be_modified(i,j,2)=temp;
			}
		}
		return 1;
	}
	if (swap_choice==2){
		for (i = 0; i < row; i++){
			for (j = 0; j < column; j++){
				temp=image_object_to_be_modified(i,j,3);
				image_object_to_be_modified(i,j,3)=image_object_to_be_modified(i,j,1);
				image_object_to_be_modified(i,j,1)=temp;
			}
		}
		return 1;
	}
	if (swap_choice==3){
		for (i = 0; i < row; i++){
			for (j = 0; j < column; j++){
				temp=image_object_to_be_modified(i,j,2);
				image_object_to_be_modified(i,j,2)=image_object_to_be_modified(i,j,3);
				image_object_to_be_modified(i,j,3)=temp;
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
				oneColor(i,j,1)=temp(i,j,1);						//altered by using function call operator
				oneColor(i,j,2)=0;
				oneColor(i,j,3)=0;
			}
		}

	}
	if (color_choice==2){
		for (int i = 0; i < temp.getColumn(); i++){
			for (int j = 0; j < temp.getRow(); j++){

				oneColor(i,j,1)=0;
				oneColor(i,j,2)=temp(i,j,2);
				oneColor(i,j,3)=0;
			}
		}
	}
	if (color_choice==3){
		for (int i = 0; i < temp.getColumn(); i++){
			for (int j = 0; j < temp.getRow(); j++){

				oneColor(i,j,1)=0;
				oneColor(i,j,2)=0;
				oneColor(i,j,3)=temp(i,j,3);
			}
		}
	}

	return oneColor;


}

// returns 1 if the operation is successful. otherwise, returns 0.
// reads images from filename_image1 and filename_image2. Adds them and saves the resulting image to filename_image3
int test_addition(const string filename_image1, const string filename_image2, const string filename_image3){
	
	ppmImage img1(filename_image1);
	ppmImage img2(filename_image2);
	ppmImage temp;
	temp = img1+img2;

	return temp.savetoFile(filename_image3);     //this member function already cheks if the operation is successful
}

// returns 1 if the operation is successful. otherwise, returns 0.
// reads images from filename_image1 and filename_image2. Subtracts filename_image2 from filename_image1 saves the resulting image to filename_image3
int test_subtraction(const string filename_image1, const string filename_image2, const string filename_image3){
	
	ppmImage img1(filename_image1);
	ppmImage img2(filename_image2);
	ppmImage temp;
	temp = img1-img2;

	return temp.savetoFile(filename_image3);
}

// returns 1 if the operation is successful. otherwise, returns 0.
// reads images from filename_image1 and prints it to stdout
int test_print(const string filename_image1){
	ppmImage temp(filename_image1);

	cout << temp << endl;

	if (temp.getRed(temp.getColumn(),temp.getRow()) >=0 || temp.getRed(temp.getColumn(),temp.getRow()) <= temp.getMax() ){
		return 1; 
	}
	return 0;
}