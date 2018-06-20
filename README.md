# 概述
在web搜索技术中，为了能够快速的找到搜索字符串所在的网页，需要对网络爬虫抓取的网页建立索引。  

在建立索引的过程中，需要对所有出现的单词建立索引，用来记录每个单词出现在那些文件中。利用该索引，可以快速找到包含搜索关键字坐在的文件。

在本项目中，我们利用倒排索引和BSBI技术建立索引，并利用变长字节编码vb技术对索引文件进行压缩。

## 倒排索引
倒排索引（Inverted index），也常被称为反向索引，是一种索引方法，被用来存储在全文搜索下某个单词在一个文档或者一组文档中的存储位置的映射。它是文档检索系统中最常用的数据结构。通过倒排索引，可以根据单词快速检索到包含该单词的文档列表。

## 倒排索引中用到的数据结构
### Document Dictionary  
所有的文件名存储在DocDict里面。  
key: FileName  value: DocID
### Term Dictionary  
TermDict保存所有文件中出现的词（空格分开）。  
key: Term  
value: TermID。  
**本项目没有考虑大小写问题。**

### Posting Dictionary
用来存储每个Term在Index文件中的位置
key：TermID  
value: position

### PostingList List
用来存储所有的PostingList


## BSBI算法
BSBI把每个子目录当做一个Block，建立索引，每个Block的索引分别存储为一个文件。所有Block的索引文件都建立好后，然后两两归并排序，生成最终索引文件。


## 索引文件
索引建立完成后，生成4个文件。  
corpus.index：用来保存所有的PostingList  
doc.dict：保存Doc Dictionary  
term.dict：保存Term Dictionary  
posting.dict：保存每个PostingList在索引文件corpus.index中的位置。  


## VB压缩
VB（Variable byte codes）压缩  
对于每个PostingList，如果不采取压缩技术，我们会采用一个int类型（4字节）来存储所有的Doc ID。  
在VB编码中，我们只存储第一个Doc ID，剩下的Doc ID只存储和前面Doc ID的差值。（注意：PostingList里的Doc ID是按照从小到大排序的）  
举例：  


docIDs: 	824 829 215406  
gaps: 		5 214577  
VBCode:	00000110 10111000 10000101	00001101 00001100 10110001  
**编码规则：每个字节的第一位表示编码是否结束，1：结束；0：未结束。**

## 查询
查找包含所有单词的文件，比如hello our world。  
首先找到每个词的PostingList（如果在Term Dictionary里没有找到该单词，则直接返回“no results found”  
然后两两Term的DocId求交集，最后的交集结果就是我们的查询结果。  
求交集时，要先对每个Term的frequency排序，先求frequency小的Term的交集。  


# 其他
##strok实现字符串split方法
C++字符串是不支持split()方法的，但是可以用strok()等函数实现同样的功能。
在本项目中，使用了该函数的从输入和文档中读取一行的输入，然后返回vector<string>作为terms.详见Terms类。

## 内存泄漏的检测
在本项目中，使用了如下的声明在main函数开头，在debug阶段，就可以显示泄漏的内存。杜绝了内存泄漏的发生。

```
#ifdef WIN32
#define new  new(_CLIENT_BLOCK, __FILE__, __LINE__)
	int tmpFlag = _CrtSetDbgFlag(_CRTDBG_REPORT_FLAG);
	tmpFlag |= _CRTDBG_LEAK_CHECK_DF;
_CrtSetDbgFlag(tmpFlag);
#endif
```

## VB编码的实现
与一开始的设计不同，考虑到对postinglist进行vb编码的操作与VBIndex类的高耦合性，这里删除了IndexCompresson类，而将编码与输入，放在了VBIndex类中实现。

## 一些新的语法特性的使用
在本次项目中，使用了lambda表达式、auto关键字、改进for循环等C++11的特性。建议在C++11或更高版本环境下编译。

## 一些不足与改进
因为时间仓促，本项目还有许多不足之处。可作为下一个版本的一些开发目标。  
1.是term的大小写问题。应该在比较和存储term时，忽略大小写。考虑把string类封装成term类，为其编写比较函数。  

2.在代码注释和文档上还不齐全，需要在以后不断完善。


# 致谢
在本项目的选题和开发过程中，得到了孙延涛老师耐心的指导和建议。在很多问题上给了我深刻的启发。在此表示感谢。
