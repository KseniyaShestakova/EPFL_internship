add_test([=[Basic.JustBoot]=]  /home/xxeniash/EPFL_internship/EPFL_internship/amazon/s3_exp/build/app [==[--gtest_filter=Basic.JustBoot]==] --gtest_also_run_disabled_tests)
set_tests_properties([=[Basic.JustBoot]=]  PROPERTIES WORKING_DIRECTORY /home/xxeniash/EPFL_internship/EPFL_internship/amazon/s3_exp/build SKIP_REGULAR_EXPRESSION [==[\[  SKIPPED \]]==])
add_test([=[Basic.BootAndCreateNamespace]=]  /home/xxeniash/EPFL_internship/EPFL_internship/amazon/s3_exp/build/app [==[--gtest_filter=Basic.BootAndCreateNamespace]==] --gtest_also_run_disabled_tests)
set_tests_properties([=[Basic.BootAndCreateNamespace]=]  PROPERTIES WORKING_DIRECTORY /home/xxeniash/EPFL_internship/EPFL_internship/amazon/s3_exp/build SKIP_REGULAR_EXPRESSION [==[\[  SKIPPED \]]==])
add_test([=[CAssert.easy_test_1]=]  /home/xxeniash/EPFL_internship/EPFL_internship/amazon/s3_exp/build/app [==[--gtest_filter=CAssert.easy_test_1]==] --gtest_also_run_disabled_tests)
set_tests_properties([=[CAssert.easy_test_1]=]  PROPERTIES WORKING_DIRECTORY /home/xxeniash/EPFL_internship/EPFL_internship/amazon/s3_exp/build SKIP_REGULAR_EXPRESSION [==[\[  SKIPPED \]]==])
add_test([=[CAssert.easy_test_2]=]  /home/xxeniash/EPFL_internship/EPFL_internship/amazon/s3_exp/build/app [==[--gtest_filter=CAssert.easy_test_2]==] --gtest_also_run_disabled_tests)
set_tests_properties([=[CAssert.easy_test_2]=]  PROPERTIES WORKING_DIRECTORY /home/xxeniash/EPFL_internship/EPFL_internship/amazon/s3_exp/build SKIP_REGULAR_EXPRESSION [==[\[  SKIPPED \]]==])
add_test([=[CAssert.easy_test_3]=]  /home/xxeniash/EPFL_internship/EPFL_internship/amazon/s3_exp/build/app [==[--gtest_filter=CAssert.easy_test_3]==] --gtest_also_run_disabled_tests)
set_tests_properties([=[CAssert.easy_test_3]=]  PROPERTIES WORKING_DIRECTORY /home/xxeniash/EPFL_internship/EPFL_internship/amazon/s3_exp/build SKIP_REGULAR_EXPRESSION [==[\[  SKIPPED \]]==])
add_test([=[CAssert.easy_test_4]=]  /home/xxeniash/EPFL_internship/EPFL_internship/amazon/s3_exp/build/app [==[--gtest_filter=CAssert.easy_test_4]==] --gtest_also_run_disabled_tests)
set_tests_properties([=[CAssert.easy_test_4]=]  PROPERTIES WORKING_DIRECTORY /home/xxeniash/EPFL_internship/EPFL_internship/amazon/s3_exp/build SKIP_REGULAR_EXPRESSION [==[\[  SKIPPED \]]==])
add_test([=[HighLoad.Create200]=]  /home/xxeniash/EPFL_internship/EPFL_internship/amazon/s3_exp/build/app [==[--gtest_filter=HighLoad.Create200]==] --gtest_also_run_disabled_tests)
set_tests_properties([=[HighLoad.Create200]=]  PROPERTIES WORKING_DIRECTORY /home/xxeniash/EPFL_internship/EPFL_internship/amazon/s3_exp/build SKIP_REGULAR_EXPRESSION [==[\[  SKIPPED \]]==])
add_test([=[HighLoad.Create500]=]  /home/xxeniash/EPFL_internship/EPFL_internship/amazon/s3_exp/build/app [==[--gtest_filter=HighLoad.Create500]==] --gtest_also_run_disabled_tests)
set_tests_properties([=[HighLoad.Create500]=]  PROPERTIES WORKING_DIRECTORY /home/xxeniash/EPFL_internship/EPFL_internship/amazon/s3_exp/build SKIP_REGULAR_EXPRESSION [==[\[  SKIPPED \]]==])
add_test([=[HighLoad.Open200]=]  /home/xxeniash/EPFL_internship/EPFL_internship/amazon/s3_exp/build/app [==[--gtest_filter=HighLoad.Open200]==] --gtest_also_run_disabled_tests)
set_tests_properties([=[HighLoad.Open200]=]  PROPERTIES WORKING_DIRECTORY /home/xxeniash/EPFL_internship/EPFL_internship/amazon/s3_exp/build SKIP_REGULAR_EXPRESSION [==[\[  SKIPPED \]]==])
add_test([=[HighLoad.Open500]=]  /home/xxeniash/EPFL_internship/EPFL_internship/amazon/s3_exp/build/app [==[--gtest_filter=HighLoad.Open500]==] --gtest_also_run_disabled_tests)
set_tests_properties([=[HighLoad.Open500]=]  PROPERTIES WORKING_DIRECTORY /home/xxeniash/EPFL_internship/EPFL_internship/amazon/s3_exp/build SKIP_REGULAR_EXPRESSION [==[\[  SKIPPED \]]==])
add_test([=[HighLoad.Delete200]=]  /home/xxeniash/EPFL_internship/EPFL_internship/amazon/s3_exp/build/app [==[--gtest_filter=HighLoad.Delete200]==] --gtest_also_run_disabled_tests)
set_tests_properties([=[HighLoad.Delete200]=]  PROPERTIES WORKING_DIRECTORY /home/xxeniash/EPFL_internship/EPFL_internship/amazon/s3_exp/build SKIP_REGULAR_EXPRESSION [==[\[  SKIPPED \]]==])
add_test([=[HighLoad.Delete500]=]  /home/xxeniash/EPFL_internship/EPFL_internship/amazon/s3_exp/build/app [==[--gtest_filter=HighLoad.Delete500]==] --gtest_also_run_disabled_tests)
set_tests_properties([=[HighLoad.Delete500]=]  PROPERTIES WORKING_DIRECTORY /home/xxeniash/EPFL_internship/EPFL_internship/amazon/s3_exp/build SKIP_REGULAR_EXPRESSION [==[\[  SKIPPED \]]==])
add_test([=[HighLoad.Write512_200]=]  /home/xxeniash/EPFL_internship/EPFL_internship/amazon/s3_exp/build/app [==[--gtest_filter=HighLoad.Write512_200]==] --gtest_also_run_disabled_tests)
set_tests_properties([=[HighLoad.Write512_200]=]  PROPERTIES WORKING_DIRECTORY /home/xxeniash/EPFL_internship/EPFL_internship/amazon/s3_exp/build SKIP_REGULAR_EXPRESSION [==[\[  SKIPPED \]]==])
add_test([=[HighLoad.Write512_500]=]  /home/xxeniash/EPFL_internship/EPFL_internship/amazon/s3_exp/build/app [==[--gtest_filter=HighLoad.Write512_500]==] --gtest_also_run_disabled_tests)
set_tests_properties([=[HighLoad.Write512_500]=]  PROPERTIES WORKING_DIRECTORY /home/xxeniash/EPFL_internship/EPFL_internship/amazon/s3_exp/build SKIP_REGULAR_EXPRESSION [==[\[  SKIPPED \]]==])
add_test([=[HighLoad.Write2048_200]=]  /home/xxeniash/EPFL_internship/EPFL_internship/amazon/s3_exp/build/app [==[--gtest_filter=HighLoad.Write2048_200]==] --gtest_also_run_disabled_tests)
set_tests_properties([=[HighLoad.Write2048_200]=]  PROPERTIES WORKING_DIRECTORY /home/xxeniash/EPFL_internship/EPFL_internship/amazon/s3_exp/build SKIP_REGULAR_EXPRESSION [==[\[  SKIPPED \]]==])
add_test([=[HighLoad.Write2048_500]=]  /home/xxeniash/EPFL_internship/EPFL_internship/amazon/s3_exp/build/app [==[--gtest_filter=HighLoad.Write2048_500]==] --gtest_also_run_disabled_tests)
set_tests_properties([=[HighLoad.Write2048_500]=]  PROPERTIES WORKING_DIRECTORY /home/xxeniash/EPFL_internship/EPFL_internship/amazon/s3_exp/build SKIP_REGULAR_EXPRESSION [==[\[  SKIPPED \]]==])
add_test([=[HighLoad.Read512_200]=]  /home/xxeniash/EPFL_internship/EPFL_internship/amazon/s3_exp/build/app [==[--gtest_filter=HighLoad.Read512_200]==] --gtest_also_run_disabled_tests)
set_tests_properties([=[HighLoad.Read512_200]=]  PROPERTIES WORKING_DIRECTORY /home/xxeniash/EPFL_internship/EPFL_internship/amazon/s3_exp/build SKIP_REGULAR_EXPRESSION [==[\[  SKIPPED \]]==])
add_test([=[HighLoad.Read512_500]=]  /home/xxeniash/EPFL_internship/EPFL_internship/amazon/s3_exp/build/app [==[--gtest_filter=HighLoad.Read512_500]==] --gtest_also_run_disabled_tests)
set_tests_properties([=[HighLoad.Read512_500]=]  PROPERTIES WORKING_DIRECTORY /home/xxeniash/EPFL_internship/EPFL_internship/amazon/s3_exp/build SKIP_REGULAR_EXPRESSION [==[\[  SKIPPED \]]==])
add_test([=[HighLoad.Read2048_200]=]  /home/xxeniash/EPFL_internship/EPFL_internship/amazon/s3_exp/build/app [==[--gtest_filter=HighLoad.Read2048_200]==] --gtest_also_run_disabled_tests)
set_tests_properties([=[HighLoad.Read2048_200]=]  PROPERTIES WORKING_DIRECTORY /home/xxeniash/EPFL_internship/EPFL_internship/amazon/s3_exp/build SKIP_REGULAR_EXPRESSION [==[\[  SKIPPED \]]==])
add_test([=[HighLoad.Read2048_500]=]  /home/xxeniash/EPFL_internship/EPFL_internship/amazon/s3_exp/build/app [==[--gtest_filter=HighLoad.Read2048_500]==] --gtest_also_run_disabled_tests)
set_tests_properties([=[HighLoad.Read2048_500]=]  PROPERTIES WORKING_DIRECTORY /home/xxeniash/EPFL_internship/EPFL_internship/amazon/s3_exp/build SKIP_REGULAR_EXPRESSION [==[\[  SKIPPED \]]==])
add_test([=[HighLoad.ListNoPrefix]=]  /home/xxeniash/EPFL_internship/EPFL_internship/amazon/s3_exp/build/app [==[--gtest_filter=HighLoad.ListNoPrefix]==] --gtest_also_run_disabled_tests)
set_tests_properties([=[HighLoad.ListNoPrefix]=]  PROPERTIES WORKING_DIRECTORY /home/xxeniash/EPFL_internship/EPFL_internship/amazon/s3_exp/build SKIP_REGULAR_EXPRESSION [==[\[  SKIPPED \]]==])
add_test([=[HighLoad.ListWithPrefix]=]  /home/xxeniash/EPFL_internship/EPFL_internship/amazon/s3_exp/build/app [==[--gtest_filter=HighLoad.ListWithPrefix]==] --gtest_also_run_disabled_tests)
set_tests_properties([=[HighLoad.ListWithPrefix]=]  PROPERTIES WORKING_DIRECTORY /home/xxeniash/EPFL_internship/EPFL_internship/amazon/s3_exp/build SKIP_REGULAR_EXPRESSION [==[\[  SKIPPED \]]==])
add_test([=[HigLoad.Close200]=]  /home/xxeniash/EPFL_internship/EPFL_internship/amazon/s3_exp/build/app [==[--gtest_filter=HigLoad.Close200]==] --gtest_also_run_disabled_tests)
set_tests_properties([=[HigLoad.Close200]=]  PROPERTIES WORKING_DIRECTORY /home/xxeniash/EPFL_internship/EPFL_internship/amazon/s3_exp/build SKIP_REGULAR_EXPRESSION [==[\[  SKIPPED \]]==])
add_test([=[HigLoad.Close500]=]  /home/xxeniash/EPFL_internship/EPFL_internship/amazon/s3_exp/build/app [==[--gtest_filter=HigLoad.Close500]==] --gtest_also_run_disabled_tests)
set_tests_properties([=[HigLoad.Close500]=]  PROPERTIES WORKING_DIRECTORY /home/xxeniash/EPFL_internship/EPFL_internship/amazon/s3_exp/build SKIP_REGULAR_EXPRESSION [==[\[  SKIPPED \]]==])
set(  app_TESTS Basic.JustBoot Basic.BootAndCreateNamespace CAssert.easy_test_1 CAssert.easy_test_2 CAssert.easy_test_3 CAssert.easy_test_4 HighLoad.Create200 HighLoad.Create500 HighLoad.Open200 HighLoad.Open500 HighLoad.Delete200 HighLoad.Delete500 HighLoad.Write512_200 HighLoad.Write512_500 HighLoad.Write2048_200 HighLoad.Write2048_500 HighLoad.Read512_200 HighLoad.Read512_500 HighLoad.Read2048_200 HighLoad.Read2048_500 HighLoad.ListNoPrefix HighLoad.ListWithPrefix HigLoad.Close200 HigLoad.Close500)
