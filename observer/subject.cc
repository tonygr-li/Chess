#include "subject.h"
#include "observer.h"
#include "event_variant.h"

#include <algorithm>
#include <iostream>

void Subject::attach(std::shared_ptr<Observer> observer) {
    observers.push_back(observer);
}

void Subject::detach(std::shared_ptr<Observer> observer) {
    observers.erase(std::remove(observers.begin(), observers.end(), observer), observers.end());
}

void Subject::notify(const EventVariant& event) {
    for (auto observer: observers) {
        observer->onNotify(event);
    }
}

Subject::~Subject() {}
