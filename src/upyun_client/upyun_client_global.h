#ifndef UPYUN_CLIENT_GLOBAL_H
#define UPYUN_CLIENT_GLOBAL_H

#include <QtCore/qglobal.h>

#if defined(UPYUN_CLIENT_LIBRARY)
#  define UPYUN_CLIENTSHARED_EXPORT Q_DECL_EXPORT
#else
#  define UPYUN_CLIENTSHARED_EXPORT Q_DECL_IMPORT
#endif

#endif // UPYUN_CLIENT_GLOBAL_H
