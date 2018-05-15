========================================================================
    CONSOLE APPLICATION : InvertedIndex Project Overview
========================================================================

AppWizard has created this InvertedIndex application for you.

This file contains a summary of what you will find in each of the files that
make up your InvertedIndex application.


InvertedIndex.vcproj
    This is the main project file for VC++ projects generated using an Application Wizard.
    It contains information about the version of Visual C++ that generated the file, and
    information about the platforms, configurations, and project features selected with the
    Application Wizard.

InvertedIndex.cpp
    This is the main application source file.

/////////////////////////////////////////////////////////////////////////////
Other standard files:

StdAfx.h, StdAfx.cpp
    These files are used to build a precompiled header (PCH) file
    named InvertedIndex.pch and a precompiled types file named StdAfx.obj.

/////////////////////////////////////////////////////////////////////////////
Other notes:

AppWizard uses "TODO:" comments to indicate parts of the source code you
should add to or customize.

/////////////////////////////////////////////////////////////////////////////
1.BasicIndex存储的数据格式约定
第一行存postinglist的个数
然后以下，每两行存一个postinglist
	第一行存 termId 和 docId的个数
	第二行存 docids
所有的整数以空格分隔