#pragma once
#include <drogon/HttpResponse.h>
#include <json/json.h>
#include <string>

namespace ai::agent::v2::ollama {

Json::Value runModel(const std::string &model);
Json::Value listModels();

}  // namespace ai::agent::v2::ollama
