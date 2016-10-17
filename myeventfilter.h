#ifndef MYEVENTFILTER_H
#define MYEVENTFILTER_H

#include <QtGui>
#include <QTimer>

class myEventFilter: public QObject
{
  public:
  myEventFilter     (QObject* qmlObject);
  ~myEventFilter    (){}

  bool eventFilter  (QObject* object,QEvent* event);
  void onHideCaps   ();
  void onHidenumlock();

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
