#include "./include/tetrisAI.h"

/* 俄罗斯方块的碰撞检测 */
bool TetrisAI::collisionJudge(int x, int y)
{
    for(int i = 0; i < 4; i++)
    {
        for(int j = 0; j < 4; j++)
        {
            if(currentblock[i][j] != 0)
            {
                if(x + i < 0 || x + i >= 15 || y + j < 0 || y + j >= 10)
                {
                    return false;
                }
                if(map[x + i][y + j] != 0)
                {
                    return false;
                }
            }
        }
    }
    return true;
}

/* 添加方块至地图并计算消除行数的贡献 */
void TetrisAI::addtomapcopy(int x, int y)
{
    /* 添加方块至地图中 */
    for(int i = 0; i < 4; i++)
    {
        for(int j = 0; j < 4; j++)
        {
            if(currentblock[i][j] != 0)
            {
                map_copy[x + i][y + j] = currentblock[i][j];
            }
        }
    }

    /* 计算消除行数的贡献 */
    int sum = 0, cnt = 0;
    for(int i = 0; i < 15; i++)
    {
        int count = 0;
        for(int j = 0; j < 10; j++)
        {
            if(map[i][j] != 0)
            {
                count++;
            }
        }
        if(count == 10)
        {
            for(int j = 0; j < 10; j++)
            {
                if(map_copy[i][j] == 2)
                {
                    sum++;
                }
                cnt++;
            }
        }
    }

    
    RowsEliminated = sum * cnt;
}

/* 复制地图 */
void TetrisAI::copymap()
{
    for(int i = 0; i < 15; i++)
    {
        for(int j = 0; j < 10; j++)
        {
            map_copy[i][j] = map[i][j];
        }
    }
}

/* 计算行变换 */
int TetrisAI::RowTransitions()
{
    int sum = 0;
    for(int i = 0; i < 15; i++)
    {
        for(int j = 0; j < 9; j++)
        {
            if((map[i][j] != 0 && map[i][j + 1] == 0) || (map[i][j] == 0 && map[i][j + 1] != 0))
            {
                sum++;
            }
        }
    }
    return sum;
}

/* 计算列变换 */
int TetrisAI::ColumnTransitions()
{
    int sum = 0;
    for(int i = 0; i < 14; i++)
    {
        for(int j = 0; j < 10; j++)
        {
            if((map[i][j] != 0 && map[i + 1][j] == 0) || (map[i][j] == 0 && map[i + 1][j] != 0))
            {
                sum++;
            }
        }
    }
    return sum;
}

/* 计算空洞数 */
int TetrisAI::NumberofHoles()
{
    int sum = 0;
    bool flag = false;
    for(int j = 0; j<10; j++)
    {
        for(int i = 0; i<15; i++)
        {
            if(map[i][j] != 0)
            {
                flag = true;
            }
            else
            {
                if(flag)
                {
                    sum++;
                    flag = false;
                }
            }
        }
    }
    return sum;
}

/* 计算井数 */
int TetrisAI::WellSums()
{
    int well[16] = {0, 1, 3, 6, 10, 15, 21, 28, 36, 45, 55, 66, 78, 91, 105, 120};
    int sum = 0;
    for(int j = 0; j < 10; j++)
    {
        int cnt = 0;
        for(int i = 0; i < 15; i++)
        {
            if(j == 0)
            {
                if(map[i][j] == 0 && map[i][j + 1] != 0)
                {
                    cnt++;
                }
                else
                {
                    sum += well[cnt];
                    cnt = 0;
                }
            }
            if(j == 9)
            {
                if(map[i][j] == 0 && map[i][j - 1] != 0)
                {
                    cnt++;
                }
                else
                {
                    sum += well[cnt];
                    cnt = 0;
                }
            }
            else
            {
                if(map[i][j] == 0 && map[i][j + 1] != 0 && map[i][j - 1] != 0)
                {
                    cnt++;
                }
                else
                {
                    sum += well[cnt];
                    cnt = 0;
                }
            }
           
        }
    }
    return sum;
}

