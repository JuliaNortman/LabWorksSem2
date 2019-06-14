/****************************************************************************
** Meta object code from reading C++ file 'mainwindow.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.12.1)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../LabWorksSem2/LabWork2/Lab2/Source code/mainwindow.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#include <QtCore/QVector>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'mainwindow.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.12.1. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
struct qt_meta_stringdata_MainWindow_t {
    QByteArrayData data[17];
    char stringdata0[313];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_MainWindow_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_MainWindow_t qt_meta_stringdata_MainWindow = {
    {
QT_MOC_LITERAL(0, 0, 10), // "MainWindow"
QT_MOC_LITERAL(1, 11, 11), // "printMatrix"
QT_MOC_LITERAL(2, 23, 0), // ""
QT_MOC_LITERAL(3, 24, 22), // "QVector<QVector<int> >"
QT_MOC_LITERAL(4, 47, 11), // "clearLabels"
QT_MOC_LITERAL(5, 59, 23), // "on_randomButton_clicked"
QT_MOC_LITERAL(6, 83, 24), // "on_directed_stateChanged"
QT_MOC_LITERAL(7, 108, 4), // "arg1"
QT_MOC_LITERAL(8, 113, 29), // "on_weightedGraph_stateChanged"
QT_MOC_LITERAL(9, 143, 14), // "on_Run_clicked"
QT_MOC_LITERAL(10, 158, 32), // "on_enterMatrixPushButton_clicked"
QT_MOC_LITERAL(11, 191, 32), // "on_algorithm_currentIndexChanged"
QT_MOC_LITERAL(12, 224, 5), // "index"
QT_MOC_LITERAL(13, 230, 11), // "algoExecute"
QT_MOC_LITERAL(14, 242, 11), // "clearOutput"
QT_MOC_LITERAL(15, 254, 32), // "on_numberOfVertexes_valueChanged"
QT_MOC_LITERAL(16, 287, 25) // "on_infoPushButton_clicked"

    },
    "MainWindow\0printMatrix\0\0QVector<QVector<int> >\0"
    "clearLabels\0on_randomButton_clicked\0"
    "on_directed_stateChanged\0arg1\0"
    "on_weightedGraph_stateChanged\0"
    "on_Run_clicked\0on_enterMatrixPushButton_clicked\0"
    "on_algorithm_currentIndexChanged\0index\0"
    "algoExecute\0clearOutput\0"
    "on_numberOfVertexes_valueChanged\0"
    "on_infoPushButton_clicked"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_MainWindow[] = {

 // content:
       8,       // revision
       0,       // classname
       0,    0, // classinfo
      12,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // slots: name, argc, parameters, tag, flags
       1,    1,   74,    2, 0x08 /* Private */,
       4,    0,   77,    2, 0x08 /* Private */,
       5,    0,   78,    2, 0x08 /* Private */,
       6,    1,   79,    2, 0x08 /* Private */,
       8,    1,   82,    2, 0x08 /* Private */,
       9,    0,   85,    2, 0x08 /* Private */,
      10,    0,   86,    2, 0x08 /* Private */,
      11,    1,   87,    2, 0x08 /* Private */,
      13,    0,   90,    2, 0x08 /* Private */,
      14,    0,   91,    2, 0x08 /* Private */,
      15,    1,   92,    2, 0x08 /* Private */,
      16,    0,   95,    2, 0x08 /* Private */,

 // slots: parameters
    QMetaType::Void, 0x80000000 | 3,    2,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void, QMetaType::Int,    7,
    QMetaType::Void, QMetaType::Int,    7,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void, QMetaType::Int,   12,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void, QMetaType::Int,    7,
    QMetaType::Void,

       0        // eod
};

void MainWindow::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        auto *_t = static_cast<MainWindow *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->printMatrix((*reinterpret_cast< QVector<QVector<int> >(*)>(_a[1]))); break;
        case 1: _t->clearLabels(); break;
        case 2: _t->on_randomButton_clicked(); break;
        case 3: _t->on_directed_stateChanged((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 4: _t->on_weightedGraph_stateChanged((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 5: _t->on_Run_clicked(); break;
        case 6: _t->on_enterMatrixPushButton_clicked(); break;
        case 7: _t->on_algorithm_currentIndexChanged((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 8: _t->algoExecute(); break;
        case 9: _t->clearOutput(); break;
        case 10: _t->on_numberOfVertexes_valueChanged((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 11: _t->on_infoPushButton_clicked(); break;
        default: ;
        }
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        switch (_id) {
        default: *reinterpret_cast<int*>(_a[0]) = -1; break;
        case 0:
            switch (*reinterpret_cast<int*>(_a[1])) {
            default: *reinterpret_cast<int*>(_a[0]) = -1; break;
            case 0:
                *reinterpret_cast<int*>(_a[0]) = qRegisterMetaType< QVector<QVector<int> > >(); break;
            }
            break;
        }
    }
}

QT_INIT_METAOBJECT const QMetaObject MainWindow::staticMetaObject = { {
    &QMainWindow::staticMetaObject,
    qt_meta_stringdata_MainWindow.data,
    qt_meta_data_MainWindow,
    qt_static_metacall,
    nullptr,
    nullptr
} };


const QMetaObject *MainWindow::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *MainWindow::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_MainWindow.stringdata0))
        return static_cast<void*>(this);
    return QMainWindow::qt_metacast(_clname);
}

int MainWindow::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QMainWindow::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 12)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 12;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 12)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 12;
    }
    return _id;
}
QT_WARNING_POP
QT_END_MOC_NAMESPACE
