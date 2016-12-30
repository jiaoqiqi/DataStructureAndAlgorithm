#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <limits.h>

typedef struct {
	unsigned char ch;
	unsigned long weight;
	char *code;
	int parent, lchild, rchild;
} HTNode, *HuffmanTree;

// 统计字符频度的临时结点
typedef struct {
	unsigned char ch;
	unsigned long weight;
} TmpNode;

typedef struct
{
	unsigned char ch;
	char *code;
}Node;



void Select(HTNode *HT, int n, int *s1, int *s2)
{
	int i;
	unsigned long min = ULONG_MAX;
	for (i = 0; i < n; ++i)
		if (HT[i].parent == 0 && HT[i].weight < min)
		{
			min = HT[i].weight;
			*s1 = i;
		}
	HT[*s1].parent = 1;   // 标记此结点已被选中

	min = ULONG_MAX;
	for (i = 0; i < n; ++i)
		if (HT[i].parent == 0 && HT[i].weight < min)
		{
			min = HT[i].weight;
			*s2 = i;
		}
}

// 建立哈夫曼树
void CreateTree(HTNode *HT, unsigned int charKinds, unsigned int nodeCount)
{
	int i;
	int s1, s2;
	for (i = charKinds; i < nodeCount; ++i)
	{
		Select(HT, i, &s1, &s2);		// 选择最小的两个结点
		HT[s1].parent = HT[s2].parent = i;
		HT[i].lchild = s1;
		HT[i].rchild = s2;
		HT[i].weight = HT[s1].weight + HT[s2].weight;
	}
}

// 生成哈夫曼编码
void HufCode(HTNode *HT, unsigned int charKinds)
{
	unsigned int i;
	int current, next, index;
	char *tempCode = (char *)malloc(256 * sizeof(char));		// 暂存编码，最多256个叶子，编码长度不超多255
	tempCode[256 - 1] = '\0';
	for (i = 0; i < charKinds; ++i)
	{
		index = 256 - 1;	// 编码临时空间索引初始化

							// 从叶子向根反向遍历求编码
		for (current = i, next = HT[i].parent; next != 0; current = next, next = HT[next].parent)
			if (HT[next].lchild == current)
				tempCode[--index] = '0';	// 左‘0’
			else
				tempCode[--index] = '1';	// 右‘1’
		HT[i].code = (char *)malloc((256 - index) * sizeof(char));			// 为第i个字符编码动态分配存储空间
		strcpy(HT[i].code, &tempCode[index]);     // 正向保存编码到树结点相应域中
	}
	free(tempCode);		// 释放编码临时空间
}

void SaveEnunsigned(HuffmanTree HT, int charKinds, char *ifile) {
	FILE *inFile, *outFile;
	char outFileName[50];
	unsigned char ch;
	int i, j;
	Node *nodes;
	nodes = (Node *)malloc(sizeof(Node) * 256);
	for (i = 0; i < 256; i++)
		nodes[i].ch = (unsigned char)(i);
	for (i = 0; i < charKinds; i++)
	{
		for (j = 0; j < 256; j++)
		{
			if (HT[i].ch == nodes[j].ch)
			{
				nodes[j].code = (char *)malloc((256) * sizeof(char));			// 为第i个字符编码动态分配存储空间
				strcpy(nodes[j].code, HT[i].code);
			}
		}
	}
	inFile = fopen(ifile, "rb");

	printf("input the save encode FileName: ");
	scanf("%s", outFileName);
	outFile = fopen(outFileName, "wb");
	if (inFile == NULL || fgetc(inFile) == EOF)
	{
		printf("failed to open\n");
		exit(1);
	}
	fread((char *)&ch, sizeof(unsigned char), 1, inFile);		// 读入一个字符
	while (!feof(inFile))
	{
		fwrite(nodes[ch].code, strlen(nodes[ch].code), 1, outFile);// 写入字符
		fread((char *)&ch, sizeof(unsigned char), 1, inFile);		// 读入一个字符
	}
	fclose(inFile);
	fclose(outFile);

}


