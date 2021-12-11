// TestTheCode.cpp : 此文件包含 "main" 函数。程序执行将在此处开始并结束。
//

#include <iostream>

//定义俄罗斯方块的摆放范围，注意保证 (length * width) % 4 = 0，且length,width >= 4
//按照个人喜好length为长边，width为短边
#define length 6
#define width 4

//定义不同类型方块的数量，注意保证数量 n = length * width / 4
//其中L1定义为正L，Z1定义为正Z
#define Line 2
#define Square 4
#define T 0
#define L1 0
#define L2 0
#define Z1 0
#define Z2 0

//定义不同类型的方块在空间内有多少种状态，即有多少个一维数组模型
//注意：不要更改！！！
const int Linecount = (width - 3) * length + (length - 3) * width;
const int Squarecount = (width - 1) * (length - 1);
const int Tcount = (width - 2) * (length - 1) * 2 + (length - 2) * (width - 1) * 2;
const int L1count = (width - 2) * (length - 1) * 2 + (length - 2) * (width - 1) * 2;
const int L2count = (width - 2) * (length - 1) * 2 + (length - 2) * (width - 1) * 2;
const int Z1count = (width - 2) * (length - 1) + (length - 2) * (width - 1);
const int Z2count = (width - 2) * (length - 1) + (length - 2) * (width - 1);


const int k = length * width + length * width / 4;
const int maxline = Line * Linecount + Square * Squarecount + T * Tcount + L1 * L1count + L2 * L2count + Z1 * Z1count + Z2 * Z2count;



//将俄罗斯方块转化为精确覆盖模型的结构体
//最终需要用到的只有函数getMatrix、数组SolveMatris和ifgo
struct TetrisMatrix
{
	int tetrisLine[Linecount][k] = { 0 };
	int tetrisSquare[Squarecount][k] = { 0 };
	int tetrisT[Tcount][k] = { 0 };
	int tetrisL1[L1count][k] = { 0 };
	int tetrisL2[L2count][k] = { 0 };
	int tetrisZ1[Z1count][k] = { 0 };
	int tetrisZ2[Z2count][k] = { 0 };
	int SolveMatrix[maxline][k] = { 0 };
	bool ifgo = false;
	int Tline = Line, Tsquare = Square, Tt = T, Tl1 = L1, Tl2 = L2, Tz1 = Z1, Tz2 = Z2;

	void TetrisLine()
	{
		for (int i = 0; i < length; i++)
		{
			for (int j = 0; j < width - 3; j++)
			{
				tetrisLine[i * (width - 3) + j][i * width + j] = 1;
				tetrisLine[i * (width - 3) + j][i * width + j + 1] = 1;
				tetrisLine[i * (width - 3) + j][i * width + j + 2] = 1;
				tetrisLine[i * (width - 3) + j][i * width + j + 3] = 1;
			}
			
		}
		for (int i = 0; i < length - 3; i++)
		{
			for (int j = 0; j < width; j++)
			{
				tetrisLine[(width - 3) * length + i * width + j][i * width + j] = 1;
				tetrisLine[(width - 3) * length + i * width + j][(i + 1) * width + j] = 1;
				tetrisLine[(width - 3) * length + i * width + j][(i + 2) * width + j] = 1;
				tetrisLine[(width - 3) * length + i * width + j][(i + 3) * width + j] = 1;
			}

		}
	}

	void TetrisSquare()
	{
		for (int i = 0; i < length - 1; i++)
		{
			for (int j = 0; j < width - 1; j++)
			{
				tetrisSquare[i * (width - 1) + j][i * width + j] = 1;
				tetrisSquare[i * (width - 1) + j][i * width + j + 1] = 1;
				tetrisSquare[i * (width - 1) + j][(i + 1) * width + j] = 1;
				tetrisSquare[i * (width - 1) + j][(i + 1) * width + j + 1] = 1;
			}
		}
	}

