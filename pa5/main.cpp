#include <iostream>
#include <vector>
#include <fstream>
#include <string>
#include <sstream>
#include <algorithm>

using namespace std;

class catalog{										//catalog base class
	public:
		string title;
		string year;

};

class book : public catalog{						//book class derived from catalog
	public:
		string authors;
		string tags;

};

class music : public catalog{						//music class derived from catalog
	public:
		string artists;
		string genre;

};

class movie : public catalog{						//movie class derived from catalog
	public:
		string director;
		string genre;
		string starring;

};


void insert_cat(string line, vector<book> &vect);	//overloaded insert to catalog functions for all types
void insert_cat(string line, vector<music> &vect);
void insert_cat(string line, vector<movie> &vect);

int countChar(string str, char x);					//char counting used in missing field check				

void search_book(string line, vector<book> &catalog);		// search functions for all types
void search_music(string line, vector<music> &catalog);
void search_movie(string line, vector<movie> &catalog);

void sort_book(string line, vector<book> &catalog);				// sort functions for all types
void sort_music(string line, vector<music> &catalog);
void sort_movie(string line, vector<movie> &catalog);


void print_line(book entry);					//print functions overloaded for printing the line as it is in data.txt
void print_line(music entry);
void print_line(movie entry);


//book fields compare
bool compare_title_book(book m1, book m2);		//compare functions for sort() functions
bool compare_authors(book m1, book m2);
bool compare_year_book(book m1, book m2);
bool compare_tags(book m1, book m2);

//music fields compare
bool compare_title_music(music m1, music m2);
bool compare_artists(music m1, music m2);
bool compare_year_music(music m1, music m2);
bool compare_genre_music(music m1, music m2);

//movie fields compare
bool compare_title_movie(movie m1, movie m2);
bool compare_director(movie m1, movie m2);
bool compare_year_movie(movie m1, movie m2);
bool compare_genre_movie(movie m1, movie m2);
bool compare_starring(movie m1, movie m2);





int main(){


	int count=0;						//for counting how many unique entries
	string catalog_type;
	string temp_line;
	
	string cmnd_line;


	vector<book> 	book_catalog;
	vector<music> 	music_catalog;
	vector<movie> 	movie_catalog;


	ifstream fin;						//data.txt input file
	fin.open("data.txt");
	getline(fin,catalog_type);			

	ifstream fincmnd;					//commands.txt input file
	fincmnd.open("commands.txt");

	ofstream ofs;															// these three lines are for erasing the content of output.txt from previous runs
	ofs.open("output.txt", std::ofstream::out | std::ofstream::trunc);		// since i openned it in append mode
	ofs.close();

	ofstream fout;
	fout.open("output.txt",ios::app);
	fout << "Catalog Read: " << catalog_type <<endl;

	if (catalog_type=="book"){
		while(getline(fin,temp_line)){
			insert_cat(temp_line,book_catalog);				//vector of catalog is read by this loop
		}
		for(auto itr : book_catalog){
			count++;										//counting how many unique entries
		}
		fout << count << " unique entries"<<endl;
		while (getline(fincmnd,cmnd_line)){	
			
			if (cmnd_line[1]=='e')							//second char of input checked for search or sort
				search_book(cmnd_line,book_catalog);
			if (cmnd_line[1]=='o')
				sort_book(cmnd_line,book_catalog);

		}
	}

	if (catalog_type=="music"){
		while(getline(fin,temp_line)){
			insert_cat(temp_line,music_catalog);
		}
		for(auto itr : music_catalog){
			count++;
		}
		fout << count << " unique entries"<<endl;
		while (getline(fincmnd,cmnd_line)){
			
			if (cmnd_line[1]=='e')
				search_music(cmnd_line,music_catalog);
			if (cmnd_line[1]=='o')
				sort_music(cmnd_line,music_catalog);

		}
	}

	if (catalog_type=="movie"){
		while(getline(fin,temp_line)){
			insert_cat(temp_line,movie_catalog);
		}
		for(auto itr : movie_catalog){
			count++;
		}
		fout << count << " unique entries"<<endl;
		while (getline(fincmnd,cmnd_line)){
			
			if (cmnd_line[1]=='e')
				search_movie(cmnd_line,movie_catalog);
			if (cmnd_line[1]=='o')
				sort_movie(cmnd_line,movie_catalog);
			
		}
	}


	return 0;
}


