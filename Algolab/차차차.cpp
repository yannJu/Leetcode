/*
‘차차차’라는 게임은 자동차를 운전하여 장애물을 피하면서 높은 점수를 얻는 것이 목적인 게임이다. 
이 게임에서 점수를 얻는 방법은 총 3가지이다.
 1) 주행거리에 비례하여 점수 획득.
 2) 장애물을 스쳐 지나가면 1점 획득.
 3) 보너스 아이템을 먹으면 아이템에 따라 점수 획득. 코스를 끝까지 주행했을 때 얻을 수 있는 최대 점수는 (2), (3)에 의해 결정된다. 
 그렇다면 전체 코스 정보가 입력으로 주어질 때, 얻을 수 있는 최대 점수를 계산하는 프로그램을 작성하시오. 
 오른쪽 그림은 입력된 코스를 시각화한 것이다. 숫자 1은 장애물, 숫자 0은
주행 가능한 빈 도로, 그 외 숫자는 아이템을 의미한다. 
아이템을 지나가는 경우 아이템을 표시한 숫자만큼 점수가 올라가며, 2번 행과 같이 두 장애물 사이를 스쳐 지나가는 경우 2점을 얻을 수 있다. 
장애물이 있는 도로는 이동할 수 없다. 
게임은 항상 2번 열에서 시작하며 가로 폭의 크기는 5로 고정돼 있다. 
자동차의 전진 주행은 일정한 속도로 자동으로 주행하며, 사용자는 전진 주행시점에 맞춰 좌측 또는 우측으로 1칸씩 이동하거나 이동하지 않을 수 있다. 
그림의 빨간 선은 최대 점수를 얻을 수 있는 경로를 표시한 것으로, 이 경로대로 주행하는 경우 13점을 얻을 수 있다.

입력
첫 번째 줄에는 테스트 케이스 개수를 나타내는 t (2 ≤ t ≤ 10)가 입력된다. 두 번째 줄부터는 각 테스트
케이스에 대한 입력이 주어진다. 각 테스트 케이스의 첫 번째 줄에는 코스의 크기 N (5 ≤ N ≤ 100)이 주어진다. 다음 N 개의 줄에는 0과
10 사이의 정수 5개가 공백을 기준으로 주어지며, 모든 입력은 끝까지 주행 가능하다. 

출력
입력되는 테스트 케이스 순서대로 출력의 첫 줄에 얻을 수 있는 최대 점수를 출력한다.
입출력 예
입력 출력 

8
1 0 0 0 0
1 0 0 0 0
0 1 0 0 0
0 1 5 0 0
0 0 0 0 1
0 0 1 0 1
0 0 1 0 0
1 0 0 0 0 
5
1 0 0 0 0
1 0 1 0 10
1 0 0 0 0
1 0 0 0 0
1 0 0 0 0

0 1 1 1 1 
0 5 0 4 14
0 3 3 3 3 
0 2 2 2 2 
0 1 1 1 1

13
11
*/

#include <iostream>
#include <vector>
using namespace std;

struct DIR {
    int x;
    int y;
};
DIR *dir;

int main() {
    int testC;

    dir = new DIR[3];
    dir[0].x = -1; dir[0].y = 1;
    dir[1].x = 0; dir[1].y = 1;
    dir[2].x = 1; dir[2].y = 1;

    cin >> testC;
    while(testC--) {
        int N, result = -1;
        cin >> N;

        //create Map
        vector<int> *map = new vector<int>[N + 1], *memo = new vector<int>[N + 1];
        for (int i = 0; i <= N; i++) {
            int tmp;
            vector<int> vtmp, ckTmp;

            if (i == N) {
                for (int j = 0; j < 5; j++) {
                    vtmp.push_back(0);
                    ckTmp.push_back(0);
                }
            }
            else {
                for (int j = 0; j < 5; j++) {
                    cin >> tmp;
                    vtmp.push_back(tmp);
                    ckTmp.push_back(0);
                }
            }
            map[i] = vtmp;
            memo[i] = ckTmp;
        }

        for (int i = N; i > -1; i--) {
            if (i == N) {
                memo[i][2] += map[i][2];
                continue;
            }
            for (int j = 0; j < 5; j++) {
                int memorize = map[i][j];
                if (map[i][j] != 1) {
                    if (j == 0) {
                        if (i < N - 1) {
                            if (map[i + 1][j] == 0 && map[i + 1][j + 1] == 0) memo[i][j] = max(memo[i + 1][j] + memorize, memo[i + 1][j + 1] + memorize);
                            else if (map[i + 1][j] == 0) memo[i][j] = memo[i + 1][j] + memorize;
                            else if (map[i + 1][j + 1] == 0) memo[i][j] = memo[i + 1][j + 1] + memorize;
                        }
                    }
                    else if (j == 4) {
                        if (i < N - 1) {
                            if (map[i + 1][j] == 0 && map[i + 1][j - 1] == 0) memo[i][j] = max(memo[i + 1][j] + memorize, memo[i + 1][j - 1] + memorize);
                            else if (map[i + 1][j] == 0) memo[i][j] = memo[i + 1][j] + memorize;
                            else if (map[i + 1][j - 1] == 0) memo[i][j] = memo[i + 1][j - 1] + memorize;
                        }
                    }
                    else {
                        memo[i][j] = max(memo[i + 1][j - 1] + memorize, memo[i + 1][j] + memorize);
                        memo[i][j] = max(memo[i][j], memo[i + 1][j + 1] + memorize);
                    }

                    if (j > 0 && j < 4) {
                        if (map[i][j - 1] == 1 && map[i][j + 1] == 1) memo[i][j] += 2;
                        else if (map[i][j - 1] == 1 || map[i][j + 1] == 1) memo[i][j] += 1;
                    }
                    else if ((j > 0) && (j > 3) && (map[i][j - 1] == 1)) memo[i][j] += 1;
                    else if ((j <= 0) && (j < 4) && (map[i][j + 1]) == 1) memo[i][j] += 1;
                }
            }
        }

        for (int i = 0; i < 5; i++) result = max(result, memo[0][i]);
        cout << result << endl;

        // for (int i = 0; i < N; i++) {
        //     for (int j = 0; j < 5; j++) cout << memo[i][j] << " ";
        //     cout << endl;
        // }
    }
}