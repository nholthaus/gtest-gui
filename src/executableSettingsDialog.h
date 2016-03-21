//--------------------------------------------------------------------------------------------------
// 
///	@PROJECT	gtest-gui
/// @BRIEF		Dialog box for gtest command line options
///	@DETAILS	
//
//--------------------------------------------------------------------------------------------------
//
// The MIT License (MIT)
//
// Permission is hereby granted, free of charge, to any person obtaining a copy of this software 
// and associated documentation files (the "Software"), to deal in the Software without 
// restriction, including without limitation the rights to use, copy, modify, merge, publish, 
// distribute, sublicense, and/or sell copies of the Software, and to permit persons to whom the 
// Software is furnished to do so, subject to the following conditions:
// 
// The above copyright notice and this permission notice shall be included in all copies or 
// substantial portions of the Software.
// 
// THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR IMPLIED, INCLUDING 
// BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND 
// NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, 
// DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING 
// FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
//
//--------------------------------------------------------------------------------------------------
//
// ATTRIBUTION:
// Parts of this work have been adapted from: 
//
//--------------------------------------------------------------------------------------------------
// 
// Copyright (c) 2016 Nic Holthaus
// 
//--------------------------------------------------------------------------------------------------

#ifndef executableSettingsDialog_h__
#define executableSettingsDialog_h__

//------------------------------
//	INCLUDE
//------------------------------

#include <QDialog>

class QExecutableSettingsDialogPrivate;

//--------------------------------------------------------------------------------------------------
//	CLASS: QExecutableSettingsDialog
//--------------------------------------------------------------------------------------------------
/// @brief		Dialog box to set gtest command line options on a per-test basis
/// @details	
//--------------------------------------------------------------------------------------------------
class QExecutableSettingsDialog : public QDialog
{
public:

	explicit QExecutableSettingsDialog(QWidget* parent = (QWidget*)0);
	virtual ~QExecutableSettingsDialog();
	
protected:

	
	
private:

	Q_DECLARE_PRIVATE(QExecutableSettingsDialog);

	QExecutableSettingsDialogPrivate*	d_ptr;

};	// CLASS: QExecutableSettingsDialog

#endif // executableSettingsDialog_h__