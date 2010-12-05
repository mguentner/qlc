/*
  Q Light Controller
  chaserrunner.h

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

#ifndef CHASERRUNNER_H
#define CHASERRUNNER_H

#include <QList>
#include <QMap>

class UniverseArray;
class FadeChannel;
class Scene;
class Doc;

class ChaserRunner
{
public:
    ChaserRunner(Doc* doc, QList <Scene*> steps);
    ~ChaserRunner();

    void tap();
    void reset();
    void write(UniverseArray* universes, quint32 holdValue);

    /**
     * Create FadeChannel map for the currently active scene. If $handover
     * == true, then the created FadeChannels' starting values are taken from
     * the old m_channelMap's current values. If the old map doesn't contain
     * a FadeChannel for a new channel, then the new FadeChannel will start
     * from whatever is currently in $universes[address]. This handover must
     * be done for HTP channels to work since UniverseArray's intensity
     * channels are always reset to zero before MasterTimer starts making
     * Function::write() calls. If this handover isn't done, all intensity
     * channels would always fade from 0 to the target value.
     *
     * @param universes Current UniverseArray
     * @param handover See above description.
     */
    void createFadeChannels(UniverseArray* universes, bool handover = false);

protected:
    Doc* m_doc;
    QList <Scene*> m_steps; //! List of steps to go thru
    QMap <quint32,FadeChannel> m_channelMap; //! Current step channels
    quint32 m_elapsed; //! Elapsed timer ticks (==write() calls)
    bool m_tap; //! Tracks bus button taps
    int m_currentStep;
};

#endif
