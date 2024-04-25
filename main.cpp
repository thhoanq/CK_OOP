#include <iostream>
#include <fstream>
#include <vector>
#include <string>

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
	int getIdSach() const {
        return idSach;
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

	// Get type
	string getType() {
		return type;
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

	void xoaSach(int idSach) {
    for (auto it = books.begin(); it != books.end(); ++it) {
        if ((*it)->getIdSach() == idSach) {
            delete *it;  // Giải phóng bộ nhớ của sách
            books.erase(it);  // Xóa sách khỏi vector
            return;  // Thoát khỏi hàm ngay sau khi tìm và xóa sách
        }
    }
    // Không cần thông báo nếu không tìm thấy sách; hàm chỉ thực hiện và kết thúc
}

	// Get danh sách sách
	// void getListSach() {
	// 	for (int i = 0; i < books.size(); i++)
	// 		cout << books[i]->getTen() << books[i]->getThe()->getThangDK() << "\n";
	// }
	
	void outListSach() {
		if (books.empty()) {
			cout << "Sach muon: Khong co\n";
		} else {
			cout << "Sach muon: ";
			for (int i = 0; i < books.size(); i++) {
				cout << books[i]->getTen();
				if (i < books.size() - 1)
					cout << ", "; 
			}
			cout << "\n";
		}
	}

	vector<Sach*> getBooks() const {
        return books;
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
		return 100 * thangDK;
	}
};

class TheTreCon : public TheThuVien
{
public:
	TheTreCon(int idThe_arg, string type_arg, int thangDK_arg)
		: TheThuVien(idThe_arg, type_arg, thangDK_arg) {};

	double tinhTien() override {
		return 20 * thangDK;
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
	int getTuoi(){
		return tuoi;
	}
	string getTen() {
		return ten;
	}
	int getIdDocGia(){
		return idDocGia;
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

	void ghiFile() {
		ofstream fileDG;
		ofstream fileSach;
		ofstream fileThe;
		fileDG.open("danhSachDocGia.csv");
		fileSach.open("danhSachBook.csv");
		fileThe.open("danhSachThe.csv");

		if (!fileDG.is_open() || !fileSach.is_open()) {
			cout << "Ko the mo file." << "\n";
			return;
		}

		for (int i = 0; i < dsDg.size(); i++) {
			fileDG << dsDg[i]->getIdDocGia() << "," << dsDg[i]->getTen() << "," << dsDg[i]->getTuoi() << "\n";
			fileThe << dsTtv[i]->getIdThe() << "," << dsTtv[i]->getType() << ",";
			for (int j = 0; j < dsTtv[i]->getBooks().size(); i++) {
				fileThe << dsTtv[i]->getBooks()[i]->getIdSach();
				if (dsTtv[i]->getBooks()[i + 1] != nullptr)
					fileThe << ";";
			}
			fileThe << "\n";
		}
	}

	// void out() {
	// 	for (int i = 0; i < dsDg.size(); i++) {
	// 		cout <<"Ten Doc Gia: "<<dsDg[i]->getTen() << "\n";
	// 		dsDg[i]->getTheThuVien()->getListSach();
	// 	}
	// }


	void ThemDocGia() {
		int idDocGia, tuoi, idThe, thangDK;
		string ten, type;
		cout << "Nhap ID Doc Gia: ";
		cin >> idDocGia;
		cout << "Nhap Ten Doc Gia: ";
		cin.ignore();
		getline(cin, ten);
		
		do{
			cout << "Nhap Tuoi Doc Gia: ";
			cin >> tuoi;
			if(tuoi<0 && tuoi>110){
				cout<<"So tuoi khong hop le";
			}
		}while(tuoi<0 && tuoi>110);
		// Thêm thẻ thư viện cho độc giả mới
		cout << "Nhap ID The: ";
		cin >> idThe;
		if(tuoi >= 18){
			type = "Adult";
		}
		else{
			type = "Child";
		}
		cout << "Nhap Thang DK: ";
		cin >> thangDK;

		TheThuVien* the;
		if (type == "Adult") {
			the = new TheNguoiLon(idThe, type, thangDK);
		} else {
			the = new TheTreCon(idThe, type, thangDK);
		}
		dsTtv.push_back(the);

		// Tạo độc giả mới với thẻ vừa thêm
		DocGia* docGia = new DocGia(idDocGia, ten, tuoi, the);
		dsDg.push_back(docGia);

		// Hỏi người dùng xem độc giả có mượn sách không
		cout << "Doc gia co muon sach khong (Co/Khong):\n1.Co\n2.Khong\nNhap lua chon: ";
		int response;
		cin >> response;
		if (response == 1) {
			int idSach;
			string tenSach;
			cout << "Nhap ID Sach: ";
			cin >> idSach;
			cout << "Nhap Ten Sach: ";
			cin.ignore();
			getline(cin, tenSach);

			Sach* sach = new Sach(idSach, tenSach);
			the->themSach(sach);  
			dsS.push_back(sach);
		}

		cout << "Doc gia va the thu vien da duoc them vao he thong.\n";
	}

	void deleteDocGia() {
		int idThe;
		cout << "Nhap ID The cua Doc Gia can xoa: ";
		cin >> idThe;

		for (auto it = dsDg.begin(); it != dsDg.end(); ++it) {
			if ((*it)->getTheThuVien() && (*it)->getTheThuVien()->getIdThe() == idThe) {
				delete *it; 
				it = dsDg.erase(it); 
				cout << "\n=====>Doc gia voi Ma The " << idThe << " da duoc xoa.\n";
				return; 
			}
		}
//**************************************************************************************
		cout << "Khong tim thay doc gia voi Ma The " << idThe << ".\n";
	}


	void chinhsuasach(){
		int idThe;
		cout << "Nhap Ma The cua Doc Gia can cap nhat sach: ";
		cin >> idThe;

		for (int i = 0; i < dsDg.size(); i++) {
			DocGia* dg = dsDg[i];  
			if (dg->getTheThuVien() && dg->getTheThuVien()->getIdThe() == idThe) {
				int idSach;
				string tenSach;
				cout << "Nhap ID Sach moi: ";
				cin >> idSach;
				cout << "Nhap Ten Sach moi: ";
				cin.ignore();
				getline(cin, tenSach);

				Sach* sach = new Sach(idSach, tenSach);
				dg->getTheThuVien()->themSach(sach); 
				dsS.push_back(sach);  

				cout << "\n==========>Da them sach moi cho doc gia voi Ma The " << idThe << ".\n";
				return;  
			}
		}

		cout << "\n========>Khong tim thay doc gia voi Ma The " << idThe << ".\n";
	}

	void tracuu(){
		int idThe;
		cout << "Nhap Ma The cua Doc Gia can tra cuu: ";
		cin >> idThe;
		for (int i = 0; i < dsDg.size(); i++) {
			DocGia* dg = dsDg[i];  // Lấy ra đối tượng DocGia từ iterator
			if (dg->getTheThuVien() && dg->getTheThuVien()->getIdThe() == idThe) {
				cout << "\n========Thong tin Doc Gia=====\n";
				cout << "ID Doc Gia: " << dg->getIdDocGia() << "\n";
				cout << "Ten Doc Gia: " << dg->getTen() << "\n";
				cout << "Tuoi Doc Gia: " << dg->getTuoi() << "\n";
				cout << "Ma The: " << dg->getTheThuVien()->getIdThe() << "\n";
				cout << "Sach dang muon:\n";
				if (!dg->getTheThuVien()->getBooks().empty()) {
					for (Sach* sach : dg->getTheThuVien()->getBooks()) {
						cout << "- " << sach->getTen() << "\n";
					}
				} else {
					cout << "Khong co sach nao\n";
				}
				return; 
			}
		}

		cout << "Khong tim thay doc gia voi Ma The " << idThe << ".\n";
		}

	void TraTien(){
		int idThe;
		cout << "Nhap Ma So The cua Doc Gia: ";
		cin >> idThe;


		for (int i = 0; i < dsDg.size(); i++) {
			DocGia* dg = dsDg[i];  
			if (dg->getTheThuVien() && dg->getTheThuVien()->getIdThe() == idThe) {   
				cout << "Tong so tien phai tra la: " << dg->getTheThuVien()->tinhTien() << ".000 VND" << endl;
				return;  
			}
		}

		cout << "Khong tim thay doc gia voi Ma So The " << idThe << "." << endl;
		}


	void out() {
    for (int i = 0; i < dsDg.size(); i++) {
        DocGia* dg = dsDg[i];
        TheThuVien* the = dg->getTheThuVien();
        cout << "Ten doc gia: " << dg->getTen() << "\n";
        cout << "Tuoi doc gia: " << dg->getTuoi() << "\n";
        cout << "Ma the: " << the->getIdThe() << "\n";
        cout << "Sach dang muon:\n";
        if (!the->getBooks().empty()) {
            for (Sach* sach : the->getBooks()) {
                cout << "- ID Sach: " << sach->getIdSach() << ", Ten Sach: " << sach->getTen() << "\n";
            }
        } else {
            cout << "Khong co sach nao\n";
        }

        cout << "Thang dang ky: " << the->getThangDK() << "\n";
        cout << "\n";
    }
}

	void xoasach(){
		int idthe, idSach;
		cout << "Nhap Ma so the cua doc gia: ";
		cin >> idthe;
		cout << "Nhap ID Sach can xoa: ";
		cin >> idSach;

		for (int i = 0; i < dsDg.size(); i++) {
			DocGia* dg = dsDg[i];  
			if (dg->getTheThuVien() && dg->getTheThuVien()->getIdThe() == idthe) {  
				if (dg->getTheThuVien()) { 
					dg->getTheThuVien()->xoaSach(idSach);  
					cout << "==========>Da Xoa Sach Co ID " << idSach << "\n";
					return;  
				}
				cout << "===========>Doc Gia Khong Co Trong Thu Vien.\n";
				return;  
			}
		}

		cout << "\n===========>Không tìm thấy độc giả với Ma So " << idthe << ".\n";  
	}
	

	void luachon(){
		int luachon;
		do{
			cout << "\n1. Them Doc Gia";
			cout << "\n2. Xoa Doc Gia";
			cout << "\n3. Xuat danh sach hien tai";
			cout << "\n4. Tra cuu doc gia";
			cout << "\n5. Cap nhat sach cua doc gia";
			cout << "\n6. Tinh tien doc gia thong qua Ma The";
			cout << "\n7. Ghi file";
			cout << "\n0. Thoat chuong trinh\n";
			cout << "(!) Nhap lua chon: ";
			cin >> luachon;
			switch (luachon) {
			case 1:
				cout<<"1.Them thu cong.\n2.Them bang file.\n";
				int n;
				do{
					cout<<"Nhap lua chon (1 hoac 2): ";
					cin>>n;
					if(n!=1 && n!=2){
						cout<<"Lua chon khong hop le!\n";
					}
					
				}while(n!=1 && n!=2);
				switch (n)
					{
					case 1:
						ThemDocGia();
						break;
					case 2:
						docFile();
						break;
					default:
						break;
					}
				cout<<"\n=====>Them Thanh Cong\n";
				break;
			case 2:
				deleteDocGia();
				break;
			case 3:
				cout<<"\n=====================================DANH SACH HIEN TAI==============================\n";
				out();
				cout<<"\n=====================================================================================\n";
				break;
			case 4:
				tracuu();
				break;
			case 5:
				cout<<"\n1.Doc gia muon them sach\n2.Doc gia tra sach\n";
				do{
					cout<<"Nhap lua chon (1 hoac 2): ";
					cin>>n;
					if(n!=1 && n!=2){
						cout<<"Lua chon khong hop le!\n";
					}
					
				}while(n!=1 && n!=2);
				switch (n)
					{
					case 1:
						chinhsuasach();
						break;
					case 2:
						xoasach();
						break;
					default:
						break;
					}
				
				break;
			case 6:
				TraTien();
				break;
			default:
				break;
			}

		}while(luachon!=0);
	}

};

int main() {

	Menu menu;
	menu.luachon();

	return 0;
}