#include <QDebug>
#include "RobotState.h"

std::map<int,QString> RobotState::statusNames;

RobotState::RobotState()
{
    initStatusNames();
}

RobotState::RobotState(Status status, qint64 timestamp,
    float x, float v, float a, qint8 light)
    : _status(status), _timestamp(timestamp), _x(x), _v(v), _a(a), _light(light)
{
    initStatusNames();
}

void RobotState::initStatusNames()
{
    if (statusNames.empty())
    {
        // Not yet initialized...
        statusNames[(int)Status::Accelerate] = QString("Accelerate");
        statusNames[(int)Status::Default] = QString("Default");
        statusNames[(int)Status::Reset] = QString("Reset");
        statusNames[(int)Status::Stopping] = QString("Stopping");
    }
}

QString RobotState::getStatusName() const
{
    auto it = statusNames.find((int)_status);
    Q_ASSERT(it != statusNames.end());
//    qDebug() << "RobotState::getStatusName(): (int)_status " << (int)_status << ": " << it->second;
    return it->second;
}


void RobotState::WriteTo(QDataStream& stream) const
{
    stream << (qint32)_status;
    stream << _timestamp;
    stream << _x;
    stream << _v;
    stream << _a;
    stream << _light;
}

void RobotState::ReadFrom(QDataStream& stream)
{
    // Hogy adom vissza, az örökléshez pointer kell!
    qint32 tmpQint32;
    stream >> tmpQint32;
    _status = (Status)tmpQint32;
    stream >> _timestamp;
    stream >> _x;
    stream >> _v;
    stream >> _a;
    stream >> _light;
}

void RobotState::CopyFrom(const RobotState &other)
{
    _status = other._status;
    _timestamp = other._timestamp;
    _x = other._x;
    _v = other._v;
    _a = other._a;
    _light = other._light;
}