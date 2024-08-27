##### 2024.5.15
摄像头只提供`Original_L/R_Line`函数，像`leftBreak`等放在**辅助**(Auxiliary)文件里，像`Corner Roundabout`等放在**接口**(Interface)文件里，像`画线和计算Midcourt_Line`放在**核心**(Core)的文件里

`Interface 里放QR标准的函数`

##### 2024.5.19
利用照成倾斜的原因进行主动控制(data 要实验),没有延时，利用mpu进行被动控制

利用无刷分配固定占空比差来消弱硬件不均匀

总共有6个PID在Updata函数里都更新，在赛道识别后，选择性调用
**Straight 直 Curved 弯 Deviation 偏差 ColumnDefference 列差**
`Deviation -> 表示 95 到 120 行中线的列值和 94 的偏差值`
`ColumnDefference -> 表示 55 到 120 行每一行与前一行的列差值`

**赛道识别，赛道有 直道 S弯 十字 左环岛 右环岛 环弯 普通弯**

```
StraightSpeedPid                PI
CurvedSpeedPid                  PI
StraightDeviationPid            P
CurvedDeviationPid              PI
StraightColumnDifferencePid     P
CurvedColumnDefferencePid       PI

Straightaway 选择 StraightSpeedPid StraightDeviationPid
S_Bend 选择 StraightSpeedPid
Cross 选择 StraightSpeedPid StraightDeviationPid
左环岛 右环岛 入环/出环 选择 CurvedSpeedPid StraightDeviationPid StraightColumnDifferencePid
            在环弯 选择 CurvedSpeedPid CurvedDeviationPid CurvedColumnDefferencePid
Ring_Bend 选择 CurvedSpeedPid CurvedDeviationPid CurvedColumnDefferencePid
Ordinary_Bend 选择 CurvedSpeedPid StraightDeviationPid StraightColumnDifferencePid

Straight 速度pid大，速度快
Curved 速度pid小，速度慢，(L_R会加速)

Straight 强平衡 Gyro 只要有值就抑制抖动，保持平衡
Curved 弱平衡 Gyro 到达一个范围在抑制抖动，保持微平衡
```
速度快不减无刷，当Duty_L_R > 60 -5 Duty_L_R > 70 -10

**当赛道不稳定检测到Gyro > 50 and Gyro < -50，无刷减20，去掉Curved，Gyro有值就抑制恢复平衡**

<u>为了防止在Duty乘以1个系数导致的问题(如Duty = 2 , 2 * Duty = 10 效果不明显, Duty = 30 , 2 * Duty = 60, 效果太大), 所以，我们建议对于上面的6个基准PID,我们可以在执行PID_Contrtol前，每次都重写刷一下Targe_Speed_Pid，然后在对于识别状态想要加速，在次刷一下Targe_Speed_Pid</u>

##### 2024.5.20
对于S弯，可以加速和增加无刷占空比来加大陀螺仪的反馈(因为船身工艺造成的误差,导致倾斜反馈给陀螺仪是微弱的)

**对于十字和环岛的补线，先写4个找等效角点函数，左下找等效角点，左上找等效角点，右下找等效补线，右上找等效角点(扫线方向)，都提供要找多少等效角点和遇到丢线时是否退出，然后在函数结束之前检查是否找到了想要的等效拐点数返回01，将计算KB和获得最终线放在一个函数也只写一个函数里，函数的参数有，存放等效角点的数组，等效角点的数量，补好线之后放的Final数组指针，是否强制将线拉直**

`返回值为 0 1 当返回值为0时可不执行得到Final函数，直接用上一次的Final值，当返回值为1时也要简单的验证K B 是否合理 (Left_K < 0 && Left_B > 0,Right_K > 0 && Right_B < 0)`

`是否强制将线拉直 表示 当 100 行 的列计算的值为 -10 开启强制拉直将将 100 行的列值写为 0 否则就写为 -10 我们建议不开启(注意数组的类型,如果为无符号类型一定要开启)`

<u>放到数组之前要先用int类型变量接收后在判断是否越界赋值给Final数组</u>

**对于十字和环岛的找角点，十字角点函数，左下，左上，右上，右下，环岛找角点函数，左下突变，左上边界，右下突变，右上边界，两个元素的四个函数都有返回值为01**

