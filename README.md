# 公交路线自动化选择系统

项目作者：由自不愿透露姓名的三位南京邮电大学大二（上学期）学子（2022.11）合作完成

~~想必没有人愿意告诉别人这坨屎山是自己写的~~

## 一、项目功能：

(1)在管理员权限下支持录入、删除、更改路线，路线信息保存到文件中，不用二次录入

(2)能够查询录入过的公交线路

(3)能够根据出发地和目的地自动获取路线，可以输出换乘最少路线与站数最少路线，包括路线的预估时间以及线路的首班车与末班车时间。

## 二、系统使用：

(1)路线录入或更改更改时请使用以下格式输入路线：

线路名 首发站名 （空格）到下一站的预估时间（要求为纯数字，且单位为分钟）（空格）站点名（空格） 预估时间 站点名 ...... 末尾站 （空格）#（空格）首班车时间（xx:xx) (空格）末班车时间（xx:xx) （空格）#

例：B1 邮电大学北 2 邮电大学东 8 南大 20 东南大学 # 6:00 22:00 #

（注：xx:xx种的":"必须为英文":"，而不时中文的"："）

(2)注意：本系统计算预估时间时未考虑转乘时间

## 三、项目创建原因

本项目为南京邮电大学程序设计实验的小组作业

~~写完啦，开摆！~~
