#include <iostream>
#include <fstream>
#include <string>
using namespace std;
////////stake/////////
const int SIZE_BUF = 30;
const int SIZE_C = 11;
const int SIZE_CM = 2;
const int INTERPUNKSZYN_S = 9;//wielkosc interpunkcji
const char TEMP[] = "temp.txt"; //nazwa pliku tymczasowego pomocniczego 
const char COMMANDS_M[][SIZE_BUF] = { //rodzaje komend
	"ERROR", "STAT"
};
const char INTERPUNKSZYN[] = "!?,.-';:-"; 
const char COMMANDS[][SIZE_BUF] = { //komendy
"ERROR:SPACJA",
"ERROR:ZNAK",
"ERROR:SLOWO",
"STAT:ZNAK",
"STAT:ZNAKNS",
"STAT:SLOWO",
"STAT:ZDANIE",
"TRANSFORM:MALE",
"TRANSFORM:DUZE",
"TRANSFORM:ZDANIE",
 "LEAVE" };


void menu(){
	cout << "PROSTY EDYTOR TEKSTU - EDYTEX" << endl;
	cout << "Podaj komende w celu anaizy!" << endl;
	cout << "1.Error-" << endl;
	cout << "spacja - eliminacja wielokrotnej spacji" << endl;
	cout << "znak - eliminacja wielokrotnych znakow interpunkcjynych" << endl;
	cout << "slowo - powtorzenia slow" << endl;
	cout << "2.Stat-" << endl;
	cout << "znak - ilosc znakow w tekscie" << endl;
	cout << "znakNS - ile jest znakow w tekscie bez spacji"<< endl;
	cout << "slowo - ile jest slow w tekscie" << endl;
	cout << "zdanie - ile jest zdan w tekscie" << endl;
	cout << "3.Transform-" << endl;
	cout << "male - zamien na male" << endl;
	cout << "duze - zamien na duze" << endl;
	cout << "zdanie -zamien jak w zdaniu" << endl;
	cout << "leave - wylacz programik" << endl;
}
//rozdziela wczytana komende na instrukcje i dana do wczytania
//usuwa spacje i pozwala na luzniejsza forme wczytania
void comparator(string Cmd, char Action[],char Name[]){
	int i = 0;
	int j = 0;
	int k = 0;
	while (Cmd[i] == ' '){
		i++;
	}
	while (Cmd[i] != '\0' && Cmd[i] != '\n' && Cmd[i] != '(' && Cmd[i] != ' '){
		Action[k] = toupper(Cmd[i]);
		i++;
		k++;
	}
	Action[k] = '\0';
	while (Cmd[i] == ' ' || Cmd[i] == '('){
		i++;
	}
	while (Cmd[i] != '\0' && Cmd[i] != ')' && Cmd[i] != '\n' && Cmd[i] != ' '){
		while (Cmd[i] == ' '){
			i++;
		}
		Name[j] = Cmd[i];
		j++;
		i++;
	}
	Name[j] = '\0';
}
///szukamy komendy 
int searchForCommand(char Action[SIZE_BUF],bool &All){
	for (int i = 0; i < SIZE_CM; i++){
		if (strcmp(Action, COMMANDS_M[i]) == 0){
			All = true;
			if (i == 0) return 0;
			else if (i == 1)return 3;
		}
	}
	for (int i = 0; i < SIZE_C; i++){
		if (strcmp(Action, COMMANDS[i]) == 0) return i;
	}
	return -1;
}
//zlicza illosc zdan
void statSentences(fstream &File){
	if (!File.is_open()){
		cout << "Plik nie istnieje" << endl << endl;
		return;
	}
	File.clear();
	File.seekg(0);
	char sign;
	int i = 0;
	while (1){
		File.get(sign);
		if (File.eof()){
			if (sign != '.') i++;
			break;
		}
		if (sign == '.')i++;
	}
	cout << "Tekst posiada " << i << " zdan" << endl << endl;
}
//zlicza slowa w tekscie
void statString(fstream &File){
	if (!File.is_open()){
		cout << "Plik nie istnieje" << endl << endl;
		return;
	}
	File.clear();
	File.seekg(0);
	string word;
	int i = 0;
	while (1){
		File >> word;
		if (File.eof()){
			if (word != "," && word != ".")i++;
			break;
		}
		if (word != "," && word != ".")i++;
	}
	cout << "Tekst posiada " << i << " slowa" << endl << endl;
}