// 压缩函数
int compress(char *ifname, char *ofname)
{
	unsigned int i, j;
	unsigned int charKinds;		// 字符种类
	unsigned char charTemp;		// 暂存8bits字符
	unsigned long fileLen = 0;
	FILE *infile, *outfile;
	TmpNode nodeType;
	HuffmanTree HT;
	unsigned int nodeCount;
	char codeBuf[256] = "\0";		// 待存编码缓冲区
	unsigned int codeLen;
	/*
	** 动态分配256个结点，暂存字符频度，
	** 统计并拷贝到树结点后立即释放
	*/
	TmpNode *tmpNodes = (TmpNode *)malloc(256 * sizeof(TmpNode));

	// 初始化暂存结点
	for (i = 0; i < 256; ++i)
	{
		tmpNodes[i].weight = 0;
		tmpNodes[i].ch = (unsigned char)i;		// 数组的256个下标与256种字符对应
	}

	// 遍历文件，获取字符频度
	infile = fopen(ifname, "rb");
	// 判断输入文件是否存在
	if (infile == NULL)
		return -1;
	fread((char *)&charTemp, sizeof(unsigned char), 1, infile);		// 读入一个字符
	while (!feof(infile))
	{
		++tmpNodes[charTemp].weight;		// 统计下标对应字符的权重，利用数组的随机访问快速统计字符频度
		++fileLen;
		fread((char *)&charTemp, sizeof(unsigned char), 1, infile);		// 读入一个字符
	}
	fclose(infile);

	// 排序，将频度为零的放最后，剔除
	for (i = 0; i < 256 - 1; ++i)
		for (j = i + 1; j < 256; ++j)
			if (tmpNodes[i].weight < tmpNodes[j].weight)
			{
				nodeType = tmpNodes[i];
				tmpNodes[i] = tmpNodes[j];
				tmpNodes[j] = nodeType;
			}

	// 统计实际的字符种类（出现次数不为0）
	for (i = 0; i < 256; ++i)
		if (tmpNodes[i].weight == 0)
			break;
	charKinds = i;

	if (charKinds == 1)
	{
		outfile = fopen(ofname, "wb");					// 打开压缩后将生成的文件
		fwrite((char *)&charKinds, sizeof(unsigned int), 1, outfile);		// 写入字符种类
		fwrite((char *)&tmpNodes[0].ch, sizeof(unsigned char), 1, outfile);		// 写入唯一的字符
		fwrite((char *)&tmpNodes[0].weight, sizeof(unsigned long), 1, outfile);		// 写入字符频度，也就是文件长度
		free(tmpNodes);
		fclose(outfile);
	}
	else
	{
		nodeCount = 2 * charKinds - 1;		// 根据字符种类数，计算建立哈夫曼树所需结点数
		HT = (HTNode *)malloc(nodeCount * sizeof(HTNode));		// 动态建立哈夫曼树所需结点    

																// 初始化前charKinds个结点
		for (i = 0; i < charKinds; ++i)
		{
			// 将暂存结点的字符和频度拷贝到树结点  creat the tree
			HT[i].ch = tmpNodes[i].ch;
			HT[i].weight = tmpNodes[i].weight;
			HT[i].parent = 0;
		}
		free(tmpNodes); // 释放字符频度统计的暂存区

						// 初始化后nodeCount-char_kins个结点
		for (; i < nodeCount; ++i)
			HT[i].parent = 0;

		CreateTree(HT, charKinds, nodeCount);		// 创建哈夫曼树

		HufCode(HT, charKinds);		// 生成哈夫曼编码
		//for (i = 0; i < charKinds; i++)
		//	printf("%c %s\n", HT[i].ch, HT[i].code);
		SaveEnunsigned(HT, charKinds, ifname);

		// 写入字符和相应权重，供解压时重建哈夫曼树
		outfile = fopen(ofname, "wb");					// 打开压缩后将生成的文件
		fwrite((char *)&charKinds, sizeof(unsigned int), 1, outfile);		// 写入字符种类
		for (i = 0; i < charKinds; ++i)
		{
			fwrite((char *)&HT[i].ch, sizeof(unsigned char), 1, outfile);			// 写入字符（已排序，读出后顺序不变）
			fwrite((char *)&HT[i].weight, sizeof(unsigned long), 1, outfile);		// 写入字符对应权重
		}

		// 紧接着字符和权重信息后面写入文件长度和字符编码
		fwrite((char *)&fileLen, sizeof(unsigned long), 1, outfile);		// 写入文件长度
		infile = fopen(ifname, "rb");		// 以二进制形式打开待压缩的文件
		fread((char *)&charTemp, sizeof(unsigned char), 1, infile);     // 每次读取8bits
		while (!feof(infile))
		{
			// 匹配字符对应编码
			for (i = 0; i < charKinds; ++i)
				if (charTemp == HT[i].ch
					)
					strcat(codeBuf, HT[i].code);

			// 以8位（一个字节长度）为处理单元
			while (strlen(codeBuf) >= 8)
			{
				charTemp = '\0';		// 清空字符暂存空间，改为暂存字符对应编码
				for (i = 0; i < 8; ++i)
				{
					charTemp <<= 1;		// 左移一位，为下一个bit腾出位置
					if (codeBuf[i] == '1')
						charTemp |= 1;		// 当编码为"1"，通过或操作符将其添加到字节的最低位
				}
				fwrite((char *)&charTemp, sizeof(unsigned char), 1, outfile);		// 将字节对应编码存入文件
				strcpy(codeBuf, codeBuf + 8);		// 编码缓存去除已处理的前八位
			}
			fread((char *)&charTemp, sizeof(unsigned char), 1, infile);     // 每次读取8bits
		}
		// 处理最后不足8bits编码
		codeLen = strlen(codeBuf);
		if (codeLen > 0)
		{
			charTemp = '\0';
			for (i = 0; i < codeLen; ++i)
			{
				charTemp <<= 1;
				if (codeBuf[i] == '1')
					charTemp |= 1;
			}
			charTemp <<= 8 - codeLen;       // 将编码字段从尾部移到字节的高位
			fwrite((char *)&charTemp, sizeof(unsigned char), 1, outfile);       // 存入最后一个字节
		}

		// 关闭文件
		fclose(infile);
		fclose(outfile);

		// 释放内存
		for (i = 0; i < charKinds; ++i)
			free(HT[i].code);
		free(HT);
	}
}//compress



 // 解压函数
