#ifndef PRJMYDBLIBRARY_GLOBAL_H
#define PRJMYDBLIBRARY_GLOBAL_H

#include <QtCore/qglobal.h>

#if defined(PRJMYDBLIBRARY_LIBRARY)
#  define PRJMYDBLIBRARYSHARED_EXPORT Q_DECL_EXPORT
#else
#  define PRJMYDBLIBRARYSHARED_EXPORT Q_DECL_IMPORT
#endif

#endif // PRJMYDBLIBRARY_GLOBAL_H
