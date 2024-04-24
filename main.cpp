#include <iostream>
#include <vector>
#include <string>
#include <fstream>

using namespace std;

// Khai báo trước class
class Sach;
class TheThuVien;
class DocGia;


/*======================================================================================
									CLASS SÁCH
======================================================================================*/
class Sach
{
private:
	int idSach;
	string ten;
	TheThuVien* the;
public:
	Sach(int idSach_arg, string ten_arg) : idSach(idSach_arg), ten(ten_arg), the(nullptr) {};

	// Set, get tên sách
	void setTen(string ten) {
		this->ten = ten;
	}

	string getTen() {
		return ten;
	}

	// Set, get thẻ
	void setThe(TheThuVien* the) {
		this->the = the;
	}

	TheThuVien* getThe() {
		return the;
	}
};


/*======================================================================================
								CLASS THẺ THƯ VIỆN
======================================================================================*/
class TheThuVien
{
protected:
	int idThe;
	int thangDK;
	string type;
	DocGia* docGia;
	vector <Sach*> books;
public:
	TheThuVien(int idThe_arg, string type_arg, int thangDK_arg)
		: idThe(idThe_arg), type(type_arg), thangDK(thangDK_arg), docGia(nullptr) {};

	// Get id thẻ
	int getIdThe() {
		return idThe;
	}

	// Set, get tháng đk
	void setThangDK(int thangDK_arg) {
		thangDK = thangDK_arg;
	}

	int getThangDK() {
		return thangDK;
	}

	// Set, get độc giả
	void setDocGia(DocGia* dg) {
		docGia = dg;
	}

	DocGia* getDocGia() {
		return docGia;
	}

	// Thêm sách
	void themSach(Sach* sach) {
		books.push_back(sach);
		sach->setThe(this);
	}

	// Get danh sách sách
	void getListSach() {
		for (int i = 0; i < books.size(); i++)
			cout << books[i]->getTen() << "\t" << books[i]->getThe()->getThangDK() << "\n";
	}

	// Tính tiền mỗi năm
	virtual double tinhTien() = 0;
};

class TheNguoiLon : public TheThuVien
{
public:
	TheNguoiLon(int idThe_arg, string type_arg, int thangDK_arg)
		: TheThuVien(idThe_arg, type_arg, thangDK_arg) {};

	double tinhTien() override {
		return 100000 * thangDK;
	}
};

class TheTreCon : public TheThuVien
{
public:
	TheTreCon(int idThe_arg, string type_arg, int thangDK_arg)
		: TheThuVien(idThe_arg, type_arg, thangDK_arg) {};

	double tinhTien() override {
		return 20000 * thangDK;
	}
};


/*======================================================================================
									CLASS ĐỘC GIẢ
======================================================================================*/
class DocGia
{
private:
	int idDocGia;
	string ten;
	int tuoi;
	TheThuVien* theThuVien;

public:
	DocGia(int idDocGia_arg, string ten_arg, int tuoi_arg)
		: idDocGia(idDocGia_arg), ten(ten_arg), tuoi(tuoi_arg) {
		this->theThuVien = nullptr;
	}

	DocGia(int idDocGia_arg, string ten_arg, int tuoi_arg, TheThuVien* theThuVien_arg)
		: idDocGia(idDocGia_arg), ten(ten_arg), tuoi(tuoi_arg), theThuVien(theThuVien_arg) {
		theThuVien->setDocGia(this);
	}

	// Set, get thẻ thư viện
	void setTheThuVien(TheThuVien* theThuVien) {
		this->theThuVien = theThuVien;
		theThuVien->setDocGia(this);
	}

	TheThuVien* getTheThuVien() {
		return theThuVien;
	}

	// Get tên
	string getTen() {
		return ten;
	}
};



