TEMPLATE = subdirs

# Output plugins
SUBDIRS              += enttecdmxusbout
SUBDIRS              += peperoniout
SUBDIRS              += udmxout
SUBDIRS              += midiout
!win32:SUBDIRS       += olaout
!macx:!win32:SUBDIRS += dmx4linuxout
!macx:SUBDIRS        += vellemanout

# Input plugins
SUBDIRS              += ewinginput
SUBDIRS              += midiinput
!macx:!win32:SUBDIRS += hidinput
