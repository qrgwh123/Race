Interface 里面函数声明

**PortLaby**
```
迷宫法(枝枝花算法)
//Port Labyrinth
```

**PortPLine**
```
4 + 1
//Port Patching Line
左边从下到上找等效角点
左边从上到下找等效角点
右边从下到上找等效角点
右边从上到下找等效角点
补线函数
```

**PortCPoin**
```
4 + 2 + 2 + 2
//Port Corner Point
识别十字的4个角点
右环岛识别判定角点开启补线，右环岛入环拉线角点，右环岛出环拉线角点，右环岛补线准备退出角点
左环岛识别判定角点开启补线，左环岛入环拉线角点，左环岛出环拉线角点，左环岛补线准备退出角点
拉线识别角点采取从下向上扫描的方式
补线采取先找到空白点，然后从下向上寻找等效角点
```

**PortAssi**
```
1 + 1
+2
//Port Assist
放入辅助函数Assist_Roundabout_Loop_Cable_End_Left/Right
```