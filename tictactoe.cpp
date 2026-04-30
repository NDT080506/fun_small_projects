#include<bits/stdc++.h>
#include <thread>
#include <chrono>

using namespace std;

void init(char matrix[7][7]){
	for(int i = 0; i < 7; ++i){
		if(i == 0){
			for(int j = 0; j < 7; ++j){
				if (j == 0){
					matrix[i][j] = (char)218;
				}else if (j == 6){
					matrix[i][j] = (char)191;
				}else if (j % 2 == 1){
					matrix[i][j] = (char)196;
				}else{
					matrix[i][j] = (char)194;
				}
			}	
		}else if (i == 6){
			for(int j = 0; j < 7; ++j){
				if (j == 0){
					matrix[i][j] = (char)192;
				}else if (j == 6){
					matrix[i][j] = (char)217;
				}else if (j % 2 == 1){
					matrix[i][j] = (char)196;
				}else{
					matrix[i][j] = (char)193;
				}
			}
		}else if (i % 2 == 0){
			for(int j = 0; j < 7; ++j){
				if (j == 0){
					matrix[i][j] = (char)195;
				}else if (j == 6){
					matrix[i][j] = (char)180;
				}else if (j % 2 == 1){
					matrix[i][j] = (char)196;
				}else{
					matrix[i][j] = (char)197;
				}
			}
		}else{
			for(int j = 0; j < 7; ++j){
				if (j % 2 == 0) matrix[i][j] = (char)179;
				else matrix[i][j] = ' ';
			}
		}
	}
}

void printmatrix(char matrix[7][7]){
	for(int i = 0; i < 7; ++i){
		for(int j = 0; j < 7; ++j){
			cout << matrix[i][j] << " ";
		}
		cout << "\n";
	}
}

int checkwinner(char matrix[7][7]){
	for(int i = 1; i < 7; i+=2){
		for(int j = 1; j < 7-4; j+=2){
			if (matrix[i][j] != ' ' && matrix[i][j] == matrix[i][j+2] && matrix[i][j+2] == matrix[i][j+4]) return 1;
		}
	}
	
	for(int i = 1; i < 7; i+=2){
		for(int j = 1; j < 7-4; j+=2){
			if (matrix[j][i] != ' ' && matrix[j][i] == matrix[j+2][i] && matrix[j+2][i] == matrix[j+4][i]) return 1;
		}
	}
	
	for(int i = 1; i < 7-4; i+=2){
		if (matrix[i][i] != ' ' && matrix[i][i] == matrix[i+2][i+2] && matrix[i+2][i+2] == matrix[i+4][i+4]) return 1;
		
		if (matrix[i][7-i-1] != ' ' && matrix[i][7-i-1] == matrix[i+2][7-i-3] && matrix[i+2][7-i-3] == matrix[i+4][7-i-5]) return 1;
	}
	
	return 0;
}

int stop(char matrix[7][7]){
	for(int i = 1; i < 7; i+=2){
		for(int j = 1; j < 7; j+=2){
			if (matrix[i][j] == ' ') return 0;
		}
	}
	return 1;
}

