#include "./include/tetrisAI.h"

int main(int argc, char** argv)
{
    int num = 0;
    TetrisAI AI;
    cout << "请输入您的俄罗斯方块编号：" << endl;
    cout << "1. I" << endl;
    cout << "2. rectangle" << endl;
    cout << "3. T" << endl;
    cout << "4. L" << endl;
    cout << "5. reverse L" << endl;
    cout << "6. Z" << endl;
    cout << "7. reverse Z" << endl;
    cout << "8. exit" << endl;
    while(cin >> num)
    {
        cout << "Wait..." <<endl;
        if(num == 8)
            break;
        AI.inittetris(num);
        cout << "AI is init..." << endl;
        AI.AIrun();
        cout << "AI is running..." << endl;
        AI.addbesttomap();
        cout << "X: " << AI.bestX << endl;
        cout << "Y: " << AI.bestY << endl;
        cout << "rotate count: " << AI.besttrans << endl;
    }
    return 0;
}