#include <gtest/gtest.h>
#include <gmock/gmock.h>

#include "Entities/User.hpp"
#include "Entities/Investor.hpp"

#include "MemoryDatabase/MemoryJson.hpp"

using namespace EcosystemServices::Library::MemoryDatabase;

class MemoryJsonTests : public ::testing::Test
{
  protected:
    // Per-test-suite set-up.
    // Called before the first test in this test suite.
    // Can be omitted if not needed.
    static void SetUpTestSuite()
    {
      // Avoid reallocating static objects if called in subclasses of FooTest.
    }

    // Per-test-suite tear-down.
    // Called after the last test in this test suite.
    // Can be omitted if not needed.
    static void TearDownTestSuite()
    {
    }

    // You can define per-test set-up logic as usual.
    void SetUp() override
    {
    }

    // You can define per-test tear-down logic as usual.
    void TearDown() override
    {
    }

  protected:
    MemoryJson m_InMemoryJson;
};

TEST_F(MemoryJsonTests, ObjectToJson)
{
}

auto main(int32_t argc, char** argv) -> int32_t
{
  ::testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}
