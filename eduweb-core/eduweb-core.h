#ifndef EDUWEB_CORE_H
#define EDUWEB_CORE_H

#include <QtCore/qglobal.h>

#if defined(EDUWEB_CORE_LIBRARY)
#  define EDUWEB_CORE_EXPORT Q_DECL_EXPORT
#else
#  define EDUWEB_CORE_EXPORT Q_DECL_IMPORT
#endif

#endif // EDUWEB_CORE_H