int extract(char *ifname, char *ofname)
{
	unsigned int i;
	unsigned long fileLen;
	unsigned long writenLen = 0;		// 控制文件写入长度
	FILE *infile, *outfile;
	unsigned int charKinds;		// 存储字符种类
	unsigned int nodeCount;
	HuffmanTree HT;
	unsigned char codeTemp;		// 暂存8bits编码
	unsigned int root;		// 保存根节点索引，供匹配编码使用

	infile = fopen(ifname, "rb");		// 以二进制方式打开压缩文件
										// 判断输入文件是否存在
	if (infile == NULL)
		return -1;

	// 读取压缩文件前端的字符及对应编码，用于重建哈夫曼树
	fread((char *)&charKinds, sizeof(unsigned int), 1, infile);     // 读取字符种类数
	if (charKinds == 1)
	{
		fread((char *)&codeTemp, sizeof(unsigned char), 1, infile);     // 读取唯一的字符
		fread((char *)&fileLen, sizeof(unsigned long), 1, infile);     // 读取文件长度
		outfile = fopen(ofname, "wb");					// 打开压缩后将生成的文件
		while (fileLen--)
			fwrite((char *)&codeTemp, sizeof(unsigned char), 1, outfile);
		fclose(infile);
		fclose(outfile);
	}
	else
	{
		nodeCount = 2 * charKinds - 1;		// 根据字符种类数，计算建立哈夫曼树所需结点数
		HT = (HTNode *)malloc(nodeCount * sizeof(HTNode));		// 动态分配哈夫曼树结点空间
																// 读取字符及对应权重，存入哈夫曼树节点
		for (i = 0; i < charKinds; ++i)
		{
			fread((char *)&HT[i].ch, sizeof(unsigned char), 1, infile);		// 读入字符
			fread((char *)&HT[i].weight, sizeof(unsigned long), 1, infile);	// 读入字符对应权重
			HT[i].parent = 0;
		}
		// 初始化后nodeCount-char_kins个结点的parent
		for (; i < nodeCount; ++i)
			HT[i].parent = 0;

		CreateTree(HT, charKinds, nodeCount);		// 重建哈夫曼树（与压缩时的一致）

													// 读完字符和权重信息，紧接着读取文件长度和编码，进行解码
		fread((char *)&fileLen, sizeof(unsigned long), 1, infile);	// 读入文件长度
		outfile = fopen(ofname, "wb");		// 打开压缩后将生成的文件
		root = nodeCount - 1;
		while (1)
		{
			fread((char *)&codeTemp, sizeof(unsigned char), 1, infile);		// 读取一个字符长度的编码

																			// 处理读取的一个字符长度的编码（通常为8位）
			for (i = 0; i < 8; ++i)
			{
				// 由根向下直至叶节点正向匹配编码对应字符
				if (codeTemp & 128)
					root = HT[root].rchild;
				else
					root = HT[root].lchild;

				if (root < charKinds)
				{
					fwrite((char *)&HT[root].ch, sizeof(unsigned char), 1, outfile);
					++writenLen;
					if (writenLen == fileLen) break;		// 控制文件长度，跳出内层循环
					root = nodeCount - 1;        // 复位为根索引，匹配下一个字符
				}
				codeTemp <<= 1;		// 将编码缓存的下一位移到最高位，供匹配
			}
			if (writenLen == fileLen) break;		// 控制文件长度，跳出外层循环
		}

		// 关闭文件
		fclose(infile);
		fclose(outfile);

		// 释放内存
		free(HT);
	}
}//extract()

