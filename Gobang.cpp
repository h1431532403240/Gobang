#include <iostream>
#include <iomanip>
#include <time.h>
#include <string>

using namespace std;

const int N = 15;				//	15 x 15的棋盤
const int None_Stone = 0;			//	0為空格
const int Black_Stone = 1;			//	1為玩家1或是電腦的棋子
const int White_Stone = 2;			//	2為玩家2的棋子

struct Position {		//	預設座標結構

	int row;		//	列
	int col;		//	行

};

class Gomoku {		//	五子棋的class

private:
	int _Board[N + 1][N + 1];		//	棋盤

public:
	Gomoku() {
		Init_Board();			//	初始化棋盤
	}

	void Play() {				//	開始下棋

		Position Player1;		//	玩家1或電腦使用座標結構
		Position Player2;		//	玩家2使用座標結構

		while (1) {

			int Mode = Choose_Mode();			//	選擇模式

			while (1) {

				if (Mode == 1) {			//	電腦 VS 玩家

					_Board[8][8] = 1;

					Place_Stone(Player2, 2, White_Stone);						//	玩家2走
					if (Get_Victory(Player2, 2, White_Stone))					//	2代表玩家2，如果勝利就會跳出迴圈
						break;

					Computer_Place_Stone(Player1, Black_Stone, Player2);				//	電腦走
					if (Get_Victory(Player1, 0, Black_Stone))					//	0代表電腦，如果勝利就會跳出迴圈
						break;

				}

				else {					//	玩家1 VS 玩家2

					Place_Stone(Player1, 1, Black_Stone);						//	玩家1走
					if (Get_Victory(Player1, 1, Black_Stone))					//	1代表玩家1，如果勝利就會跳出迴圈
						break;

					Place_Stone(Player2, 2, White_Stone);						//	玩家2走
					if (Get_Victory(Player2, 2, White_Stone))					//	2代表玩家2，如果勝利就會跳出迴圈
						break;

				}
			}

			cout << "再來一局？" << endl;
			cout << "「yes」 or 「no」：";

			string Again;
			while (1) {					//	判斷玩家是否要繼續遊玩
				cin >> Again;
				if (Again == "yes")
					break;
				else if (Again == "no")
					exit(1);
				else {
					cout << "輸入錯誤，請輸入「yes」 or 「no」：";
					continue;
				}
			}
			system("cls");
		}
	}

protected:
	void Init_Board() {							//	初始化棋盤
		for (int i = 0; i < N + 1; ++i) {				//	全部格子設為0
			for (int j = 0; j < N + 1; ++j) {
				_Board[i][j] = None_Stone;
			}
		}
	}

	int Choose_Mode() {		//	選擇模式

		system("cls");
		Init_Board();		//	初始化棋盤

		cout << "－－－－－－－－－－－－－－－－－－－－－－－－－－－－－－" << endl;
		cout << "－－－－－－－－－－－０、退出遊戲　　－－－－－－－－－－－" << endl;
		cout << "－－－－－－－－－－－１、電腦ｖｓ玩家－－－－－－－－－－－" << endl;
		cout << "－－－－－－－－－－－２、玩家ｖｓ玩家－－－－－－－－－－－" << endl;
		cout << "－－－－－－－－－－－－－－－－－－－－－－－－－－－－－－" << endl;

		while (1) {		//	判斷使用者選擇哪種模式
			int Chooce;
			cout << "請選擇模式：";
			cin >> Chooce;
			if (Chooce == 0) {
				exit(1);							//	退出程式
			}
			else if (Chooce == 1 || Chooce == 2) {					//	回傳選擇的模式
				return Chooce;
			}
			else {									//	輸入錯誤資訊判斷
				cout << "請輸入「0」、「1」、「2」選擇模式" << endl;
			}
		}
	}

