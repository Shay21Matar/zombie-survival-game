# How to Run the Tests

## Quick Start

1. Open PowerShell in the `tests/build` directory
2. Run these commands:

```powershell
$env:PATH = "C:\Qt\6.10.1\mingw_64\bin;C:\Qt\Tools\mingw1310_64\bin;" + $env:PATH
.\game_tests.exe
```

## Test Results

**Status:** ✅ All 35 tests PASSED

```
[==========] Running 35 tests from 3 test suites.
[  PASSED  ] 35 tests.
```

### Test Breakdown:
- **PlayerTest**: 15 tests - Testing health, damage, position, edge cases
- **ScoreBoardTest**: 15 tests - Testing score, reset, health tracking
- **ScoreBoardMockTest**: 5 tests - Demonstrating Google Mock with EXPECT_CALL

## Files for Assignment

1. **Test Code:**
   - `PlayerTest.cpp` - 15 unit tests for Player class
   - `ScoreBoardTest.cpp` - 20 tests including 5 Google Mock examples

2. **Test Results:**
   - `test_results.txt` - Full test output showing all passed

3. **Documentation:**
   - `TESTING_REPORT.md` - Detailed report with edge cases and discussion
   - `README.md` - Setup instructions

## Rebuilding from Scratch

If you need to rebuild:

```powershell
cd tests
Remove-Item -Recurse -Force build
mkdir build
cd build

$env:PATH = "C:\Qt\Tools\mingw1310_64\bin;" + $env:PATH
cmake -G "MinGW Makefiles" -DCMAKE_PREFIX_PATH="C:/Qt/6.10.1/mingw_64" ..
mingw32-make

$env:PATH = "C:\Qt\6.10.1\mingw_64\bin;C:\Qt\Tools\mingw1310_64\bin;" + $env:PATH
.\game_tests.exe
```

## What Was Tested

### Player Class Edge Cases:
- ✅ Health cannot go below 0
- ✅ Health cannot exceed 100
- ✅ Damage cooldown prevents rapid consecutive damage
- ✅ Zero damage/healing handling
- ✅ Boundary position values (negative, very large)

### ScoreBoard Class Edge Cases:
- ✅ Large score values (1000+)
- ✅ Negative score increments
- ✅ Reset idempotency
- ✅ Health/score independence

### Google Mock Examples (EXPECT_CALL):
- ✅ Basic EXPECT_CALL with specific parameters
- ✅ Mock return values with SetArgReferee
- ✅ Flexible call counts (AnyNumber)
- ✅ Parameter matchers (Gt, Le)
- ✅ InSequence for ordered expectations

**Date:** December 6, 2025  
**Status:** Complete ✅
