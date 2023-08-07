#include<iostream>
#include<string>
#include<vector>

using namespace std;

class Food{
public:
	string name;
	double vitamin;
	double protein;
	double carb;
	double price;
	double allVitamin;
	double allProtein;
	double allCarb;
	void SimplexMethod();
};


void Food::SimplexMethod() {
	Food rice;
	rice.name ;      //1つ目の食べ物の名前
	rice.vitamin;    //1つ目の食べ物のビタミンの値
	rice.protein;    //1つ目の食べ物のたんぱく質の値
	rice.carb;       //1つ目の食べ物の炭水化物の値
	rice.price;      //1つ目の食べ物の値段

	Food meet;
	meet.name;       //2つ目の食べ物の名前
	meet.vitamin;    //2つ目の食べ物のビタミンの値
	meet.protein;    //2つ目の食べ物のたんぱく質の値
	meet.carb;       //2つ目の食べ物の炭水化物の値
	meet.price;      //2つ目の食べ物の値段

	cout << "1つ目の食べ物の名前を入れてください:";
	cin >> rice.name;

	cout << "ビタミンの値を入れてください：";
	cin >> rice.vitamin;

	cout << "たんぱく質の値を入れてください：";
	cin >> rice.protein;

	cout << "炭水化物の値を入れてください：";
	cin >> rice.carb;

	cout << "値段を入れてください：";
	cin >> rice.price;
	cout << endl;

	cout << "2つ目の食べ物の名前を入れてください:";
	cin >> meet.name;

	cout << "ビタミンの値を入れてください：";
	cin >> meet.vitamin;

	cout << "たんぱく質の値を入れてください：";
	cin >> meet.protein;

	cout << "炭水化物の値を入れてください：";
	cin >> meet.carb;

	cout << "値段を入れてください：";
	cin >> meet.price;
	cout << endl;

	cout << "ビタミンの必要摂取量を入れてください：";
	cin >> allVitamin;

	cout << "たんぱく質の必要摂取量を入れてください：";
	cin >> allProtein;

	cout << "炭水化物の必要摂取量を入れてください：";
	cin >> allCarb;
	cout << endl;

	//初期頂点を求める
	//シンプレックス表を作成
	vector<vector<double>> initial={ { 0, 0, 0, 0, 0, 1, 1, 1, 0 },
									 { rice.vitamin, meet.vitamin, -1, 0, 0, 1, 0, 0, allVitamin },
									 { rice.protein, meet.protein, 0, -1, 0, 0, 1, 0, allProtein },
									 { rice.carb, meet.carb, 0, 0, -1, 0, 0, 1, allCarb} };
	
	int n = initial.size();     //行数4
	int m = initial[0].size();  //列数9
	
	//目的関数の行の係数を掃き出す
	for (int i = 0; i < m; ++i) 
		initial[0][i] = initial[0][i] - initial[1][i] - initial[2][i] - initial[3][i];
	
	while (1) {
		//列を決める
		double min = 10000;
		int y;
		for (int i = 0; i < m - 1; ++i) {
			if (initial[0][i] < min) {
				min = initial[0][i];
				y = i;
			}
		}
		//目的関数の係数が0以上になれば終了
		if (min >= -0.0000001) break;

		//行を決める
		double min1 = 10000;
		int x;
		double a;
		for (int i = 1; i < n; ++i) {
			a = initial[i][m - 1] / initial[i][y];
			if (a > 0 && a < min1) {
				min1 = a;
				x = i;
			}
		}

		//1に規格化
		double c = initial[x][y];
		for (int i = 0; i < m; ++i) {
			initial[x][i] = initial[x][i] / c;
		}

		//掃き出す
		for (int i = 0; i < n; ++i) {
			if (x != i) {
				double d = initial[i][y] / initial[x][y];
				for (int j = 0; j < m; ++j) {
					initial[i][j] = initial[i][j] - initial[x][j] * d;
				}
			}
		}
	}

	//最適解を求める
	//シンプレックス表を作成
	vector<vector<double>> simplex{ { rice.price, meet.price, 0, 0, 0, 0 },
									{ initial[1][0], initial[1][1], initial[1][2], initial[1][3], initial[1][4], initial[1][m - 1] },
									{ initial[2][0], initial[2][1], initial[2][2], initial[2][3], initial[2][4], initial[2][m - 1] },
									{ initial[3][0], initial[3][1], initial[3][2], initial[3][3], initial[3][4], initial[3][m - 1] }};

	int ns = simplex.size();     //行数4
	int ms = simplex[0].size();  //列数6

	//目的関数の行の係数を掃き出す
	double p=0;
	double q=0;
	double r=0;
	for (int i = 0; i < 2; ++i) {
		if (simplex[1][i] == 1)
			p = simplex[0][i] / simplex[1][i];
		else p = p;
		if (simplex[2][i] == 1)
			q = simplex[0][i] / simplex[2][i];
		else q = q;
		if (simplex[3][i] == 1)
			r = simplex[0][i] / simplex[3][i];
		else r = r;
	}
	for (int i = 0; i < ms; ++i)
		simplex[0][i] = simplex[0][i] - p * simplex[1][i] - q * simplex[2][i] - r * simplex[3][i];

	while (1) {
		//列を決める
		double min = 10000;
		double ys;
		for (int i = 0; i < ms - 1; ++i) {
			if (simplex[0][i] < min) {
				min = simplex[0][i];
				ys = i;
			}
		}
		//目的関数の係数が0以上になれば終了
		if (min >= -0.0000001) break;

		//行を決める
		double min1 = 10000;
		double xs{};
		double a;
		for (int i = 1; i < ns; ++i) {
			a = simplex[i][ms - 1] / simplex[i][ys];
			if (a > 0 && a < min1) {
				min1 = a;
				xs = i;
			}
		}

		//1に規格化
		double c = simplex[xs][ys];
		for (int i = 0; i < ms; ++i) {
			simplex[xs][i] = simplex[xs][i] / c;
		}

		//掃き出す
		for (int i = 0; i < ns; ++i) {
			if (xs != i) {
				double d = simplex[i][ys] / simplex[xs][ys];
				for (int j = 0; j < ms; ++j) {
					simplex[i][j] = simplex[i][j] - simplex[xs][j] * d;
				}
			}
		}
	}

	double totalprice = -1 * simplex[0][ms - 1];
	double totalrice{};
	double totalmeet{};
	for (int i = 1; i < ns; ++i) {
		if (simplex[i][0] == 1)
			totalrice = simplex[i][ms - 1];
		else totalprice = totalprice;
		if (simplex[i][1] == 1)
			totalmeet = simplex[i][ms - 1];
		else totalmeet = totalmeet;
	}

	vector<double> food;
	food.emplace_back();
	food[food.size() - 1] = totalrice;
	food.emplace_back();
	food[food.size() - 1] = totalmeet;
	food.emplace_back();
	food[food.size() - 1] = totalprice;

	cout << rice.name << "　" << meet.name << "　" << "合計金額 (円)" << endl;
	for (auto result = food.cbegin(); result != food.end(); ++result) {
		cout << *result << "　　";
	}	
}

int main() {
	Food fo;
	fo.SimplexMethod();
}