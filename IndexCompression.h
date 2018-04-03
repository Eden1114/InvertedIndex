#pragma once

class IndexCompression
{
public:
	IndexCompression(void);
	~IndexCompression(void);

	static void gapEncode(int inputDocIdsOutputGaps[], int len);
	static void gapDecode(int inputGapsOutputDocIds[], int len);
	static int VBEncodeInteger(int gap, unsigned char outputVBCode[]);
	static void VBDecodeInteger(unsigned char inputVBCode[], int startIndex, int numberEndIndex[]);
};