	void TetrisT()
	{
		for (int i = 0; i < length - 1; i++)
		{
			for (int j = 0; j < width - 2; j++)
			{
				tetrisT[i * (width - 2) + j][i * width + j] = 1;
				tetrisT[i * (width - 2) + j][i * width + j + 1] = 1;
				tetrisT[i * (width - 2) + j][i * width + j + 2] = 1;
				tetrisT[i * (width - 2) + j][(i + 1) * width + j + 1] = 1;
				tetrisT[(width - 2) * (length - 1) + i * (width - 2) + j][i * width + j + 1] = 1;
				tetrisT[(width - 2) * (length - 1) + i * (width - 2) + j][(i + 1) * width + j] = 1;
				tetrisT[(width - 2) * (length - 1) + i * (width - 2) + j][(i + 1) * width + j + 1] = 1;
				tetrisT[(width - 2) * (length - 1) + i * (width - 2) + j][(i + 1) * width + j + 2] = 1;
			}
		}

		for (int i = 0; i < length - 2; i++)
		{
			for (int j = 0; j < width - 1; j++)
			{
				tetrisT[(width - 2) * (length - 1) * 2 + i * (width - 1) + j][i * width + j] = 1;
				tetrisT[(width - 2) * (length - 1) * 2 + i * (width - 1) + j][(i + 1) * width + j] = 1;
				tetrisT[(width - 2) * (length - 1) * 2 + i * (width - 1) + j][(i + 2) * width + j] = 1;
				tetrisT[(width - 2) * (length - 1) * 2 + i * (width - 1) + j][(i + 1) * width + j + 1] = 1;
				tetrisT[(width - 2) * (length - 1) * 2 + (length - 2) * (width - 1) + i * (width - 1) + j][i * width + j + 1] = 1;
				tetrisT[(width - 2) * (length - 1) * 2 + (length - 2) * (width - 1) + i * (width - 1) + j][(i + 1) * width + j + 1] = 1;
				tetrisT[(width - 2) * (length - 1) * 2 + (length - 2) * (width - 1) + i * (width - 1) + j][(i + 2) * width + j + 1] = 1;
				tetrisT[(width - 2) * (length - 1) * 2 + (length - 2) * (width - 1) + i * (width - 1) + j][(i + 1) * width + j] = 1;
			}
		}
	}

	void TetrisL1()
	{
		for (int i = 0; i < length - 2; i++)
		{
			for (int j = 0; j < width - 1; j++)
			{
				tetrisL1[i * (width - 1) + j][i * width + j] = 1;
				tetrisL1[i * (width - 1) + j][(i + 1) * width + j] = 1;
				tetrisL1[i * (width - 1) + j][(i + 2) * width + j] = 1;
				tetrisL1[i * (width - 1) + j][(i + 2) * width + j + 1] = 1;
				tetrisL1[(length - 2)*(width - 1) + i * (width - 1) + j][i * width + j] = 1;
				tetrisL1[(length - 2) * (width - 1) + i * (width - 1) + j][i * width + j + 1] = 1;
				tetrisL1[(length - 2) * (width - 1) + i * (width - 1) + j][(i + 1) * width + j + 1] = 1;
				tetrisL1[(length - 2) * (width - 1) + i * (width - 1) + j][(i + 2) * width + j + 1] = 1;
			}
		}

		for (int i = 0; i < length - 1; i++)
		{
			for (int j = 0; j < width - 2; j++)
			{
				tetrisL1[(length - 2) * (width - 1) * 2 + i * (width - 2) + j][i * width + j + 2] = 1;
				tetrisL1[(length - 2) * (width - 1) * 2 + i * (width - 2) + j][(i + 1) * width + j] = 1;
				tetrisL1[(length - 2) * (width - 1) * 2 + i * (width - 2) + j][(i + 1) * width + j + 1] = 1;
				tetrisL1[(length - 2) * (width - 1) * 2 + i * (width - 2) + j][(i + 1) * width + j + 2] = 1;
				tetrisL1[(length - 2) * (width - 1) * 2 + (length - 1) * (width - 2) + i * (width - 2) + j][i * width + j] = 1;
				tetrisL1[(length - 2) * (width - 1) * 2 + (length - 1) * (width - 2) + i * (width - 2) + j][i * width + j + 1] = 1;
				tetrisL1[(length - 2) * (width - 1) * 2 + (length - 1) * (width - 2) + i * (width - 2) + j][i * width + j + 2] = 1;
				tetrisL1[(length - 2) * (width - 1) * 2 + (length - 1) * (width - 2) + i * (width - 2) + j][(i + 1) * width + j] = 1;
			}
		}

	}

