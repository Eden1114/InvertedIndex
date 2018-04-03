#include "StdAfx.h"
#include "IndexCompression.h"

IndexCompression::IndexCompression(void)
{
}

IndexCompression::~IndexCompression(void)
{
}



/**
   * Gap encodes a postings list.  The DocIds in the postings list are provided
   * in the array inputDocIdsOutputGaps.  The output gaps are placed right back
   * into this array, replacing each docId with the corresponding gap.
   *
   * Example:
   * If inputDocIdsOutputGaps is initially {5, 1000, 1005, 1100}
   * then at the end inputDocIdsOutputGaps is set to {5, 995, 5, 95}
   *
   * @param inputDocIdsOutputGaps The array of input docIds.
   *                              The output gaps are placed back into this array!
   */

void IndexCompression::gapEncode(int inputDocIdsOutputGaps[], int len) {
	  // TODO: Fill in your code here
	
  }


/**
   * Decodes a gap encoded postings list into the corresponding docIds.  The input
   * gaps are provided in inputGapsOutputDocIds.  The output docIds are placed
   * right back into this array, replacing each gap with the corresponding docId.
   *
   * Example:
   * If inputGapsOutputDocIds is initially {5, 905, 5, 95}
   * then at the end inputGapsOutputDocIds is set to {5, 1000, 1005, 1100}
   *
   * @param inputGapsOutputDocIds The array of input gaps.
   *                              The output docIds are placed back into this array.
   */
void IndexCompression::gapDecode(int inputGapsOutputDocIds[], int len) {
	  // TODO: Fill in your code here
	 
  }



 /**
   * Encodes gap using a VB code.  The encoded bytes are placed in outputVBCode.
   * Returns the number bytes placed in outputVBCode.
   *
   * @param gap          gap to be encoded.  Assumed to be greater than or equal to 0.
   * @param outputVBCode VB encoded bytes are placed here.  This byte array is assumed to be large
   *                     enough to hold the VB code for gap (e.g., Integer.SIZE/7 + 1).
   * @return Number of bytes placed in outputVBCode.
   */
  int VBEncodeInteger(int gap, unsigned char outputVBCode[]) {
    int numBytes = 0;
    // TODO: Fill in your code here  


    return numBytes;
  }
  

  /**
   * Decodes the first integer encoded in inputVBCode starting at index startIndex.  The decoded
   * number is placed in the element zero of the numberEndIndex array and the index position
   * immediately after the encoded value is placed in element one of the numberEndIndex array.
   *
   * @param inputVBCode    Byte array containing the VB encoded number starting at index startIndex.
   * @param startIndex     Index in inputVBCode where the VB encoded number starts
   * @param numberEndIndex Outputs are placed in this array.  The first element is set to the
   *                       decoded number and the second element is set to the index of inputVBCode
   *                       immediately after the end of the VB encoded number.
   * @throws IllegalArgumentException If not a valid variable byte code
   */
  void VBDecodeInteger(unsigned char inputVBCode[], int startIndex, int numberEndIndex[]) {
    // TODO: Fill in your code here
	  
  }
