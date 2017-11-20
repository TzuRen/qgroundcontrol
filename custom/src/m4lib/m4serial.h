/**
 * @file SerialComm.h
 *
 * @author Gus Grubba <mavlink@grubba.com>
 */

#pragma once

// TODO: include to be removed
#include "TyphoonHCommon.h"

// Only to be compiled on ST16 hardware (Android x86)
#if defined(__androidx86__)

#include <termios.h>

class M4SerialComm : public QObject
{
    Q_OBJECT
public:
    M4SerialComm  (QObject* parent = NULL);
    ~M4SerialComm ();
    bool        init    (QString port, int baud);
    bool        open    ();
    void        close   ();
    bool        write   (QByteArray data, bool debug = false);
    bool        write   (void* data, int length);
    void        tryRead ();

private:
    int         _openPort       (const char* port);
    int         _writePort      (void *buffer, int len);
    bool        _setupPort      (int baud);
    void        _readPacket     (uint8_t length);
    bool        _readData       (void *buffer, int len);
signals:
    void        bytesReady      (QByteArray data);

private:
    enum class SerialPortState {
        CLOSED,
        OPEN,
        ERROR
    };
    enum class PacketState {
        NONE,
        FIRST_ID,
        SECOND_ID
    };

    int         _fd = -1;
    int         _baudrate = 230400;
    SerialPortState _serialPortStatus = SerialPortState::CLOSED;
    QString     _uart_name {};
    PacketState _currentPacketStatus = PacketState::NONE;
    struct termios  _savedtio;
};

#endif
