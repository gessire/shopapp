#include <iostream>
#include <vector>
#include <fstream>

using namespace std;

// کلاس محصول
class Product {
public:
  string name;
  int stock;
  double price;

  Product(string name, int stock, double price) {
    this->name = name;
    this->stock = stock;
    this->price = price;
  }
};

// کلاس فروشگاه
class Store {
private:
  vector<Product> products;

public:
  void addProduct();
  void showProducts();
  void saveProductsToFile();
  void loadProductsFromFile();
};

// تابع ثبت محصول
void Store::addProduct() {
  string name;
  int stock;
  double price;

  cout << "نام محصول: ";
  cin >> name;

  cout << "موجودی: ";
  cin >> stock;

  cout << "قیمت: ";
  cin >> price;

  products.push_back(Product(name, stock, price));
}

// تابع نمایش محصولات
void Store::showProducts() {
  if (products.empty()) {
    cout << "هیچ محصولی ثبت نشده است!" << endl;
    return;
  }

  cout << "----------------------------------------" << endl;
  cout << "لیست محصولات:" << endl;
  for (Product product : products) {
    cout << "نام: " << product.name << ", موجودی: " << product.stock << ", قیمت: " << product.price << endl;
  }
  cout << "----------------------------------------" << endl;
}

// تابع ذخیره محصولات در فایل
void Store::saveProductsToFile() {
  ofstream file("products.dat");

  if (file.is_open()) {
    for (Product product : products) {
      file << product.name << "," << product.stock << "," << product.price << endl;
    }
    file.close();
    cout << "محصولات با موفقیت ذخیره شدند!" << endl;
  } else {
    cout << "خطا در ذخیره محصولات!" << endl;
  }
}

// تابع بارگذاری محصولات از فایل
void Store::loadProductsFromFile() {
  ifstream file("products.dat");
  string line;

  if (file.is_open()) {
    while (getline(file, line)) {
      vector<string> tokens;
      //split(line, ',', tokens);

      if (tokens.size() == 3) {
        string name = tokens[0];
        int stock = stoi(tokens[1]);
        double price = stod(tokens[2]);

        products.push_back(Product(name, stock, price));
      }
    }
    file.close();
    cout << "محصولات با موفقیت بارگذاری شدند!" << endl;
  } else {
    cout << "فایل محصولات یافت نشد!" << endl;
  }
}

int main() {
  Store store;

  // بارگذاری محصولات از فایل در ابتدای برنامه
  store.loadProductsFromFile();

  int choice;

  do {
    cout << "----------------------------------------" << endl;
    cout << "منوی فروشگاه:" << endl;
    cout << "1. ثبت محصول" << endl;
    cout << "2. نمایش محصولات" << endl;
    cout << "3. خروج از برنامه" << endl;
    cout << "----------------------------------------" << endl;
    cout << "انتخاب خود را وارد کنید: ";
    cin >> choice;

    switch (choice) {
      case 1:
        store.addProduct();
        break;
      case 2:
        store.showProducts();
        break;
      case 3:
        cout << "از برنامه خارج شدید!" << endl;
        break;
      default:
        cout << "انتخاب نامعتبر!" << endl;
    }
  } while (choice != 3);

  // ذخیره محصولات در فایل قبل از خروج از برنامه
  store.saveProductsToFile();

  return 0;
}
