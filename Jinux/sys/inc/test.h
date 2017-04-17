/*
 * test.h
 *
 *  Created on: 2016-8-23
 *      Author: wenrenjinjun
 */

#ifndef TEST_H_
#define TEST_H_


#ifdef __WHITEBOX_TEST
    #include <CUnit\console.h>

    //------------------------------ 测试用例 --------------------------------//
    #define __DECLARE_TEST(x)        void __test_##x(void);    //测试用例外部声明
    #define __IMPLEMENT_TEST(x)      void __test_##x(void)    //测试用例实体


    //------------------------------ 测试集     --------------------------------//
    #define __BEGIN_TESTMAP_OF_SUITE(x) \
                                    CU_TestInfo __tests_info_table_##x[] = \
                                    {	                            //测试用例注册表开始
    #define __REG_TEST(x)               {"__test_"#x , __test_##x}, //测试用例注册
    #define __END_TESTMAP()             CU_TEST_INFO_NULL,\
                                    };					            //测试用例注册表结束

    #define __INIT_SUITE(x)         int __init_suite_##x(void)	    //测试集初始化 	函数
    #define __CLEAN_SUITE(x)        int __clean_suite_##x(void)	    //测试集清理 		函数

    #define __DECLARE_SUITE(x)      extern int __init_suite_##x(void);\
                                    extern int __clean_suite_##x(void);\
                                    extern CU_TestInfo __tests_info_table_##x[];\

    //------------------------------ 测试簿     --------------------------------//
    #define __BEGIN_SUITEMAP_OF_TESTBOOK(x)\
                                    CU_SuiteInfo __suites_info_table_##x[] = \
                                    {
    #define __REG_SUITE(x)	            {"__suit_"#x, __init_suite_##x, __clean_suite_##x, NULL, NULL, __tests_info_table_##x},
    #define __END_SUITEMAP()            CU_SUITE_INFO_NULL,\
                                    };

    #define __TESTBOOK(x)  __suites_info_table_##x

    //------------------------------ 测试工程     -------------------------------//
    #define __DO_WHITEBOX_TEST() \
        extern int __do_test_fun(void);\
        __do_test_fun();
#else
     #define __DO_WHITEBOX_TEST()
#endif

#endif /* TEST_H_ */
