/*
*フィールドポインター
*概要：フィールドをシェアドポインタに変える
*/
#ifndef FIELDPTR_H_
#define FIELDPTR_H_
#include<memory>

//フィールド用シェアドポインタ
class Field;
using FieldPtr = std::shared_ptr<Field>;

#endif
