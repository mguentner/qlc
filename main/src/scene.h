/*
  Q Light Controller
  scene.h
  
  Copyright (C) 2000, 2001, 2002 Heikki Junnila
  
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

#ifndef SCENE_H
#define SCENE_H

#include "function.h"
#include "classes.h"
#include <qlist.h>

class Scene : public Function
{
  Q_OBJECT

 public:
  Scene(unsigned short channels);
  Scene();
  ~Scene();

 public:
  Event* getEvent(Feeder* feeder);
  Event* getNextLevel(Feeder* f);
  void recalculateSpeed(Feeder* feeder);

  void allocate(unsigned short channels);
  void set(unsigned short ch, unsigned char value);

  void saveToFile(QFile &file);

  void unRegisterFunction();
  void registerFunction(Feeder* feeder);

  void createContents(QList<QString> &list);

 private:
  unsigned char* m_values;
};

#endif