`十字发现角点较严格找角点，环岛判断标准找角点，绝对严格找角点，环岛里面找连线点角点极宽松找角点，环岛里面找边界角点，较宽松找角点`

<u>函数提供一个参数变量初始化为多少(我们建议对于 uint8 为 255)</u>

每一个文件向外提供两个函数，一个Init,一个Control，在Control里面，写Var_Init,Actual_Control,Virtual_Control

当一个赛道结束就直接将控制权交给NNLL_Track,赛道之间不可以相互改变

用编码器积分看跑了多远，达到一定范围可以将控制权交给NULL_Track

**在进行识别环岛或者其他元素的时候，不应该只局限于当前赛道的特征，还应该和其他赛道对于，先排除其他赛道的可能，在写环岛元素特征**

```
一层一层的if进行排除其他赛道，在最后一层进行特征判断，比如环岛找角点在最后一个if里进行判断，减少计算量，提高帧率(在识别元素的时候，准备区别那个元素就只关注这一个元素)
像中间是否丢线可以看是否可以加上，在Auxiliary里面的变量都可以考虑一下是否可以用

L/R_Near_Lost 仅作为状态改变，不可以作为识别依据，防止倾斜造成的不稳定

如在右环岛防止误判成十字，可以根据L_L <= 0 为右环岛

如在十字不仅 L_L >= x 还要规定 L_L <= y 与弯道区别

尽量将Auxiliary里面的变量都用到
```

##### 2024.5.21
迷宫法 返回值 uint8 
参数 1 Image_ 2 width(x) 3 height(y) 4 threshould 5 Original_L_line
6 Original_R_Line 7 maximumSearchStep 8 initialization 9 moveValue
10 Select
**在迷宫法寻找开启点，可以加入(-1)的n次方来控制向左还是向右，每一次都加上moveValue的一半**
**while(image[i][j]这个起始点的合理性判断，之前是丢掉这一帧，优化为重新选择起始点)**

##### 2024.5.23
柔风动力控制系统--中线列值相对于188/2的偏差值(95,120)和中线上一点相对于下一个点的列差值(55,120)决定

```
当加大列差值的数据会提前入弯，加大偏差值的数据会相对较晚入弯

主动无刷，被动无刷，微调，辅控
```

##### 2024.6.2
用到了状态标志位一定要注意是否恢复原样，入环拉线结束辅助函数`for(uint8 i = MT9V03X_H; i > 80; i--)` i 的开始和i 的结束都要合理，像其他的for也要想好，入获得Final数组

##### 2024.6.10
1 出环加速 `Re_Set_Targe_Speed_Pid`
2 S_Bned优化 (柔风动力控制系统可以开启Duty_L_R,放宽,优先级放低,重点放中间识别代码)
3 出环优化 (防止出环贴近圆环而退不出去)
4 入环无法拉线进入圆环优化 (船身不稳定，导致右边补线太向左偏，无法让右边近端丢线小于5而无法进入拉线状态优化)
5 十字识别优化 (添加优化代码，左右丢线差不多，丢线前的线符合直线，L_Break + R_Break >= 2 || L_Break == 2 || R_Break == 2即可)
6 小直道加速 (2m小直到就加速)
7 迷宫法优化 (选择保存最后一次搜到的点保存在数组里,还是第一次,或者交给我写的函数来动态切换)
8 添加元素锁定 (直接在每一次都会刷新的Re_PID里进行判断,路障过了加直道速度,环岛过了加直到和弯道速度)
9 直到放宽 (也可以在直到切换到NULL_Track里面加切换所需要的帧数)
10 辅助优化
11 补线方向
12 入环可以加速，出环不可以加速 (拉线)
13 二次入环

##### 2024.6.19
动态PID,选择改变 Straight 与 Bend 的比例系数，Speed 越大 Bend 的比重越大`(Speed, K)`
```
当 Speed = 200 K = 1, Bend : Straight = 1 : 1
当 Speed = 500 k = 3, Bend : Straight = 3 : 1
线性方程
k = 1 + (2 / 300) * (Speed - 200)
```

数据结构队列来优化识别存储

##### 2024.8.11
迷宫法优化方向
1 -> 在现在得到的边界数组进行滤波`最少的时间达到相同的效果`
2 -> 根据迷宫法搜线方向进程原始识别