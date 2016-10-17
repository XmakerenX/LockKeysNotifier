#include "myeventfilter.h"
#include <QtX11Extras/QX11Info>
#include <X11/XKBlib.h>

myEventFilter::myEventFilter(QObject* qmlObject): QObject(),m_object(qmlObject)
{
    unsigned int state = -1;

    XkbGetIndicatorState(QX11Info::display(), XkbUseCoreKbd, &state);
    m_capsState = state & 1;
    m_numlockState = state &2;

    m_capsTimer = new QTimer(this);
    m_capsTimer->setSingleShot(true);
    m_numlockTimer = new QTimer(this);
    m_numlockTimer->setSingleShot(true);

    QObject::connect(m_capsTimer, &QTimer::timeout, this, &myEventFilter::onHideCaps);
    QObject::connect(m_numlockTimer, &QTimer::timeout, this, &myEventFilter::onHidenumlock);

    m_capsOn = m_object->findChild<QObject*>("capsOn");
    m_capsOff = m_object->findChild<QObject*>("capsOff");

    m_numlockOn = m_object->findChild<QObject*>("numlockOn");
    m_numlockOff = m_object->findChild<QObject*>("numlockOff");
}

bool myEventFilter::eventFilter(QObject* object,QEvent* event)
{
    unsigned int state = -1;

    XkbGetIndicatorState(QX11Info::display(), XkbUseCoreKbd, &state);

    if (m_capsState != (state & 1) )
    {
        m_capsState = state & 1;

        if (m_capsOn && m_capsOff)
        {
           m_capsOn->setProperty("visible", m_capsState);
           m_capsOff->setProperty("visible", !m_capsState);

           m_capsTimer->start(3000);
        }

    }

    bool newNumlockState = state & 2;
    if (m_numlockState != (newNumlockState) )
    {
        m_numlockState = state & 2;

        if (m_numlockOn && m_numlockOff)
        {
            m_numlockOn->setProperty("visible", m_numlockState);
            m_numlockOff->setProperty("visible", !m_numlockState);

            m_numlockTimer->start(3000);
        }
    }

   return QObject::eventFilter(object,event);
}

void myEventFilter::onHideCaps()
{
    if (m_capsOn && m_capsOff)
    {
        m_capsOn->setProperty("visible", false);
        m_capsOff->setProperty("visible", false);
    }
}

void myEventFilter::onHidenumlock()
{
    if (m_numlockOn && m_numlockOff)
    {
        m_numlockOn->setProperty("visible", false);
        m_numlockOff->setProperty("visible", false);
    }
}
