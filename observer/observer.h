#ifndef OBSERVER_H
#define OBSERVER_H

#include <memory>
#include <vector>

#include "event_variant.h"

class Observer {
public:
    virtual void onNotify(const EventVariant&) = 0;
};

#endif // OBSERVER_H
