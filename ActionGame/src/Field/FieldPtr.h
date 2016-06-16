#ifndef FIELDPTR_H_
#define FIELDPTR_H_
#include<memory>

//フィールド用シェアドポインタ
class Field;
using FieldPtr = std::shared_ptr<Field>;

#endif
