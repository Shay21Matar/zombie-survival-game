#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include "core/ScoreBoard.h"

/**
 * Unit tests for the ScoreBoard class
 * Tests cover score management, health tracking, level progression,
 * and demonstrates Google Mock usage for save/load functionality
 */

class ScoreBoardTest : public ::testing::Test {
protected:
    ScoreBoard* scoreboard;

    void SetUp() override {
        scoreboard = new ScoreBoard();
    }

    void TearDown() override {
        delete scoreboard;
    }
};

// Test 1: ScoreBoard initialization with correct defaults
TEST_F(ScoreBoardTest, InitializationTest) {
    EXPECT_EQ(scoreboard->getScore(), 0);
    EXPECT_EQ(scoreboard->getHealth(), 100);
    EXPECT_EQ(scoreboard->getKillsToNextLevel(), 10);
}

// Test 2: Increment score by default amount (1)
TEST_F(ScoreBoardTest, IncrementScoreByOne) {
    scoreboard->incrementScore();
    EXPECT_EQ(scoreboard->getScore(), 1);
    
    scoreboard->incrementScore();
    EXPECT_EQ(scoreboard->getScore(), 2);
}

// Test 3: Increment score by custom amount
TEST_F(ScoreBoardTest, IncrementScoreByCustomAmount) {
    scoreboard->incrementScore(10);
    EXPECT_EQ(scoreboard->getScore(), 10);
    
    scoreboard->incrementScore(5);
    EXPECT_EQ(scoreboard->getScore(), 15);
}

// Test 4: Increment score with large values
TEST_F(ScoreBoardTest, IncrementScoreWithLargeValues) {
    scoreboard->incrementScore(1000);
    EXPECT_EQ(scoreboard->getScore(), 1000);
    
    scoreboard->incrementScore(9999);
    EXPECT_EQ(scoreboard->getScore(), 10999);
}

// Test 5: Reset functionality
TEST_F(ScoreBoardTest, ResetTest) {
    scoreboard->incrementScore(50);
    EXPECT_EQ(scoreboard->getScore(), 50);
    
    scoreboard->reset();
    EXPECT_EQ(scoreboard->getScore(), 0);
}

// Test 6: Reset on already zero score
TEST_F(ScoreBoardTest, ResetOnZeroScore) {
    EXPECT_EQ(scoreboard->getScore(), 0);
    scoreboard->reset();
    EXPECT_EQ(scoreboard->getScore(), 0);
}

// Test 7: Health getter and setter
TEST_F(ScoreBoardTest, HealthGetterSetter) {
    EXPECT_EQ(scoreboard->getHealth(), 100);
    
    scoreboard->setHealth(75);
    EXPECT_EQ(scoreboard->getHealth(), 75);
    
    scoreboard->setHealth(0);
    EXPECT_EQ(scoreboard->getHealth(), 0);
}

// Test 8: Negative health (edge case)
TEST_F(ScoreBoardTest, NegativeHealth) {
    scoreboard->setHealth(-10);
    EXPECT_EQ(scoreboard->getHealth(), -10);
}

// Test 9: KillsToNextLevel getter and setter
TEST_F(ScoreBoardTest, KillsToNextLevelGetterSetter) {
    EXPECT_EQ(scoreboard->getKillsToNextLevel(), 10);
    
    scoreboard->setKillsToNextLevel(5);
    EXPECT_EQ(scoreboard->getKillsToNextLevel(), 5);
    
    scoreboard->setKillsToNextLevel(20);
    EXPECT_EQ(scoreboard->getKillsToNextLevel(), 20);
}

// Test 10: Zero increment (edge case)
TEST_F(ScoreBoardTest, ZeroIncrement) {
    scoreboard->incrementScore(0);
    EXPECT_EQ(scoreboard->getScore(), 0);
    
    scoreboard->incrementScore(10);
    scoreboard->incrementScore(0);
    EXPECT_EQ(scoreboard->getScore(), 10);
}

// Test 11: Negative score increment (edge case - testing what happens)
TEST_F(ScoreBoardTest, NegativeIncrement) {
    scoreboard->incrementScore(10);
    EXPECT_EQ(scoreboard->getScore(), 10);
    
    // Decrement by using negative value
    scoreboard->incrementScore(-5);
    EXPECT_EQ(scoreboard->getScore(), 5);
    
    // Can go negative
    scoreboard->incrementScore(-10);
    EXPECT_EQ(scoreboard->getScore(), -5);
}

// Test 12: Multiple resets
TEST_F(ScoreBoardTest, MultipleResets) {
    scoreboard->incrementScore(100);
    scoreboard->reset();
    EXPECT_EQ(scoreboard->getScore(), 0);
    
    scoreboard->incrementScore(50);
    scoreboard->reset();
    EXPECT_EQ(scoreboard->getScore(), 0);
}

// Test 13: Score accumulation scenario
TEST_F(ScoreBoardTest, ScoreAccumulationScenario) {
    // Simulate a game progression
    for (int i = 0; i < 10; i++) {
        scoreboard->incrementScore(1);
    }
    EXPECT_EQ(scoreboard->getScore(), 10);
    
    // Boss kill gives more points
    scoreboard->incrementScore(50);
    EXPECT_EQ(scoreboard->getScore(), 60);
}

