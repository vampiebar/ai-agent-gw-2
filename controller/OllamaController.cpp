#include "OllamaController.h"
#include "OllamaService.h"

void OllamaController::runModel(const HttpRequestPtr &req, std::function<void(const HttpResponsePtr &)> &&callback, std::string model) {
    auto result = ai::agent::v2::ollama::runModel(model);
    auto resp = HttpResponse::newHttpJsonResponse(result);
    callback(resp);
}

void OllamaController::listModels(const HttpRequestPtr &req, std::function<void(const HttpResponsePtr &)> &&callback) {
    auto result = ai::agent::v2::ollama::listModels();
    auto resp = HttpResponse::newHttpJsonResponse(result);
    callback(resp);
}

void OllamaController::handleOperation(const HttpRequestPtr &req, std::function<void(const HttpResponsePtr &)> &&callback) {
    auto json = req->getJsonObject();
    Json::Value result;

    if (!json || !(*json).isMember("operation")) {
        result["error"] = "Missing 'operation' field";
        callback(HttpResponse::newHttpJsonResponse(result));
        return;
    }

    std::string op = (*json)["operation"].asString();
    if (op == "run_model" && (*json).isMember("model_to_run")) {
        std::string model = (*json)["model_to_run"].asString();
        result = ai::agent::v2::ollama::runModel(model);
    } else {
        result["error"] = "Unsupported operation or missing model";
    }

    auto resp = HttpResponse::newHttpJsonResponse(result);
    callback(resp);
}