//statystyka bez spacji
void statChar(fstream &File){
	if (!File.is_open()){
		cout << "Plik nie istnieje" << endl<<endl;
		return;
	}
	File.clear();
	File.seekg(0);
	char sign;
	int i = 0;
	while (1){
		File.get(sign);
		if (File.eof()) break;
		if (sign != '\t' && sign != '\n' && sign != '\v' 
			&& sign != '\r' && sign != '\f')i++;
	}
	cout << "Tekst posiada " << i << " znakow nie liczac bialych(z spacjami)" << endl<<endl;
}
//statystyka z spacjami
void statCharNS(fstream &File){
	if (!File.is_open()){
		cout << "Plik nie istnieje" << endl << endl;
		return;
	}
	File.clear();
	File.seekg(0);
	char sign;
	int i = 0;
	while (1){
		File.get(sign);
		if (File.eof()) break;
		if (isspace(sign) == 0) i++;
	}
	cout << "Tekst posiada " << i << " znakow nie liczac bialych" << endl<<endl;
}
//wszystkie litery na duze
void toBig(fstream &File, char Name[]){
	if (!File.is_open()){
		cout << "Plik nie istnieje" << endl << endl;
		return;
	}
	File.clear();
	File.seekg(0);
	fstream temp(TEMP, ios::out | ios::trunc);
	char sign;
	while (1){
		File.get(sign);
		if (File.eof()) break;
		if (isspace(sign) == 0){
			temp << char(toupper(sign));
		}
		else temp << sign;
	}
	File.close();
	temp.close();
	remove(Name);
	rename(TEMP, Name);
}
//wszystkie litery zmienia na male
void toSmall(fstream &File,char Name[]){
	if (!File.is_open()){
		cout << "Plik nie istnieje" << endl << endl;
		return;
	}
	File.clear();
	File.seekg(0);
	fstream temp(TEMP, ios::out | ios::trunc);
	char sign;
	while (1){
		File.get(sign);
		if (File.eof()) break;
		if (isspace(sign) == 0){
			temp << char(tolower(sign));
		}
		else temp << sign;
	}
	File.close();
	temp.close();
	remove(Name);
	rename(TEMP, Name);
}
//kopiuje slowo, konczy gdy napotka spacje itp
void copy(fstream &File, char &Sign, char tab[]) {
	int i = 0;
	while (Sign != ' ' && Sign != '.' && Sign != ',' && !File.eof()){
		tab[i++] = Sign;
		File.get(Sign);
	}
	tab[i] = '\0';

}
void repetition(fstream &File, char Name[]){
	if (!File.is_open()){
		cout << "Plik nie istnieje" << endl << endl;
		return;
	}
	File.clear();
	File.seekg(0);
	fstream temp(TEMP, ios::out | ios::trunc);
	bool start = true;
	bool in = false;
	char first[SIZE_BUF], second[SIZE_BUF];
	char sign;
	while (1){
		File >> sign;
		if (File.eof()) break;
		if (sign != ' ' && sign != '.'&& sign != ','){
			if (start == true){
				copy(File, sign, first);
				in = false;
				start = false;
			}
			else {
				strcpy_s(second, first);
				copy(File, sign, first);
				while (strcmp(first, second) == 0){
					while ((sign == ' ' || sign == '.' || sign == ',') && !File.eof()) File.get(sign);
					if (File.eof())break;
					copy(File, sign, first);
					strcpy_s(second, first);
				}
				temp << first;
			}
		}
		if (File.eof())break;
		temp << sign;
	}
	File.close();
	temp.close();
	remove(Name);
	rename(TEMP, Name);
}
//funckja usuwa za duzo spacji wystepujacych w tekscie
void manySpaces(fstream &File, char Name[]){
	if (!File.is_open()){
		cout << "Plik nie istnieje" << endl << endl;
		return;
	}
	File.clear();
	File.seekg(0);
	fstream temp(TEMP, ios::out | ios::trunc);
	bool duble = false;
	char sign;
	while (1){
		File.get(sign);
		if (File.eof()) break;
		if (sign == ' ' && duble == true){
			while (!File.eof() && sign == ' ')File.get(sign);
			duble = false;
		}
		else if (sign == ' '){
			duble = true;
		}
		
	    temp << sign;
	}
	File.close();
	temp.close();
	remove(Name);
	rename(TEMP, Name);
}
//sprawdza czy litera to znak interpunkcyjy
int checkSignInter(char s){
	for (int i = 0; i < INTERPUNKSZYN_S; i++){
		if (s == INTERPUNKSZYN[i]) return 1;
	}
	return -1;
}

