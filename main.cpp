#include <iostream>
#include <vector>
#include <string>

using namespace std;

// Khai báo trước class
class Sach;
class TheThuVien;
class DocGia;


/*======================================================================================
								CLASS THẺ THƯ VIỆN
======================================================================================*/
class TheThuVien
{
protected:
	int maThe;
	int thangDK;
	DocGia* docGia;
public:
	TheThuVien(int maThe_arg) : maThe(maThe_arg), thangDK(0), docGia(nullptr) {}

	// Get mã thẻ
	int getMaThe() {
		return maThe;
	}

	// Set, get active
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

	// Tính tiền mỗi năm
	virtual double tinhTien() = 0;
};

class TheNguoiLon : public TheThuVien
{
public:
	TheNguoiLon(int maThe_arg) : TheThuVien(maThe_arg) {};

	double tinhTien() override {
		return 100000 * thangDK;
	}
};

class TheTreCon : public TheThuVien
{
public:
	TheTreCon(int maThe_arg) : TheThuVien(maThe_arg) {};

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
	string ten;
	int tuoi;
	TheThuVien* theThuVien;
	vector <Sach*> books;
public:
	DocGia(string ten_arg, int tuoi_arg, TheThuVien* theThuVien_arg) : ten(ten_arg), tuoi(tuoi_arg), theThuVien(theThuVien_arg) {
		theThuVien->setDocGia(this);
	}

	// Thêm sách
	void themSach(Sach* sach) {
		books.push_back(sach);
		sach->setDocGia(this);
	}
};


/*======================================================================================
									CLASS SÁCH
======================================================================================*/
class Sach
{
private:
	string ten;
	DocGia* docGia;
public:
	Sach(string ten_arg) : ten(ten_arg), docGia(nullptr) {};

	// Set, get tên sách
	void setTen(string ten) {
		this->ten = ten;
	}

	string getTen() {
		return ten;
	}

	// Set, get độc giả
	void setDocGia(DocGia* dg) {
		docGia = dg;
	}

	DocGia* getDocGia() {
		return docGia;
	}
};


class Menu
{
private:
	vector <DocGia*> dg;
	vector <TheThuVien*> ttv;

public:
	void docFile() {
		
	}
};

int main() {

	return 0;
}