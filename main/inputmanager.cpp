/*
  Q Light Controller
  inputmanager.cpp
  
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

#include <QTreeWidgetItem>
#include <QTreeWidget>
#include <QStringList>
#include <QVBoxLayout>
#include <QMessageBox>
#include <QToolBar>
#include <QAction>
#include <QDebug>
#include <QIcon>

#include <common/qlcinplugin.h>

#include "inputpatcheditor.h"
#include "inputmanager.h"
#include "inputpatch.h"
#include "inputmap.h"
#include "app.h"

#define KColumnUniverse 0
#define KColumnPlugin   1
#define KColumnInput    2
#define KColumnTemplate 3
#define KColumnInputNum 4

extern App* _app;

InputManager::InputManager(QWidget* parent) : QWidget(parent)
{
	setupUi();
	fillTree();
}

InputManager::~InputManager()
{
}

void InputManager::setupUi()
{
	QStringList columns;

	/* Create a new layout for this widget */
	new QVBoxLayout(this);

	/* Toolbar */
	m_toolbar = new QToolBar(tr("Input Manager"), this);
	m_toolbar->addAction(QIcon(":/edit.png"), tr("Edit Mapping"),
			     this, SLOT(slotEditClicked()));
	layout()->addWidget(m_toolbar);
			     
	/* Tree */
	m_tree = new QTreeWidget(this);
	layout()->addWidget(m_tree);
	m_tree->setRootIsDecorated(false);
	m_tree->setItemsExpandable(false);
	m_tree->setSortingEnabled(false);
	m_tree->setAllColumnsShowFocus(true);
	columns << tr("Universe")
		<< tr("Plugin")
		<< tr("Input")
		<< tr("Template");
	m_tree->setHeaderLabels(columns);
		
	connect(m_tree, SIGNAL(itemDoubleClicked(QTreeWidgetItem*,int)),
		this, SLOT(slotEditClicked()));
	
}

/****************************************************************************
 * Toolbar
 ****************************************************************************/

void InputManager::slotEditClicked()
{
	t_input_universe universe;
	InputPatch* inputPatch;
	QTreeWidgetItem* item;

	item = m_tree->currentItem();
	if (item == NULL)
		return;

	universe = item->text(KColumnUniverse).toInt() - 1;
	inputPatch = _app->inputMap()->patch(universe);
	Q_ASSERT(inputPatch != NULL);
	
	InputPatchEditor ipe(this, universe, inputPatch);
	if (ipe.exec() == QDialog::Accepted)
		updateItem(item, inputPatch, universe);
}

/*****************************************************************************
 * Tree widget
 *****************************************************************************/

void InputManager::fillTree()
{
	/* Clear the mapping list just in case and fill with plugins */
	m_tree->clear();
	for (t_input_universe i = 0; i < _app->inputMap()->universes(); i++)
	{
		InputPatch* inputPatch;
		QTreeWidgetItem* item;

		inputPatch = _app->inputMap()->patch(i);
		Q_ASSERT(inputPatch != NULL);

		item = new QTreeWidgetItem(m_tree);
		updateItem(item, inputPatch, i);
	}
}

void InputManager::updateItem(QTreeWidgetItem* item, InputPatch* inputPatch,
			      t_input_universe universe)
{
	Q_ASSERT(item != NULL);
	Q_ASSERT(inputPatch != NULL);

	/* Universe */
	item->setText(KColumnUniverse, QString("%1").arg(universe + 1));

	/* Plugin name */
	if (inputPatch->plugin() != NULL &&
	    inputPatch->input() != KInputInvalid)
	{
		/* Plugin name */
		item->setText(KColumnPlugin, inputPatch->pluginName());

		/* Plugin's input name */
		item->setText(KColumnInput, inputPatch->inputName());

		/* Plugin's input number */
		item->setText(KColumnInputNum,
			      QString("%1").arg(inputPatch->input() + 1));

		/* Device template */
		item->setText(KColumnTemplate, inputPatch->templateName());
	}
	else
	{
		item->setText(KColumnPlugin, KInputNone);
		item->setText(KColumnInput, KInputNone);
		item->setText(KColumnInputNum, KInputNone);
		item->setText(KColumnTemplate, KInputNone);
	}
}