//funckja usuwa za duzo znakow interpunkcyjnych (powtarzajace sie)
void manyInterpunkszyn(fstream &File, char Name[]){
	if (!File.is_open()){
		cout << "Plik nie istnieje" << endl << endl;
		return;
	}
	File.clear();
	File.seekg(0);
	fstream temp(TEMP, ios::out | ios::trunc);
	bool duble = false;
	char sign;
	while (1){
		File.get(sign);
		if (File.eof()) break;
		if (checkSignInter(sign) == 1 && duble == true){
			while (!File.eof() && checkSignInter(sign)==1)File.get(sign);
			duble = false;
		}
		if (File.eof()) break;
		else if (checkSignInter(sign) == 1){
			duble = true;
		}

		temp << sign;
	}
	File.close();
	temp.close();
	remove(Name);
	rename(TEMP, Name);
}
void changeSign(fstream &File, char Name[]){
	if (!File.is_open()){
		cout << "Plik nie istnieje" << endl << endl;
		return;
	}
	File.clear();
	File.seekg(0);
	fstream temp(TEMP, ios::out | ios::trunc);
	char sign;
	while (1){
		File.get(sign);
		if (File.eof()) break;
		if (isspace(sign) == 0){
			if (isupper(sign))temp << char(tolower(sign));
			else temp << char(toupper(sign));
		}
		else temp << sign;
	}
	File.close();
	temp.close();
	remove(Name);
	rename(TEMP, Name);
}
void pickOption(int Choice,bool All, fstream &File,bool &Program, char Name[]){
	switch (Choice){
	case 0:
		manySpaces(File, Name);
		if (All == false) break;
	case 1:
		manyInterpunkszyn(File, Name);
		if (All == false) break;
	case 2:
		repetition(File, Name);
		break;
	case 3:
		statChar(File);
		if (All == false) break;
	case 4:
		statCharNS(File);
		if (All == false) break;
	case 5:
		statString(File);
		if (All == false) break;
	case 6:
		statSentences(File);
		break;
	case SIZE_C-1 :
		Program = false;
		return;
	case 7:
		toSmall(File,Name);
		break;
	case 8:
		toBig(File, Name);
		break;
	case 9:
		changeSign(File, Name);
		break;
	}
	if (All == true) All = false;
}
void input(string &Cmd,bool &Program){
	char Action[SIZE_BUF], Name[SIZE_BUF];
	int Choice;
	bool All = false;
	fstream File;
	cout << "Podaj komende ";
	getline(cin, Cmd);
	system("CLS");
	comparator(Cmd,Action,Name);
	File.open(Name, ios::in);
	Choice = searchForCommand(Action, All);
	pickOption(Choice, All, File,Program,Name);

}
int main(){
	bool Program = true;
	string Command;

	//////////////////////////
	while (Program){
		menu();
		input(Command,Program);
	}
	//////////////////////////
}