void insert_cat(string line, vector<book> &vect){

	stringstream s(line);
	book temp_book;													//first temp is filled with informations then pushed backed to vector

	try{
		if (countChar(line,'"')!=8)									//checking the line if it has any missing fields
			throw 0;
	}catch(int ex){
				ofstream fout;
				fout.open("output.txt", ios::app);
				fout << "Exception: missing field"<<endl;
				fout << line <<endl;
				return;
	}

	getline(s,temp_book.title,'"');
	getline(s,temp_book.title,'"');
	

	try{
		for(auto itr : vect){
			if (itr.title==temp_book.title)
			throw 1;
		}
	}catch(int ex){
		ofstream fout;
		fout.open("output.txt", ios::app);							//checking existing objects for duplicate entries
		fout << "Exception: duplicate entry"<<endl;
		fout << line <<endl;
		return;
	}
	
	getline(s,temp_book.authors,'"');
	getline(s,temp_book.authors,'"');
	

	getline(s,temp_book.year,'"');
	getline(s,temp_book.year,'"');
	

	getline(s,temp_book.tags,'"');
	getline(s,temp_book.tags,'"');


	vect.push_back(temp_book);						//if the entry is safe its pushed back to vector

}


void insert_cat(string line, vector<music> &vect){

	stringstream s(line);
	music temp_music;													//first temp is filled with informations then pushed backed to vector

	try{
		if (countChar(line,'"')!=8)							//checking the line if it has any missing fields
			throw 0;
	}catch(int ex){
				ofstream fout;
				fout.open("output.txt", ios::app);
				fout << "Exception: missing field"<<endl;
				fout << line <<endl;
				return;
	}



	getline(s,temp_music.title,'"');
	getline(s,temp_music.title,'"');



	try{
		for(auto itr : vect){
			if (itr.title==temp_music.title)				//checking existing objects for duplicate entries
			throw 1;
		}
	}catch(int ex){
		ofstream fout;
		fout.open("output.txt", ios::app);
		fout << "Exception: duplicate entry"<<endl;
		fout << line <<endl;
		return;
	}
	
	getline(s,temp_music.artists,'"');
	getline(s,temp_music.artists,'"');

	getline(s,temp_music.year,'"');
	getline(s,temp_music.year,'"');

	getline(s,temp_music.genre,'"');
	getline(s,temp_music.genre,'"');

	vect.push_back(temp_music);								//if the entry is safe its pushed back to vector

}


void insert_cat(string line, vector<movie> &vect){

	stringstream s(line);
	movie temp_movie;													//first temp is filled with informations then pushed backed to vector

	try{
		if (countChar(line,'"')!=10)						//checking the line if it has any missing fields
			throw 0;
	}catch(int ex){
				ofstream fout;
				fout.open("output.txt", ios::app);
				fout << "Exception: missing field"<<endl;
				fout << line <<endl;
				return;
	}

	getline(s,temp_movie.title,'"');
	getline(s,temp_movie.title,'"');

	try{
		for(auto itr : vect){
			if (itr.title==temp_movie.title)				//checking existing objects for duplicate entries
			throw 1;
		}
	}catch(int ex){
		ofstream fout;
		fout.open("output.txt", ios::app);
		fout << "Exception: duplicate entry"<<endl;
		fout << line <<endl;
		return;
	}
	
	getline(s,temp_movie.director,'"');
	getline(s,temp_movie.director,'"');

	getline(s,temp_movie.year,'"');
	getline(s,temp_movie.year,'"');

	getline(s,temp_movie.genre,'"');
	getline(s,temp_movie.genre,'"');

	getline(s,temp_movie.starring,'"');
	getline(s,temp_movie.starring,'"');



	vect.push_back(temp_movie);								//if the entry is safe its pushed back to vector



}

int countChar(string str, char x){							//basic char counter function
    int count = 0, n = 10;
    for (int i = 0; i < str.size(); i++){
        if (str[i] == x)
            count++;
    }
    return count;
}

void search_book(string line, vector<book> &catalog){

	stringstream s(line);

	string word;
	string field;

	getline(s,word,'"');						//word and field seperated 
	getline(s,word,'"');

	getline(s,field,'"');
	getline(s,field,'"');

	ofstream fout;
	fout.open("output.txt", ios::app);


	try{
		if (field!="title" && field!="authors" && field!="year" && field!="tags") //checking commands 
			throw 99;
	}catch(int ex){
			
			fout << "Exception: command is wrong"<<endl;
			fout << line <<endl;
		return;
	}


	fout << line << endl;
	
	if (field=="title"){											//searched in specified field then printed
		for(auto itr : catalog){
			if (itr.title.find(word) != std::string::npos) {
	    		print_line(itr);
			}
		}
	}
	if (field=="authors"){
		for(auto itr : catalog){
			if (itr.authors.find(word) != std::string::npos) {
	    		print_line(itr);
			}
		}
	}
	if (field=="year"){
		for(auto itr : catalog){
			if (itr.year.find(word) != std::string::npos) {
	    		print_line(itr);
			}
		}
	}
	if (field=="tags"){
		for(auto itr : catalog){
			if (itr.tags.find(word) != std::string::npos) {
	    		print_line(itr);
			}
		}
	}
	

}

