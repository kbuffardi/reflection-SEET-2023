# SEER-PairwiseTester

A tool for assessing students' unit tests by running their tests against all other students' solutions.

## Requirements

To run this application, the following dependencies are required:
* [Docker](www.docker.com)

## Getting Started

First, build the docker image with the command:

```
docker build . -t pairwise-tester
```

After successful build, run the container:

```
docker run \
--mount type=bind,source="$(pwd)",target=/read-src,readonly \
--mount type=bind,source="$(pwd)/output",destination=/output \
-it pairwise-tester
```

Within the container, `/read-src` will have a synchronized, read-only reference to the host's repo and `/output` is a writable directory for data persistence (written to this repo's `/output` subdirectory) even after terminating a container.

## File Structure

 `/read-src` is a *read only* mount of this repository. It is linked to the directory on the host so that script editing can be done on the host machine and then within the container, the edited files can be copied into their appropriate locations in the ephemeral environment.

`/output` is bound to the repository's `output` subdirectory with both *read and write* permissions. This directory is meant to hold data output from the scripts so it can persist after the container terminates. In other words, it allows data from the container to be stored on the host.

`/data` contains a copy of all files and subdirectories in the repository's `quiz-data` directory. The copy has write permissions but it is ephemeral.

`/usr/src/pairwise-tester` is the working directory, where the python scripts are copied and stored. This is where the scripts should be executed. It is also referenced by the environmental variable `WORKDIR`.


## All Function Pairs Analysis

### Step 1: Function-under-test (FUT) and Coverage (COV) Analysis

To analyze each unit test for its FUT and each test suite for its coverage, invoke the following scripts from the working directory and specify the directory containing students' subdirectories (e.g. `/data`) and the path that contains the reference Makefile that will be copied into each student subdirectory (e.g. `/data/quizReference`):

```
python run_fut.py /data
python run_cov_fut.py /data /data/quizReferences
```

This generates files `fut_results` and `cov_fut_results` in the working directory.

### Step 2: All Pairs analysis

To run the all pairs testing analysis, invoke the `tests.bash` script:

```
source /data/tests.bash
```

**WARNING!** this process takes a very long time when there is more than just a few students. It grows exponentially with each additional student and may take hours to complete. It creates a `results.txt` file in the same directory, which summarizes each pairwise test result.

### Step 3: All Pairs spreadsheet

To convert the all pairs results into comma-separated format (CSV) spreadsheet, invoke the following script from the working directory and specify the location of the `results.txt` file:

```
python csvbytestcase.py /data/results.txt
```

When successful, this produces a CSV file of the same name (e.g. `results.txt.csv`).


### Step 4: Aggregate analyses

Gather all the analyses into a spreadsheet with the following command, given the *output files* from steps 2 and 3 as the three arguments:

```
python meta-fut.py results.txt.csv fut_results cov_fut_results
```

This generates a file `results.txt.csv.accuracy.csv` (by appending `.accuracy.csv`) to the file name of the script's first argument. The spreadsheet summarizes results according to the FUT for each student.

## Features Under Construction

Gerard Meszaros' [xUnit Patterns](http://xunitpatterns.com/) describes **Conditional Test Logic** as a *Code Smell*. Conditional logic can be identified using McCabe's Cyclomatic Complexity. The docker container installs [PMCcabe](https://people.debian.org/~bame/pmccabe/pmccabe.1). This tool can be used on an individual test file by using the following command:

```
pmccabe -v /data/student-000/*Test.cpp
```

Which should produce output such as:

```
Modified McCabe Cyclomatic Complexity
|   Traditional McCabe Cyclomatic Complexity
|       |    # Statements in function
|       |        |   First line of function
|       |        |       |   # lines in function
|       |        |       |       |  filename(definition line number):function
|       |        |       |       |           |
1 1 0 16  1 PiezasTest.cpp(16): PiezasTest::PiezasTest
1 1 0 17  1 PiezasTest.cpp(17): PiezasTest::~PiezasTest
1 1 0 18  1 PiezasTest.cpp(18): PiezasTest::SetUp
1 1 0 19  1 PiezasTest.cpp(19): PiezasTest::TearDown
3 3 8 27  11  PiezasTest.cpp(27): TEST
3 3 10  40  13  PiezasTest.cpp(40): TEST
1 1 6 55  9 PiezasTest.cpp(55): TEST
1 1 3 66  6 PiezasTest.cpp(66): TEST
1 1 5 74  8 PiezasTest.cpp(74): TEST
1 1 13  84  19  PiezasTest.cpp(84): TEST
1 1 14  106 21  PiezasTest.cpp(106): TEST
1 1 2 129 5 PiezasTest.cpp(129): TEST
2 2 6 136 9 PiezasTest.cpp(136): TEST
1 1 14  147 17  PiezasTest.cpp(147): TEST
1 1 14  166 17  PiezasTest.cpp(166): TEST
1 1 14  185 17  PiezasTest.cpp(185): TEST
```

For the purpose of our analysis, we can ignore the fixture functions (constructor, destructor, `SetUp`, and `TearDown`). The other lines (ending with `TEST`) corresponds with each unit test in order as they appear in the file. The second column (`Traditional McCabe Cyclomatic Complexity`) contains the number that we want to collect for each unit test for each student's tests. That complexity should then be summed for each FUT, as a new column `test_complexity` in the `results.txt.csv.accuracy.csv` output file; consequently, each row in this file should have the total complexity for all the unit tests for each individual FUT as well as a total for the `xTOTAL` rows to sum the complexity for each student's tests as a whole.