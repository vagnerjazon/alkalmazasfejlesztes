#pragma once
#ifndef ROBOTSTATEHISTORY_H
#define ROBOTSTATEHISTORY_H
#include <QtCore>
//#include <QList>
#include <memory>
#include <vector>
#include "RobotState.h"

class RobotStateHistory : public QObject
{
    Q_OBJECT

public:
    RobotStateHistory();
    virtual ~RobotStateHistory() = default;

    // This needs to be a QObject* list. Pointers to derived classes are
    //  not recognized by QML for proper data binding.
    QList<QObject*> stateList;

    /** Pointer to the most current state. Updated by add(). */
    RobotState *currentState;

    /** This container handles the ownership of the elements referenced in stateList */
    std::vector<std::unique_ptr<RobotState>> container;

    /** Adds a copy of the state to the end of the history. */
    void Add(const RobotState& state);

    // Containers for direct visualization
    QList<int> graphTimestamps;
    QList<int> graphVelocities;
    QList<int> graphAcceleration;
    const int shownStateNumber = 20;

signals:
    void historyChanged();
};

#endif // ROBOTSTATEHISTORY_H