	void TetrisL2()
	{
		for (int i = 0; i < length - 2; i++)
		{
			for (int j = 0; j < width - 1; j++)
			{
				tetrisL2[i * (width - 1) + j][i * width + j] = 1;
				tetrisL2[i * (width - 1) + j][(i + 1) * width + j] = 1;
				tetrisL2[i * (width - 1) + j][(i + 2) * width + j] = 1;
				tetrisL2[i * (width - 1) + j][i * width + j + 1] = 1;
				tetrisL2[(length - 2) * (width - 1) + i * (width - 1) + j][(i + 2) * width + j] = 1;
				tetrisL2[(length - 2) * (width - 1) + i * (width - 1) + j][i * width + j + 1] = 1;
				tetrisL2[(length - 2) * (width - 1) + i * (width - 1) + j][(i + 1) * width + j + 1] = 1;
				tetrisL2[(length - 2) * (width - 1) + i * (width - 1) + j][(i + 2) * width + j + 1] = 1;
			}
		}

		for (int i = 0; i < length - 1; i++)
		{
			for (int j = 0; j < width - 2; j++)
			{
				tetrisL2[(length - 2) * (width - 1) * 2 + i * (width - 2) + j][i * width + j] = 1;
				tetrisL2[(length - 2) * (width - 1) * 2 + i * (width - 2) + j][(i + 1) * width + j] = 1;
				tetrisL2[(length - 2) * (width - 1) * 2 + i * (width - 2) + j][(i + 1) * width + j + 1] = 1;
				tetrisL2[(length - 2) * (width - 1) * 2 + i * (width - 2) + j][(i + 1) * width + j + 2] = 1;
				tetrisL2[(length - 2) * (width - 1) * 2 + (length - 1) * (width - 2) + i * (width - 2) + j][i * width + j] = 1;
				tetrisL2[(length - 2) * (width - 1) * 2 + (length - 1) * (width - 2) + i * (width - 2) + j][i * width + j + 1] = 1;
				tetrisL2[(length - 2) * (width - 1) * 2 + (length - 1) * (width - 2) + i * (width - 2) + j][i * width + j + 2] = 1;
				tetrisL2[(length - 2) * (width - 1) * 2 + (length - 1) * (width - 2) + i * (width - 2) + j][(i + 1) * width + j + 2] = 1;
			}
		}

	}

	void TetrisZ1()
	{
		for (int i = 0; i < length - 1; i++)
		{
			for (int j = 0; j < width - 2; j++)
			{
				tetrisZ1[i * (width - 2) + j][i * width + j] = 1;
				tetrisZ1[i * (width - 2) + j][i * width + j + 1] = 1;
				tetrisZ1[i * (width - 2) + j][(i + 1) * width + j + 1] = 1;
				tetrisZ1[i * (width - 2) + j][(i + 1) * width + j + 2] = 1;
			}
		}
		for (int i = 0; i < length - 2; i++)
		{
			for (int j = 0; j < width - 1; j++)
			{
				tetrisZ1[(length - 1) * (width - 2) + i * (width - 1) + j][i * width + j + 1] = 1;
				tetrisZ1[(length - 1) * (width - 2) + i * (width - 1) + j][(i + 1) * width + j + 1] = 1;
				tetrisZ1[(length - 1) * (width - 2) + i * (width - 1) + j][(i + 1) * width + j] = 1;
				tetrisZ1[(length - 1) * (width - 2) + i * (width - 1) + j][(i + 2) * width + j] = 1;
			}
		}
	}

	void TetrisZ2()
	{
		for (int i = 0; i < length - 1; i++)
		{
			for (int j = 0; j < width - 2; j++)
			{
				tetrisZ2[i * (width - 2) + j][i * width + j + 2] = 1;
				tetrisZ2[i * (width - 2) + j][i * width + j + 1] = 1;
				tetrisZ2[i * (width - 2) + j][(i + 1) * width + j + 1] = 1;
				tetrisZ2[i * (width - 2) + j][(i + 1) * width + j] = 1;
			}
		}
		for (int i = 0; i < length - 2; i++)
		{
			for (int j = 0; j < width - 1; j++)
			{
				tetrisZ2[(length - 1) * (width - 2) + i * (width - 1) + j][i * width + j] = 1;
				tetrisZ2[(length - 1) * (width - 2) + i * (width - 1) + j][(i + 1) * width + j] = 1;
				tetrisZ2[(length - 1) * (width - 2) + i * (width - 1) + j][(i + 1) * width + j + 1] = 1;
				tetrisZ2[(length - 1) * (width - 2) + i * (width - 1) + j][(i + 2) * width + j + 1] = 1;
			}
		}
	}

