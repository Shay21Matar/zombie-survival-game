#include <gtest/gtest.h>
#include "core/Player.h"
#include <QPointF>

/**
 * Unit tests for the Player class
 * Tests cover initialization, position/angle updates, health management,
 * and edge cases like damage cooldown and health boundaries
 */

class PlayerTest : public ::testing::Test {
protected:
    Player* player;

    void SetUp() override {
        player = new Player();
    }

    void TearDown() override {
        delete player;
    }
};

// Test 1: Player initialization with correct default values
TEST_F(PlayerTest, InitializationTest) {
    EXPECT_EQ(player->getPosition().x(), 400);
    EXPECT_EQ(player->getPosition().y(), 300);
    EXPECT_EQ(player->getHealth(), 100);
    EXPECT_EQ(player->getAngle(), 0);
    EXPECT_FLOAT_EQ(player->getDamageCooldown(), 0.0f);
}

// Test 2: Position setter and getter
TEST_F(PlayerTest, SetPositionTest) {
    QPointF newPos(150.5, 250.7);
    player->setPosition(newPos);
    
    EXPECT_EQ(player->getPosition().x(), 150.5);
    EXPECT_EQ(player->getPosition().y(), 250.7);
}

// Test 3: Angle setter and getter
TEST_F(PlayerTest, SetAngleTest) {
    player->setAngle(45.0);
    EXPECT_EQ(player->getAngle(), 45.0);
    
    player->setAngle(180.0);
    EXPECT_EQ(player->getAngle(), 180.0);
    
    // Test negative angle
    player->setAngle(-90.0);
    EXPECT_EQ(player->getAngle(), -90.0);
}

// Test 4: Basic damage taken
TEST_F(PlayerTest, TakeDamageBasic) {
    player->takeDamage(30);
    EXPECT_EQ(player->getHealth(), 70);
    EXPECT_GT(player->getDamageCooldown(), 0.0f);
}

// Test 5: Health cannot go below zero (edge case)
TEST_F(PlayerTest, HealthCannotGoNegative) {
    player->takeDamage(150); // More damage than health
    EXPECT_EQ(player->getHealth(), 0);
}

// Test 6: Damage cooldown prevents immediate consecutive damage (edge case)
TEST_F(PlayerTest, DamageCooldownPreventsConsecutiveDamage) {
    // First damage should work
    player->takeDamage(20);
    EXPECT_EQ(player->getHealth(), 80);
    
    // Second immediate damage should be blocked by cooldown
    player->takeDamage(20);
    EXPECT_EQ(player->getHealth(), 80); // Health unchanged
    EXPECT_GT(player->getDamageCooldown(), 0.0f);
}

// Test 7: Damage works after cooldown expires
TEST_F(PlayerTest, DamageAfterCooldownExpires) {
    // Take initial damage
    player->takeDamage(20);
    EXPECT_EQ(player->getHealth(), 80);
    
    // Manually expire cooldown
    player->setDamageCooldown(0.0f);
    
    // Should be able to take damage again
    player->takeDamage(15);
    EXPECT_EQ(player->getHealth(), 65);
}

// Test 8: Basic healing
TEST_F(PlayerTest, HealBasic) {
    player->takeDamage(40);
    player->setDamageCooldown(0.0f); // Reset cooldown for clean test
    EXPECT_EQ(player->getHealth(), 60);
    
    player->heal(20);
    EXPECT_EQ(player->getHealth(), 80);
}

// Test 9: Health cannot exceed maximum (edge case)
TEST_F(PlayerTest, HealthCannotExceedMaximum) {
    player->heal(50); // Player already at 100
    EXPECT_EQ(player->getHealth(), 100);
    
    // Try healing from damaged state
    player->takeDamage(10);
    player->setDamageCooldown(0.0f);
    EXPECT_EQ(player->getHealth(), 90);
    
    player->heal(20); // Would go to 110
    EXPECT_EQ(player->getHealth(), 100); // Capped at 100
}

// Test 10: Multiple position updates
TEST_F(PlayerTest, MultiplePositionUpdates) {
    player->setPosition(QPointF(100, 100));
    EXPECT_EQ(player->getPosition(), QPointF(100, 100));
    
    player->setPosition(QPointF(200, 200));
    EXPECT_EQ(player->getPosition(), QPointF(200, 200));
    
    player->setPosition(QPointF(0, 0));
    EXPECT_EQ(player->getPosition(), QPointF(0, 0));
}

// Test 11: Boundary position values (edge case)
TEST_F(PlayerTest, BoundaryPositionValues) {
    // Test negative positions
    player->setPosition(QPointF(-100, -100));
    EXPECT_EQ(player->getPosition().x(), -100);
    EXPECT_EQ(player->getPosition().y(), -100);
    
    // Test very large positions
    player->setPosition(QPointF(10000, 10000));
    EXPECT_EQ(player->getPosition().x(), 10000);
    EXPECT_EQ(player->getPosition().y(), 10000);
}

// Test 12: Zero damage
TEST_F(PlayerTest, ZeroDamage) {
    player->takeDamage(0);
    EXPECT_EQ(player->getHealth(), 100);
}

// Test 13: Zero healing
TEST_F(PlayerTest, ZeroHealing) {
    player->takeDamage(30);
    player->setDamageCooldown(0.0f);
    EXPECT_EQ(player->getHealth(), 70);
    
    player->heal(0);
    EXPECT_EQ(player->getHealth(), 70);
}

// Test 14: Large angle values
TEST_F(PlayerTest, LargeAngleValues) {
    player->setAngle(360.0);
    EXPECT_EQ(player->getAngle(), 360.0);
    
    player->setAngle(720.0);
    EXPECT_EQ(player->getAngle(), 720.0);
}

// Test 15: Complete health depletion scenario
TEST_F(PlayerTest, CompleteHealthDepletionScenario) {
    // Simulate taking damage multiple times until death
    player->takeDamage(30);
    EXPECT_EQ(player->getHealth(), 70);
    
    player->setDamageCooldown(0.0f);
    player->takeDamage(40);
    EXPECT_EQ(player->getHealth(), 30);
    
    player->setDamageCooldown(0.0f);
    player->takeDamage(50);
    EXPECT_EQ(player->getHealth(), 0);
    
    // Verify health stays at 0
    player->setDamageCooldown(0.0f);
    player->takeDamage(10);
    EXPECT_EQ(player->getHealth(), 0);
}
