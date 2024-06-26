/****************************************************************************
** Meta object code from reading C++ file 'texteditor.h'
**
** Created by: The Qt Meta Object Compiler version 68 (Qt 6.7.1)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../../../texteditor.h"
#include <QtGui/qtextcursor.h>
#include <QtCore/qmetatype.h>

#include <QtCore/qtmochelpers.h>

#include <memory>


#include <QtCore/qxptype_traits.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'texteditor.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 68
#error "This file was generated using the moc from 6.7.1. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

#ifndef Q_CONSTINIT
#define Q_CONSTINIT
#endif

QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
QT_WARNING_DISABLE_GCC("-Wuseless-cast")
namespace {

#ifdef QT_MOC_HAS_STRINGDATA
struct qt_meta_stringdata_CLASSTextEditorENDCLASS_t {};
constexpr auto qt_meta_stringdata_CLASSTextEditorENDCLASS = QtMocHelpers::stringData(
    "TextEditor",
    "newFile",
    "",
    "saveAsFile",
    "saveFile",
    "exitFile",
    "openFile",
    "textModified",
    "undo",
    "cut",
    "copy",
    "paste",
    "deleteText",
    "toggleDarkMode",
    "dark"
);
#else  // !QT_MOC_HAS_STRINGDATA
#error "qtmochelpers.h not found or too old."
#endif // !QT_MOC_HAS_STRINGDATA
} // unnamed namespace

Q_CONSTINIT static const uint qt_meta_data_CLASSTextEditorENDCLASS[] = {

 // content:
      12,       // revision
       0,       // classname
       0,    0, // classinfo
      12,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // slots: name, argc, parameters, tag, flags, initial metatype offsets
       1,    0,   86,    2, 0x0a,    1 /* Public */,
       3,    0,   87,    2, 0x0a,    2 /* Public */,
       4,    0,   88,    2, 0x0a,    3 /* Public */,
       5,    0,   89,    2, 0x0a,    4 /* Public */,
       6,    0,   90,    2, 0x0a,    5 /* Public */,
       7,    0,   91,    2, 0x0a,    6 /* Public */,
       8,    0,   92,    2, 0x0a,    7 /* Public */,
       9,    0,   93,    2, 0x0a,    8 /* Public */,
      10,    0,   94,    2, 0x0a,    9 /* Public */,
      11,    0,   95,    2, 0x0a,   10 /* Public */,
      12,    0,   96,    2, 0x0a,   11 /* Public */,
      13,    1,   97,    2, 0x0a,   12 /* Public */,

 // slots: parameters
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void, QMetaType::Bool,   14,

       0        // eod
};

Q_CONSTINIT const QMetaObject TextEditor::staticMetaObject = { {
    QMetaObject::SuperData::link<QMainWindow::staticMetaObject>(),
    qt_meta_stringdata_CLASSTextEditorENDCLASS.offsetsAndSizes,
    qt_meta_data_CLASSTextEditorENDCLASS,
    qt_static_metacall,
    nullptr,
    qt_incomplete_metaTypeArray<qt_meta_stringdata_CLASSTextEditorENDCLASS_t,
        // Q_OBJECT / Q_GADGET
        QtPrivate::TypeAndForceComplete<TextEditor, std::true_type>,
        // method 'newFile'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        // method 'saveAsFile'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        // method 'saveFile'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        // method 'exitFile'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        // method 'openFile'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        // method 'textModified'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        // method 'undo'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        // method 'cut'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        // method 'copy'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        // method 'paste'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        // method 'deleteText'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        // method 'toggleDarkMode'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        QtPrivate::TypeAndForceComplete<bool, std::false_type>
    >,
    nullptr
} };

void TextEditor::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        auto *_t = static_cast<TextEditor *>(_o);
        (void)_t;
        switch (_id) {
        case 0: _t->newFile(); break;
        case 1: _t->saveAsFile(); break;
        case 2: _t->saveFile(); break;
        case 3: _t->exitFile(); break;
        case 4: _t->openFile(); break;
        case 5: _t->textModified(); break;
        case 6: _t->undo(); break;
        case 7: _t->cut(); break;
        case 8: _t->copy(); break;
        case 9: _t->paste(); break;
        case 10: _t->deleteText(); break;
        case 11: _t->toggleDarkMode((*reinterpret_cast< std::add_pointer_t<bool>>(_a[1]))); break;
        default: ;
        }
    }
}

const QMetaObject *TextEditor::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *TextEditor::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_CLASSTextEditorENDCLASS.stringdata0))
        return static_cast<void*>(this);
    return QMainWindow::qt_metacast(_clname);
}

int TextEditor::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
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
            *reinterpret_cast<QMetaType *>(_a[0]) = QMetaType();
        _id -= 12;
    }
    return _id;
}
QT_WARNING_POP