	void getMatrix()
	{
		if (Line + Square + T + L1 + L2 + Z1 + Z2 != length * width / 4 || length * width % 4 != 0)
		{
			ifgo = false;
		}
		else
		{
			int m = 0, n = 0;
			while (Tline != 0)
			{
				TetrisLine();
				for (int i = 0; i < Linecount; i++)
				{
					for (int j = 0; j < length * width; j++)
					{
						SolveMatrix[i + m * Linecount][j] = tetrisLine[i][j];
					}
					SolveMatrix[i + m * Linecount][length * width + n] = 1;
				}
				m++;
				n++;
				Tline--;
			}
			m = 0;
			while (Tsquare != 0)
			{
				TetrisSquare();
				for (int i = 0; i < Squarecount; i++)
				{
					for (int j = 0; j < length * width; j++)
					{
						SolveMatrix[i + Line * Linecount + m * Squarecount][j] = tetrisSquare[i][j];
					}
					SolveMatrix[i + Line * Linecount + m * Squarecount][length * width + n] = 1;
				}
				m++;
				n++;
				Tsquare--;
			}
			m = 0;
			while (Tt != 0)
			{
				TetrisT();
				for (int i = 0; i < Tcount; i++)
				{
					for (int j = 0; j < length * width; j++)
					{
						SolveMatrix[i + Line * Linecount + Square * Squarecount + m * Tcount][j] = tetrisT[i][j];
					}
					SolveMatrix[i + Line * Linecount + Square * Squarecount + m * Tcount][length * width + n] = 1;
				}
				m++;
				n++;
				Tt--;
			}
			m = 0;
			while (Tl1 != 0)
			{
				TetrisL1();
				for (int i = 0; i < L1count; i++)
				{
					for (int j = 0; j < length * width; j++)
					{
						SolveMatrix[i + Line * Linecount + Square * Squarecount + T * Tcount + m * L1count][j] = tetrisL1[i][j];
					}
					SolveMatrix[i + Line * Linecount + Square * Squarecount + T * Tcount + m * L1count][length * width + n] = 1;
				}
				m++;
				n++;
				Tl1--;
			}
			m = 0;
			while (Tl2 != 0)
			{
				TetrisL2();
				for (int i = 0; i < L2count; i++)
				{
					for (int j = 0; j < length * width; j++)
					{
						SolveMatrix[i + Line * Linecount + Square * Squarecount + T * Tcount + L1 * L1count + m * L2count][j] = tetrisL2[i][j];
					}
					SolveMatrix[i + Line * Linecount + Square * Squarecount + T * Tcount + L1 * L1count + m * L2count][length * width + n] = 1;
				}
				m++;
				n++;
				Tl2--;
			}
			m = 0;
			while (Tz1 != 0)
			{
				TetrisZ1();
				for (int i = 0; i < Z1count; i++)
				{
					for (int j = 0; j < length * width; j++)
					{
						SolveMatrix[i + Line * Linecount + Square * Squarecount + T * Tcount + L1 * L1count + L2 * L2count + m * Z1count][j] = tetrisZ1[i][j];
					}
					SolveMatrix[i + Line * Linecount + Square * Squarecount + T * Tcount + L1 * L1count + L2 * L2count + m * Z1count][length * width + n] = 1;
				}
				m++;
				n++;
				Tz1--;
			}
			m = 0;
			while (Tz2 != 0)
			{
				TetrisZ2();
				for (int i = 0; i < Z2count; i++)
				{
					for (int j = 0; j < length * width; j++)
					{
						SolveMatrix[i + Line * Linecount + Square * Squarecount + T * Tcount + L1 * L1count + L2 * L2count + Z1 * Z1count + m * Z2count][j] = tetrisZ2[i][j];
					}
					SolveMatrix[i + Line * Linecount + Square * Squarecount + T * Tcount + L1 * L1count + L2 * L2count + Z1 * Z1count + m * Z2count][length * width + n] = 1;
				}
				m++;
				n++;
				Tz2--;
			}
			
				ifgo = true;

		}
	}
}TetrisMatrix;



#define clr(x) memset(x, 0, sizeof(x))
#define clrlow(x) memset(x, -1, sizeof(x))
#define maxnode 1000010
#define maxn 1010



struct DL {
	//行数 列数
	int n, m;
	//U[],D[],L[],R[] 上下左右 col[],row[] 行列编号
	int U[maxnode], D[maxnode], L[maxnode], R[maxnode], col[maxnode], row[maxnode];
	//H[]行首指针, S[]列中节点数
	int H[maxn], S[maxn];
	//包含的行数，ans[]答案,s节点数
	int ansed, ans[maxn], s;