int evaluate(char matrix[7][7]){ 
	for(int i = 1; i < 7; i+=2){ 
		for(int j = 1; j < 7-4; j+=2){ 
			if (matrix[i][j] == 'X' && matrix[i][j] == matrix[i][j+2] && matrix[i][j+2] == matrix[i][j+4]) return -10; 
		} 
	} 
	
	for(int i = 1; i < 7; i+=2){ 
		for(int j = 1; j < 7-4; j+=2){ 
			if (matrix[j][i] == 'X' && matrix[j][i] == matrix[j+2][i] && matrix[j+2][i] == matrix[j+4][i]) return -10; 
		} 
	} 
	
	for(int i = 1; i < 7-4; i+=2){ 
		if (matrix[i][i] == 'X' && matrix[i][i] == matrix[i+2][i+2] && matrix[i+2][i+2] == matrix[i+4][i+4]) return -10; 
		if (matrix[i][7-i-1] == 'X' && matrix[i][7-i-1] == matrix[i+2][7-i-3] && matrix[i+2][7-i-3] == matrix[i+4][7-i-5]) return -10; 
	} 
	
	for(int i = 1; i < 7; i+=2){ 
		for(int j = 1; j < 7-4; j+=2){ 
			if (matrix[i][j] == 'O' && matrix[i][j] == matrix[i][j+2] && matrix[i][j+2] == matrix[i][j+4]) return 10; 
		} 
	} 
	
	for(int i = 1; i < 7; i+=2){ 
		for(int j = 1; j < 7-4; j+=2){ 
			if (matrix[j][i] == 'O' && matrix[j][i] == matrix[j+2][i] && matrix[j+2][i] == matrix[j+4][i]) return 10; 
		} 
	} 
	
	for(int i = 1; i < 7-4; i+=2){ 
		if (matrix[i][i] == 'O' && matrix[i][i] == matrix[i+2][i+2] && matrix[i+2][i+2] == matrix[i+4][i+4]) return 10; 
		if (matrix[i][7-i-1] == 'O' && matrix[i][7-i-1] == matrix[i+2][7-i-3] && matrix[i+2][7-i-3] == matrix[i+4][7-i-5]) return 10; 
	} 
	
	return 0; 
}

int minimax(char matrix[7][7], bool isMax, int depth){
    int score = evaluate(matrix);
    if (score == 10) return score - depth;
    if (score == -10) return score + depth;
    if (stop(matrix)) return 0;

    if (isMax){
        int best = -1e9;
        for(int i = 1; i < 7; i+=2)
            for(int j = 1; j < 7; j+=2)
                if (matrix[i][j] == ' '){
                    matrix[i][j] = 'O';
                    best = max(best, minimax(matrix, false, depth+1));
                    matrix[i][j] = ' ';
                }
        return best;
    }else{
        int best = 1e9;
        for(int i = 1; i < 7; i+=2)
            for(int j = 1; j < 7; j+=2)
                if (matrix[i][j] == ' '){
                    matrix[i][j] = 'X';
                    best = min(best, minimax(matrix, true, depth+1));
                    matrix[i][j] = ' ';
                }
        return best;
    }
}

int main(){
    
	char matrix[7][7];
	init(matrix);
	
	int player = 1;
	int draw = 0;
	while(1){
		
		printmatrix(matrix);
		
		
		cout << "\n";
		
		if (checkwinner(matrix))break;
		
		if (stop(matrix)){
			draw = 1;
			break;
		}
		
		if (player){
			cout << "Luot cua player, ban muon danh dau X vao o co hang, cot: ";
			int n, m; cin >> n >> m;
			n += n-1;
			m += m-1;
			
			if (matrix[n][m] != ' ') {
			    cout << "O nay da duoc danh, chon o khac!\n";
			    continue;
			}
			
			matrix[n][m] = 'X';
		}else{
			cout << "Luot cua Bot: ";
			int idxi = -1, idxj = -1;
			int best = -1e9;
			for(int i = 1; i < 7; i+=2){
				for(int j = 1; j < 7; j+=2){
					if (matrix[i][j] == ' '){
						matrix[i][j] = 'O';
						int value = minimax(matrix, false, 0);
						if (best < value){
							best = value;
							idxi = i, idxj = j;
						}
						matrix[i][j] = ' ';
					}
				}
			}
			matrix[idxi][idxj] = 'O';
		}
		
		
		player = !player;
		
		cout << "\n";
	}
	
	
	if (draw) cout << "Hoa dai nhan!\n";
	else{
		if (player) cout << "Bot thang!\n";
		else cout << "Player thang!\n";
	}
	
	cout << "Ket thuc tro choi.\n";
	return 0;
}
