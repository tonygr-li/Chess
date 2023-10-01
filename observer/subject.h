#ifndef SUBJECT_H
#define SUBJECT_H

#include <memory>
#include <vector>

#include "event_variant.h"

class Board;

class Observer;

class Subject {
protected:
    std::vector<std::shared_ptr<Observer>> observers;
public:
    virtual void attach(std::shared_ptr<Observer>);
    virtual void detach(std::shared_ptr<Observer>);
    virtual void notify(const EventVariant&);
    virtual ~Subject() = 0;
};

#endif // SUBJECT_H
