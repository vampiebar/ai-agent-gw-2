#define CATCH_CONFIG_MAIN
#include <catch2/catch_test_macros.hpp>
#include "OllamaService.h"

using namespace ai::agent::v2::ollama;

TEST_CASE("OllamaService::listModels returns expected structure", "[listModels]") {
    Json::Value result = listModels();

    REQUIRE(result.isMember("command"));
    REQUIRE(result.isMember("output"));
    REQUIRE(result.isMember("success"));
}

TEST_CASE("OllamaService::runModel handles non-existent model", "[runModel]") {
    Json::Value result = runModel("nonexistent_model_xyz");

    REQUIRE(result.isMember("command"));
    REQUIRE(result.isMember("output"));
    REQUIRE(result.isMember("success"));
}
