/*
  Q Light Controller
  qlcfixturedefcache.h

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

#ifndef QLCFIXTUREDEFCACHE_H
#define QLCFIXTUREDEFCACHE_H

#include <QStringList>
#include <QObject>
#include <QString>
#include <QMap>

#include <common/qlctypes.h>

class QLCFixtureDef;

/**
 * QLCFixtureDefCache is a cache of fixture definitions that are currently
 * available to the application. Application can get a list of available
 * manufacturer names with QLCFixturedefCache::manufacturers() and subsequently
 * all models for a particular manufacturer with QLCFixtureDefCache::models().
 *
 * The internal structure is a two-tier map (m_models), with the first tier
 * containing manufacturer names as the keys for the first map. The value of
 * each key is another map (the second-tier) whose keys are model names. The
 * value for each model name entry in the second-tier map is the actual
 * QLCFixtureDef instance.
 *
 * Multiple manufacturer & model combinations are discarded.
 */
class QLC_DECLSPEC QLCFixtureDefCache : public QObject
{
	Q_OBJECT

public:
	/**
	 * Create a new fixture definition cache instance.
	 */
	QLCFixtureDefCache(QObject* parent);

	/**
	 * Destroy a fixture definition cache instance.
	 */
	~QLCFixtureDefCache();

	/**
	 * Get a fixture definition by its manufacturer and model.
	 *
	 * @param manufacturer The fixture definition's manufacturer
	 * @param model The fixture definition's model
	 * @return A matching fixture definition or NULL if not found
	 */
	QLCFixtureDef* fixtureDef(const QString& manufacturer,
				  const QString& model) const;

	/**
	 * Get a list of available manufacturer names.
	 */
	QStringList manufacturers() const;

	/**
	 * Get a list of available model names for the given manufacturer.
	 */
	QStringList models(const QString& manufacturer) const;

	/**
	 * Load fixture definitions from the given path. Ignores duplicates.
	 * Returns true even if $fixturePath doesn't contain any fixtures,
	 * if it is still accessible (and exists).
	 *
	 * @param path The fixturePath to load from.
	 * @return true, if the path could be accessed, otherwise false.
	 */
	bool load(const QString& fixturePath);

	/**
	 * Add a fixture definition to the model map.
	 *
	 * @param fixtureDef The fixture definition to add
	 * @return true, if $fixtureDef was added, otherwise false
	 */
	bool addFixtureDef(QLCFixtureDef* fixtureDef);

signals:
	/** Tells that a fixture definition was added */
	void fixtureDefAdded(const QString& manufacturer, const QString& model);

protected:
	/** Map of manufacturers (key) and their models (value) */
	QMap <QString, QMap <QString,QLCFixtureDef*> > m_models;
};

#endif