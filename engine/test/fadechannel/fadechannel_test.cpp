/*
  Q Light Controller - Unit test
  fadechannel_test.cpp

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

#include <QtTest>

#include "qlcmacros.h"
#include "qlcchannel.h"
#include "fadechannel_test.h"

#define private public
#include "fadechannel.h"
#undef private

void FadeChannel_Test::address()
{
    Doc doc(this);
    Fixture* fxi = new Fixture(&doc);
    fxi->setAddress(400);
    fxi->setChannels(5);
    doc.addFixture(fxi);

    FadeChannel fc;
    fc.setFixture(fxi->id());
    fc.setChannel(2);
    QCOMPARE(fc.address(&doc), quint32(402));
}

void FadeChannel_Test::comparison()
{
    FadeChannel ch1;
    ch1.setFixture(0);
    ch1.setChannel(0);

    FadeChannel ch2;
    ch2.setFixture(1);
    ch2.setChannel(0);
    QVERIFY((ch1 == ch2) == false);

    ch1.setFixture(1);
    QVERIFY((ch1 == ch2) == true);

    ch1.setChannel(1);
    QVERIFY((ch1 == ch2) == false);
}

void FadeChannel_Test::group()
{
    Doc doc(this);
    Fixture* fxi = new Fixture(&doc);
    fxi->setChannels(5);
    doc.addFixture(fxi);

    FadeChannel fc;
    fc.setFixture(fxi->id());
    fc.setChannel(2);
    QCOMPARE(fc.group(&doc), QLCChannel::Intensity);
}

void FadeChannel_Test::start()
{
    FadeChannel fch;
    QCOMPARE(fch.start(), uchar(0));

    for (uint i = 0; i <= 255; i++)
    {
        fch.setStart(i);
        QCOMPARE(fch.start(), uchar(i));
    }
}

void FadeChannel_Test::target()
{
    FadeChannel fch;
    QCOMPARE(fch.target(), uchar(0));

    for (uint i = 0; i <= 255; i++)
    {
        fch.setTarget(i);
        QCOMPARE(fch.target(), uchar(i));
    }
}

void FadeChannel_Test::current()
{
    FadeChannel fch;
    QCOMPARE(fch.current(), uchar(0));

    for (uint i = 0; i <= 255; i++)
    {
        fch.setCurrent(i);
        QCOMPARE(fch.current(), uchar(i));
        QCOMPARE(fch.current(0.4), uchar(floor((qreal(i) * 0.4) + 0.5)));
    }
}

void FadeChannel_Test::ready()
{
    FadeChannel ch;
    QVERIFY(ch.isReady() == false);
    ch.setReady(true);
    QVERIFY(ch.isReady() == true);
}

void FadeChannel_Test::fadeTime()
{
    FadeChannel ch;
    QVERIFY(ch.fadeTime() == 0);
    ch.setFadeTime(50);
    QVERIFY(ch.fadeTime() == 50);
}

void FadeChannel_Test::nextStep()
{
    FadeChannel fc;
    fc.setStart(0);
    fc.setTarget(250);

    fc.setFadeTime(1000);

    for (int i = 5; i < 250; i += 5)
    {
        int value = fc.nextStep(MasterTimer::tick());
        QCOMPARE(value, i);
    }

    fc.setCurrent(0);
    fc.setReady(false);
    fc.setFadeTime(0);
    fc.setElapsed(0);
    QCOMPARE(fc.nextStep(MasterTimer::tick()), uchar(250));

    fc.setCurrent(0);
    fc.setReady(false);
    fc.setFadeTime(MasterTimer::tick() / 5);
    fc.setElapsed(0);
    QCOMPARE(fc.nextStep(MasterTimer::tick()), uchar(250));

    fc.setCurrent(0);
    fc.setReady(false);
    fc.setFadeTime(1 * MasterTimer::tick());
    fc.setElapsed(0);
    QCOMPARE(fc.nextStep(MasterTimer::tick()), uchar(250));

    fc.setCurrent(0);
    fc.setReady(false);
    fc.setFadeTime(2 * MasterTimer::tick());
    fc.setElapsed(0);
    QCOMPARE(fc.nextStep(MasterTimer::tick()), uchar(125));
    QCOMPARE(fc.nextStep(MasterTimer::tick()), uchar(250));

    fc.setCurrent(0);
    fc.setReady(false);
    fc.setFadeTime(5 * MasterTimer::tick());
    fc.setElapsed(0);
    QCOMPARE(fc.nextStep(MasterTimer::tick()), uchar(50));
    QCOMPARE(fc.nextStep(MasterTimer::tick()), uchar(100));
    QCOMPARE(fc.nextStep(MasterTimer::tick()), uchar(150));
    QCOMPARE(fc.nextStep(MasterTimer::tick()), uchar(200));
    QCOMPARE(fc.nextStep(MasterTimer::tick()), uchar(250));
}

void FadeChannel_Test::calculateCurrent()
{
    FadeChannel fch;
    fch.setStart(0);
    fch.setTarget(255);

    // Simple: 255 ticks to fade from 0 to 255
    for (uint time = 0; time < 255; time++)
        QCOMPARE(fch.calculateCurrent(255, time), uchar(time));

    // Same thing, but the value should stay at 255 same after 255 ticks
    for (uint time = 0; time <= 512; time++)
        QCOMPARE(fch.calculateCurrent(255, time), uchar(MIN(time, 255)));

    // Simple reverse: 255 ticks to fade from 255 to 0
    fch.setStart(255);
    fch.setTarget(0);
    for (uint time = 0; time <= 255; time++)
        QCOMPARE(fch.calculateCurrent(255, time), uchar(255 - time));

    // A bit more complex involving decimals that don't produce round integers
    fch.setStart(13);
    fch.setTarget(147);
    QCOMPARE(fch.calculateCurrent(13, 0), uchar(13));
    QCOMPARE(fch.calculateCurrent(13, 1), uchar(23));
    QCOMPARE(fch.calculateCurrent(13, 2), uchar(33));
    QCOMPARE(fch.calculateCurrent(13, 3), uchar(43));
    QCOMPARE(fch.calculateCurrent(13, 4), uchar(54));
    QCOMPARE(fch.calculateCurrent(13, 5), uchar(64));
    QCOMPARE(fch.calculateCurrent(13, 6), uchar(74));
    QCOMPARE(fch.calculateCurrent(13, 7), uchar(85));
    QCOMPARE(fch.calculateCurrent(13, 8), uchar(95));
    QCOMPARE(fch.calculateCurrent(13, 9), uchar(105));
    QCOMPARE(fch.calculateCurrent(13, 10), uchar(116));
    QCOMPARE(fch.calculateCurrent(13, 11), uchar(126));
    QCOMPARE(fch.calculateCurrent(13, 12), uchar(136));
    QCOMPARE(fch.calculateCurrent(13, 13), uchar(147));

    // One more to check slower operation (200 ticks for 144 steps)
    fch.setStart(245);
    fch.setTarget(101);
    QCOMPARE(fch.calculateCurrent(200, 0), uchar(245));
    QCOMPARE(fch.calculateCurrent(200, 1), uchar(245));
    QCOMPARE(fch.calculateCurrent(200, 2), uchar(244));
    QCOMPARE(fch.calculateCurrent(200, 3), uchar(243));
    QCOMPARE(fch.calculateCurrent(200, 4), uchar(243));
    QCOMPARE(fch.calculateCurrent(200, 5), uchar(242));
    QCOMPARE(fch.calculateCurrent(200, 6), uchar(241));
    QCOMPARE(fch.calculateCurrent(200, 7), uchar(240));
    QCOMPARE(fch.calculateCurrent(200, 8), uchar(240));
    QCOMPARE(fch.calculateCurrent(200, 9), uchar(239));
    QCOMPARE(fch.calculateCurrent(200, 10), uchar(238));
    QCOMPARE(fch.calculateCurrent(200, 11), uchar(238));
    // Skip...
    QCOMPARE(fch.calculateCurrent(200, 100), uchar(173));
    QCOMPARE(fch.calculateCurrent(200, 101), uchar(173));
    QCOMPARE(fch.calculateCurrent(200, 102), uchar(172));
    // Skip...
    QCOMPARE(fch.calculateCurrent(200, 198), uchar(103));
    QCOMPARE(fch.calculateCurrent(200, 199), uchar(102));
    QCOMPARE(fch.calculateCurrent(200, 200), uchar(101));
}

QTEST_APPLESS_MAIN(FadeChannel_Test)
