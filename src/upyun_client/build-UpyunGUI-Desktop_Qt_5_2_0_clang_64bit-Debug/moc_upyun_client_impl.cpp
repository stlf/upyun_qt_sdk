/****************************************************************************
** Meta object code from reading C++ file 'upyun_client_impl.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.2.0)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../upyun_client_impl.h"
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
struct qt_meta_stringdata_UpyunClientPrivate_t {
    QByteArrayData data[15];
    char stringdata[155];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    offsetof(qt_meta_stringdata_UpyunClientPrivate_t, stringdata) + ofs \
        - idx * sizeof(QByteArrayData) \
    )
static const qt_meta_stringdata_UpyunClientPrivate_t qt_meta_stringdata_UpyunClientPrivate = {
    {
QT_MOC_LITERAL(0, 0, 18),
QT_MOC_LITERAL(1, 19, 5),
QT_MOC_LITERAL(2, 25, 0),
QT_MOC_LITERAL(3, 26, 4),
QT_MOC_LITERAL(4, 31, 10),
QT_MOC_LITERAL(5, 42, 14),
QT_MOC_LITERAL(6, 57, 8),
QT_MOC_LITERAL(7, 66, 11),
QT_MOC_LITERAL(8, 78, 12),
QT_MOC_LITERAL(9, 91, 10),
QT_MOC_LITERAL(10, 102, 7),
QT_MOC_LITERAL(11, 110, 9),
QT_MOC_LITERAL(12, 120, 7),
QT_MOC_LITERAL(13, 128, 13),
QT_MOC_LITERAL(14, 142, 11)
    },
    "UpyunClientPrivate\0error\0\0info\0"
    "uploadFile\0QNetworkReply*\0filedata\0"
    "remote_path\0downloadFile\0removeFile\0"
    "makeDir\0removeDir\0listDir\0getBucketInfo\0"
    "getFileInfo\0"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_UpyunClientPrivate[] = {

 // content:
       7,       // revision
       0,       // classname
       0,    0, // classinfo
       9,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       1,       // signalCount

 // signals: name, argc, parameters, tag, flags
       1,    1,   59,    2, 0x06,

 // slots: name, argc, parameters, tag, flags
       4,    2,   62,    2, 0x0a,
       8,    1,   67,    2, 0x0a,
       9,    1,   70,    2, 0x0a,
      10,    1,   73,    2, 0x0a,
      11,    1,   76,    2, 0x0a,
      12,    1,   79,    2, 0x0a,
      13,    0,   82,    2, 0x0a,
      14,    1,   83,    2, 0x0a,

 // signals: parameters
    QMetaType::Void, QMetaType::QString,    3,

 // slots: parameters
    0x80000000 | 5, QMetaType::QByteArray, QMetaType::QString,    6,    7,
    0x80000000 | 5, QMetaType::QString,    7,
    0x80000000 | 5, QMetaType::QString,    7,
    0x80000000 | 5, QMetaType::QString,    7,
    0x80000000 | 5, QMetaType::QString,    7,
    0x80000000 | 5, QMetaType::QString,    7,
    0x80000000 | 5,
    0x80000000 | 5, QMetaType::QString,    7,

       0        // eod
};

void UpyunClientPrivate::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        UpyunClientPrivate *_t = static_cast<UpyunClientPrivate *>(_o);
        switch (_id) {
        case 0: _t->error((*reinterpret_cast< const QString(*)>(_a[1]))); break;
        case 1: { QNetworkReply* _r = _t->uploadFile((*reinterpret_cast< const QByteArray(*)>(_a[1])),(*reinterpret_cast< const QString(*)>(_a[2])));
            if (_a[0]) *reinterpret_cast< QNetworkReply**>(_a[0]) = _r; }  break;
        case 2: { QNetworkReply* _r = _t->downloadFile((*reinterpret_cast< const QString(*)>(_a[1])));
            if (_a[0]) *reinterpret_cast< QNetworkReply**>(_a[0]) = _r; }  break;
        case 3: { QNetworkReply* _r = _t->removeFile((*reinterpret_cast< const QString(*)>(_a[1])));
            if (_a[0]) *reinterpret_cast< QNetworkReply**>(_a[0]) = _r; }  break;
        case 4: { QNetworkReply* _r = _t->makeDir((*reinterpret_cast< const QString(*)>(_a[1])));
            if (_a[0]) *reinterpret_cast< QNetworkReply**>(_a[0]) = _r; }  break;
        case 5: { QNetworkReply* _r = _t->removeDir((*reinterpret_cast< const QString(*)>(_a[1])));
            if (_a[0]) *reinterpret_cast< QNetworkReply**>(_a[0]) = _r; }  break;
        case 6: { QNetworkReply* _r = _t->listDir((*reinterpret_cast< const QString(*)>(_a[1])));
            if (_a[0]) *reinterpret_cast< QNetworkReply**>(_a[0]) = _r; }  break;
        case 7: { QNetworkReply* _r = _t->getBucketInfo();
            if (_a[0]) *reinterpret_cast< QNetworkReply**>(_a[0]) = _r; }  break;
        case 8: { QNetworkReply* _r = _t->getFileInfo((*reinterpret_cast< const QString(*)>(_a[1])));
            if (_a[0]) *reinterpret_cast< QNetworkReply**>(_a[0]) = _r; }  break;
        default: ;
        }
    } else if (_c == QMetaObject::IndexOfMethod) {
        int *result = reinterpret_cast<int *>(_a[0]);
        void **func = reinterpret_cast<void **>(_a[1]);
        {
            typedef void (UpyunClientPrivate::*_t)(const QString & );
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&UpyunClientPrivate::error)) {
                *result = 0;
            }
        }
    }
}

const QMetaObject UpyunClientPrivate::staticMetaObject = {
    { &QObject::staticMetaObject, qt_meta_stringdata_UpyunClientPrivate.data,
      qt_meta_data_UpyunClientPrivate,  qt_static_metacall, 0, 0}
};


const QMetaObject *UpyunClientPrivate::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *UpyunClientPrivate::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_UpyunClientPrivate.stringdata))
        return static_cast<void*>(const_cast< UpyunClientPrivate*>(this));
    return QObject::qt_metacast(_clname);
}

int UpyunClientPrivate::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QObject::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 9)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 9;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 9)
            *reinterpret_cast<int*>(_a[0]) = -1;
        _id -= 9;
    }
    return _id;
}

// SIGNAL 0
void UpyunClientPrivate::error(const QString & _t1)
{
    void *_a[] = { 0, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 0, _a);
}
QT_END_MOC_NAMESPACE
