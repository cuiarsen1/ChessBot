#ifndef _OBSERVER_H
#define _OBSERVER_H

class Observer {
public:
    virtual void render() = 0;
    virtual ~Observer();
};

#endif