	void Print_Board() {		//	輸出棋盤
		system("cls");
		cout << "      1    2    3    4    5    6    7    8    9   10   11   12   13   14   15" << endl;
		cout << "   |----|----|----|----|----|----|----|----|----|----|----|----|----|----|----|" << endl;
		for (int i = 1; i <= N; i++) {
			cout << setw(2) << i << " ";
			for (int j = 1; j <= N; j++) {
				if (_Board[i][j] == 0)
					cout << "|    ";
				if (_Board[i][j] == 1)
					cout << "| ○ ";
				if (_Board[i][j] == 2)
					cout << "| ● ";
				if (j == 15) {
					cout << "|\n";
				}
			}
			cout << "   |----|----|----|----|----|----|----|----|----|----|----|----|----|----|----|" << endl;
		}
		cout << endl;
	}

	void Computer_Place_Stone(Position& pos, int stone, Position& get) {     //電腦下棋
		Print_Board();
		int x = 0;
		int y = 0;
		int Get_Stone[4];
		int choose = 0;
		int warning = 0;
		int random = 0;
		int choise = 0;
		int havechess = 1;

		if (_Board[get.row][get.col + 1] == 2)
			choise++;
		if (_Board[get.row][get.col + 2] == 2)
			choise++;
		if (_Board[get.row][get.col - 1] == 2)
			choise++;
		if (_Board[get.row][get.col - 2] == 2)
			choise++;
		Get_Stone[0] = choise;
		choise = 0;

		if (_Board[get.row + 1][get.col + 1] == 2)
			choise++;
		if (_Board[get.row + 2][get.col + 2] == 2)
			choise++;
		if (_Board[get.row - 1][get.col - 1] == 2)
			choise++;
		if (_Board[get.row - 2][get.col - 2] == 2)
			choise++;
		Get_Stone[1] = choise;
		choise = 0;

		if (_Board[get.row - 1][get.col] == 2)
			choise++;
		if (_Board[get.row - 2][get.col] == 2)
			choise++;
		if (_Board[get.row + 1][get.col] == 2)
			choise++;
		if (_Board[get.row + 2][get.col] == 2)
			choise++;
		Get_Stone[2] = choise;
		choise = 0;

		if (_Board[get.row - 1][get.col + 1] == 2)
			choise++;
		if (_Board[get.row - 2][get.col + 2] == 2)
			choise++;
		if (_Board[get.row + 1][get.col - 1] == 2)
			choise++;
		if (_Board[get.row + 2][get.col - 2] == 2)
			choise++;
		Get_Stone[3] = choise;
		choise = 0;

		/*cout << Get_Stone[0] << endl;
		cout << Get_Stone[1] << endl;
		cout << Get_Stone[2] << endl;
		cout << Get_Stone[3] << endl;*/
		for (int i = 0; i < 4; i++) {
			if (Get_Stone[i] > warning) {
				warning = Get_Stone[i];		//	warning	= 為範圍內有多少白棋
				choose = i;					//	choose	= 固定危險的方向性
			}
		}
		//	cout << warning << endl;

		while (1) {     //	循環查找空位置

			if (get.col > 1 && get.col < 15 && get.row > 1 && get.row < 15) {			//	四顆強制判斷
				int sum = 1;        //    總和鄰近棋數
				for (int i = 1; i <= 4; i++) {
					if (_Board[get.row][get.col] == _Board[get.row][get.col + i] && _Board[get.row][get.col - 1] == None_Stone)
						sum++;
					else
						break;
				}
				if (sum >= 4) {
					x = get.row;
					y = get.col - 1;
					break;
				}

				sum = 1;
				for (int i = 1; i <= 4; i++) {
					if (_Board[get.row][get.col] == _Board[get.row][get.col - i] && _Board[get.row][get.col + 1] == None_Stone)
						sum++;
					else
						break;
				}
				if (sum >= 4) {
					x = get.row;
					y = get.col + 1;
					break;
				}

				sum = 1;        //    總和鄰近棋數
				for (int i = 1; i <= 4; i++) {
					if (_Board[get.row][get.col] == _Board[get.row + i][get.col] && _Board[get.row - 1][get.col] == None_Stone)
						sum++;
					else
						break;
				}
				if (sum >= 4) {
					x = get.row - 1;
					y = get.col;
					break;
				}

				sum = 1;
				for (int i = 1; i <= 4; i++) {
					if (_Board[get.row][get.col] == _Board[get.row - i][get.col] && _Board[get.row + 1][get.col] == None_Stone)
						sum++;
					else
						break;
				}
				if (sum >= 4) {
					x = get.row + 1;
					y = get.col;
					break;
				}

				sum = 1;        //    總和鄰近棋數
				for (int i = 1; i <= 4; i++) {
					if (_Board[get.row][get.col] == _Board[get.row + i][get.col + i] && _Board[get.row - 1][get.col - 1] == None_Stone)
						sum++;
					else
						break;
				}
				if (sum >= 4) {
					x = get.row - 1;
					y = get.col - 1;
					break;
				}

				sum = 1;
				for (int i = 1; i <= 4; i++) {
					if (_Board[get.row][get.col] == _Board[get.row - i][get.col - i] && _Board[get.row + 1][get.col + 1] == None_Stone)
						sum++;
					else
						break;
				}
				if (sum >= 4) {
					x = get.row + 1;
					y = get.col + 1;
					break;
				}

				sum = 1;        //    總和鄰近棋數
				for (int i = 1; i <= 4; i++) {
					if (_Board[get.row][get.col] == _Board[get.row - i][get.col + i] && _Board[get.row + 1][get.col - 1] == None_Stone)
						sum++;
					else
						break;
				}
				if (sum >= 4) {
					x = get.row + 1;
					y = get.col - 1;
					break;
				}

				sum = 1;
				for (int i = 1; i <= 4; i++) {
					if (_Board[get.row][get.col] == _Board[get.row + i][get.col - i] && _Board[get.row - 1][get.col + 1] == None_Stone)
						sum++;
					else
						break;
				}
				if (sum >= 4) {
					x = get.row - 1;
					y = get.col + 1;
					break;
				}
			}


			if (warning == 0) {
				for (int i = 0; i < 3; i++) {
					for (int j = 0; j < 3; j++) {
						if (_Board[get.row + i - 1][get.col + j - 1] == None_Stone) {
							havechess = 0;
							break;
						}
					}
					if (havechess == 0)
						break;
				}
				srand(time(NULL));
				random = (rand() % 8) + 1;
				switch (random) {
				case 1: {
					x = get.row - 1;
					y = get.col - 1;
					break;
				}
				case 2: {
					x = get.row - 1;
					y = get.col;
					break;
				}
				case 3: {
					x = get.row - 1;
					y = get.col + 1;
					break;
				}
				case 4: {
					x = get.row;
					y = get.col - 1;
					break;
				}
				case 5: {
					x = get.row;
					y = get.col + 1;
					break;
				}
				case 6: {
					x = get.row + 1;
					y = get.col - 1;
					break;
				}
				case 7: {
					x = get.row + 1;
					y = get.col;
					break;
				}
				case 8: {
					x = get.row + 1;
					y = get.col + 1;
					break;
				}
				}
				if (havechess == 1) {
					srand(time(NULL));
					random = (rand() % 15) + 1;
					x = random;
					srand(time(NULL));
					random = (rand() % 15) + 1;
					y = random;
				}
				havechess = 1;
			}

			else if (warning == 1 || warning == 2) {
				if (choose == 0) {
					srand(time(NULL));
					random = (rand() % 2) + 1;
					switch (random) {
					case 1: {
						x = get.row;
						y = get.col - 1;
						if (_Board[get.row][get.col - 1] != None_Stone && _Board[get.row][get.col + 1] != None_Stone)
							y = get.col - 2;
						break;
					}
					case 2: {
						x = get.row;
						y = get.col + 1;
						if (_Board[get.row][get.col - 1] != None_Stone && _Board[get.row][get.col + 1] != None_Stone)
							y = get.col + 2;
						break;
					}
					}
					if (_Board[get.row][get.col - 1] == None_Stone || _Board[get.row][get.col + 1] == None_Stone) {

					}
					else if (_Board[get.row][get.col - 2] != None_Stone && _Board[get.row][get.col + 2] != None_Stone) {
						warning = 0;
					}

				}
				else if (choose == 1) {
					srand(time(NULL));
					random = (rand() % 2) + 1;
					switch (random) {
					case 1: {
						x = get.row - 1;
						y = get.col - 1;
						if (_Board[get.row - 1][get.col - 1] != None_Stone && _Board[get.row + 1][get.col + 1] != None_Stone) {
							x = get.row - 2;
							y = get.col - 2;
						}
						break;
					}
					case 2: {
						x = get.row + 1;
						y = get.col + 1;
						if (_Board[get.row - 1][get.col - 1] != None_Stone && _Board[get.row + 1][get.col + 1] != None_Stone) {
							x = get.row + 2;
							y = get.col + 2;
						}
						break;
					}
					}
					if (_Board[get.row - 1][get.col - 1] == None_Stone || _Board[get.row + 1][get.col + 1] == None_Stone) {

					}
					else if (_Board[get.row - 2][get.col - 2] != None_Stone && _Board[get.row + 2][get.col + 2] != None_Stone) {
						warning = 0;
					}
				}
				else if (choose == 2) {
					srand(time(NULL));
					random = (rand() % 2) + 1;
					switch (random) {
					case 1: {
						x = get.row - 1;
						y = get.col;
						if (_Board[get.row - 1][get.col] != None_Stone && _Board[get.row + 1][get.col] != None_Stone)
							x = get.row - 2;
						break;
					}
					case 2: {
						x = get.row + 1;
						y = get.col;
						if (_Board[get.row - 1][get.col] != None_Stone && _Board[get.row + 1][get.col] != None_Stone)
							x = get.row + 2;
						break;
					}
					}
					if (_Board[get.row - 1][get.col] == None_Stone || _Board[get.row + 1][get.col] == None_Stone) {

					}
					else if (_Board[get.row - 2][get.col] != None_Stone && _Board[get.row + 2][get.col] != None_Stone) {
						warning = 0;
					}
				}
				else if (choose == 3) {
					srand(time(NULL));
					random = (rand() % 2) + 1;
					switch (random) {
					case 1: {
						x = get.row - 1;
						y = get.col + 1;
						if (_Board[get.row - 1][get.col + 1] != None_Stone && _Board[get.row + 1][get.col - 1] != None_Stone) {
							x = get.row - 2;
							y = get.col + 2;
						}
						break;
					}
					case 2: {
						x = get.row + 1;
						y = get.col - 1;
						if (_Board[get.row - 1][get.col + 1] != None_Stone && _Board[get.row + 1][get.col - 1] != None_Stone) {
							x = get.row + 2;
							y = get.col - 2;
						}
						break;
					}
					}
					if (_Board[get.row - 1][get.col + 1] == None_Stone || _Board[get.row + 1][get.col - 1] == None_Stone) {

					}
					else if (_Board[get.row - 2][get.col + 2] != None_Stone && _Board[get.row + 2][get.col - 2] != None_Stone) {
						warning = 0;
					}
				}
			}
			else {
				if (choose == 0) {
					srand(time(NULL));
					random = (rand() % 4) + 1;
					switch (random) {
					case 1: {
						x = get.row;
						y = get.col - 2;
						break;
					}
					case 2: {
						x = get.row;
						y = get.col - 1;
						break;
					}
					case 3: {
						x = get.row;
						y = get.col + 1;
						break;
					}
					case 4: {
						x = get.row;
						y = get.col + 2;
					}
					}
					if (_Board[get.row][get.col - 2] != None_Stone && _Board[get.row][get.col + 2] != None_Stone) {
						if (_Board[get.row][get.col - 2] == Black_Stone && _Board[get.row][get.col + 2] == Black_Stone)
							warning = 0;
						else if (_Board[get.row][get.col - 2] == White_Stone)
							y = get.col - 3;
						else if (_Board[get.row][get.col + 2] == White_Stone)
							y = get.col + 3;
					}
				}
				else if (choose == 1) {
					srand(time(NULL));
					random = (rand() % 4) + 1;
					switch (random) {
					case 1: {
						x = get.row - 2;
						y = get.col - 2;
						break;
					}
					case 2: {
						x = get.row - 1;
						y = get.col - 1;
						break;
					}
					case 3: {
						x = get.row + 1;
						y = get.col + 1;
						break;
					}
					case 4: {
						x = get.row + 2;
						y = get.col + 2;
						break;
					}
					}
					if (_Board[get.row - 2][get.col - 2] != None_Stone && _Board[get.row + 2][get.col + 2] != None_Stone) {
						if (_Board[get.row - 2][get.col - 2] == Black_Stone && _Board[get.row + 2][get.col + 2] == Black_Stone)
							warning = 0;
						else if (_Board[get.row - 2][get.col - 2] == White_Stone) {
							x = get.row - 3;
							y = get.col - 3;
						}
						else if (_Board[get.row + 2][get.col + 2] == White_Stone) {
							x = get.row + 3;
							y = get.col + 3;
						}
					}
				}
				else if (choose == 2) {
					srand(time(NULL));
					random = (rand() % 4) + 1;
					switch (random) {
					case 1: {
						x = get.row - 2;
						y = get.col;
						break;
					}
					case 2: {
						x = get.row - 1;
						y = get.col;
						break;
					}
					case 3: {
						x = get.row + 1;
						y = get.col;
						break;
					}
					case 4: {
						x = get.row + 2;
						y = get.col;
						break;
					}
					}
					if (_Board[get.row - 2][get.col] != None_Stone && _Board[get.row + 2][get.col] != None_Stone) {
						if (_Board[get.row - 2][get.col] == Black_Stone && _Board[get.row + 2][get.col] == Black_Stone)
							warning = 0;
						else if (_Board[get.row - 2][get.col] == White_Stone)
							x = get.row - 3;
						else if (_Board[get.row + 2][get.col] == White_Stone)
							x = get.row + 3;
					}
				}
				else if (choose == 3) {
					srand(time(NULL));
					random = (rand() % 4) + 1;
					switch (random) {
					case 1: {
						x = get.row - 2;
						y = get.col + 2;
						break;
					}
					case 2: {
						x = get.row - 1;
						y = get.col + 1;
						break;
					}
					case 3: {
						x = get.row + 1;
						y = get.col - 1;
						break;
					}
					case 4: {
						x = get.row + 2;
						y = get.col - 2;
						break;
					}
					}
					if (_Board[get.row - 2][get.col + 2] != None_Stone && _Board[get.row + 2][get.col - 2] != None_Stone) {
						if (_Board[get.row - 2][get.col + 2] == Black_Stone && _Board[get.row + 2][get.col - 2] == Black_Stone)
							warning = 0;
						else if (_Board[get.row - 2][get.col + 2] == White_Stone) {
							x = get.row - 3;
							y = get.col + 3;
						}
						else if (_Board[get.row + 2][get.col - 2] == White_Stone) {
							x = get.row + 3;
							y = get.col - 3;
						}
					}
				}
			}
			if (_Board[x][y] == None_Stone) {
				break;
			}
			else
				continue;
		}
		pos.row = x;
		pos.col = y;
		_Board[pos.row][pos.col] = stone;
	}