class Menu
{
private:
	vector <DocGia*> dsDg;
	vector <TheThuVien*> dsTtv;
	vector <Sach*> dsS;
public:
	void docFile() {
		ifstream fileDG;
		ifstream fileSach;
		ifstream fileThe;
		fileDG.open("danhSachDocGia.csv");
		fileSach.open("danhSachBook.csv");
		fileThe.open("danhSachThe.csv");

		if (!fileDG.is_open() || !fileSach.is_open()) {
			cout << "Ko the mo file." << "\n";
			return;
		}

		string line;

		vector <string> temp;
		while (getline(fileThe, line)) {
			int idThe_temp; string type_temp; int thangDK_temp; string dsSach;

			string delimiter = ",";
			int pos_of_delimiter = line.find(delimiter);
			if (pos_of_delimiter != std::string::npos) {
				idThe_temp = stoi(line.substr(0, pos_of_delimiter));
				line = line.substr(pos_of_delimiter + 1, line.length() - 1);
				pos_of_delimiter = line.find(delimiter);

				type_temp = line.substr(0, pos_of_delimiter);
				line = line.substr(pos_of_delimiter + 1, line.length() - 1);
				pos_of_delimiter = line.find(delimiter);

				thangDK_temp = stoi(line.substr(0, pos_of_delimiter));
				line = line.substr(pos_of_delimiter + 1, line.length() - 1);
				pos_of_delimiter = line.find(delimiter);

				dsSach = line.substr(0, pos_of_delimiter);
				line = line.substr(pos_of_delimiter + 1, line.length() - 1);
				pos_of_delimiter = line.find(delimiter);
			}
			TheThuVien* the_temp;
			if (type_temp == "Adult")
				the_temp = new TheNguoiLon(idThe_temp, type_temp, thangDK_temp);
			else if (type_temp == "Child")
				the_temp = new TheTreCon(idThe_temp, type_temp, thangDK_temp);
			dsTtv.push_back(the_temp);
			temp.push_back(dsSach);
		}

		while (getline(fileSach, line)) {
			int idSach_temp;  string tenSach_temp; string idThe_temp;

			string delimiter = ",";
			int pos_of_delimiter = line.find(delimiter);
			if (pos_of_delimiter != std::string::npos) {
				idSach_temp = stoi(line.substr(0, pos_of_delimiter));
				line = line.substr(pos_of_delimiter + 1, line.length() - 1);
				pos_of_delimiter = line.find(delimiter);

				tenSach_temp = line.substr(0, pos_of_delimiter);
				line = line.substr(pos_of_delimiter + 1, line.length() - 1);
				pos_of_delimiter = line.find(delimiter);

				idThe_temp = line.substr(0, pos_of_delimiter);
				line = line.substr(pos_of_delimiter + 1, line.length() - 1);
				pos_of_delimiter = line.find(delimiter);
			}
			Sach* s_temp = new Sach(idSach_temp, tenSach_temp);
			if (idThe_temp != "") {
				int temp = stoi(idThe_temp);
				for (int i = 0; i < dsTtv.size(); i++)
					if (dsTtv[i]->getIdThe() == temp) {
						s_temp->setThe(dsTtv[i]);
						dsTtv[i]->themSach(s_temp);
					}						
			}
			dsS.push_back(s_temp);
		}



		while (getline(fileDG, line)) {
			int idDocGia_temp; string ten_temp; int tuoi_temp;

			string delimiter = ",";
			int pos_of_delimiter = line.find(delimiter);
			if (pos_of_delimiter != std::string::npos) {
				idDocGia_temp = stoi(line.substr(0, pos_of_delimiter));
				line = line.substr(pos_of_delimiter + 1, line.length() - 1);
				pos_of_delimiter = line.find(delimiter);

				ten_temp = line.substr(0, pos_of_delimiter);
				line = line.substr(pos_of_delimiter + 1, line.length() - 1);
				pos_of_delimiter = line.find(delimiter);

				tuoi_temp = stoi(line.substr(0, pos_of_delimiter));
				line = line.substr(pos_of_delimiter + 1, line.length() - 1);
				pos_of_delimiter = line.find(delimiter);
			}
			DocGia* dg_temp;
			for (int i = 0; i < dsTtv.size(); i++)
				if (dsTtv[i]->getIdThe() == idDocGia_temp)
					dg_temp = new DocGia(idDocGia_temp, ten_temp, tuoi_temp, dsTtv[i]);
			dsDg.push_back(dg_temp);
		}
		fileDG.close();
		fileSach.close();
		fileThe.close();
	}

	void out() {
		for (int i = 0; i < dsDg.size(); i++) {
			cout << dsDg[i]->getTen() << "\n";
			dsDg[i]->getTheThuVien()->getListSach();
		}
	}
};

int main() {

	Menu menu;
	menu.docFile();

	menu.out();

	return 0;
}