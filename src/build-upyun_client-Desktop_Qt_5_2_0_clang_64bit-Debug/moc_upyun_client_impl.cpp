/****************************************************************************
** Meta object code from reading C++ file 'upyun_client_impl.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.2.0)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../upyun_client/upyun_client_impl.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'upyun_client_impl.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.2.0. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
struct qt_meta_stringdata_upyun_client_impl_t {
    QByteArrayData data[17];
    char stringdata[201];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    offsetof(qt_meta_stringdata_upyun_client_impl_t, stringdata) + ofs \
        - idx * sizeof(QByteArrayData) \
    )
static const qt_meta_stringdata_upyun_client_impl_t qt_meta_stringdata_upyun_client_impl = {
    {
QT_MOC_LITERAL(0, 0, 17),
QT_MOC_LITERAL(1, 18, 14),
QT_MOC_LITERAL(2, 33, 0),
QT_MOC_LITERAL(3, 34, 9),
QT_MOC_LITERAL(4, 44, 10),
QT_MOC_LITERAL(5, 55, 16),
QT_MOC_LITERAL(6, 72, 13),
QT_MOC_LITERAL(7, 86, 5),
QT_MOC_LITERAL(8, 92, 1),
QT_MOC_LITERAL(9, 94, 8),
QT_MOC_LITERAL(10, 103, 10),
QT_MOC_LITERAL(11, 114, 14),
QT_MOC_LITERAL(12, 129, 10),
QT_MOC_LITERAL(13, 140, 11),
QT_MOC_LITERAL(14, 152, 12),
QT_MOC_LITERAL(15, 165, 6),
QT_MOC_LITERAL(16, 172, 27)
    },
    "upyun_client_impl\0uploadProgress\0\0"
    "bytesSent\0bytesTotal\0downloadProgress\0"
    "bytesReceived\0error\0e\0finished\0"
    "uploadFile\0QNetworkReply*\0local_path\0"
    "remote_path\0downloadFile\0_error\0"
    "QNetworkReply::NetworkError\0"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_upyun_client_impl[] = {

 // content:
       7,       // revision
       0,       // classname
       0,    0, // classinfo
       7,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       4,       // signalCount

 // signals: name, argc, parameters, tag, flags
       1,    2,   49,    2, 0x06,
       5,    2,   54,    2, 0x06,
       7,    1,   59,    2, 0x06,
       9,    0,   62,    2, 0x06,

 // slots: name, argc, parameters, tag, flags
      10,    2,   63,    2, 0x0a,
      14,    1,   68,    2, 0x0a,
      15,    1,   71,    2, 0x0a,

 // signals: parameters
    QMetaType::Void, QMetaType::LongLong, QMetaType::LongLong,    3,    4,
    QMetaType::Void, QMetaType::LongLong, QMetaType::LongLong,    6,    4,
    QMetaType::Void, QMetaType::QString,    8,
    QMetaType::Void,

 // slots: parameters
    0x80000000 | 11, QMetaType::QString, QMetaType::QString,   12,   13,
    0x80000000 | 11, QMetaType::QString,   13,
    QMetaType::Void, 0x80000000 | 16,    2,

       0        // eod
};

void upyun_client_impl::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        upyun_client_impl *_t = static_cast<upyun_client_impl *>(_o);
        switch (_id) {
        case 0: _t->uploadProgress((*reinterpret_cast< qint64(*)>(_a[1])),(*reinterpret_cast< qint64(*)>(_a[2]))); break;
        case 1: _t->downloadProgress((*reinterpret_cast< qint64(*)>(_a[1])),(*reinterpret_cast< qint64(*)>(_a[2]))); break;
        case 2: _t->error((*reinterpret_cast< const QString(*)>(_a[1]))); break;
        case 3: _t->finished(); break;
        case 4: { QNetworkReply* _r = _t->uploadFile((*reinterpret_cast< const QString(*)>(_a[1])),(*reinterpret_cast< const QString(*)>(_a[2])));
            if (_a[0]) *reinterpret_cast< QNetworkReply**>(_a[0]) = _r; }  break;
        case 5: { QNetworkReply* _r = _t->downloadFile((*reinterpret_cast< const QString(*)>(_a[1])));
            if (_a[0]) *reinterpret_cast< QNetworkReply**>(_a[0]) = _r; }  break;
        case 6: _t->_error((*reinterpret_cast< QNetworkReply::NetworkError(*)>(_a[1]))); break;
        default: ;
        }
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        switch (_id) {
        default: *reinterpret_cast<int*>(_a[0]) = -1; break;
        case 6:
            switch (*reinterpret_cast<int*>(_a[1])) {
            default: *reinterpret_cast<int*>(_a[0]) = -1; break;
            case 0:
                *reinterpret_cast<int*>(_a[0]) = qRegisterMetaType< QNetworkReply::NetworkError >(); break;
            }
            break;
        }
    } else if (_c == QMetaObject::IndexOfMethod) {
        int *result = reinterpret_cast<int *>(_a[0]);
        void **func = reinterpret_cast<void **>(_a[1]);
        {
            typedef void (upyun_client_impl::*_t)(qint64 , qint64 );
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&upyun_client_impl::uploadProgress)) {
                *result = 0;
            }
        }
        {
            typedef void (upyun_client_impl::*_t)(qint64 , qint64 );
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&upyun_client_impl::downloadProgress)) {
                *result = 1;
            }
        }
        {
            typedef void (upyun_client_impl::*_t)(const QString & );
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&upyun_client_impl::error)) {
                *result = 2;
            }
        }
        {
            typedef void (upyun_client_impl::*_t)();
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&upyun_client_impl::finished)) {
                *result = 3;
            }
        }
    }
}

const QMetaObject upyun_client_impl::staticMetaObject = {
    { &QObject::staticMetaObject, qt_meta_stringdata_upyun_client_impl.data,
      qt_meta_data_upyun_client_impl,  qt_static_metacall, 0, 0}
};


const QMetaObject *upyun_client_impl::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *upyun_client_impl::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_upyun_client_impl.stringdata))
        return static_cast<void*>(const_cast< upyun_client_impl*>(this));
    return QObject::qt_metacast(_clname);
}

int upyun_client_impl::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QObject::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 7)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 7;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 7)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 7;
    }
    return _id;
}

// SIGNAL 0
void upyun_client_impl::uploadProgress(qint64 _t1, qint64 _t2)
{
    void *_a[] = { 0, const_cast<void*>(reinterpret_cast<const void*>(&_t1)), const_cast<void*>(reinterpret_cast<const void*>(&_t2)) };
    QMetaObject::activate(this, &staticMetaObject, 0, _a);
}

// SIGNAL 1
void upyun_client_impl::downloadProgress(qint64 _t1, qint64 _t2)
{
    void *_a[] = { 0, const_cast<void*>(reinterpret_cast<const void*>(&_t1)), const_cast<void*>(reinterpret_cast<const void*>(&_t2)) };
    QMetaObject::activate(this, &staticMetaObject, 1, _a);
}

// SIGNAL 2
void upyun_client_impl::error(const QString & _t1)
{
    void *_a[] = { 0, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 2, _a);
}

// SIGNAL 3
void upyun_client_impl::finished()
{
    QMetaObject::activate(this, &staticMetaObject, 3, 0);
}
QT_END_MOC_NAMESPACE