void search_music(string line, vector<music> &catalog){

	stringstream s(line);

	string word;
	string field;

	getline(s,word,'"');						//word and field seperated 
	getline(s,word,'"');

	getline(s,field,'"');
	getline(s,field,'"');

	ofstream fout;
	fout.open("output.txt", ios::app);


	try{
		if (field!="title" && field!="artists" && field!="year" && field!="genre") //checking commands 
			throw 99;
	}catch(int ex){
			
			fout << "Exception: command is wrong"<<endl;
			fout << line <<endl;
		return;
	}


	fout << line << endl;
	
	if (field=="title"){											//searched in specified field then printed
		for(auto itr : catalog){
			if (itr.title.find(word) != std::string::npos) {
	    		print_line(itr);
			}
		}
	}
	if (field=="artists"){
		for(auto itr : catalog){
			if (itr.artists.find(word) != std::string::npos) {
	    		print_line(itr);
			}
		}
	}
	if (field=="year"){
		for(auto itr : catalog){
			if (itr.year.find(word) != std::string::npos) {
	    		print_line(itr);
			}
		}
	}
	if (field=="genre"){
		for(auto itr : catalog){
			if (itr.genre.find(word) != std::string::npos) {
	    		print_line(itr);
			}
		}
	}
	

}



void search_movie(string line, vector<movie> &catalog){

	stringstream s(line);

	string word;
	string field;

	getline(s,word,'"');
	getline(s,word,'"');									//word and field seperated 

	getline(s,field,'"');
	getline(s,field,'"');

	ofstream fout;
	fout.open("output.txt", ios::app);


	try{
		if (field!="title" && field!="director" && field!="year" && field!="genre" && field!="starring") //checking commands 
			throw 99;
	}catch(int ex){
			
			fout << "Exception: command is wrong"<<endl;
			fout << line <<endl;
		return;
	}


	fout << line << endl;
	
	if (field=="title"){													//searched in specified field then printed
		for(auto itr : catalog){
			if (itr.title.find(word) != std::string::npos) {
	    		print_line(itr);
			}
		}
	}
	if (field=="director"){
		for(auto itr : catalog){
			if (itr.director.find(word) != std::string::npos) {
	    		print_line(itr);
			}
		}
	}
	if (field=="year"){
		for(auto itr : catalog){
			if (itr.year.find(word) != std::string::npos) {
	    		print_line(itr);
			}
		}
	}
	if (field=="genre"){
		for(auto itr : catalog){
			if (itr.genre.find(word) != std::string::npos) {
	    		print_line(itr);
			}
		}
	}
	if (field=="starring"){
		for(auto itr : catalog){
			if (itr.starring.find(word) != std::string::npos) {
	    		print_line(itr);
			}
		}
	}


}


void sort_book(string line, vector<book> &catalog){

	stringstream s(line);
	string field;

	getline(s,field,'"');					//field is read
	getline(s,field,'"');

	ofstream fout;
	fout.open("output.txt", ios::app);

	try{
		if (field!="title" && field!="authors" && field!="year" && field!="tags")	//checking for validity of field
			throw 99;
	}catch(int ex){
			
			fout << "Exception: command is wrong"<<endl;
			fout << line <<endl;
		return;
	}

	fout << line << endl;

	if (field=="title"){
		sort(catalog.begin(), catalog.end(), compare_title_book);						//sorting according to specified field
	}
	if (field=="authors"){
		sort(catalog.begin(), catalog.end(), compare_authors);
	}
	if (field=="year"){
		sort(catalog.begin(), catalog.end(), compare_year_book);
	}
	if (field=="tags"){
		sort(catalog.begin(), catalog.end(), compare_tags);
	}

	for(auto itr : catalog){						//printing to file
		print_line(itr);
	}
}


