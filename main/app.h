/*
  Q Light Controller
  app.h

  Copyright (c) Heikki Junnila

  This program is free software; you can redistribute it and/or
  modify it under the terms of the GNU General Public License
  Version 2 as published by the Free Software Foundation.

  This program is distributed in the hope that it will be useful,
  but WITHOUT ANY WARRANTY; without even the implied warranty of
  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
  GNU General Public License for more details. The license is
  in the file "COPYING".

  You should have received a copy of the GNU General Public License
  along with this program; if not, write to the Free Software
  Foundation, Inc., 59 Temple Place - Suite 330, Boston, MA  02111-1307, USA.
*/

#ifndef APP_H
#define APP_H

#include <QMainWindow>
#include <QString>
#include <QList>

#include "common/qlcinplugin.h"
#include "common/qlcoutplugin.h"

class QMessageBox;
class QToolButton;
class QFileDialog;
class QStatusBar;
class QMenuBar;
class QToolBar;
class QPixmap;
class QAction;
class QLabel;
class QTimer;
class QMenu;

class FunctionConsumer;
class DummyOutPlugin;
class DummyInPlugin;
class QLCFixtureDef;
class QLCInPlugin;
class QLCPlugin;
class OutputMap;
class InputMap;
class Doc;
class App;

const QString KApplicationNameLong  = "Q Light Controller";
const QString KApplicationNameShort = "QLC";
const QString KApplicationVersion   = QString("Version ") + QString(VERSION);
const int KApplicationDefaultWidth  = 800;
const int KApplicationDefaultHeight = 600;

class App : public QMainWindow
{
	Q_OBJECT

	/*********************************************************************
	 * Initialization
	 *********************************************************************/
public:
	App();
	~App();

private:
	Q_DISABLE_COPY(App)

protected:
	void init();
	void closeEvent(QCloseEvent*);

	/*********************************************************************
	 * Output mapping
	 *********************************************************************/
public:
	OutputMap* outputMap() const { return m_outputMap; }

protected:
	void initOutputMap();

protected slots:
	void slotOutputMapBlackoutChanged(bool state);
	void slotFlashBlackoutIndicator();

protected:
	OutputMap* m_outputMap;

	/*********************************************************************
	 * Input mapping
	 *********************************************************************/
public:
	InputMap* inputMap() { return m_inputMap; }

protected:
	void initInputMap();

protected:
	InputMap* m_inputMap;

	/*********************************************************************
	 * Function Consumer
	 *********************************************************************/
public:
	/** Get a pointer to the function runner object */
	FunctionConsumer* functionConsumer() { return m_functionConsumer; }

protected:
	/** Initialize the function runner object */
	void initFunctionConsumer();

protected:
	/** The function runner object */
	FunctionConsumer* m_functionConsumer;

	/*********************************************************************
	 * Doc
	 *********************************************************************/
public:
	Doc* doc() { return m_doc; }
	void newDocument();

signals:
	void documentChanged(Doc* doc);

protected slots:
	void slotDocModified(bool state);

protected:
	void initDoc();

protected:
	Doc* m_doc;

	/*********************************************************************
	 * Fixture definitions
	 *********************************************************************/
public:
	/** Load all fixture definitions from the given directory */
	bool loadFixtureDefinitions(QString fixturePath);

	/** Get a fixture definition by its manufacturer & model */
	QLCFixtureDef* fixtureDef(const QString& manufacturer,
				  const QString& model);

	/** Get a list of fixture definitions */
	QList <QLCFixtureDef*> *fixtureDefList() { return &m_fixtureDefList; }

protected:
	/** List of fixture definitions */
	QList <QLCFixtureDef*> m_fixtureDefList;

	/*********************************************************************
	 * Mode: operate or design
	 *********************************************************************/
public:
	enum Mode { Operate, Design };
	Mode mode() { return m_mode; }

public slots:
	void slotModeOperate();
	void slotModeDesign();
	void slotModeToggle();

signals:
	void modeChanged(App::Mode mode);

protected:
	/** Main operating mode */
	Mode m_mode;

	/*********************************************************************
	 * Sane style
	 *********************************************************************/
public:
	/** Attempt to get a sane style that replaces windows' crappy sliders
	 *  and buttons that don't obey background color setting. */
	static QStyle* saneStyle();

protected:
	static QStyle* s_saneStyle;

	/*********************************************************************
	 * Status bar
	 *********************************************************************/
protected:
	void initStatusBar();

protected:
	/** Flashing blackout indicator on the status bar */
	QLabel* m_blackoutIndicator;

	/** Periodic timer object for the flashing indicator */
	QTimer* m_blackoutIndicatorTimer;

	/** Mode indicator on the status bar */
	QLabel* m_modeIndicator;

	/** Indicator showing available fixture space */
	QLabel* m_fixtureAllocationIndicator;

	/** Indicator showing available function space */
	QLabel* m_functionAllocationIndicator;

	/*********************************************************************
	 * Menus & toolbars
	 *********************************************************************/	
protected:
	void initActions();
	void initMenuBar();
	void initToolBar();
	QMenuBar *menuBar();

public slots:
	bool slotFileNew();
	void slotFileOpen();
	void slotFileSave();
	void slotFileSaveAs();
	void slotFileQuit();

	void slotFixtureManager();
	void slotFunctionManager();
	void slotBusManager();
	void slotOutputManager();
	void slotInputManager();

	void slotControlVC();
	void slotControlMonitor();
	void slotControlBlackout();
	void slotControlPanic();

	void slotHelpIndex();
	void slotHelpAbout();
	void slotHelpAboutQt();

	void slotCustomContextMenuRequested(const QPoint&);

protected:
	QAction* m_fileNewAction;
	QAction* m_fileOpenAction;
	QAction* m_fileSaveAction;
	QAction* m_fileSaveAsAction;
	QAction* m_fileQuitAction;

	QAction* m_fixtureManagerAction;
	QAction* m_functionManagerAction;
	QAction* m_busManagerAction;
	QAction* m_inputManagerAction;
	QAction* m_outputManagerAction;

	QAction* m_modeToggleAction;
	QAction* m_controlVCAction;
	QAction* m_controlMonitorAction;
	QAction* m_controlBlackoutAction;
	QAction* m_controlPanicAction;

	QAction* m_helpIndexAction;
	QAction* m_helpAboutAction;
	QAction* m_helpAboutQtAction;

protected:
	QMenu* m_fileMenu;
	QMenu* m_managerMenu;
	QMenu* m_controlMenu;
	QMenu* m_helpMenu;

	QToolBar* m_toolbar;

	/*********************************************************************
	 * Workspace background
	 *********************************************************************/	
public:
	/** Set workspace background image from the given path */
	void setBackgroundImage(QString path);

	/** Get the current workspace background image path */
	QString backgroundImage() const { return m_backgroundImage; }

public slots:
	/** Open a file dialog to browse an image for workspace background */
	void slotSetBackgroundImage();

	/** Clear the current workspace background */
	void slotClearBackgroundImage();

protected:
	QString m_backgroundImage;
};

#endif

