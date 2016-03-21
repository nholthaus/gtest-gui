//--------------------------------------------------------------------------------------------------
// 
///	@PROJECT	project
///	@BRIEF		brief
///	@DETAILS	details
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

#ifndef mainwindow_p_h__
#define mainwindow_p_h__

//------------------------------
//	INCLUDE
//------------------------------
#include "mainwindow.h"
#include "qexecutablemodel.h"
#include "QBottomUpSortFilterProxy.h"
#include "executableSettingsDialog.h"
#include "QStdOutSyntaxHighlighter.h"
#include "appinfo.h"
#include "gtestModel.h"

#include <atomic>
#include <condition_variable>
#include <map>
#include <mutex>
#include <thread>

#include <QAction>
#include <QApplication>
#include <QDateTime>
#include <QDebug>
#include <QDesktopServices>
#include <QDialog>
#include <QDockWidget>
#include <QDomDocument>
#include <QEventLoop>
#include <QFileDialog>
#include <QFileSystemWatcher>
#include <QFrame>
#include <QHash>
#include <QLayout>
#include <QLineEdit>
#include <QListWidget>
#include <QMenu>
#include <QMessageBox>
#include <QPersistentModelIndex>
#include <QProcess>
#include <QPushButton>
#include <QSettings>
#include <QStandardItem>
#include <QStandardItemModel>
#include <QStandardPaths>
#include <QStatusBar>
#include <QSystemTrayIcon>
#include <QTextEdit>
#include <QTreeView>

#include <qglobal.h>

//--------------------------------------------------------------------------------------------------
//	CLASS: MainWindowPrivate
//--------------------------------------------------------------------------------------------------
/// @brief		Private members of MainWindow
/// @details	
//--------------------------------------------------------------------------------------------------
class MainWindowPrivate : public QObject
{
	Q_OBJECT

public:

	Q_DECLARE_PUBLIC(MainWindow);

	// GUI components

	MainWindow*								q_ptr;
	
	QDockWidget*							executableDock;							///< Dock Widget for the gtest executable selector.
	QFrame*									executableDockFrame;					///< Frame for containing the dock's sub-widgets
	QTreeView*								executableTreeView;						///< Widget to display and select gtest executables	
	QExecutableModel*						executableModel;						///< Item model for test executables.
	QPushButton*							addTestButton;							///< Button which adds a test to the monitored tests.
	QFileSystemWatcher*						fileWatcher;							///< Hash table to store the file system watchers.
	QStringList								executablePaths;						///< String list of all the paths, which can be used to re-constitute the filewatcher after an executable rebuild.
	QExecutableSettingsDialog*				executableAdvancedSettingsDialog;		///< Dialog to display/select advanced command-line settings.

	QFrame*									centralFrame;							///< Central widget frame.
	QLineEdit*								testCaseFilterEdit;						///< Line edit for filtering test cases.
	QTreeView*								testCaseTreeView;						///< Tree view where the test results are displayed.
	QBottomUpSortFilterProxy*				testCaseProxyModel;						///< Sort/filter proxy for the test-case mode.

	QDockWidget*							failureDock;							///< Dock widget for reporting failures.
	QTreeView*								failureTreeView;						///< Tree view for failures.
	QBottomUpSortFilterProxy*				failureProxyModel;						///< Proxy model for sorting failures.

	QStatusBar*								statusBar;								///< status

	QDockWidget*							consoleDock;							///< Console emulator
	QTextEdit*								consoleTextEdit;						///< Console emulator text edit
	QStdOutSyntaxHighlighter*				consoleHighlighter;						///< Console syntax highlighter.

	QSystemTrayIcon*						systemTrayIcon;							///< System Tray Icon.

	// Menus
	QMenu*									executableContextMenu;					///< context menu for the executable list view.
	QAction*								killTestAction;							///< Kills a running test
	QAction*								runTestAction;							///< Manually forces a test-run.
	QAction*								removeTestAction;						///< Removes a test from being watched.
	
	QMenu*									optionsMenu;							///< Menu to set system options
	QAction*								notifyOnFailureAction;					///< Enable failure notifications
	QAction*								notifyOnSuccessAction;					///< Enable success notifications

	QMenu*									windowMenu;								///< Menu to display/change dock visibility.

	QMenu*									testMenu;								///< Menu for test-related actions
	QAction*								addTestAction;							///< Opens a dialog to add a test executable.
	QAction*								selectAndKillTest;						///< Selects and kills a running test.
	QAction*								selectAndRemoveTestAction;				///< Remove a test after choosing it from a list.
	QAction*								selectAndRunTest;						///< Run a test after selecting it from a list.																	///< program options.

	QMenu*									testCaseViewContextMenu;				///< Context menu for the test case tree view
	QAction*								testCaseViewExpandAllAction;			///< expands all nodes in the test case tree view
	QAction*								testCaseViewCollapseAllAction;			///< Collapses all nodes in the test case tree view.

	QMenu*									consoleContextMenu;						///< Context menu for the console dock;
	QAction*								clearConsoleAction;						///< Clears the console window.
	
	// state variables
	QString									mostRecentFailurePath;					///< Stores the path [key] of the most recently failed test.
	QHash<QString, QPersistentModelIndex>	executableModelHash;					///< Hash for finding entries in the executable model.
	QHash<QString, Qt::CheckState>			executableCheckedStateHash;				///< Hash of the previous state of the checkboxes.
	QHash<QString, QDomDocument>			testResultsHash;						///< Hash table storing the xml test results for each test path.
	std::map<QString, std::atomic<bool>>	testRunningHash;						///< Stores whether the given test is actively running.

	// synchronization
	std::mutex								threadKillMutex;						
	std::condition_variable					threadKillCv;							///< Condition variable that is notified when a thread is killed.

signals:

	void testResultsReady(QString path, bool notify);								///< Signal emitted when new test results are ready
	void setStatus(QString);
	void showMessage(QString msg, int timeout = 0);
	void testOutputReady(QString);
	void testProgress(QString path, int complete, int total);
	void runTest(QString path, bool notify);
	void killTest(QString path);													///< kills the test if it's currently running

public:

	explicit MainWindowPrivate(MainWindow* q);

	QString xmlPath(const QString& testPath) const;

	void addTestExecutable(const QString& path, Qt::CheckState checked, QDateTime lastModified);

	void runTestInThread(const QString& pathToTest, bool notify);

	bool loadTestResults(const QString& testPath, bool notify);

	void selectTest(const QString& testPath);

	void saveSettings() const;

	void loadSettings();

	void removeTest(const QModelIndex &index);

protected:

	void createTestMenu();
	void createOptionsMenu();
	void createWindowMenu();

	void createExecutableContextMenu();
	void createTestCaseViewContextMenu();
	void createConsoleContextMenu();

	QModelIndex getTestIndexDialog(const QString& label, bool running = false);

};	// CLASS: MainWindowPrivate


#endif // mainwindow_p_h__