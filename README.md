# Summer@EPFL 2023 internship project by Kseniya Shastakova
This repository contains results of reasearch at Summer@EPFL 2023 internship carried by Kseniya Shastakova. \
The aim of the project was to develop backend for JULEA using APIs for object storages. OpenIO C SDK, MinIO C++ SDK and AWS C++ SDK were used for implementing 3 different backends.
## Navigation
* [`amazon/minio_exp/`](https://github.com/KseniyaShestakova/EPFL_internship/tree/main/amazon/minio_exp) contains backend implementation with MinIO C++ SDK, benchmark report, code samples used for testing,
 testing script and CMakeLists used for running tests on a local computer
* [`amazon/s3_exp/`](https://github.com/KseniyaShestakova/EPFL_internship/tree/main/amazon/s3_exp) contains backend implementation with AWS C++ SDK, benchmark report, code samples used for testing,
 testing script and CMakeLists used for running tests on a local computer
* [`auxiliary/`](https://github.com/KseniyaShestakova/EPFL_internship/tree/main/auxiliary) contains small apps showing how to work with JULEA and OpenIO C SDK
* [`build/`](https://github.com/KseniyaShestakova/EPFL_internship/tree/main/build) contains `meson.build` file for building JULEA with new backend (`oio.c`) and examples of files with backend implementations (`foo.c` and `oio.c`)
* [`oio-sds/`](https://github.com/KseniyaShestakova/EPFL_internship/tree/main/oio-sds) contains oio-sds library with changes made during resolving of compilations issues when building apps with OpenIO C SDK. ATTENTION: may be removed later
* [`random/`](https://github.com/KseniyaShestakova/EPFL_internship/tree/main/random) contains files not connected directly to the project. ATTENTION: may be removed later
* [`readings/`](https://github.com/KseniyaShestakova/EPFL_internship/tree/main/readings) contains information regarding building, compiling and running code samples from this repo,
   as well as some general information that will help the reader to get more comprehensive understanding of object storages
* [`scripts/`](https://github.com/KseniyaShestakova/EPFL_internship/tree/main/scripts) contains scripts used to automate some repetitive and routine stuff occuring along building and running code samples
* [`paper/`](https://github.com/KseniyaShestakova/EPFL_internship/tree/main/paper) contains detailed [report](https://github.com/KseniyaShestakova/EPFL_internship/blob/main/paper/JULEA.pdf) about the work done and source code of the report latex file