/* 根据类型生成俄罗斯方块 */
void TetrisAI::inittetris(int type)
{
    switch(type)
    {
        case 1: //I
            tetris.block[0][0] = 2;
            tetris.block[0][1] = 2;
            tetris.block[0][2] = 2;
            tetris.block[0][3] = 2;
            tetris.pose[0][0] = 1;
            tetris.transpose = 2;
            break;
        case 2: //rectangle
            tetris.block[0][0] = 2;
            tetris.block[0][1] = 2;
            tetris.block[1][0] = 2;
            tetris.block[1][1] = 2;
            tetris.pose[0][0] = 1;
            tetris.transpose = 1;
            break;
        case 3: //T
            tetris.block[0][0] = 2;
            tetris.block[1][0] = 2;
            tetris.block[2][0] = 2;
            tetris.block[1][1] = 2;
            tetris.pose[0][0] = 1;
            tetris.transpose = 2;
            break;
        case 4: //L
            tetris.block[0][0] = 2;
            tetris.block[1][0] = 2;
            tetris.block[2][0] = 2;
            tetris.block[2][1] = 2;
            tetris.pose[0][0] = 1;
            tetris.transpose = 4;
            break;
        case 5: //reverse L
            tetris.block[0][0] = 2;
            tetris.block[0][1] = 2;
            tetris.block[0][2] = 2;
            tetris.block[1][2] = 2;
            tetris.pose[0][0] = 1;
            tetris.transpose = 4;
            break;
        case 6: //Z
            tetris.block[0][0] = 2;
            tetris.block[0][1] = 2;
            tetris.block[1][1] = 2;
            tetris.block[1][2] = 2;
            tetris.pose[0][0] = 1;
            tetris.transpose = 2;
            break;
        case 7: //reverse Z
            tetris.block[0][0] = 2;
            tetris.block[1][0] = 2;
            tetris.block[1][1] = 2;
            tetris.block[2][1] = 2;
            tetris.pose[0][0] = 1;
            tetris.transpose = 2;
            break;
        
    }
    tetris.typenum = type;
}

/* 根据Pierre Dellacherie算法进行加权计算 */
int TetrisAI::PierreDellacherie()
{
    int score =34*RowsEliminated -
    32*RowTransitions() -
    93*ColumnTransitions() -
    1000*NumberofHoles() -
    34*WellSums();
    
    return score;
}

/* 俄罗斯方块的旋转（逆时针） */
void TetrisAI::tetrisrotate()
{
    int temp[4][4];
    int temppose[4][4];
    for(int i = 0; i < 4; i++)
    {
        for(int j = 0; j < 4; j++)
        {
            temp[i][j] = tetris.block[i][j];
            temppose[i][j] = tetris.pose[i][j];
        }
    }
    for(int i = 0; i < 4; i++)
    {
        for(int j = 0; j < 4; j++)
        {
            tetris.block[i][j] = temp[j][3 - i];
            tetris.pose[i][j] = temppose[j][3 - i];
        }
    }
}

/* AI运行的总揽 */
void TetrisAI::AIrun()
{
    cout << "running..." << endl;
    int MaxScore = -2147483647;
    bestX = -100, bestY = -100;
    for(int trans = 0; trans < tetris.transpose; trans++)
    {
        for(int i = 0; i < 4; i++)
        {
            for(int j = 0; j < 4; j++)
            {
                currentblock[i][j] = tetris.block[i][j];
            }
        }
        cout << "First step" << endl;
        for(int j = 0; j < 10; j++)
        {
            for(int i = 0; j < 15; i++)
            {
                cout << "111" << endl;
                if(collisionJudge(i, j))
                {
                    cout << "2" << endl;
                    copymap();
                    addtomapcopy(i, j);
                    int score = PierreDellacherie();
                    if(score > MaxScore)
                    {
                        MaxScore = score;
                        bestX = i;
                        bestY = j;
                        besttrans = trans;
                        
                    }
                }
            }
            cout << "finish 1 line" << endl;
        }
        tetrisrotate();
    }
}

/* 将最后的最佳位置添加到map */
void TetrisAI::addbesttomap()
{
    for(int trans = 0; trans < besttrans; trans++)
    {
        tetrisrotate();
    }
    for(int i = 0; i < 4; i++)
    {
        for(int j = 0; j < 4; j++)
        {
            if(tetris.block[i][j] != 0)
            {
                map[bestX + i][bestY + j] = 1;
            }
        }
    }
}
