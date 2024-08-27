变量命名规范`StanfLeftK`,函数不可以直接用全局变量，要以参数或者指针的方式传入传出`int My_Adapt_Threshoud(uint8 *image, uint16 width, uint16 height)`

**变量命名规范**

```
宏定义 #define IMAGE_BLACK (0x00)

普通变量 uint8 threshould firstName
全局变量 uint8 Threshould FirstName

建议数组最好有两个数组构成
普通数组 uint8 threshould_[2] first_Name[2];
全局数组 uint8 Threshould_[2] First_Name[2];

```

**函数命名规范**

```
函数名加入文件名关键词

无参函数
void Core_Draw_Midcourt_Line(void);
有参函数(变量同普通变量)
uint8 Cream_Find_Strating_Point(uint8 i, uint8 j);

```

**枚举值**

```
定义规范(在 .h 文件定义， 在.c 文件里#include "*.h")

typedef enum
{
    bitReset_enum = 0,
    bitSet_enum
}BitAction_Enum;

声明枚举类型名 = 全局变量 + _Enum
枚举成员变量 = 普通变量 + _enum

```

**结构体**

```
定义规范(在 .h 文件定义， 在.c 文件里#include "*.h")

typedef struct
{
    float Target;
    float Error;
    float Kp;
    float Ki;
    float Kd;
}PID;

声明结构体类型名 = 全局变量 + _Struct
结构体成员没有要求，因为要访问结构体成员要通过结构体来访问

```

**文件**

```
文件命名(每个单词首字母大写)

当只有一个单词 && 单词数量 <= 10 直接书写， > 10 只写前 5 个
当大于一个单词 无论单词数量，第一个单词最多书写 5 个字母，最后一个最多书写 4 个字母，中间的都只写第一个字母

在 .h 文件的最后一行 书写完整的英文单词
```

<u>多文件协同操作，在 .c 文件里定义变量 .h 文件声明,那个 .c 文件要用只需要在 .c 文件里 #include ".h"</u>

`.c uint8 thershould = 0;`

`.h extern uint8 thershould;`

<u>如果其他文件想使用main.c里面的文件只需要在其他文件的.c里声明就可以</u>

`extern uint8 variableName`