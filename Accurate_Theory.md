##### 行列和 x y 的对应
行 i = -y - 1 列 j = x - 1 -> x = j + 1 y = -i - 1

**行列**      `i    j`
**坐标**      `x = j + 1    y = -i - 1`
**绘图**      `x = x - 1    y = -y - 1`
**行列**      `i = y    j = x`

```
源 Original_L_Line[5] = 2 表示 5 行 2 列
对应到坐标 ( 3, -6 )
绘图 ( 2, 5 )
行列 ( 5, 2 )
```

##### p i 建议
直到 p 大 i 小
弯道 p 小 i 大

##### Original_L_Line[120] 和 Roundabout_Upper_Boundary[188] 的关系
<u>对于分辨率 188 * 120 来说</u>
```
Original_L_Line[120] 是通过 标记 行(i) 追踪 列(j)
Original_L_Line[5] = 21 表示 第 5 行的列值为 21

Roundabout_Upper_Boundary[188] 是通过 标记 列(j) 追踪 行(i)
Roundabout_Upper_Boundary[13] = 14 表示 第 13 列的行值为 14
```

##### 初始化建议
uint8 类型的初始化为 255 除了 Original_R_Line[] = 0
定义为 int8 Original_R_Line[] = -256

##### 是否开启和是否成功的01参数和返回值表示
0 表示不开启 返回 flase
1 表示开启 返回 true

##### 画线建议
绿色-中线 蓝色-正常边界线(包括正常补线) 红色-超过了边界虚拟仅在画的时候 < 0 -> = 0 > 187 -> = 187
