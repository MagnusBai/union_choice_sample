#include <iostream>

// b选项的数据
struct X_Range_Setting {
    bool is_auto_xrange;    // 
    float x_start;
    float x_end;
    // https://q.cnblogs.com/q/57184/
    // union里面的类不能放有构造函数，析构函数和拷贝构造函数的class的成员变量
    // 因为编译器无法决定是否该调用构造函数去初始化成员变量
};

// 升级b数据，增加构造函数
// 直接在X_Range_Setting里放构造函数，会报错
struct X_Range_Setting_: public X_Range_Setting {
    X_Range_Setting_(float x0, float x1) {
        // CHECK_GT(x1, x0)
	is_auto_xrange = false;
	x_start = x0;
	x_end = x1;
    }
};

// 存储用户选项的结构体
struct Cfg {
    union X_Status {
        bool is_auto_x;                     // 选项a：自动决定x范围
	struct X_Range_Setting x_setting;   // 选项b：手动确定x范围
    } x_status;
   
    void process() {
        switch (x_status.is_auto_x) {
	    case true: // 处理用户a选项
	        std::cout << "CHOICE A: auto_range" << std::endl;
	        break;
            case false:  // 处理用户b选项
		std::cout << "CHOICE B: set_range" << std::endl;
	        std::cout << " start_point: " << x_status.x_setting.x_start;
	        std::cout << " end_point: " << x_status.x_setting.x_end << std::endl;
		break;
	}
    }
};

// 主测试函数
void test_cfg() {
    // 用户a选项
    Cfg cfg1;
    cfg1.x_status.is_auto_x = true;
    cfg1.process();

    // 用户b选项
    Cfg cfg2;
    // cfg2.x_status.x_setting.is_auto_xrange = false;
    // cfg2.x_status.x_setting.x_start= 1.7f;
    // cfg2.x_status.x_setting.x_end = 7.6f;
    cfg2.x_status.x_setting = X_Range_Setting_(1.7f, 7.6f);
    cfg2.process();

}

int main() {
    test_cfg();
    return 0;
}