	//初始化十字链表
	void init(int _n, int _m) {
		n = _n;
		m = _m;
		for (int i = 0; i <= m; i++) {
			U[i] = D[i] = i;
			L[i] = i - 1; R[i] = i + 1;
			col[i] = i; row[i] = 0;
			S[i] = 0;
		}
		L[0] = m; R[m] = 0;
		//从m号元素后就表示普通元素
		s = m;
		clrlow(H);
		clr(ans);
		ansed = 0;
		return;
	}

	//在第r行，c列添加新节点，即把第（r，c）个数变成1
	//注意：（r，c）为广义上的位置，并非C++的数组标号，
	//对应C++中的数组为：   example[r - 1][c - 1]
	void push(int r, int c) 
	{
		s++;
		D[s] = D[c];
		U[s] = c;
		U[D[c]] = s;
		D[c] = s;
		row[s] = r;
		col[s] = c;
		S[c]++;
		//如果插入成该行第一个元素
		if (H[r] < 0) 
		{
			H[r] = R[s] = L[s] = s;
		}
		else {
			L[s] = H[r];
			R[s] = R[H[r]];
			L[R[H[r]]] = s;
			R[H[r]] = s;
		}
	}

	//删除列及该列上节点所在的行
	void del(int c) 
	{
		R[L[c]] = R[c];
		L[R[c]] = L[c];
		for (int i = D[c]; i != c; i = D[i]) {
			for (int j = R[i]; j != i; j = R[j]) {
				D[U[j]] = D[j];
				U[D[j]] = U[j];
				--S[col[j]];
			}
		}
		return;
	}

	//恢复第c列及该列上节点所在的行
	void reback(int c) 
	{
		for (int i = U[c]; i != c; i = U[i]) {
			for (int j = L[i]; j != i; j = L[j]) {
				D[U[j]] = j;
				U[D[j]] = j;
			}
		}
		R[L[c]] = c;
		L[R[c]] = c;
		return;
	}

	//求解函数
	//dep为搜索深度
	bool dancing(int dep) 
	{
		if (R[0] == 0) {
			ansed = dep;
			return 1;
		}
		int c = R[0];
		for (int i = R[0]; i != 0; i = R[i]) {
			if (S[i] < S[c])
				c = i;
		}
		del(c);
		for (int i = D[c]; i != c; i = D[i]) {//逐个尝试
			ans[dep] = row[i];
			for (int j = R[i]; j != i; j = R[j]) {
				del(col[j]);
			}
			if (dancing(dep + 1))
				return 1;
			for (int j = L[i]; j != i; j = L[j]) {
				reback(col[j]);
			}
		}
		reback(c);//这个可有可无，写只是为了完整性
		return 0;
	}
}dlx;




int main()
{
	//查看转化后的原始矩阵代码
	//TetrisMatrix.getMatrix();
	////TetrisMatrix.tetrisLineF();
 //   for (int i = 0; i < 96; i++) 
 //   {
 //       for (int j = 0; j < 20; j++)
 //       {
 //           printf("%d  ",TetrisMatrix.SolveMatrix[i][j]);
 //       }
	//	printf("\n");
 //   }

	//求精确覆盖问题，找到答案即停止运算
	TetrisMatrix.getMatrix();
	if (TetrisMatrix.ifgo)
	{
		dlx.init(maxline, k);
		for (int i = 0; i < maxline; i++)
		{
			for (int j = 0; j < k; j++)
			{
				if (TetrisMatrix.SolveMatrix[i][j] == 1)
					dlx.push(i + 1, j + 1);
			}
		}
		if (!dlx.dancing(0))
			printf("No Solution!\n");
		else {
			printf("Solution Count: %d\n", dlx.ansed);
			printf("Solution Line: ");
			for (int i = 0; i < dlx.ansed; i++) 
			{
				printf("%d  ", dlx.ans[i]);
			}
			printf("\n");
			for (int i = 0; i < dlx.ansed; i++)
			{
				for (int j = 0; j < length * width; j++)
				{
					printf("%d  ", TetrisMatrix.SolveMatrix[dlx.ans[i] - 1][j]);
				}
				printf("\n");
			}
			printf("\n");
		}
	}
	else printf("Error!");

	
    return 0;
}
