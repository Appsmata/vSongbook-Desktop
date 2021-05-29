#ifndef PREFERENCE_H
#define PREFERENCE_H

#include <QMetaType>

struct Preference {
    int preferenceid;
    QString title;
    QString content;
    QString created;
    QString updated;
};

Q_DECLARE_METATYPE(Preference)

#endif // PREFERENCE_H