	void Place_Stone(Position& pos, int player, int stone) {
		Print_Board();
		while (1) {
			cout << "請玩家" << player << "輸入座標：";
			cin >> pos.row >> pos.col;

			if (Judge_Coordinate(pos)) {
				break;
			}
			cout << "座標不合法，請重新輸入：" << endl;
			cin.clear();
			cin.ignore(numeric_limits<streamsize>::max(), '\n');
		}
		_Board[pos.row][pos.col] = stone;
	}

	bool Judge_Coordinate(const Position& pos) {	//	判斷座標的合法性
		if (pos.row > 0 && pos.row <= N && pos.col > 0 && pos.col <= N) {	//	判斷是否在棋盤內
			if (_Board[pos.row][pos.col] == None_Stone) {					//	判斷該位置是否為空
				return true;	//	合法
			}
		}
		return false;			//	非法
	}

	int Judge_Victory(Position pos, int stone) {		//	判斷是否有人獲勝

		int sum = 1;        //    總和鄰近棋數
		for (int i = 1; i <= 5; i++) {
			if (_Board[pos.row][pos.col] == _Board[pos.row][pos.col + i])
				sum++;
			else
				break;
		}
		for (int i = 1; i <= 5; i++) {
			if (_Board[pos.row][pos.col] == _Board[pos.row][pos.col - i])
				sum++;
			else
				break;
		}
		if (sum >= 5)
			return 1;

		sum = 1;        //    總和鄰近棋數
		for (int i = 1; i <= 5; i++) {
			if (_Board[pos.row][pos.col] == _Board[pos.row + i][pos.col])
				sum++;
			else
				break;
		}
		for (int i = 1; i <= 5; i++) {
			if (_Board[pos.row][pos.col] == _Board[pos.row - i][pos.col])
				sum++;
			else
				break;
		}
		if (sum >= 5)
			return 1;

		sum = 1;        //    總和鄰近棋數
		for (int i = 1; i <= 5; i++) {
			if (_Board[pos.row][pos.col] == _Board[pos.row + i][pos.col + i])
				sum++;
			else
				break;
		}
		for (int i = 1; i <= 5; i++) {
			if (_Board[pos.row][pos.col] == _Board[pos.row - i][pos.col - i])
				sum++;
			else
				break;
		}
		if (sum >= 5)
			return 1;

		sum = 1;        //    總和鄰近棋數
		for (int i = 1; i <= 5; i++) {
			if (_Board[pos.row][pos.col] == _Board[pos.row - i][pos.col + i])
				sum++;
			else
				break;
		}
		for (int i = 1; i <= 5; i++) {
			if (_Board[pos.row][pos.col] == _Board[pos.row + i][pos.col - i])
				sum++;
			else
				break;
		}
		if (sum >= 5)
			return 1;

		//	判斷棋盤是否下滿
		for (int x = 1; x < N + 1; x++) {
			for (int y = 1; y < N + 1; y++) {
				if (_Board[x][y] == None_Stone) {
					return 0;		//	未下滿回傳 0
				}
			}
		}

		return -1;					//	棋盤下滿為和局
	}

	bool Get_Victory(Position& pos, int player, int stone) {		//	判斷哪位玩家獲勝
		if (Judge_Victory(pos, stone) != 0) {						//	判斷回傳值，若 != 0 則沒人獲勝
			if (Judge_Victory(pos, stone) == 1) {					//	判斷回傳值，若 == 1 代表有玩家獲勝
				Print_Board();
				if (player == 0) {
					cout << "電腦勝利！" << endl;
				}
				else {
					cout << "恭喜玩家" << player << "獲勝！" << endl;
				}
			}
			else {													//	判斷回傳值，若 != 1 代表有和局（回傳值為 -1）
				cout << "和局！" << endl;
			}
			return true;		//	獲勝回傳true，遊戲會詢問是否繼續遊玩
		}
		return false;			//	沒有人贏得遊戲，遊戲繼續進行下去
	}

};

int main() {
	Gomoku game;
	game.Play();
	system("pause");
	return 0;
}