void sort_music(string line, vector<music> &catalog){

	stringstream s(line);
	string field;

	getline(s,field,'"');
	getline(s,field,'"');

	ofstream fout;
	fout.open("output.txt", ios::app);
	
	try{
		if (field!="title" && field!="artists" && field!="year" && field!="genre")	//checking for validity of field
			throw 99;
	}catch(int ex){
			
			fout << "Exception: command is wrong"<<endl;
			fout << line <<endl;
		return;
	}

	fout << line << endl;

	if (field=="title"){
		sort(catalog.begin(), catalog.end(), compare_title_music);						//sorting according to specified field
	}
	if (field=="artists"){
		sort(catalog.begin(), catalog.end(), compare_artists);
	}
	if (field=="year"){
		sort(catalog.begin(), catalog.end(), compare_year_music);
	}
	if (field=="genre"){
		sort(catalog.begin(), catalog.end(), compare_genre_music);
	}

	for(auto itr : catalog){						//printing to file
		print_line(itr);
	}
}


void sort_movie(string line, vector<movie> &catalog){

	stringstream s(line);
	string field;

	getline(s,field,'"');
	getline(s,field,'"');

	ofstream fout;
	fout.open("output.txt", ios::app);
	
	
	try{
		if (field!="title" && field!="director" && field!="year" && field!="genre" && field!="starring")	//checking for validity of field
			throw 99;
	}catch(int ex){
			
			fout << "Exception: command is wrong"<<endl;
			fout << line <<endl;
		return;
	}
	fout << line << endl;

	if (field=="title"){
		sort(catalog.begin(), catalog.end(), compare_title_movie);						//sorting according to specified field
	}
	if (field=="director"){
		sort(catalog.begin(), catalog.end(), compare_director);
	}
	if (field=="year"){
		sort(catalog.begin(), catalog.end(), compare_year_movie);
	}
	if (field=="genre"){
		sort(catalog.begin(), catalog.end(), compare_genre_movie);
	}
	if (field=="starring"){
		sort(catalog.begin(), catalog.end(), compare_starring);
	}

	for(auto itr : catalog){						//printing to file
		print_line(itr);
	}
}


void print_line(book entry){						//since inputs are stored with fields print_line functions help print them as in data.txt

	ofstream fout;
	fout.open("output.txt", ios::app);
	fout <<'"'<< entry.title << '"'<< ' '; 
	fout <<'"'<< entry.authors << '"'<< ' '; 
	fout <<'"'<< entry.year << '"'<< ' '; 
	fout <<'"'<< entry.tags << '"'<<endl; 

}

void print_line(music entry){

	ofstream fout;
	fout.open("output.txt", ios::app);
	fout <<'"'<< entry.title << '"'<< ' '; 
	fout <<'"'<< entry.artists << '"' << ' '; 
	fout <<'"'<< entry.year << '"'<< ' '; 
	fout <<'"'<< entry.genre << '"'<<endl; 

}

void print_line(movie entry){

	ofstream fout;
	fout.open("output.txt", ios::app);
	fout <<'"'<< entry.title << '"'<< ' '; 
	fout <<'"'<< entry.director << '"'<< ' '; 
	fout <<'"'<< entry.year << '"'<< ' '; 
	fout <<'"'<< entry.genre << '"' << ' '; 
	fout <<'"'<< entry.starring << '"'<<endl; 

}


//book fields compare
bool compare_title_book(book m1, book m2){		//these functions are for sort() functions
	return (m1.title < m2.title);
}
bool compare_authors(book m1, book m2){
	return (m1.authors < m2.authors);
}
bool compare_year_book(book m1, book m2){
	return (m1.year < m2.year);
}
bool compare_tags(book m1, book m2){
	return (m1.tags < m2.tags);
}

//music fields compare
bool compare_title_music(music m1, music m2){
	return (m1.title < m2.title);
}
bool compare_artists(music m1, music m2){
	return (m1.artists < m2.artists);
}
bool compare_year_music(music m1, music m2){
	return (m1.year < m2.year);
}
bool compare_genre_music(music m1, music m2){
	return (m1.genre < m2.genre);
}

//movie fields compare
bool compare_title_movie(movie m1, movie m2){
	return (m1.title < m2.title);
}
bool compare_director(movie m1, movie m2){
	return (m1.director < m2.director);
}
bool compare_year_movie(movie m1, movie m2){
	return (m1.year < m2.year);
}
bool compare_genre_movie(movie m1, movie m2){
	return (m1.genre < m2.genre);
}
bool compare_starring(movie m1, movie m2){
	return (m1.starring < m2.starring);
}
