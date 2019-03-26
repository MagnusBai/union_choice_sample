# 一点心得，使用联合体union存储用户选项的方法


在使用C++设计一个存储用户选项的结构体(类)时，往往会遇到a选项, b选项等包含的信息数据不一致的问题。

如果为a、b、c等选项强行设计统一的数据结构体，再统一写处理逻辑。个人感觉比较困难：
* 原因1. 统一的数据结构，需要照顾所有选项，维护成本高；
* 原因2. 写处理逻辑时也会涉及复杂的检查；


所以，在业务没完全定型，在需要quick and dirty搞定该问题相关的业务时，**个人认为联合体(union)适合处理该类问题。**

举个例子:
假设有一个画图表的需求，用户有2个选项：
* a. 由程序自动确认绘制范围；
* b. 用户制定绘制某个区间；

存储用户选择的数据结构中，a, b中除了状态标志( is_auto_x )外，还有各选项独有的数据(本例体现在b选项会引入起始点x_start，终止点x_end，然而这些数据对a选项并无意义)。

定义选项数据如下
```c++
// 用户选项结构体
struct Cfg {
    union X_Status {
        bool is_auto_x;                      // a 选项相关数据
        struct X_Range_Setting x_setting;    // b 选项相关数据
    } x_status;                              // 用此联合体表示互斥的选项
    // ……其他数据和方法，略
}
// b选项相关数据
struct X_Range_Setting {
    bool is_auto_xrange;    // 标志位统一
    float x_start;
    float x_end;
}
```
处理代码逻辑如下:
```
switch (x_status.is_auto_x) {
    case true: // 处理用户a选项，具体访问`x_status.is_auto_x`
        ...; break;
    case false:  // 处理用户b选项，具体访问`x_status.x_setting`
        ...; break;
}
```

[demo传送门在这](https://github.com/MagnusBai/union_choice_sample/blob/master/test.cpp)

另外值得注意的是：
* 由于c++里联合体是多个类共用一块数据内存，可以解释成所有类，因此，这些类不能包含构造、析构函数。
* 想用构造函数创建该选项对象，得自己写子类了。
这2点demo里也有一点体现。
