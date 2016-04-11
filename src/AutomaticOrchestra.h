/*
+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
 AutomaticOrchestra.h
 Copyright (c) 2016 Automatic Orchestra

 See the COPYRIGHT file at the top-level directory of this distribution and at:
 https://github.com/automatic-orchestra/ao_library/blob/master/COPYRIGHT.
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
 This file is part of Automatic Orchestra. It is subject to the license terms
 in the LICENSE file found in the top-level directory of this distribution and at:
 https://github.com/automatic-orchestra/ao_library/blob/master/LICENSE.

 No part of Automatic Orchestra, including this file, may be copied, modified,
 propagated, or distributed except according to the terms contained in the
 LICENSE file.
+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
*/

#ifndef AUTOMATICORCHESTRA_H
#define AUTOMATICORCHESTRA_H

#include <Arduino.h>
#include "Orchestra.h"

class Movement;
class Clock;
class Playlist;

//TODO add global volume control!!!!
class AutomaticOrchestra : public Orchestra
{
public:
    AutomaticOrchestra(Clock* pClock, Playlist* pPlaylist);
    void loop();

    Clock* getClock() {
        return mClock;
    }

    /* receive events from network */
    void onNoteOn(byte channel, byte note, byte velocity);
    void onNoteOff(byte channel, byte note, byte velocity);
    void onControlChange(byte channel, byte control, byte value);
    /* receive events from clock */
    void onClockBarChange(unsigned long bar);
    void onClockBeatChange(unsigned long beat);

    void sendChangeMovement(int mMovementID);
    void sendChangeBPM(unsigned int pBPM);
    void sendEnumeratePods(unsigned int pStartCount);
    void sendPodCount(unsigned int pPodCount);
    void sendRootNote(int pRootNote);
    void sendShift(int pValue);

    void killNotes();

    const static int AO_CONTROL_MESSAGES = 40;
    const static int AO_CONTROL_MESSAGE_CHANGE_MOVEMENT = AO_CONTROL_MESSAGES + 0;
    const static int AO_CONTROL_MESSAGE_CHANGE_BPM = AO_CONTROL_MESSAGES + 1;
    const static int AO_CONTROL_MESSAGE_ENUMERATE_PODS = AO_CONTROL_MESSAGES + 2;
    const static int AO_CONTROL_MESSAGE_POD_COUNT = AO_CONTROL_MESSAGES + 3;
    const static int AO_CONTROL_MESSAGE_SCALE = AO_CONTROL_MESSAGES + 4;
    const static int AO_CONTROL_MESSAGE_ROOT_NOTE = AO_CONTROL_MESSAGES + 5;
    const static int AO_CONTROL_MESSAGE_SHIFT = AO_CONTROL_MESSAGES + 6;
    const static int AO_CONTROL_MESSAGES_MAX = 69;

protected:
    void changeMovement(int pMovementID);

private:
    Clock* mClock;
    bool mWaitingFirstBeat = true;
};

#endif //AUTOMATICORCHESTRA_H
