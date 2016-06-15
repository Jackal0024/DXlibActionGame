#pragma once

#include<memory>

//フィールド用シェアドポインタ
class Field;
using FieldPtr = std::shared_ptr<Field>;
