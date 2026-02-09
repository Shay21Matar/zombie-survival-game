# GoogleTest Setup and Execution Guide

## Quick Start

### 1. Build the Tests
```powershell
cd tests
mkdir build
cd build
cmake ..
cmake --build .
```

### 2. Run the Tests
```powershell
# Windows
.\Debug\run_tests.exe

# Or if using Release build
.\Release\run_tests.exe
```

## What Gets Tested

### Player Class (15 tests)
- ✅ Initialization and default values
- ✅ Position and angle management
- ✅ Health system (damage, healing, boundaries)
- ✅ Damage cooldown mechanism
- ✅ Edge cases (negative health, overheal, zero damage)

### ScoreBoard Class (20 tests)
- ✅ Score increment and reset
- ✅ Health and level tracking
- ✅ Edge cases (large values, negative scores)
- ✅ **Google Mock examples** (EXPECT_CALL, matchers, sequences)

## Files Created

```
tests/
├── CMakeLists.txt              # Build configuration
├── PlayerTest.cpp              # 15 Player tests
├── ScoreBoardTest.cpp          # 20 ScoreBoard tests (with mocks)
├── TESTING_REPORT.md           # Detailed test documentation
└── README.md                   # This file
```

## Understanding the Test Output

```
[==========] Running 35 tests from 3 test suites.
[----------] 15 tests from PlayerTest
[ RUN      ] PlayerTest.InitializationTest
[       OK ] PlayerTest.InitializationTest (0 ms)
...
[  PASSED  ] 35 tests.
```

- Green `[  PASSED  ]` = All tests passed ✅
- Red `[  FAILED  ]` = Something broke ❌

## Google Mock Examples in ScoreBoardTest.cpp

Look for these patterns in the code:

### 1. Basic EXPECT_CALL
```cpp
EXPECT_CALL(mockObject, methodName(param1, param2))
    .Times(1);
```

### 2. Parameter Matchers
```cpp
EXPECT_CALL(mock, method(Gt(50), Le(100), _))  // Greater than 50, Less/equal 100, any value
```

### 3. Return Values
```cpp
EXPECT_CALL(mock, method(_, _, _))
    .WillOnce(DoAll(
        SetArgReferee<0>(value1),
        SetArgReferee<1>(value2)
    ));
```

### 4. Call Sequences
```cpp
InSequence seq;
EXPECT_CALL(mock, first());  // Must happen first
EXPECT_CALL(mock, second()); // Must happen second
```

## Troubleshooting

### CMake can't find Qt6
Make sure Qt6 is installed and in your PATH. Update CMakeLists.txt if needed:
```cmake
set(CMAKE_PREFIX_PATH "C:/Qt/6.x.x/mingw_64")
```

### Tests won't compile
Check that all header includes point to the correct paths. The test assumes this structure:
```
code/core/Player.h
code/core/Player.cpp
code/core/ScoreBoard.h
code/core/scoreboard.cpp
```

### GoogleTest download fails
If behind a firewall, manually download GoogleTest:
```powershell
git clone https://github.com/google/googletest.git
# Then update CMakeLists.txt to use local path
```

## Next Steps

1. **Run the tests** to verify everything works
2. **Read TESTING_REPORT.md** for detailed test analysis
3. **Experiment** by breaking a test to see failures
4. **Add more tests** for other classes (Bullet, Zombie, etc.)

## Key Concepts You Learned

- ✅ **Unit Testing**: Testing individual components in isolation
- ✅ **Test Fixtures**: SetUp/TearDown for consistent test state
- ✅ **Edge Cases**: Testing boundary conditions (zero, negative, maximum)
- ✅ **EXPECT_CALL**: Mocking expectations in Google Mock
- ✅ **Parameter Matchers**: Gt(), Le(), _, etc.
- ✅ **Mock Return Values**: SetArgReferee, WillOnce, DoAll

Good luck with your assignment! 🚀
