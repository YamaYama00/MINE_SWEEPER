#include <iostream>
#include <random>

char masu[10][10];
//マスを確認
int check(int x, int y, int ii, int jj, int iii, int jjj) {
    int num_bomb = 0;
    for (int i = ii; i <= iii; i++) {         //行を固定して,
        for (int j = jj; j <= jjj; j++) {     //列を変える
            if (masu[x + i][y + j] == '9') {  // 9があったらnum_bomb++
                num_bomb++;
            }
        }
    }
    return num_bomb;
}

int main() {
    //初期化
    for (int kk = 0; kk < 10; kk++) {
        for (int ll = 0; ll < 10; ll++) {
            masu[kk][ll] = '0';
        }
    }
    char masu_[10][10];
    for (int k = 0; k <= 9; k++) {  //ここ配列に[11]入るから怒られるかも
        for (int l = 0; l <= 9; l++) {
            std::random_device rnd;  //乱数を生成
            masu_[k][l] = rnd() % 9;
            // std::cout << masu_[k][l] << std::endl;             //masu_に代入
            if (masu_[k][l] == '0') {  // masu_をmasuに代入
                masu[k][l] = '9';
            }
        }
    }
    for (int k = 0; k <= 9; k++) {  //バグ取り用出力
        for (int l = 0; l <= 9; l++) {
            std::cout << masu[k][l] << " ";
        }
        std::cout << std::endl;
    }
    std::cout << std::endl;

    for (int k = 1; k <= 8; k++) {  //非カドのマスの確認
        for (int l = 1; l <= 8; l++) {
            if (masu[k][l] != 9) {  //確認するマスが9だったらbreak
                int num_masu = check(k, l, -1, -1, 1, 1);
                masu[k][l] = num_masu;
            }
        }
    }
    //(0,0)のとき
    if (masu[0][0] != 9) {
        masu[0][0] = check(0, 0, 0, 0, 1, 1);
    }
    //(9,0)
    if (masu[9][0] != 9) {
        masu[9][0] = check(9, 0, -1, 0, 0, 1);
    }
    //(9,9)
    if (masu[9][9] != 9) {
        masu[9][9] = check(9, 9, -1, -1, 0, 0);
    }
    //(0,9)
    if (masu[0][9] != 9) {
        masu[0][9] = check(0, 9, 0, -1, 1, 0);
    }
    // 0行をチェック
    for (int l = 1; l <= 8; l++) {
        if (masu[0][l] != 9) {
            masu[0][l] = check(0, l, 0, -1, 1, 1);
        }
    }
    // 9行をチェック
    for (int l = 1; l <= 8; l++) {
        if (masu[9][l] != 9) {
            masu[9][l] = check(9, l, -1, -1, 0, 1);
        }
    }
    // 0列をチェック
    for (int k = 1; k <= 8; k++) {
        if (masu[k][0] != 9) {
            masu[k][0] = check(k, 0, -1, 0, 1, 1);
        }
    }
    // 9列をチェック
    for (int k = 1; k <= 8; k++) {
        if (masu[k][9] != 9) {
            masu[k][9] = check(k, 9, -1, -1, 1, 0);
        }
    }

    //出力
    /*   std::cout << "    ";
       for(int n = 0; n < 10; n++){
           std::cout << n << " ";
       }
       std::cout << std::endl;
       std::cout << "    ";
       for(int n = 0; n < 10; n++){
           std::cout << "- ";
       }
       std::cout << std::endl;
       for(int k = 0; k <= 9; k++){
           std::cout << k << " | ";
           for(int l = 0; l <= 9; l++){
               std::cout << masu[k][l] << " ";
           }
           std::cout << std::endl;
       }
   */
    //ゲーム機能
    int game[10][10];
    std::cout << std::endl;
    std::cout << "    ";
    for (int n = 0; n <= 9; n++) {
        std::cout << n << " ";
    }
    std::cout << std::endl;
    std::cout << "    ";
    for (int n = 0; n < 10; n++) {
        std::cout << "- ";
    }
    std::cout << std::endl;
    for (int k = 0; k <= 9; k++) {
        std::cout << k << " | ";
        for (int l = 0; l <= 9; l++) {
            game[k][l] = 8;
            std::cout << game[k][l] << " ";
        }
        std::cout << std::endl;
    }
    int k, l;
    while (game[k][l] != 9) {
        std::cout << "行番号を入力しろ 1 ~ 9" << std::endl;
        std::cin >> k;
        std::cout << "列番号を入力しろ 1 ~ 9" << std::endl;
        std::cin >> l;
        game[k][l] = masu[k][l];
        masu[k][l] = 10;
        std::cout << "    ";
        for (int n = 0; n <= 9; n++) {
            std::cout << n << " ";
        }
        std::cout << std::endl;
        std::cout << "    ";
        for (int n = 0; n < 10; n++) {
            std::cout << "- ";
        }
        std::cout << std::endl;
        for (int k = 0; k <= 9; k++) {
            std::cout << k << " | ";
            for (int l = 0; l <= 9; l++) {
                std::cout << game[k][l] << " ";
            }
            std::cout << std::endl;
        }
        if (game[k][l] == 9) {
            std::cout << "GAME OVER!" << std::endl;
            break;
        }
    }
}
