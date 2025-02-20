#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <clocale>
#include <limits>

using namespace std;

struct urun {
    string adi;
    int stok;
    float fiyat;
};

int getValidIntInput() {
    int value;
    while (true) {
        cin >> value;
        if (cin.fail()) {
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            cout << "Geçersiz giriş! Lütfen geçerli bir tamsayı girin: ";
        } else {
            return value;
        }
    }
}

float getValidFloatInput() {
    float value;
    while (true) {
        cin >> value;
        if (cin.fail()) {
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            cout << "Geçersiz giriş! Lütfen geçerli bir fiyat girin: ";
        } else {
            return value;
        }
    }
}

void urunEkle() {
    int urunSayisi;
    cout << "Kaç adet ürün gireceksiniz? ";
    urunSayisi = getValidIntInput();

    vector<urun> urunler(urunSayisi);

    ofstream dosyaYaz("urunler.txt", ios::app);

    if (!dosyaYaz) {
        cerr << "Dosya açma hatası!" << endl;
        return;
    }

    for (int i = 0; i < urunSayisi; i++) {
        cout << i + 1 << ". ürün adını giriniz: ";
        cin >> ws;
        getline(cin, urunler[i].adi);

        while (urunler[i].adi.empty()) {
            cout << "Ürün adı boş olamaz. Lütfen geçerli bir ürün adı giriniz: ";
            getline(cin, urunler[i].adi);
        }

        cout << i + 1 << ". ürün stok miktarını giriniz: ";
        urunler[i].stok = getValidIntInput();

        while (urunler[i].stok < 0) {
            cout << "Stok miktarı sıfırdan küçük olamaz. Lütfen geçerli bir stok giriniz: ";
            urunler[i].stok = getValidIntInput();
        }

        cout << i + 1 << ". ürün fiyatını giriniz: ";
        urunler[i].fiyat = getValidFloatInput();

        while (urunler[i].fiyat < 0) {
            cout << "Fiyat sıfırdan küçük olamaz. Lütfen geçerli bir fiyat giriniz: ";
            urunler[i].fiyat = getValidFloatInput();
        }

        dosyaYaz << urunler[i].adi << " " << urunler[i].stok << " " << urunler[i].fiyat << endl;
    }

    dosyaYaz.close();
    cout << "\nÜrünler başarıyla dosyaya eklendi!\n" << endl;
}

void urunListele() {
    ifstream dosyaOku("urunler.txt");

    if (!dosyaOku) {
        cerr << "Dosya okuma hatası!" << endl;
        return;
    }

    cout << "\n--- Kayıtlı Ürünler ---\n" << endl;
    urun temp;
    int index = 1;
    while (dosyaOku >> temp.adi >> temp.stok >> temp.fiyat) {
        cout << index++ << ". Ürün Adı: " << temp.adi << endl;
        cout << "   Stok: " << temp.stok << endl;
        cout << "   Fiyat: " << temp.fiyat << " TL" << endl;
        cout << "-----------------------------\n";
    }

    dosyaOku.close();
}

void urunSil() {
    ifstream dosyaOku("urunler.txt");

    if (!dosyaOku) {
        cerr << "Dosya okuma hatası!" << endl;
        return;
    }

    vector<urun> urunler;
    urun temp;
    int index = 1;

    while (dosyaOku >> temp.adi >> temp.stok >> temp.fiyat) {
        urunler.push_back(temp);
    }

    dosyaOku.close();

    if (urunler.empty()) {
        cout << "Silinecek ürün bulunmuyor." << endl;
        return;
    }

    cout << "\n--- Kayıtlı Ürünler ---\n";
    for (int i = 0; i < urunler.size(); i++) {
        cout << (i + 1) << ". Ürün Adı: " << urunler[i].adi << endl;
        cout << "   Stok: " << urunler[i].stok << endl;
        cout << "   Fiyat: " << urunler[i].fiyat << " TL" << endl;
        cout << "-----------------------------\n";
    }

    cout << "\nSilmek istediğiniz ürünün numarasını giriniz: ";
    int silinecekUrunNumarasi = getValidIntInput();

    while (silinecekUrunNumarasi < 1 || silinecekUrunNumarasi > urunler.size()) {
        cout << "Geçersiz ürün numarası! Lütfen geçerli bir numara girin: ";
        silinecekUrunNumarasi = getValidIntInput();
    }

    urunler.erase(urunler.begin() + silinecekUrunNumarasi - 1);

    ofstream dosyaYaz("urunler.txt", ios::trunc);

    if (!dosyaYaz) {
        cerr << "Dosya yazma hatası!" << endl;
        return;
    }

    for (const auto& urun : urunler) {
        dosyaYaz << urun.adi << " " << urun.stok << " " << urun.fiyat << endl;
    }

    dosyaYaz.close();
    cout << "Seçilen ürün başarıyla silindi.\n";
}