// Test 14: Health and score independence
TEST_F(ScoreBoardTest, HealthAndScoreIndependence) {
    scoreboard->incrementScore(25);
    scoreboard->setHealth(50);
    
    EXPECT_EQ(scoreboard->getScore(), 25);
    EXPECT_EQ(scoreboard->getHealth(), 50);
    
    scoreboard->reset();
    EXPECT_EQ(scoreboard->getScore(), 0);
    EXPECT_EQ(scoreboard->getHealth(), 50); // Health should be unchanged
}

// Test 15: KillsToNextLevel edge values
TEST_F(ScoreBoardTest, KillsToNextLevelEdgeValues) {
    scoreboard->setKillsToNextLevel(0);
    EXPECT_EQ(scoreboard->getKillsToNextLevel(), 0);
    
    scoreboard->setKillsToNextLevel(1000);
    EXPECT_EQ(scoreboard->getKillsToNextLevel(), 1000);
    
    // Negative kills (edge case)
    scoreboard->setKillsToNextLevel(-1);
    EXPECT_EQ(scoreboard->getKillsToNextLevel(), -1);
}

/**
 * GOOGLE MOCK DEMONSTRATION
 * 
 * Below is a demonstration of how to use Google Mock for testing.
 * Since ScoreBoard::save() and load() use QSettings (external dependency),
 * we can create a mock interface to test the behavior.
 */

// Mock interface for save/load operations
class MockSaveLoadInterface {
public:
    virtual ~MockSaveLoadInterface() = default;
    virtual void saveData(int score, int health, int kills) = 0;
    virtual void loadData(int& score, int& health, int& kills) = 0;
};

class MockSaveLoad : public MockSaveLoadInterface {
public:
    MOCK_METHOD(void, saveData, (int score, int health, int kills), (override));
    MOCK_METHOD(void, loadData, (int& score, int& health, int& kills), (override));
};

// Test 16: Mock save operation demonstration
TEST(ScoreBoardMockTest, MockSaveOperation) {
    using ::testing::_;
    using ::testing::DoAll;
    using ::testing::SetArgReferee;
    
    MockSaveLoad mockSaveLoad;
    
    // EXPECT_CALL: Verify that saveData is called with specific parameters
    EXPECT_CALL(mockSaveLoad, saveData(50, 75, 5))
        .Times(1);  // Expect exactly one call
    
    // Simulate saving game state
    mockSaveLoad.saveData(50, 75, 5);
}

// Test 17: Mock load operation demonstration with return values
TEST(ScoreBoardMockTest, MockLoadOperation) {
    using ::testing::_;
    using ::testing::DoAll;
    using ::testing::SetArgReferee;
    
    MockSaveLoad mockSaveLoad;
    
    int score = 0, health = 0, kills = 0;
    
    // EXPECT_CALL: Set up expectations and mock return values
    EXPECT_CALL(mockSaveLoad, loadData(_, _, _))
        .Times(1)
        .WillOnce(DoAll(
            SetArgReferee<0>(100),  // Set score to 100
            SetArgReferee<1>(80),   // Set health to 80
            SetArgReferee<2>(3)     // Set kills to 3
        ));
    
    // Execute the mocked load
    mockSaveLoad.loadData(score, health, kills);
    
    // Verify the values were loaded correctly
    EXPECT_EQ(score, 100);
    EXPECT_EQ(health, 80);
    EXPECT_EQ(kills, 3);
}

// Test 18: Mock save operation called multiple times
TEST(ScoreBoardMockTest, MockSaveCalledMultipleTimes) {
    using ::testing::_;
    using ::testing::AnyNumber;
    
    MockSaveLoad mockSaveLoad;
    
    // EXPECT_CALL: Allow any number of saves
    EXPECT_CALL(mockSaveLoad, saveData(_, _, _))
        .Times(AnyNumber());
    
    // Simulate multiple save operations
    mockSaveLoad.saveData(10, 100, 10);
    mockSaveLoad.saveData(20, 90, 9);
    mockSaveLoad.saveData(30, 80, 8);
}

// Test 19: Mock with specific parameter matching
TEST(ScoreBoardMockTest, MockWithSpecificParameterMatching) {
    using ::testing::Gt;
    using ::testing::Le;
    using ::testing::_;
    
    MockSaveLoad mockSaveLoad;
    
    // EXPECT_CALL: Only accept saves where score > 50 and health <= 100
    EXPECT_CALL(mockSaveLoad, saveData(Gt(50), Le(100), _))
        .Times(1);
    
    // This should match the expectation
    mockSaveLoad.saveData(75, 100, 5);
}

// Test 20: Mock demonstrating action sequences
TEST(ScoreBoardMockTest, MockActionSequence) {
    using ::testing::_;
    using ::testing::Return;
    using ::testing::InSequence;
    
    MockSaveLoad mockSaveLoad;
    
    {
        // InSequence ensures calls happen in order
        InSequence seq;
        
        // First save
        EXPECT_CALL(mockSaveLoad, saveData(0, 100, 10))
            .Times(1);
        
        // Second save after some gameplay
        EXPECT_CALL(mockSaveLoad, saveData(50, 75, 5))
            .Times(1);
    }
    
    // Execute in the expected sequence
    mockSaveLoad.saveData(0, 100, 10);
    mockSaveLoad.saveData(50, 75, 5);
}
