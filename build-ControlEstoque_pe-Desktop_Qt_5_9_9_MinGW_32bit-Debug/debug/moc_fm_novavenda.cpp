/****************************************************************************
** Meta object code from reading C++ file 'fm_novavenda.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.9.9)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../ControlEstoque_pe/fm_novavenda.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'fm_novavenda.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.9.9. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
struct qt_meta_stringdata_fm_novavenda_t {
    QByteArrayData data[6];
    char stringdata0[135];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_fm_novavenda_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_fm_novavenda_t qt_meta_stringdata_fm_novavenda = {
    {
QT_MOC_LITERAL(0, 0, 12), // "fm_novavenda"
QT_MOC_LITERAL(1, 13, 31), // "on_txt_codproduto_returnPressed"
QT_MOC_LITERAL(2, 45, 0), // ""
QT_MOC_LITERAL(3, 46, 29), // "on_btn_excluirproduto_clicked"
QT_MOC_LITERAL(4, 76, 28), // "on_btn_editarproduto_clicked"
QT_MOC_LITERAL(5, 105, 29) // "on_btn_finalizarvenda_clicked"

    },
    "fm_novavenda\0on_txt_codproduto_returnPressed\0"
    "\0on_btn_excluirproduto_clicked\0"
    "on_btn_editarproduto_clicked\0"
    "on_btn_finalizarvenda_clicked"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_fm_novavenda[] = {

 // content:
       7,       // revision
       0,       // classname
       0,    0, // classinfo
       4,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // slots: name, argc, parameters, tag, flags
       1,    0,   34,    2, 0x08 /* Private */,
       3,    0,   35,    2, 0x08 /* Private */,
       4,    0,   36,    2, 0x08 /* Private */,
       5,    0,   37,    2, 0x08 /* Private */,

 // slots: parameters
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,

       0        // eod
};

void fm_novavenda::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        fm_novavenda *_t = static_cast<fm_novavenda *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->on_txt_codproduto_returnPressed(); break;
        case 1: _t->on_btn_excluirproduto_clicked(); break;
        case 2: _t->on_btn_editarproduto_clicked(); break;
        case 3: _t->on_btn_finalizarvenda_clicked(); break;
        default: ;
        }
    }
    Q_UNUSED(_a);
}

const QMetaObject fm_novavenda::staticMetaObject = {
    { &QDialog::staticMetaObject, qt_meta_stringdata_fm_novavenda.data,
      qt_meta_data_fm_novavenda,  qt_static_metacall, nullptr, nullptr}
};


const QMetaObject *fm_novavenda::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *fm_novavenda::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_fm_novavenda.stringdata0))
        return static_cast<void*>(this);
    return QDialog::qt_metacast(_clname);
}

int fm_novavenda::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QDialog::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 4)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 4;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 4)
            *reinterpret_cast<int*>(_a[0]) = -1;
        _id -= 4;
    }
    return _id;
}
QT_WARNING_POP
QT_END_MOC_NAMESPACE