void urunGuncelle() {
    ifstream dosyaOku("urunler.txt");

    if (!dosyaOku) {
        cerr << "Dosya okuma hatası!" << endl;
        return;
    }

    vector<urun> urunler;
    urun temp;
    int index = 1;

    while (dosyaOku >> temp.adi >> temp.stok >> temp.fiyat) {
        urunler.push_back(temp);
    }

    dosyaOku.close();

    if (urunler.empty()) {
        cout << "Güncellenecek ürün bulunmuyor." << endl;
        return;
    }

    cout << "\n--- Kayıtlı Ürünler ---\n";
    for (int i = 0; i < urunler.size(); i++) {
        cout << (i + 1) << ". Ürün Adı: " << urunler[i].adi << endl;
        cout << "   Stok: " << urunler[i].stok << endl;
        cout << "   Fiyat: " << urunler[i].fiyat << " TL" << endl;
        cout << "-----------------------------\n";
    }

    cout << "\nGüncellemek istediğiniz ürünün numarasını giriniz: ";
    int guncellenecekUrunNumarasi = getValidIntInput();

    while (guncellenecekUrunNumarasi < 1 || guncellenecekUrunNumarasi > urunler.size()) {
        cout << "Geçersiz ürün numarası! Lütfen geçerli bir numara girin: ";
        guncellenecekUrunNumarasi = getValidIntInput();
    }

    urun& secilenUrun = urunler[guncellenecekUrunNumarasi - 1];

    cout << "Seçilen Ürün: " << secilenUrun.adi << endl;
    cout << "Mevcut Stok: " << secilenUrun.stok << ", Mevcut Fiyat: " << secilenUrun.fiyat << " TL\n";

    cout << "Yeni stok miktarını giriniz: ";
    secilenUrun.stok = getValidIntInput();
    while (secilenUrun.stok < 0) {
        cout << "Stok miktarı sıfırdan küçük olamaz. Lütfen geçerli bir stok giriniz: ";
        secilenUrun.stok = getValidIntInput();
    }

    cout << "Yeni fiyatı giriniz: ";
    secilenUrun.fiyat = getValidFloatInput();
    while (secilenUrun.fiyat < 0) {
        cout << "Fiyat sıfırdan küçük olamaz. Lütfen geçerli bir fiyat giriniz: ";
        secilenUrun.fiyat = getValidFloatInput();
    }

    ofstream dosyaYaz("urunler.txt", ios::trunc);

    if (!dosyaYaz) {
        cerr << "Dosya yazma hatası!" << endl;
        return;
    }

    for (const auto& urun : urunler) {
        dosyaYaz << urun.adi << " " << urun.stok << " " << urun.fiyat << endl;
    }

    dosyaYaz.close();
    cout << "Seçilen ürün başarıyla güncellendi.\n";
}

int main() {
    setlocale(LC_ALL, "turkish");

    int secim;

    while (true) {
        cout << "\n--- Ana Menü ---\n";
        cout << "1. Ürün Ekle\n";
        cout << "2. Ürünleri Listele\n";
        cout << "3. Ürün Sil\n";
        cout << "4. Ürün Güncelle\n";
        cout << "5. Çıkış\n";
        cout << "Seçiminizi yapın (1-5): ";
        secim = getValidIntInput();

        switch (secim) {
            case 1:
                urunEkle();
                break;
            case 2:
                urunListele();
                break;
            case 3:
                urunSil();
                break;
            case 4:
                urunGuncelle();
                break;
            case 5:
                cout << "Çıkılıyor..." << endl;
                return 0;
            default:
                cout << "Geçersiz seçenek, lütfen tekrar deneyin!" << endl;
                break;
        }
    }

    return 0;
}
