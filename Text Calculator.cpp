#include <iostream>
#include <fstream>
#include <string>
#include <map>
#include <vector>
#include <filesystem>
using namespace std;
#define satir lines[i]

string scanbtw(const string& str, const string& delimeter1, const string& delimeter2) {
	int pos = str.find(delimeter1) + delimeter1.size();
	int pos1 = str.find(delimeter2);
	return str.substr(pos, pos1 - pos);
}

string scanbtw(const string& str, int pos, const string& delimeter2) {
	int pos1 = str.find(delimeter2);
	return str.substr(pos, pos1 - pos);
}
string scanbtw(const string& str, int pos, int pos1) {
	return str.substr(pos, pos1 - pos + 1);
}
string scanbtw(const string& str, const string& delimeter1, int pos1) {
	int pos = str.find(delimeter1) + delimeter1.size();
	return str.substr(pos, (pos1 - pos) + 1);
}

void bosluksil(string& str) {
	str.erase(remove(str.begin(), str.end(), ' '), str.end());
}


class allstr {
public://deðiþkenler
	string dosyaadi; string dosyastring; string parantezici;  string* lines = nullptr;
	size_t hmlines = 1; size_t whami = 0; size_t pos = 0; map<string, double> variables;
	map <string, double>::iterator itr;
	size_t hmvars; int hmplus = 0;
	fstream dosya;
	void chmlines(string& str) {
		for (size_t i = 0; i < str.size(); i++) {
			if (str[i] == '\n') hmlines++;
		}
		while (str[str.size() - 1] == '\n') { hmlines--; str.pop_back(); }

	}
	bool numbered(const string& str) {
		string ab = str.substr(str.find("=") + 1); bool numbered = false;
		for (size_t i = 0; i < str.size(); i++) {
			if ((str[i] < 58 && str[i]>47) && !(str[i] > 64 && str[i] < 91))
				numbered = true;
			else if (str[i] > 64 && str[i] < 91) { numbered = false; break; }
			else continue;

		}
		return numbered;
	}
	void deiskenatama() {
		for (size_t i = 0; i < hmlines; i++) {
			if (satir.find("=") != string::npos) {
				string var = scanbtw(satir, 0, "=");
				string val = scanbtw(satir, "=", satir.size());
				double value = atof(val.c_str());
				variables.insert(pair<string, double>(var, value));
			}
		}
	}
	double toplama(string strr) {
		string str = strr; string temp;
		if (str.find("+") == string::npos) {
			if (str[0] < 58 && str[0] > 47) {
				return atof(str.c_str());
			}
			else return variables[str];
		}

		for (size_t i = 0; i < str.size(); i++) {
			if (str[i] != '+' && str[i] != '-')
				temp += str[i];
			else {
				if (variables.find(temp) == variables.end()) {
					str.erase(0, i + 1); return atof(temp.c_str()) + toplama(str);
				}
				else { str.erase(0, i + 1); return variables[temp] + toplama(str); }
			}
		}

		//return ret;
	}
	double bolme(string strr) {
		string str = strr; string temp;
		if (str.find("/") == string::npos) {
			if (str[0] < 58 && str[0] > 47) {
				return atof(str.c_str());
			}
			else return variables[str];
		}
		for (size_t i = 0; i < str.size(); i++) {
			if (str[i] != '/')
				temp += str[i];
			else {
				if (variables.find(temp) == variables.end()) {
					str.erase(0, i + 1); return atof(temp.c_str()) / bolme(str);
				}
				else { str.erase(0, i + 1); return variables[temp] / bolme(str); }
			}
		}


	}
	double carpma(string strr) {
		string str = strr; string temp;
		if (str.find("*") == string::npos) {
			if (str[0] < 58 && str[0] > 47) {
				return atof(str.c_str());
			}
			else return variables[str];
		}
		for (size_t i = 0; i < str.size(); i++) {
			if (str[i] != '*')
				temp += str[i];
			else {
				if (variables.find(temp) == variables.end()) {
					str.erase(0, i + 1); return atof(temp.c_str()) * carpma(str);
				}
				else { str.erase(0, i + 1); return variables[temp] * carpma(str); }
			}
		}


	}
	void ifelse(string& str) {
		string var = scanbtw(str, 0, "=");
		string ifthen = scanbtw(str, "IF", "THEN");
		string thenelse = scanbtw(str, "THEN", "ELSE");
		string elsend = scanbtw(str, "ELSE", str.size());
		if (str.find(">") != string::npos) {
			string left = scanbtw(ifthen, 0, ">");
			string right = scanbtw(ifthen, ">", ifthen.size());
			if (islem(left) > islem(right)) {
				variables[var] = variables[thenelse];
			}
			else variables[var] = variables[elsend];

		}
		else if (str.find("<=") != string::npos) {
			string left = scanbtw(ifthen, 0, "<=");
			string right = scanbtw(ifthen, "<=", ifthen.size());
			if (islem(left) <= islem(right)) {
				variables[var] = variables[thenelse];
			}
			else variables[var] = variables[elsend];

		}
		else if (str.find(">=") != string::npos) {
			string left = scanbtw(ifthen, 0, ">=");
			string right = scanbtw(ifthen, ">=", ifthen.size());
			if (islem(left) >= islem(right)) {
				variables[var] = variables[thenelse];
			}
			else variables[var] = variables[elsend];

		}
		else if (str.find("==") != string::npos) {
			string left = scanbtw(ifthen, 0, "==");
			string right = scanbtw(ifthen, "==", ifthen.size());
			if (islem(left) == islem(right)) {
				variables[var] = variables[thenelse];
			}
			else variables[var] = variables[elsend];

		}

		else if (str.find("<") != string::npos) {
			string left = scanbtw(ifthen, 0, "<");
			string right = scanbtw(ifthen, "<", ifthen.size());
			if (islem(left) < islem(right)) {
				variables[var] = variables[thenelse];
			}
			else variables[var] = variables[elsend];

		}
		else if (str.find(">") != string::npos) {
			string left = scanbtw(ifthen, 0, ">");
			string right = scanbtw(ifthen, ">", ifthen.size());
			if (islem(left) > islem(right)) {
				variables[var] = variables[thenelse];
			}
			else variables[var] = variables[elsend];

		}
	}
	void loop(string& str) {
		string lptimes = scanbtw(str, "LOOP", "TIMES");
		string timesnd = scanbtw(str, "TIMES", str.size());
		for (int i = 0; i < atoi(timesnd.c_str()); i++) {
			islem(lptimes);
		}

	}
	double islem(string& str) {
		string temp = scanbtw(str, 0, str.find("=") - 1);
		string temp1 = str.substr(str.find("=") + 1, str.size());
		if (str.find("(") != string::npos && str.find(")") != string::npos)
		{
			string temp = scanbtw(str, "(", ")");
			int pos1 = str.find("("); int pos2 = str.find(")");
			str.replace(pos1, pos2 - pos1 + 1, to_string(islem(temp)));
			islem(str);
			//return islem(scanbtw(str, "(", ")")); //burda r value regerans olmaz mý
		}
		else {
			if (str.find("*") != string::npos) {
				if (str.find("/") != string::npos) {
					if (str.find("+") != string::npos || str.find("-") != string::npos) {}//çarpma bölme toplama
					else {}//çarpma bölme
				}
				else if (str.find("+") != string::npos || temp1.find("-") != string::npos) {
					vector<int> pos; int tsayac = 0;
					for (size_t i = 0; i < temp1.size(); i++) {
						if (temp1[i] == '+')
						{
							tsayac++; pos.push_back(i);
						}
						else continue;
					}
					string* crp = new string[tsayac + 1];
					for (int i = 0; i < tsayac + 1; i++) {
						if (i == 0) { crp[i] = scanbtw(temp1, 0, pos[0] - 1); }
						else if (i == tsayac) { crp[i] = scanbtw(temp1, pos[i - 1] + 1, temp1.size()); }
						else {
							crp[i] = scanbtw(temp1, pos[i - 1] + 1, pos[i] - 1);
						}
					}
					double b = 0;
					for (int i = 0; i < tsayac + 1; i++) {
						b += carpma(crp[i]);
					}
					variables[temp] = b;

					return variables[temp];
				}//çarpma toplama
				else {
					variables[temp] = carpma(str.substr(str.find("=") + 1));
					return variables[temp];
				}//çarpma

			}
			else if (str.find("/") != string::npos) {
				if (str.find("+") != string::npos || str.find("-") != string::npos) {}//bölme toplama
				else {
					variables[temp] = bolme(str.substr(str.find("=") + 1));
					return variables[temp];
				}//bölme

			}
			else if (str.find("+") != string::npos || str.find("-") != string::npos) {
				variables[temp] += toplama(str.substr(str.find("=") + 1));
				return variables[temp];
			} // toplama


			if (str[0] > 47 && str[0] < 58) {
				return atof(str.c_str());
			}
			else { return variables[str]; }
		}
	}
	allstr(string s) :dosya(s), dosyaadi(s) {
		dosyaadi.replace(dosyaadi.find("."), dosyaadi.length(), ".out");
		ofstream cikis(dosyaadi);
		getline(dosya, dosyastring, '?');
		chmlines(dosyastring); lines = new string[hmlines];
		for (size_t i = 0; i < hmlines; i++) {
			while (whami < dosyastring.size()) {
				if (dosyastring[whami] != '\n') { lines[i] += dosyastring[whami]; whami++; }
				else { whami++; break; }
			}
		}
		for (size_t i = 0; i < hmlines; i++) {
			bosluksil(satir);	//buraya kadar satýr satýr ayýrdýk ve boþluklarý yok ettik
		}
		deiskenatama();
		for (int i = 0; i < hmlines; i++) {
			if (satir.find("IF") != string::npos) { ifelse(satir); }
			else if (satir.find("LOOP") != string::npos) { loop(satir); }
			else if (satir.find("OUT") != string::npos) {
				string ab = scanbtw(satir, "OUT", satir.size());
				cikis << variables[ab];
			}
			else if (!numbered(satir)) { islem(satir); }
			else continue;
		}


	}
};
int main(){

	try {
		filesystem::path p(".\\"); //gets the current path.

		if (!is_directory(p)) {
			cout << "!not in a accessable directory!" << endl;
			return 1;
		}
	/*	cout << "Current Path:" << absolute(p) << endl;
		cout << "--------------------------------------" << endl;
		cout << "Inp (.inp) files in this folder" << endl;
		cout << "--------------------------------------" << endl;*/
		for (const filesystem::directory_entry& dre : filesystem::directory_iterator(p))
		{
			if (!is_directory(dre))    // is a file
			{
				if (dre.path().extension() == ".inp")
				{

					allstr a(dre.path().filename().string());
				}
			}
		}
	}
	catch (const filesystem::filesystem_error& ex)
	{
		cout << ex.what() << endl;
	}

		
	return 0;
	
}
