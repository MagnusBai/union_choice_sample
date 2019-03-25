#include <iostream>

struct X_Range_Setting {
    bool is_auto_xrange;    // 
    float x_start;
    float x_end;
    // https://q.cnblogs.com/q/57184/
    // union里面不能放有构造函数，析构函数和拷贝构造函数的class的成员变量
    // 因为编译器无法决定是否该调用构造函数去初始化成员变量
    /*
    X_Range_Setting(float x0, float x1) {
        // CHECK_GT(x1, x0)
	x_start = x0;
	x_end = x1;
    }*/
};

struct X_Range_Setting_: public X_Range_Setting {
    X_Range_Setting_(float x0, float x1) {
        // CHECK_GT(x1, x0)
	is_auto_xrange = false;
	x_start = x0;
	x_end = x1;
    }
};

struct Cfg {
    union X_Status {
        bool is_auto_x;
	struct X_Range_Setting x_setting;
    } x_status;

    ~Cfg() {
        if(!x_status.is_auto_x) {
	    std::cout << "is setting start&end points" << std::endl;
	    std::cout << "start_point:" << x_status.x_setting.x_start << std::endl;
	    std::cout << "end_point:" << x_status.x_setting.x_end << std::endl;
	}
	else {
	    std::cout << "is auto range" << std::endl;
	}
    }
};

void test_cfg() {
    // test1: is_auto_x
    Cfg cfg1;
    cfg1.x_status.is_auto_x = true;

    // test2: has start&end setting
    Cfg cfg2;
    // cfg2.x_status.x_setting.is_auto_xrange = false;
    // cfg2.x_status.x_setting.x_start= 1.7;
    // cfg2.x_status.x_setting.x_end = 7.6;
    cfg2.x_status.x_setting = X_Range_Setting_(1.783, 0.704);
}

int main() {
    std::cout << "dota2 wtf" << std::endl;
    test_cfg();
    return 0;
}

