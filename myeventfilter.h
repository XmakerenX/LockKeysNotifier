#ifndef MYEVENTFILTER_H
#define MYEVENTFILTER_H

#include <QtGui>
#include <iostream>

#include <X11/XKBlib.h>
#undef KeyPress
#undef FocusIn

#include <QtX11Extras/QX11Info>
#include <QTimer>
#include <QEvent>
#include <string>

class myEventFilter: public QObject
{
  public:
  myEventFilter(QObject* qmlObject): QObject(),m_object(qmlObject)
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

  ~myEventFilter(){}

  void onHideCaps()
  {
      if (m_capsOn && m_capsOff)
      {
          m_capsOn->setProperty("visible", false);
          m_capsOff->setProperty("visible", false);
      }
  }

  void onHidenumlock()
  {
      if (m_numlockOn && m_numlockOff)
      {
          m_numlockOn->setProperty("visible", false);
          m_numlockOff->setProperty("visible", false);
      }
  }

  bool eventFilter(QObject* object,QEvent* event)
  {
      unsigned int state = -1;

      XkbGetIndicatorState(QX11Info::display(), XkbUseCoreKbd, &state);

      if (m_capsState != (state & 1) )
      {
          m_capsState = state & 1;

//          QObject* capsOn = nullptr;
//          capsOn = m_object->findChild<QObject*>("capsOn");

//          QObject* capsOff = nullptr;
//          capsOff = m_object->findChild<QObject*>("capsOff");

          if (m_capsOn && m_capsOff)
          {
             m_capsOn->setProperty("visible", m_capsState);
             m_capsOff->setProperty("visible", !m_capsState);

             m_capsTimer->start(3000);
             //QTimer::singleShot(3000, this, &myEventFilter::onHideCaps);
          }

      }

      if (m_numlockState != (state & 2) )
      {
          m_numlockState = state & 2;

          if (m_numlockOn && m_numlockOff)
          {
              m_numlockOn->setProperty("visible", m_numlockState);
              m_numlockOff->setProperty("visible", !m_numlockState);

              m_numlockTimer->start(3000);
          }
      }

//      if ( (event->type() == QEvent::KeyPress))
//      {
//          return true;
//      }
//      if ( (event->type() == QEvent::FocusIn) || (event->type() == QEvent::FocusAboutToChange) )
//      {
//          return false;
//      }
//      else if (event->type() == QEvent::MouseButtonPress)
//      {
//          return true;
//      }

     return QObject::eventFilter(object,event);
//      if ((state & 1) == true)
//      {
//          static unsigned int count = 0;

//          QObject* caps1 = nullptr;
//          caps1 = object->findChild<QObject*>("caps1");

//          count++;
//          std::cout <<"GOT CAPS LOCK " << count << std::endl;

//          if (caps1)
//          {
//             caps1->setProperty("visible", true);
//          }

//          return true;
//      }

//      if ((state & 1) == false)
//      {
//          static unsigned int count = 0;

//          QObject* caps1 = nullptr;
//          caps1 = object->findChild<QObject*>("caps1");

//          count++;
//          std::cout <<"GOT CAPS unlock " << count << std::endl;

//          if (caps1)
//          {
//             caps1->setProperty("visible", false);
//          }

//          return true;
//      }

      //if(event->type() == QEvent::KeyPress)
      //{
      //    QKeyEvent *key = static_cast<QKeyEvent*>(event);
      //    if (key->key() == Qt::Key_CapsLock)
      //    {
      //        std::cout << "Caps lock pressed Event" << std::endl;
      //        return true;
      //    }
      //    else
      //    {
      //        std::cout <<"Filtered KeyPress Event.."<<std::endl;
      //        return true;
      //    }
      //}
      //else
      //{
//          return QObject::eventFilter(object,event);
     // }
  }
private:
  QObject* m_object;

  QObject* m_capsOn;
  QObject* m_capsOff;

  QObject* m_numlockOn;
  QObject* m_numlockOff;

  QTimer* m_capsTimer;
  QTimer* m_numlockTimer;

  bool m_capsState;
  bool m_numlockState;

};

#endif // MYEVENTFILTER_H