int main()
{
	while (1)
	{
		char *inFile, *outFile;
		int chose, flag = 0;		// 每次进入循环都要初始化flag为0
		char ifname[256], ofname[256];		// 保存输入输出文件名
		printf("********************************************************************\n");
		printf("                  Please input the number of operations:        \n\n");
		printf("\t\t\t1: compress  								    \n");
		printf("\t\t\t2: extract  									\n");
		printf("\t\t\t3: quit  										\n");
		printf("**********************************************************************\n");


		// printf("Please input the number of operations:\n 1: compress\n 2: extract\n 3: quit\n");
		scanf("%d", &chose);
		if (chose == 3)
			break;
		else
		{
			printf("Please input the  souce file name: ");
			scanf("%s", ifname);
			inFile = fopen(ifname, "rb");
			if (inFile == NULL) {
				printf("The file is not exits!\n");
				exit(1);
			}

			printf("Please input the compressed name: ");
			scanf("%s", ofname);
		}
		switch (chose)
		{
		case 1: printf("Compressing……\n");
			flag = compress(ifname, ofname);	// 压缩，返回值用于判断是否文件名不存在
			break;
		case 2: printf("Extracting……\n");
			flag = extract(ifname, ofname);		// 解压，返回值用于判断是否文件名不存在
			break;
		}
		if (flag == -1)
			printf("Sorry, infile \"%s\" doesn't exist!\n", ifname);		// 如果标志为‘-1’则输入文件不存在
		else
			printf("Operation is done!\n");		// 操作完成
	}

	return 0;
}